// Homework 2 - Bankers Algorithm
// Sean Shea

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const bool DEBUG = false;   // change to true for more detailed information

int n = 0;  // Number of processes
int m = 0;  // Number of Resource types

// Allocations table
std::vector<std::vector<int>> allocated;
// Maximum Matrix
std::vector<std::vector<int>> max;
// Resource availability
std::vector<int> available;

std::ifstream inFile;
std::string line = "";


void write_allocated();
void write_max();
void write_available();

int main() {
    
    // open a file of the user's choice
    std::string fileName;
    std::cout << "Enter the resource file name " << std::endl << "> ";
    std::cin >> fileName;

    inFile.open(fileName);
    if(!inFile.is_open()) {
        std::cerr << "Couldn't open '" << fileName << "'" << std::endl;
        return 1;
    }

    getline(inFile,line);

    while(!inFile.eof()) {
        if (line.find("ALLOCATED") != -1) {
            write_allocated();
        }
        if (line.find("MAX") != -1) {
            write_max();
        }
        if (line.find("AVAILABLE") != -1) {
            write_available();
        }
        getline(inFile,line);
    }
    
    inFile.close();
    
    n = allocated.size();
    m = allocated[0].size();


    std::vector<bool> finish(n,false);
    std::vector<int> work = available;

    // make the need vector
    // initalize to be correct size
    std::vector<std::vector<int>> need(n, std::vector<int>(m, 0));

    // need = max - allocated
    if(DEBUG) std::cout << "Need table" << std::endl;
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocated[i][j];
            if(DEBUG) std:: cout << need[i][j] << " ";
        }
        if(DEBUG) std::cout << std::endl;
    }


    // safety algorithm
    bool finished = false;
    bool safe = true;
    
    // the safety sequence
    std::vector<int> sequence(n);
    int seq_i = 0;

    // repeats the check of each process unless all the processes are finished or it isn't safe
    while(finished == false && safe == true) {
        // this is set back to true if the for loop acts once with a process
        safe = false;

        // checks each process and acts on it
        for(int i = 0; i < n; i++) {

            // if process isn't finished
            if(finish[i] == false) {
                if(DEBUG) std::cout << "<DEBUG> P" << i << " is not finished" << std::endl;

                // check if need <= work
                bool needLessWork = true;
                
                if(DEBUG) std::cout << "<DEBUG> need & work vectors: ";

                for(int j = 0; j < m; j++) {
                    // if the need vector is NOT <= work vector, set flag to false
                    if(!(need[i][j] <= work[j])) {
                        needLessWork = false;
                    }

                    // printing vectors
                    if(DEBUG) std::cout << "N" << need[i][j] << " W" << work[j] << " | ";
                }
                if(DEBUG) std::cout << std::endl;
                

                if (needLessWork) {
                    if(DEBUG) std::cout << "<DEBUG> P" << i << " is added to sequence" << std::endl;
                    // if got here, process may pretend to allocate resources now
                    for(int j = 0; j < m; j++) {
                        work[j] += allocated[i][j];
                        finish[i] = true;

                    }
                    // write to sequence vector
                    sequence[seq_i] = i;
                    seq_i++;
                    // set safe back to true
                    safe = true;
                } 
                else {
                    if(DEBUG) std::cout << "<DEBUG> P" << i << " is waiting" << std::endl;
                }
                if(DEBUG) std::cout << std::endl;
            }

        }

        // check to see if all processes are finished
        finished = true;
        for(int k = 0; k < m; k++) {
            if (finish[k] == false) {
                finished = false;
            }
        }
        // if finished = true, while loop ends
    }

    if (safe == false) {
        std::cout << "The system is NOT SAFE" << std::endl;
    } else {
        // print sequence
        std::cout << "The Saftey Sequence: " << std::endl;
        for(int i = 0; i < n-1; i++) {
            std::cout << "P" << sequence[i] << " -> ";
        }
        std::cout << "P" << sequence[n-1] << std::endl;
    }

    return 0;

}

void write_allocated(){
    getline(inFile,line);
    int start = 0;
    int end = 0;
    std::string num;
    std::vector<int> resources;
    bool eol = false;

    while(line != "END") {
        while(eol == false) {
        // for(int i = 0; i < 10 || eol == false; ++i) {
            end = line.find_first_of(',',start);
            // std::cout << start << ", " << end << std::endl;
            if (end != std::string::npos) {
                num = line.substr(start,end);
                start = end + 1;
            } else {
                num = line.substr(start,line.size());
                eol = true;
            }
            resources.push_back(std::stoi(num));
        }
        start = 0;
        end = 0;
        eol = false;

        allocated.push_back(resources);

        resources.clear();

        getline(inFile,line);
    }

    if(DEBUG) {
        std::cout << "Allocated Table: " << std::endl;
        for(int i = 0; i < allocated.size(); i++) {
            for(int j = 0; j < allocated[i].size(); j++) {
                std::cout << allocated[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

void write_max(){
    getline(inFile,line);
    int start = 0;
    int end = 0;
    std::string num;
    std::vector<int> resources;
    bool eol = false;

    while(line != "END") {
        while(eol == false) {
        // for(int i = 0; i < 10 || eol == false; ++i) {
            end = line.find_first_of(',',start);
            // std::cout << start << ", " << end << std::endl;
            if (end != std::string::npos) {
                num = line.substr(start,end);
                start = end + 1;
            } else {
                num = line.substr(start,line.size());
                eol = true;
            }
            resources.push_back(std::stoi(num));
        }
        start = 0;
        end = 0;
        eol = false;

        max.push_back(resources);

        resources.clear();

        getline(inFile,line);
    }

    if(DEBUG) {
        std::cout << "Max Table: " << std::endl;
        for(int i = 0; i < max.size(); i++) {
            for(int j = 0; j < max[i].size(); j++) {
                std::cout << max[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

void write_available(){
    getline(inFile,line);
    int start = 0;
    int end = 0;
    std::string num;
    bool eol = false;

    while(eol == false) {
        end = line.find_first_of(',',start);
        if (end != std::string::npos) {
            num = line.substr(start,end);
            start = end + 1;
        } else {
            num = line.substr(start,line.size());
            eol = true;
        }
        available.push_back(std::stoi(num));
    }

    if(DEBUG) {
        std::cout << "Available Table: " << std::endl;
        for(int i = 0; i < available.size(); i++) {
            std::cout << available[i] << " ";
        }
        std::cout << std::endl;
    }
}