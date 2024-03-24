#include "graphBuildOps.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <chrono>

using namespace std;

int main( int argc, const char* argv[] )
{
    (void)argc;             // ignores 0-element argument
    string inputFile;       
    inputFile = argv[1];    // input file named in run cmd

    ifstream portal1( inputFile );  // begin file read 

    // FIRST FILE LOOP . . .
    string startVertex;
    string endVertex;
    string source, destination;
    int weight;

    portal1 >> startVertex;
    portal1 >> endVertex;
    portal1 >> source;

    int edgeCnt = 0;

    auto clockStart = std::chrono::high_resolution_clock::now(); // begin read + calc timer

    // first graph input reading scheme; counts edges for edgeArr sizing
    while( portal1 >> source >> destination >> weight )
    {
        edgeCnt++;
    }
    portal1.close();

    // dynamic list of edge arrays for VertexTrack build, indexed by vrespective vertex sink/source
    Edge** edgeArr = new Edge*[edgeCnt];

    // dereferenced vertex array described graph abstraction
    VertexTrack* vertexArr[edgeCnt];

    ifstream portal2( inputFile );

    portal2 >> startVertex;
    portal2 >> endVertex;
    portal2 >> source;

    int edgeIndex = 0;
    int vertexIndex = 0;

    // second graph input read; dynamically populates dereferenced vertextrack array
    while( portal2 >> source >> destination >> weight )
    {
        bool newSource = true;
        bool newSink = true;

        // if empty, add new edge and vertextracker to respective arrays
        if(vertexIndex == 0)
        {
            vertexArr[vertexIndex] = new VertexTrack(source, 1);
            vertexIndex++;
            edgeArr[edgeIndex] = new Edge(source, destination, weight);
            edgeIndex++;
        }
        else // subseqent vertexTracks have attributes populated for sink/source assessment and targetting count adjsutmen
        {
            for( int i = 0; i < vertexIndex; i++ )
            {
                if( vertexArr[i]->name == source )
                {
                    vertexArr[i]->targettings++;
                    newSource = false;
                }
                if( vertexArr[i]->name == destination )
                {
                    newSink = false;
                }
            }
            if( newSource == true )
            {
                vertexArr[vertexIndex] = new VertexTrack(source, 1);
                vertexIndex++;
            }
            if( newSink == true )
            {
                vertexArr[vertexIndex] = new VertexTrack(destination, 0);
                vertexIndex++;
            }
            edgeArr[edgeIndex] = new Edge(source, destination, weight);
            edgeIndex++;
        }
    }
    portal2.close();

    // edges and vertex indices finalized for vertex object graph abstraction
    // each tracked vertex has 2 lists of attached edges differentiated by 
    // navigation concepts: 0) destination options + 1) possible sources 

    // graph abstraction by indexed, dereferenced Vertices 
    Vertex* vertices[vertexIndex];

    // loads # of targettings and id
    for( int i = 0; i < vertexIndex; i++ )
    {
        vertices[i] = new Vertex(vertexArr[i]->targettings, vertexArr[i]->name); 
    } 

    // vertex edges attribute finalized 
    for( int i = 0; i < vertexIndex; i++ )
    {
        int vEdgeIndex = 0;
        for( int z = 0; z < edgeCnt; z++ )
        {
            if ( edgeArr[z]->source == vertices[i]->id)
            {
                Edge* inEdge = new Edge(edgeArr[z]->source, edgeArr[z]->destination, edgeArr[z]->weight);
                vertices[i]->edges[vEdgeIndex] = inEdge;
                vEdgeIndex++;
            }
        }
    }

    // declare directed weighted graph fit for dijkstra navigation
    graphDW unit_01(vertexIndex);

    // final vertices loaded to graphDW object
    for (int i = 0; i < vertexIndex; i++) 
    {
        unit_01.addVertex(vertices[i]);
    }

    // shortest path calculated and printed in cmd via cout in graphDW.cpp
    unit_01.dijkstrasAlgorithm( startVertex, endVertex );

    // end timer for total read and calc runtime; then store
    auto clockEnd = std::chrono::high_resolution_clock::now();
    auto runTime = std::chrono::duration_cast<std::chrono::nanoseconds>(clockEnd - clockStart);

    cout << "runtime = " << runTime.count() << " nanoseconds." << endl;

    // final cleanup 
    for (int i = 0; i < vertexIndex; i++) 
    {
        delete vertexArr[i];
        delete vertices[i];
    }
    for (int i = 0; i < edgeCnt; i++) 
    {
        delete edgeArr[i];
    }

    //END ALL DIJKSTRA'S ALGORITHM PROCEDURES
};
