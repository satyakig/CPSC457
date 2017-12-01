/*
 * pagesim.cpp
 * 
 * Student Name: Satyaki Ghosh
 * Student Number: 10077685
 * 
 * Assignment 5
 * Question 6
 * T-01
 * CPSC 457 Fall 2017
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct FRAME {
    int index;
    int page;
};

struct CLOCK {
    int bit;
    int page;
};

vector <int> reference; // holds the reference string
int total;  // # of available frames
int faults; // # of faults for a specific algorithm
int* frame; // the frame used for LRU and OPT computation
vector <CLOCK> clockFrame;  // the frame used for Clock computation
int clockPointer;   // the pointer to the Clock

// creates an array for the frame, using the # of available frames
void makeFrames(bool makeClock);
// prints the frame after each algorithm finishes
void print(string type, bool clk);

// checks if a page already exists in the frame for OPT and LRU
bool exists(int page);

// returns the page to be replaced in the frame for LRU
int LRURemoveIndex(int refInd);
// does the LRU algorithm
void LRU();

// returns the page to be replaced in the frame for OPT
int OPTRemoveIndex(int refInd);
// does the Optimal algorithm
void OPT();

// checks if a page already exists in the frame for Clock
bool clkExists(int page);
// increments the clock pointer
int getNextClock();
// does the Clock algorithm
void CLK();

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("Error! Available frames and test file name required to run.\n");
        printf("Eg:     g++ pagesim.cpp -o pagesim\n        ./pagesim 4 test1.txt\n");
        exit(-1);
    }

    total = atoi(argv[1]);
    if(total < 1 || total > 20) {
        printf("Error! Available frames has to be greater than 0 and less than or equal to 20.\n");
        exit(-1);
    }

    char* fileName = argv[2];
    ifstream file(fileName);
    if(!file) {
        printf("Error! Could not open file: %s\n", argv[2]);
        exit(-1);
    }

    int x;
    while(file >> x)
        reference.push_back(x);     // fills the reference string into a vector
    
    cout << endl << "Reference String:" << endl;
    for(int i = 0; i < reference.size(); i++)
        cout << reference.at(i) << " ";
    cout << endl << endl;

    
    makeFrames(false);
    // does the OPT computation and prints it
    OPT();

    makeFrames(false);
    // does the LRU computation and prints it
    LRU();

    makeFrames(true);
    // does the Clock computation and prints it
    CLK();

    delete [] frame;

    return 0;
}

void makeFrames(bool makeClock) {
    faults = 0;
    if(frame)
        delete [] frame;

    frame = new int[total];
    for(int i = 0; i < total; i++)
        frame[i] = -100;

    if(makeClock) {
        clockPointer = 0;
        for(int i = 0; i < total; i++) {
            CLOCK temp;
            temp.bit = 1;
            temp.page = -100;
            clockFrame.push_back(temp);
        }
    }    
}

bool exists(int page) {
    for(int i = 0; i < total; i++) {
        if(frame[i] == page)
            return true;
    }    
    faults++;    
    return false;
}

void print(string type, bool clk) {
    if(!clk) {
        cout << type << ":" << endl;
        cout << "   - frames:  ";
        for(int i = 0; i < total; i++)
            cout << frame[i] << "  ";
        cout << endl;
        cout << "   - page faults:  " << faults << endl;
    }
    else {
        cout << type << ":" << endl;
        cout << "   - frames:  ";
        for(int i = 0; i < total; i++)
            cout << clockFrame.at(i).page << "  ";
        cout << endl;
        cout << "   - page faults:  " << faults << endl;
    }    
}

int LRURemoveIndex(int refInd) {
    vector <FRAME> arr;
    for(int i = 0; i < total; i++) {
        FRAME temp;
        temp.index = i;
        temp.page = frame[i];
        arr.push_back(temp);
    }

    for(int i = refInd - 1; i < reference.size(); i--) {
        if(arr.size() == 1)
            break;
        else {
            int page = reference.at(i);
            for(int j = 0; j < arr.size(); j++) {
                if(arr.at(j).page == page) {
                    arr.erase(arr.begin() + j);
                    break;
                }
            }
        }
    }    
    return arr.at(0).index;    
}

void LRU() {
    for(int refIndex = 0, frameIndex = 0; refIndex < reference.size(); refIndex++) {
        int page =  reference.at(refIndex);
        if(frameIndex < total) {
            if(!exists(page)) {
                frame[frameIndex] = page;
                frameIndex++;
            }            
        }
        else {
            if(!exists(page))
                frame[LRURemoveIndex(refIndex)] = page;
        }
    }
    print("LRU", false);
}

int OPTRemoveIndex(int refInd) {
    vector <FRAME> arr;
    for(int i = 0; i < total; i++) {
        FRAME temp;
        temp.index = i;
        temp.page = frame[i];
        arr.push_back(temp);
    }

    for(int i = refInd; i < reference.size(); i++) {
        if(arr.size() == 1)
            break;
        else {
            int page = reference.at(i);
            for(int j = 0; j < arr.size(); j++) {
                if(arr.at(j).page == page) {
                    arr.erase(arr.begin() + j);
                    break;
                }
            }
        }
    }    
    return arr.at(0).index;   
}

void OPT() {
    for(int refIndex = 0, frameIndex = 0; refIndex < reference.size(); refIndex++) {
        int page =  reference.at(refIndex);
        if(frameIndex < total) {
            if(!exists(page)) {
                frame[frameIndex] = page;
                frameIndex++;
            }            
        }
        else {
            if(!exists(page))
                frame[OPTRemoveIndex(refIndex)] = page;
        }
    }
    print("Optimal", false);
}

bool clkExists(int page) {
    for(int i = 0; i < clockFrame.size(); i++) {
        if(clockFrame.at(i).page == page)
            return true;     
    }
    faults++;
    return false;
}

int getNextClock() {
    clockPointer++;
    if(clockPointer == total)
        clockPointer = 0;

    return clockPointer;
}

void CLK() {
    int index = 0;
    int pointer;

    for(int refIndex = 0; refIndex < reference.size(); refIndex++) {
        int page =  reference.at(refIndex);

        if(index < total) {
            if(!clkExists(page)) {
                CLOCK temp;
                temp.bit = 1;
                temp.page = page;
                clockFrame.at(index) = temp;
                index++;
                pointer = getNextClock();
            }            
        }
        else {
            if(!clkExists(page)) {
                while(clockFrame.at(pointer).bit == 1) {
                    clockFrame.at(pointer).bit = 0;
                    pointer = getNextClock();
                }
                clockFrame.at(pointer).bit = 1;
                clockFrame.at(pointer).page = page;
            }
        }
    }
    print("Clock", true);
}