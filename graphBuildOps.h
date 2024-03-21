#include "graphComp.h"
#include "MinHeap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#ifndef GRAPHBUILDOPS_H
#define GRAPHBUILDOPS_H

// BEGIN GRAPH BUILD AND OPERATION
// - single class graphDW (Directed + Weighted graph)
// - graph abstraction achieved via dynamic array of Vertex (graphComp) pointers

class graphDW {
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

// END GRAPH BUILD AND OPERATION

#endif