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
#include <math.h>

using namespace std;

static int sum = 0;
static int arr[1000000];
static int splits[1000000];

void* thread_print(void* tid) {
    printf("Thread %ld: \n", tid);
    pthread_exit(0);
}  

int main(int argc, char **argv){
    
    if(argc != 3) {
        fprintf(stderr, "This program needs 2 arguments to run. The name of the file with integers and the number of threads to use\n");
        exit(-1);
    }

    char* file = argv[1];
    int max_threads = atoi(argv[2]);
    cout << "Input file: " << file << endl;
    cout << "# of threads to use: " << max_threads << endl;

    ifstream read(file);
    int num, totalInts = 0;
    while(read >> num) {
        if(totalInts > 999999) 
            break;        
        else{
            arr[totalInts] = num;
            totalInts++;
        }        
    }

    cout << "Total # of integers: " << totalInts << endl;
    int split = (int) ceil(((double)(1.0 * totalInts))/((double)(1.0 * max_threads)));
    cout << "split by " << split << endl;


    for(int i = 0; i < max_threads; i++){
        if(i == max_threads - 1)
            splits[i] = totalInts;
        else
            splits[i] = split * (i + 1);
        cout << "split " << i << " = " << splits[i] << endl;
    }
    

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
