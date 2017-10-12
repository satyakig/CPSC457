#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FNAME_SIZE 512
#define MAX_FILES 1024

struct file_info {
  char name [MAX_FNAME_SIZE];
  long long size;
};

int main(int argc, char **argv) {
  if(argc != 3) {
    fprintf(stderr, "This program needs 2 arguments to run. The suffix of the files and the number of files to display.\n");
    exit(-1);
  }

  char* suffix = argv[1];
  int fileNum = atoi(argv[2]);
  char cmd[50] = "find . -type f -name '*";
  strcat(cmd, suffix);
  strcat(cmd, "'");
  FILE* fp = popen(cmd, "r");
  if(fp == NULL) {
    perror("popen failed:");
    exit(-1);
  }

  char buff[MAX_FNAME_SIZE];
  int nFiles = 0;
  char* files[MAX_FILES];
  struct file_info arr[MAX_FILES];
  while(fgets(buff, MAX_FNAME_SIZE, fp)) {
    int len = strlen(buff) - 1;
    files[nFiles] = strndup(buff,len);
    arr[nFiles] = files[nFiles];
    nFiles ++;
  }
  fclose(fp);
  printf("Found %d files:\n", nFiles);

  long long totalSize = 0;
  struct stat st;
  for(int i = 0 ; i < nFiles ; i ++ ) {
    if(0 != stat(files[i], &st)) {
      perror("stat failed:");
      exit(-1);
    }
    arr[i].size = st.st_size;
    // totalSize += st.st_size;
    // printf("\t%s: %ld\n", files[i], st.st_size);
  }
  // printf("Total size: %lld bytes.\n", totalSize);

  // qsort();

  for(int i = 0; i < fileNum; i++) {
    printf("\t%s: %lld\n", arr[i].name, arr[i].size);
    totalSize += arr[i].size;
  }
  printf("Total size: %lld bytes.\n", totalSize);

  for(int i = 0; i < nFiles ; i ++ ) {
    free(files[i]);
  }
  return 0;
}

// int compare();
