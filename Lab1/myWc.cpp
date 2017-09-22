/**********************************************
 * Last Name:   Ghosh
 * First Name:  Satyaki
 * Student ID:  10077685
 * Course:      CPSC 457
 * Tutorial:    T01
 * Assignment:  1
 * Question:    Q4
 *
 * File name: myWc.cpp
 *********************************************/

#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main (int argc, char *const argv[])
{
  string filename;
  if (argc != 2) {
    cerr << "Usage: readFile <input file> " << endl;
    return -1;
  }
  else {
    filename = argv[1];
  }
  
  int count = 0;

  ifstream file(filename);
  if(file.is_open()) {
    string line;
    while (getline(file, line))
      ++count;
  }
  else {
    cerr << "Could not open file " << filename << "\n";
    exit(-1);
  }
  file.close();  

  // int fd = open(filename.c_str(), O_RDONLY);
  // if(fd < 0) {
  //   cerr << "Could not open file " << filename << "\n";
  //   exit(-1);
  // }

  // while(1) {
  //   char c;
  //   if(read(fd, &c, 1) < 1) break;
  //   if(c == '\n') count ++;
  // }
  // close(fd);

  cout << count << " " << filename << "\n";

  return 0;
}
