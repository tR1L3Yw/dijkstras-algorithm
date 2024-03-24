#include "graphBuildOps.h"

using namespace std;

graphDW::graphDW( int nV ) {
    numVertices = nV;
    buildIndex = 0;
    graphVertices = new Vertex*[nV];
}
 
void graphDW::addVertex( Vertex* inVertex ) {
    graphVertices[buildIndex] = inVertex;
    buildIndex++;
}

Vertex* graphDW::getVertex( int index ) {
    return graphVertices[index];
}

int graphDW::getVertexIndex( string name ) {
    int index;
    for( int i = 0; i < numVertices; i++ ) {
        if( graphVertices[i]->id == name ) {
            index = i;
        }
    }
    return index;
}


void graphDW::dijkstrasAlgorithm ( string startVertex, string endVertex ) {
    int startIndex = this->getVertexIndex(startVertex);
    int endIndex = this->getVertexIndex(endVertex);

    this->getVertex(startIndex)->distance = 0;

    Vertex* start = this->getVertex(startIndex);

    MinHeap<Vertex>::Node initial(start, 0);

    MinHeap<Vertex> pq(numVertices);

    pq.insert(initial);

    while(!pq.isEmpty()) {
        MinHeap<Vertex>::Node extract = pq.extractMin();

        Vertex* current = extract.vertex;
        current->seen = true;

        for( int i = 0; i < current->outDegree; i++) {
            int adjacentIndex = this->getVertexIndex(current->edges[i]->destination);

            Vertex* adjacent = this->getVertex(adjacentIndex);

            if( !adjacent->seen ) {
                int tempDistance = current->distance + current->edges[i]->weight;

                if( tempDistance < adjacent->distance ) {
                    adjacent->distance = tempDistance;
                    adjacent->lastJump = current;
                }

                if( adjacent->id == endVertex ) {
                    //cout << adjacent->id << " " << adjacent->distance << endl;
                    break;
                }

                MinHeap<Vertex>::Node fresh(adjacent, adjacent->distance);
                pq.insert(fresh);
            }
        }
    }

    string path = "";

    Vertex* target = this->getVertex(endIndex);
    int cost = target->distance;

    while( target->lastJump != nullptr ) {
        path = target->id + " " + path;
        target = target->lastJump;
    }

    path = startVertex + " " + path;

    cout << "Path: " << path << endl;
    cout << "Cost: " << cost << endl;
}
