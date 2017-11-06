/**********************************************
 * Last Name:   Ghosh
 * First Name:  Satyaki
 * Student ID:  10077685
 * Course:      CPSC 457
 * Tutorial:    T01
 * Assignment:  3
 * Question:    Q7
 * File Name:   scheduler.cpp 
 * compile with:
 *  $ g++ scheduler.cpp
 *********************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue> 
  
using namespace std;

int minIndex(vector<int> vec) {
    int index = 0;
    for(int i = 1; i < vec.size(); i++) {
        if(vec.at(index) > vec.at(i))
            index = i;
    }

    return index;
}

int findFirstSJF(vector<int> arrival, vector<int> burst) {
    int index = 0;
    int bur = burst.at(0);
    
    for(int i = 1; i < arrival.size() && arrival.at(0) == arrival.at(i); i++) {
        if(bur > burst.at(i)) {
            bur = burst.at(i);
            index = i;
        }
    }

    return index;
}

int printStart(vector<int> arrival) {
    printf("Time");
    for(int i = 0; i < arrival.size(); i++)
        printf(" P%d ", i);
    cout << endl;
    printf("-------------------------------------------------------------------------------------------------\n");

    if(arrival.at(0) == 0) {        
        return 0;
    }
    else {
        int i;
        for(i = 0; i < arrival.at(0); i++) {
            printf("%d\n", i);
        }
        return i;
    }
}

void SJF(vector<int> arrival, vector<int> burst) {
    queue<int> que;
    que.push(findFirstSJF(arrival, burst));

    int arrIndex = 0;

    for(int i = printStart(arrival); que.size() != 0; i++) {
        printf("%d    .  .  .\n", i);
    }
}

int main(int argc, char **argv)
{
    if(argc < 3) {
        printf("Configuration file name and scheduling algorithm required to run!\n");
        exit(-1);
    }

    char* config = argv[1];
    string command = argv[2];
    int quantum = 0; 
    
    vector<int> arrival;   
    vector<int> burst;  

    if(command.compare("SJF") == 0 || command.compare("RR") == 0) {
        if(command.compare("RR") == 0) {
            if(argc != 4) {
                printf("You need to specify the time-quantum for RR scheduling.\n");
                exit(-1);
            }
            else {
                quantum = atoi(argv[3]);
                if(quantum == 0) {
                    printf("Invalid time-quantum.\n");
                    exit(-1);
                }
            }                
        }
        else if(argc == 4)
            printf("Time-quantum specified for SJF algorithm but it is ignored.\n");
    }
    else {
        printf("Invalid scheduling algorithm, only SJF and RR accepted.\n");
        exit(-1);
    }
    
    ifstream file(config);
    if(!file){
        printf("Could not open file.\n");
        exit(-1);
    }

    int a, b;
    while(file >> a && file >> b) {
        arrival.push_back(a);
        burst.push_back(b);
    }

    if(command.compare("SJF") == 0)
        SJF(arrival, burst);
    
    return 0;
}