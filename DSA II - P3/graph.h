#ifndef graph_h
#define graph_h

#include <climits>
#include <string>
#include <list>
#include <fstream>
#include "heap.h"
using namespace std;

class graph{
private:
    int size;

    class edge;
    class vertex;

    class edge{
    public:
        int w; //weight/cost
        vertex *connected;
    };
    class vertex{
    public:
        string id;
        bool known = false; //set to false for initialization
        int max = INT_MAX;
        list<edge> adjacency;
        list<string> path;
    };
    vertex* insertVertex(const string &name);
    list<vertex *> vertexList;
    hashTable *vertices;
public:
    graph();
    bool contain(const string &id);
    void insert(const string &name, const string &dest, int dis);
    void dijkstra(const string &id);
    void outputpath(const string &outName);

};

#endif