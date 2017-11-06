/**********************************************
 * Last Name:   Ghosh
 * First Name:  Satyaki
 * Student ID:  10077685
 * Course:      CPSC 457
 * Tutorial:    T01
 * Assignment:  3
 * Question:    Q5
 * File Name:   findPrimes.c 
 * compile with:
 *  $ g++ findPrimes.c -O2 -o count -lm -pthread 
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <pthread.h>


static int64_t nums[10000];
static int arrSize = 0;

static int splits[10000];
static int split = 0;

static int64_t primeCount = 0;
pthread_mutex_t lock;

// primality test, if n is prime, return 1, else return 0
void* isPrime(void* tid)
{
    int id = (long) tid;
    int i = (splits[id] - split);
    if(splits[id] == arrSize)
        i = splits[id - 1];

    printf("Thread %d: start[%d] = %d  end[%d] = %d\n", id, i, nums[i], splits[id], nums[splits[id]-1]);

    for( ; i < splits[id]; i++) {
        int64_t num = nums[i];
        bool prime = true;

        if(num <= 1) 
            prime = false; // small numbers are not primes
        else if(num <= 3)
            prime = true; // 2 and 3 are prime
        else if(num % 2 == 0 || num % 3 == 0)
            prime = false; // multiples of 2 and 3 are not primes
        else {
            int64_t i = 5;
            int64_t max = sqrt(num);
    
            while(i <= max) {
                if (num % i == 0 || num % (i + 2) == 0) {
                    prime = false;
                    break;
                }
                i += 6;
            }
        }
        
        if(prime) {
            pthread_mutex_lock(&lock);
            primeCount++;
            pthread_mutex_unlock(&lock);
        }
        
        printf("Thread %d: %" PRId64 "is %s\n", id, num, prime? "prime" : "not prime");
    }

    pthread_exit(0);
}

int main(int argc, char ** argv)
{
    // parse command line arguments
    int nThreads = 1;

    if(argc != 2) {
        printf("Please specify the number of threads to run this program.\n");
        exit(-1);
    }

    // handle invalid arguments
    if(nThreads < 1 || nThreads > 256) {
        printf("Bad arguments. 1 <= nThreads <= 256!\n");
        exit(-1);
    }
    
    nThreads = atoi(argv[1]);

    printf("Counting primes using %d thread%s.\n", nThreads, nThreads == 1 ? "" : "s");    

    for(; true; arrSize++) {
        int64_t num;
        if(1 != scanf("%ld", &num)) 
            break;
        nums[arrSize] = num;
    }

    if(arrSize == 0) {
        printf("No inputs were read.\n");
        exit(-1);
    }

    if(nThreads > arrSize)
        nThreads = arrSize;

    split = (int) ceil(((double)(1.0 * arrSize))/((double)(1.0 * nThreads)));
    for(int i = 0; i < nThreads; i++) {
        if(i == nThreads - 1)
            splits[i] = arrSize;
        else
            splits[i] = split * (i + 1);
    }

    if(pthread_mutex_init(&lock, NULL) != 0) {
        printf("mutex init failed.\n");
        exit(-1);
    }

    pthread_t threads[nThreads];

    for(int i = 0; i < nThreads; i++ ) {
        int rc = pthread_create(&threads[i], NULL, isPrime, (void *) (intptr_t) i);       
        if(rc) {
            printf("Oops, pthread_create returned error code %d\n", rc);
            exit(-1);
        }
    }

    for(int i = 0; i < nThreads; i++)
        pthread_join(threads[i], NULL);   

    // report results
    printf("Found %ld primes.\n", primeCount);
    pthread_mutex_destroy(&lock);    

    printf("size %d\n", arrSize);
    printf("split %d\n", split);    

    return 0;
}

