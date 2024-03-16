#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <string>

// BEGIN GRAPH COMPONENTS
// fundamental structs for a weighted & directed graph
// defines building blocks + minimal navigation required for djikstra's algorithm
// in order: Edge, VertexTrack (navigation), & Vertex

// begin Edge struct
// This struct describes a single path between two vertices

struct Edge {
    // attributes
    std::string source;        // source and destination tags to indicate direction
    std::string destination;
    int weight;                // weight in this application denotes distance

    // default constuctor
    Edge() {
        source = "";           
        destination = "";
        weight = 0;
    }

    // parameterized constuctor
    Edge( std::string src, std::string dst, int wt ) {
        source = src;
        destination = dst;
        weight = wt;
    }

    // assignment operator 
    void operator=( Edge* e2 ) {
        source = e2->source;
        destination = e2->destination;
        weight = e2->weight;
    }
}; // end of Edge struct 


// begin VertexTrack struct
// This struct holds a vertex id and count of its In-Degrees...
// ...the number of edges with destination at object's named vertex

struct VertexTrack {     
    std::string name;    // tag for tracked vertex
    int targettings;     // count of In-Degrees

    // parameterized constuctor
    VertexTrack( std::string n, int t ) {
        name = n;
        targettings = t;
    }
}; // end of VertexTrack struct


// begin Vertex struct
// This struct describes Vertices as building blocks of the actual graph abstraction.
// Out-Degrees and NOT In-Degrees are attributed as this is all that's needed from our pal dijkstra.
// A dynamic array of Edge struct pointers is also necessary for processing along with
// a boolean indicator set to false after its first input data point appearance,
// an int measure of distance from the source of desired shortest path and a 
// pointer ( only used in attempted navigation ) to the vertex last processed 

struct Vertex {
    // attributes
    std::string id;        // tag for vertex id 
    int outDegree;         // number of destinations from vertex
    Edge** edges;          // dynamic array of pointers to outbound edges

    bool seen;             // set to false after graph construction
    int distance;          // distance from desired path source
    Vertex* lastJump;      // In-Degree vertex last used in processing

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

#endif
