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

vector<int> arrival;   
vector<int> burst;
vector<bool> completed;


int findFirstSJF() {
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

void print(vector<int> chart) {
    printf("Time ");
    for(int i = 0; i < arrival.size(); i++)
        printf(" P%d ", i);
    cout << endl;
    printf("------------------------------------------------------------------------------\n");

    for(int i = 0; i < chart.size(); i++) {
        printf("%d    ", i);
        if(chart.at(i) == -1){           
            for(int i = 0; i < arrival.size(); i++)
                printf("   ", i);
            cout << endl;
        }
        else {
            for(int i = 0; i < arrival.size(); i++) {
                if(chart.at(i) == i)
                    printf(" + ", i);
                else
                    printf(" . ", i);
            }                
            cout << endl;
        }
    }
}

bool isEmpty() {
    bool empty = true;

    for(int i = 0; i < completed.size(); i++) {
        if(completed.at(i) == false) {
            empty = false;
            break;
        }
    }

    return empty;
}

void SJF() {
    vector<int> chart;

    for(int i = 0; i < findFirstSJF(); i++)
        chart.push_back(-1);

    int pID = findFirstSJF();
    int time = arrival.at(pID);

    while(true) {
        while(burst.at(pID) != 0) {
            chart.push_back(pID);
            burst.at(pID) = burst.at(pID) - 1;
            time++;
        }
        completed.at(pID) = true;
        
        int ind = -1;
        if(!isEmpty()) {
            for(int i = 0; i < arrival.size(); i++) {
                if(completed.at(i) == false && arrival.at(i) <= time) {
                    if(ind == -1)
                        ind = i;
                    else if(burst.at(ind) > burst.at(i))
                        ind = i;
                }
            }
            pID = ind;
        }
        else
            break;
    }

    for(int i = 0; i < chart.size(); i++)
        printf(" %d \n", chart.at(i));

    //print(chart);
    return;
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
        completed.push_back(false);
    }

    if(command.compare("SJF") == 0)
        SJF();
    
    
    return 0;
}