#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

bool array[1002][1002] = {false};

bool merge (string A, string B, string C, ofstream* output);

void readFile(string inputFile, string outputFile){
  ifstream input(inputFile);
  ofstream output(outputFile);

  if (!input.is_open()){
    fprintf(stderr, "Cannot Open input file");
  }

  while (!input.eof()){
    //while (input >> A && input >> B && input >> C){
    //merge
    string A, B, C;
    
    if (!getline(input, A)) break;
    if (!getline(input, B)) break;
    if (!getline(input, C)) break;
    
    A += '\n';
    B += '\n';
    C += "\n\n"; 
    
    merge(A,B,C, &output);
  }
  input.close();
  output.close();
}

bool merge(string A, string B, string C, ofstream* output){
  int lenA = A.length();
  int lenB = B.length();
  int lenC = C.length();

  if (lenA + lenB != lenC){
    *output<<"*** NOT A MERGE ***\n";
    return false;
  }
  for (int i = 0; i < lenA + 1; i++) {
    for (int j = 0; j < lenB + 1; j++) {
      array[i][j] = false;
    }
  }
  array [0][0] = true;

  //merge
  for (int i = 0; i < lenA + 1; i++) {
    for (int j = 0; j < lenB + 1; j++) {
      if (array[i][j] == false){
        continue; //skip if did not pass first letter test
      }
      if (C[i+j] == A[i]) {
        array[i + 1][j] = true;
      } 
      if (C[i+j] == B[j]) { // if C=B, insert B first letter
        array[i][j + 1] = true;  
      }
    }
  }
  if (array[lenA-1][lenB-1] != false) { //not empty
    lenA -= 1;
    lenB -= 1;;

    while (lenA > 0 && lenB > 0){
      if (array[lenA][lenB-1]){
        lenB--;
      }
      else if (array[lenA-1][lenB]){
        lenA--;
        C[lenA + lenB] = toupper(C[lenA + lenB]);
      }
    }
    if(!lenB){
      for (int i = 0; i < lenA; i++){
        C[i] = toupper(C[i]);
      }
    }
    C.pop_back();
    *output << C;
  }
  else{
    *output<<"*** NOT A MERGE ***\n";
    return 0;
  }
  return 0;
}

int main() {
    string inputFile, outputFile;
    cout << "Input file name:";
    cin >> inputFile;
    cout << "Output file name:";
    cin >> outputFile;

    readFile(inputFile, outputFile);
    return 0;
}

