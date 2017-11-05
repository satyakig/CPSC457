// counts number of primes from standard input
// compile with:
// $ gcc findPrimes.c -O3 -o count -lm

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <pthread.h>


int64_t nums[10000];
int size = 0; 
int64_t primeCount = 0;
pthread_mutex_t lock;

// primality test, if n is prime, return 1, else return 0
void* isPrime(void* n)
{
    if(n <= 1) 
        return 0; // small numbers are not primes

    if(n <= 3)
        return 1; // 2 and 3 are prime

    if(n % 2 == 0 || n % 3 == 0)
        return 0; // multiples of 2 and 3 are not primes

    int64_t i = 5;
    int64_t max = sqrt(n);

    while(i <= max) {
        if (n % i == 0 || n % (i+2) == 0)
            return 0;
        i += 6;
    }
    
    return 1;

    pthread_exit(0);
}

int main(int argc, char ** argv)
{
    // parse command line arguments
    int nThreads = 1;
    if(argc != 1 && argc != 2) {
        printf("Usage: countPrimes [nThreads]\n");
        exit(-1);
    }
    if(argc == 2)
        nThreads = atoi(argv[1]);

    // handle invalid arguments
    if(nThreads < 1 || nThreads > 256) {
        printf("Bad arguments. 1 <= nThreads <= 256!\n");
    }
    if(nThreads != 1) {
        printf("I am not multithreaded yet :-(\n");
        exit(-1);
    }

    // count the primes
    printf("Counting primes using %d thread%s.\n", nThreads, nThreads == 1 ? "" : "s");    

    for(; true; size++) {
        int64_t num;
        if(1 != scanf("%ld", &num)) 
            break;
        nums[size] = num;
    }

    // report results
    printf("Found %ld primes.\n", count);
    printf("Size %d.\n", size);

    return 0;
}
