#include "main.h"

using namespace std;

int main( int argc, const char* argv[] )
{
    (void)argc;
    string inputFile;
    inputFile = argv[1];

    ifstream portal1( inputFile );

    // FIRST FILE LOOP . . .
    string startVertex;
    string endVertex;
    string source, destination;
    int weight;

    portal1 >> startVertex;
    portal1 >> endVertex;

    portal1 >> source;

    int edgeCnt = 0;

    auto clockStart = std::chrono::high_resolution_clock::now();

    while( portal1 >> source >> destination >> weight )
    {
        edgeCnt++;
    }
    portal1.close();


    Edge** edgeArr = new Edge*[edgeCnt];

    VertexTrack* vertexArr[edgeCnt];

    ifstream portal2( inputFile );

    portal2 >> startVertex;
    portal2 >> endVertex;
    portal2 >> source;

    int edgeIndex = 0;
    int vertexIndex = 0;

    while( portal2 >> source >> destination >> weight )
    {
        bool newSource = true;
        bool newSink = true;

        if(vertexIndex == 0)
        {
            vertexArr[vertexIndex] = new VertexTrack(source, 1);
            vertexIndex++;
            edgeArr[edgeIndex] = new Edge(source, destination, weight);
            edgeIndex++;
        }
        else
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

    Vertex* vertices[vertexIndex];

    for( int i = 0; i < vertexIndex; i++ )
    {
        vertices[i] = new Vertex(vertexArr[i]->targettings, vertexArr[i]->name); 
    }



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


    graphDW unit_01(vertexIndex);

    for (int i = 0; i < vertexIndex; i++) 
    {
        unit_01.addVertex(vertices[i]);
    }


    unit_01.dijkstrasAlgorithm( startVertex, endVertex );

    auto clockEnd = std::chrono::high_resolution_clock::now();

    auto runTime = std::chrono::duration_cast<std::chrono::nanoseconds>(clockEnd - clockStart);

    cout << "runtime = " << runTime.count() << " nanoseconds." << endl;

    for (int i = 0; i < vertexIndex; i++) 
    {
        delete vertexArr[i];
        delete vertices[i];
    }

    for (int i = 0; i < edgeCnt; i++) 
    {
        delete edgeArr[i];
    }

};
