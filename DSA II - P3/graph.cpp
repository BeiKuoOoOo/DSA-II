#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <climits>
#include <fstream>
#include <sstream>
#include <vector>
#include "graph.h"

using namespace std;

//initialize and construct
graph::graph(){
    vertices = new hashTable(10000000);
    size = 0;
}

//insert vertex name, position, vertex
void graph::insert(const string &name, const string &destination, int dis) {
    vertex *start;
    vertex *end;
    start = insertVertex(name);
    end = insertVertex(destination);
    edge newedge;
    newedge.w = dis;
    newedge.connected = end;
    start->adjacency.push_back(newedge);
}

//insert the vertex (used in insert)
graph::vertex * graph::insertVertex(const string &name) {
    vertex *tempVertex;
    if (vertices->contains(name)){
        tempVertex = (vertex *)vertices->getPointer(name);
    } else{
        tempVertex = new vertex;
        tempVertex -> id = name;
        vertexList.push_back(tempVertex);
        vertices->insert(name, tempVertex);
        size++;
    }
    return tempVertex;
}

//dijkstra algo
void graph::dijkstra(const string &id) {
    heap newHeap(size);
    vertex *start = (vertex *)vertices->getPointer(id);
    start -> max = 0; //vertex start at max 0
    start -> path.push_back(id); //adds a new element at the end of the vector, after its current last element
    for (list<vertex*>::const_iterator iter = vertexList.begin(), end = vertexList.end(); iter !=vertexList.end(); iter++){
        newHeap.insert((*iter)->id, (*iter)->max, *iter);
    }
    for (int i = 0; i < size; i++){
        vertex *tempVertex;
        newHeap.deleteMin(nullptr, nullptr, &tempVertex);
        tempVertex -> known = true; //mark known
        for (list<edge>::const_iterator iter = tempVertex->adjacency.begin(), end = tempVertex->adjacency.end(); iter !=tempVertex->adjacency.end() && tempVertex->max !=INT_MAX; iter++){
            if ((!iter->connected->known) && (iter->w+tempVertex->max) < iter->connected->max){
                iter->connected->path.clear(); //clear path
                iter->connected->path.insert(iter->connected->path.begin(), tempVertex->path.begin(), tempVertex->path.end());
                iter->connected->path.push_back(iter->connected->id);
                iter->connected->max = iter->w+tempVertex->max;
                newHeap.setKey(iter->connected->id, iter->connected->max);
            }
        }
    }
}

//check if there's vertex
bool graph::contain(const string &id) {
    return vertices -> contains(id);
}

//function for output file
void graph::outputpath(const string &outputFile) {
    ofstream output;
    output.open(outputFile);
    for (list<vertex *>::const_iterator iter = vertexList.begin(); iter != vertexList.end(); iter++){
        if ((*iter)->max == INT_MAX){
            output << (*iter)->id << ": NO PATH" <<endl;
        } else{
            output << (*iter)->id << ": " << (*iter)->max << " [";
            for (list<string>::const_iterator itera = (*iter)->path.begin(); itera != --(*iter)->path.end(); itera++){
                output << *itera << ", " ;
            }
            output << (*iter)->path.back() << "]" << endl;
        }
    }
}