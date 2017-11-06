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
  
 using namespace std;

 int main(int argc, char **argv)
 {
    if(argc < 3) {
        printf("Configuration file name and scheduling algorithm required to run!\n");
        exit(-1);
    }

    char* config = argv[1];
    string command = argv[2];
    int quantum = 0; 
    
    vector <int> arrival;   
    vector <int> burst;  

    if(command.compare("SFJ") == 0 || command.compare("RR") == 0) {
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
            printf("Time-quantum specified for SFJ algorithm but it is ignored.\n");
    }
    else {
        printf("Invalid scheduling algorithm, only SFJ and RR accepted.\n");
        exit(-1);
    }

    cout << config << endl;
    cout << command << endl;
    cout << quantum << endl;
    
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

    for(int i = 0; i < arrival.size(); i++) {
        cout << arrival.at(i) << " " << burst.at(i) << endl;
    }

    cout << "Size: " << arrival.size() << " " << burst.size() << endl;

    return 0;

 }