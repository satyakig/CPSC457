/**********************************************
 * Last Name:   Ghosh
 * First Name:  Satyaki
 * Student ID:  10077685
 * Course:      CPSC 457
 * Tutorial:    T01
 * Assignment:  2
 * Question:    Q6
 * File Name:   sum.cpp
 *********************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <pthread.h>

using namespace std;

static int sum = 0;
static int arr[1000000];

void * thread_print(void * tid) {
    printf("thread %ld running\n", tid);
    pthread_exit(0);
}
  

int main(int argc, char **argv){
    pthread_t threads[NUM_THREADS];
    int rc;
    int i;
    
    for( i = 0; i < NUM_THREADS; i++ ) {
       cout << "main() : creating thread, " << i << endl;
       rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
       
       if (rc) {
          cout << "Error:unable to create thread," << rc << endl;
          exit(-1);
       }
    }
    pthread_exit(NULL);


}
