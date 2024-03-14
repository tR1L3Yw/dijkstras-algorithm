#include <iostream>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

struct Edge{
    string source;
    string destination;
    int weight;

    Edge()
    {
        source = "";
        destination = "";
        weight = 0;
    }

    Edge( string src, string dst, int wt)
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

struct VertexTrack{
    string name;
    int targettings;

    VertexTrack( string n, int t )
    {
        name = n;
        targettings = t;
    }
};

struct Vertex{
    string id;
    int outDegree;
    Edge** edges;

    bool seen;
    int distance;
    Vertex* lastJump;

    Vertex() {}    

    Vertex(int outDeg, string name) {
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
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    void swapNodes(int i, int j) {
        Node temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }
    void siftUp(int i) {
        while (i > 0 && heap[parent(i)].distance > heap[i].distance) {
            swapNodes(i, parent(i));
            i = parent(i);
        }
    }
    void siftDown(int i) {
        int minIndex = i;
        int l = leftChild(i);
        if (l < size && heap[l].distance < heap[minIndex].distance) {
            minIndex = l;
        }
        int r = rightChild(i);
        if (r < size && heap[r].distance < heap[minIndex].distance) {
            minIndex = r;
        }
        if (i != minIndex) {
            swapNodes(i, minIndex);
            siftDown(minIndex);
        }
    }
    
public:
    MinHeap(int cap) {
        heap = new Node[cap];
        capacity = cap;
        size = 0;
    }
    ~MinHeap() {
        delete[] heap;
    }
    
    void insert(Node node) {
        if (size == capacity) {
            return;
        }
        heap[size] = node;
        size++;
        siftUp(size - 1);
    }
    Node extractMin() {
        Node minNode = heap[0];
        heap[0] = heap[size - 1];
        size--;
        siftDown(0);
        return minNode;
    }
    bool isEmpty() {
        return size == 0;
    }
};

class graphDW{
private:
    int numVertices;
    int buildIndex;
    Vertex** graphVertices;

public:
    graphDW( int nV )
    {
        numVertices = nV;
        buildIndex = 0;
        graphVertices = new Vertex*[nV];
    }

    void addVertex( Vertex* inVertex )
    {
        graphVertices[buildIndex] = inVertex;
        buildIndex++;
    }

    Vertex* getVertex( int index ) 
    {
        return graphVertices[index];
    }

    int getVertexIndex( string name )
    {
        int index;
        for( int i = 0; i < numVertices; i++ )
        {
            if( graphVertices[i]->id == name )
            {
                index = i;
            }
        }
        return index;
    }

    void dijkstrasAlgorithm ( string startVertex, string endVertex )
    {
        int startIndex = this->getVertexIndex(startVertex);
        int endIndex = this->getVertexIndex(endVertex);

        this->getVertex(startIndex)->distance = 0;

        Vertex* start = this->getVertex(startIndex);

        Node initial(start, 0);

        MinHeap pq(numVertices);

        pq.insert(initial);



        while(!pq.isEmpty())
        {
            Node extract = pq.extractMin();

            Vertex* current = extract.vertex;
            current->seen = true;

            for( int i = 0; i < current->outDegree; i++)
            {
                int adjacentIndex = this->getVertexIndex(current->edges[i]->destination);

                //cout << adjacentIndex << endl;

                Vertex* adjacent = this->getVertex(adjacentIndex);

                if( !adjacent->seen )
                {
                    int tempDistance = current->distance + current->edges[i]->weight;

                    if( tempDistance < adjacent->distance )
                    {
                        adjacent->distance = tempDistance;
                        adjacent->lastJump = current;
                    }

                    if( adjacent->id == endVertex )
                    {
                        //cout << adjacent->id << " " << adjacent->distance << endl;
                        break;
                    }

                    Node fresh(adjacent, adjacent->distance);
                    pq.insert(fresh);
                }
            }
        }

        string path = "";

        Vertex* target = this->getVertex(endIndex);
        int cost = target->distance;

        while( target->lastJump != nullptr )
        {
            path = target->id + " " + path;
            target = target->lastJump;
        }

        path = startVertex + " " + path;

        cout << "Path: " << path << endl;
        cout << "Cost: " << cost << endl;

    }    

};

