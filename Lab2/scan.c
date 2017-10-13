/**********************************************
 * Last Name:   Ghosh
 * First Name:  Satyaki
 * Student ID:  10077685
 * Course:      CPSC 457
 * Tutorial:    T01
 * Assignment:  2
 * Question:    Q6
 * File Name: scan.c
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FNAME_SIZE 512
#define MAX_FILES 1024

struct file_info {
  char* name;
  long long size;
};

int compare(const void *p, const void *q) {
  long long l = ((struct file_info *)p)->size;
  long long r = ((struct file_info *)q)->size;
  return (r - l);
}

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
  // char* files[MAX_FILES];
  struct file_info files[MAX_FILES];

  while(fgets(buff, MAX_FNAME_SIZE, fp)) {
    int len = strlen(buff) - 1;
    // files[nFiles] = strndup(buff,len);
    files[nFiles].name = strndup(buff,len);
    nFiles++;
  }
  fclose(fp);
  printf("Found %d files:\n", nFiles);

  long long totalSize = 0;
  struct stat st;
  for(int i = 0 ; i < nFiles ; i ++ ) {
    if(0 != stat(files[i].size, &st)) {
      perror("stat failed:");
      exit(-1);
    }
    // files[i].size = st.st_size;
  }

  qsort((void*) files, nFiles, sizeof(files[0]), compare);

  int max = 0;
  if(nFiles < fileNum)
    max = nFiles;
  else
    max = fileNum

  for(int i = 0; i < max; i++) {
    printf("\t%s: %lld bytes.\n", files[i].name, files[i].size);
    totalSize += files[i].size;
  }
  printf("Total Size: %lld bytes.\n", totalSize);

  for(int i = 0; i < nFiles ; i++ ) {
    free(files[i].name);
  }
  
  return 0;
}
