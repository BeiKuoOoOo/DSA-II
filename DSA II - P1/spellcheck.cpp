//DSA II Program 1, Sophia (Ruxi) Xu

#include "hash.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cctype>
#include <cstdlib>

using namespace std;
//initial hash table with size of 50000
hashTable *Hash  = new hashTable(50000);

//function that loads dictionary
void loadDict(const string &dictionary, hashTable *Hash){
    ifstream input;
    input.open(dictionary);

    if(!input.is_open()){           //if cannot open, exit with error
        cout << "Error: cannot open dictionary" << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    //get line and lowercase dictionary
    //insert them to the hash table
    while(getline(input, line)){
        for (int i = 0; i < line.size(); i++){
            line[i] = tolower(line[i]);
        }
        Hash->insert(line);
    }
    //close dictionary
    input.close();
}

//function to check the spelling of input
void spellCheck(const string& inFile, hashTable* Hash, const string& outFile) {
    //open input file
    ifstream inputFile;
    inputFile.open(inFile);
    if (!inputFile.is_open()) { //if cannot open, exit with error
        cout << "Error" << endl;
        exit(EXIT_FAILURE);
    }

    //open output file
    ofstream outputFile;
    outputFile.open(outFile);
    if (!outputFile.is_open()) { //if cannot open, exit with error
        cout << "Error" << endl;
        exit(EXIT_FAILURE);
    }

    string word, line;
    word.clear();
    line.clear();
    bool nonum = false;
    char temp;
    unsigned long p = 0;
    //get line for the input and lowercase them
    while (getline(inputFile, line)) {
        ++p;
        for (int i = 0; i <= line.size(); ++i) {
            temp = tolower(line[i]);
            if (isdigit(temp) && !nonum) {
                nonum = true;
            }
            if (isalnum(temp) || temp == '-' || temp == '\'') {
                word += temp;
            }

            //unknown or long word
            else if (!word.empty() && !nonum) {
                if (word.size() > 20) {
                    outputFile << "Long word at line " << p << ", starts: " << word.substr(0, 20) << endl;
                    word.clear();
                    nonum = false;
                }
                else if (!Hash->contains(word)) {
                    outputFile << "Unknown word at line " << p << ": " << word << endl;
                    word.clear();
                    nonum = false;
                }
                else{
                    word.clear();
                    nonum = false;
                }
            } else {
                word.clear();
                nonum = false;
            }
        }
    }
    //clear everyhing and close file
    line.clear();
    inputFile.close();
    outputFile.close();
}

int main(){
    string dicFile, infile, outfile;
    cout << "Enter name of dictionary: ";
    cin >>dicFile;

    //use clock to calculate time difference
    clock_t t1 = clock();
    loadDict(dicFile, Hash);
    clock_t t2 = clock();
    double time = (double (t2 - t1))/CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << time << endl;

    //open input and output file
    cout << "Enter name of input file: ";
    cin >> infile;
    cout << "Enter name of output file: ";
    cin >> outfile;

    //check time for spell check
    t1 = clock();
    spellCheck(infile,Hash, outfile);
    t2 = clock();
    time = (double (t2 - t1))/CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to check document: " << time << endl;
    return 0;
}