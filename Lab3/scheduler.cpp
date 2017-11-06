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
vector<int> burst_orig;
vector<bool> completed;
vector<double> times;


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

    for(int chartI = 0; chartI < chart.size(); chartI++) {
        printf("%d    ", chartI);
        if(chart.at(chartI) == -1){           
            for(int j = 0; j < arrival.size(); j++)
                printf("   ");
            cout << endl;
        }
        else {
            for(int j = 0; j < arrival.size(); j++) {
                if(chart.at(chartI) == j)
                    printf("  . ");
                else
                    printf("  + ");
            }                
            cout << endl;
        }
    }
    printf("------------------------------------------------------------------------------\n");
    double total = 0;
    for(int i = 0; i < arrival.size(); i++) {
        printf("P%d waited %f sec.\n", i, times.at(i));
        total += times.at(i);
    }
    printf("Average waiting time = %f\n", total/arrival.size());
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

    for(int i = 0; i < arrival.at(findFirstSJF()); i++)
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
        times.at(pID) = time - burst_orig.at(pID) - arrival.at(pID); 
        
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

    print(chart);
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
        burst_orig.push_back(b);
        completed.push_back(false);
        times.push_back(0);
    }

    if(command.compare("SJF") == 0)
        SJF();
    else
        printf("Did not have time to do RR algorithm.\n");    
    
    return 0;
}