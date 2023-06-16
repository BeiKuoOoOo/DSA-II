#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <list>
#include <iterator>
#include <chrono>
#include "graph.h"


using namespace std;

int main(){
    ifstream input;
    ofstream output;
    string inputFile, outputFile, origin, destination, id;
    clock_t start;
    clock_t end;
    graph ndijkstra;
    int dis;

    //open the input file
    while (!input.is_open()){
        cout << "Enter a valid graph input file: ";
        flush(cout);
        cin >> inputFile;
        input.open(inputFile,ifstream::in);
        if(!input.is_open()){
            fprintf(stderr, "\nCannot open input file\n");
        }
    }
    //insert the input file
    while (input >> origin >> destination >> dis){
        ndijkstra.insert(origin,destination,dis);
    }
    input.close();

    //input starting vertex as id
    while (!ndijkstra.contain(id)){
        cout << "Enter name of starting vertex: ";
        flush(cout);
        cin >> id;
        if(!ndijkstra.contain(id)){
            fprintf(stderr, "\nInvalid input vertex \n") ;
        }
    }

    //time the dijkstra sort
    start = clock();
    ndijkstra.dijkstra(id);
    end = clock();
    cout << "Total time (in seconds) to apply Dijkstra's algorithm:" << (float(end-start))/CLOCKS_PER_SEC << endl;

    //output
    cout << "Enter name of output file: ";
    cin >> outputFile;
    ndijkstra.outputpath(outputFile);
    output.close();
    return 0;
}