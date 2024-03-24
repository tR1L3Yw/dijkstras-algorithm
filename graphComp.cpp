#include "graphComp.cpp"
#include "MinHeap.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <climits>


class graphDW {
private:
    // attributes
    int numVertices;        // vertex count
    int buildIndex;         // vertex track relative to graph
    Vertex** graphVertices; // dynamic array representing graph via Vertex pointers
    
public:
    // parameterized constructor
    graphDW( int nV );

    // adds vertex element to array representation
    void addVertex( Vertex* inVertex );
    
    // returns vertex object from index in array rep
    Vertex* getVertex( int index );
    
    // returns array index of target vertex object 
    int getVertexIndex( std::string name );
    
    // navigates graph for shortest path from start and end verticies passesd as arguments
    void dijkstrasAlgorithm ( std::string startVertex, std::string endVertex );
}; // END graphDW

// END GRAPH BUILD AND OPERATION
