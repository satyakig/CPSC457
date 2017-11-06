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
 
 
 using namespace std;

 int main(int argc, char **argv)
 {
    if(argc < 3){
        printf("Program requires configuration file name and scheduling algorithm to run!");
        exit(-1);
    }

    string config = argv[1];
    string command = argv[2];
    int quantum = 0;   

    if(command.compare("SFJ") == 0 || command.compare("RR") == 0) {
        if(command.compare("RR") == 0){
            if(argc != 4){
                printf("You need to speficy the time quantum for RR scheduling.");
                exit(-1);
            }
            else
                quantum = atoi(argv[3]);
        }
    }
    else{
        printf("Invalid scheduling command.");
        exit(-1);
    }

    cout << config << endl;
    cout << command << endl;
    cout << quantum << endl;

 }