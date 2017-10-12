#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FNAME_SIZE 512
#define MAX_FILES 1024

int main(int argc, char **argv) {
  if(argc != 3) {
    fprintf(stderr, "This program needs 2 arguments to run. The suffix of the files and the number of files to display.\n");
    exit(-1);
  }

  char* suffix = argv[1];
  int file_no = atoi(argv[2]); 
  printf("%s + %d\n", suffix, file_no);
  
  char* cmd = "find . -type f -name ";
  strcat(cmd, suffix);
  printf("%s\n", cmd);
  FILE* fp = popen(cmd, "r");
  if(fp == NULL) {
    perror("popen failed:");
    exit(-1);
  }

  // read in all filenames
  char buff[MAX_FNAME_SIZE];
  int nFiles = 0;
  char* files[MAX_FILES];
  while(fgets(buff, MAX_FNAME_SIZE, fp)) {
    int len = strlen(buff) - 1;
    files[nFiles] = strndup(buff,len);
    nFiles ++;
  }
  fclose(fp);
  printf("Found %d files:\n", nFiles);

  // get file sizes for each file and sum them up
  long long totalSize = 0;
  struct stat st;
  for(int i = 0 ; i < nFiles ; i ++ ) {
    if(0 != stat(files[i], &st)) {
      perror("stat failed:");
      exit(-1);
    }
    totalSize += st.st_size;
    printf("\t%s: %ld\n", files[i], st.st_size);
  }
  printf("Total size: %lld bytes.\n", totalSize);

  // clean up
  for(int i = 0; i < nFiles ; i ++ ) {
    free(files[i]);
  }
  // return success
  return 0;
}