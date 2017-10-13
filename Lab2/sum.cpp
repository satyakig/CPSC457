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
#include <fstream>

using namespace std;

static int sum = 0;
static int arr[1000000];

void* thread_print(void * tid) {
    printf("thread %ld running\n", tid);
    pthread_exit(0);
}  

int main(int argc, char **argv){
    
    if(argc != 3) {
        fprintf(stderr, "This program needs 2 arguments to run. The name of the file with integers and the number of threads to use\n");
        exit(-1);
    }

    char* file = argv[1];
    int max_threads = atoi(argv[2]);

    ifstream read(file);
    int num, total = 0;
    while(read >> num) {
        arr[total] = num;
        total++;
    }

    cout << "Total: " << total << endl;
    for(int i = 0; i <= total; i++)
        cout << arr[i] << endl;

    // pthread_t threads[max_threads];
    // int rc;
    // int i;
    
    // for( i = 0; i < max_threads; i++ ) {
    //    cout << "main() : creating thread, " << i << endl;
    //    rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
       
    //    if (rc) {
    //       cout << "Error:unable to create thread," << rc << endl;
    //       exit(-1);
    //    }
    // }
    // pthread_exit(NULL);

    return 0;
}
