#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#ifndef GRAPH_H
#define GRAPH_H

#include<string>

struct Edge {
    //std::
    std::string source;
    std::string destination;
    int weight;
    
    Edge()
    {
        source = "";
        destination = "";
        weight = 0;
    }

    Edge( std::string src, std::string dst, int wt )
    {
        source = src;
        destination = dst;
        weight = wt;
    }

    void operator=( Edge* e2)
    {
        source = e2->source;
        destination = e2->destination;
        weight = e2->weight;
    }
};

#endif

struct VertexTrack{
    std::string name;
    int targettings;

    VertexTrack( std::string n, int t )
    {
        name = n;
        targettings = t;
    }
};

struct Vertex{
    std::string id;
    int outDegree;
    Edge** edges;

    bool seen;
    int distance;
    Vertex* lastJump;

    Vertex() {}    

    Vertex(int outDeg, std::string name) {
        id = name;
        outDegree = outDeg;
        edges = new Edge*[outDeg];

        seen = false;
        distance = 99999;
        lastJump = nullptr;
    }
};

struct Node {
    Vertex* vertex;
    int distance;
    
    Node() {}
    
    Node(Vertex* v, int d) {
        vertex = v;
        distance = d;
    }
};

class MinHeap {
private:
    
    Node* heap;
    int capacity;
    int size;
    
    void swapNodes(int i, int j);
    void siftUp(int i);
    void siftDown(int i);
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
public:
    
    MinHeap(int cap);
    ~MinHeap();

    void insert(Node node);
    Node extractMin();
    bool isEmpty();
    
};
    
class graphDW{
private:
    
    int numVertices;
    int buildIndex;
    Vertex** graphVertices;
    
public:
    
    graphDW( int nV );
    
    void addVertex( Vertex* inVertex );
    
    Vertex* getVertex( int index );
    
    int getVertexIndex( std::string name );
    
    void dijkstrasAlgorithm ( std::string startVertex, std::string endVertex );
    
};

