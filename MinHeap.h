#include "graphComp.h"

#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#ifndef MINHEAP_H
#define MINHEAP_H

#include<string>

    // BEGIN MINIMUM HEAP COMPONENTS
    // - struct and class attributes for a Minimum Heap 
    // - optimized for implementation in dijkstra's algorithm 
    // - components in order: building block Node struct & MinHeap class attributes



// BEGIN MinHeap Class
// This class describes the minimum heap to be implemented in the 
// final dijkstra's shortest path processing. With the exception of 
// it's (core) component Node struct being variable constrained
// the the explicit Vertex pointer attribute, the MinHeap class
// is a standard Minimum Heap-Binary Tree with overall complexities 
// of O(log(N)) for both insertion or deletion of a node and O(1)
// in retrieval of the minimum value node. Function definitions
// in MinHeap.cpp with exception of in lines  

//   MinHeap Total Complexity: O(log(N)) * O(1) = O(log(N))   //

template <class T> class MinHeap 
{
private:
    // attributes
             // pointer to beginning (min) of dynamic array
    int capacity;       // capacity measure = vertex count WD-graph already instantiated 
    int size;           // size measure = node count which is necessarily mutable for build and dijkstra
    
    void swapNodes( int i, int j );     // parent-child nodes exchange heights
    void siftUp( int i );               // node swapped TOWARD MIN until MinHeap justified
    void siftDown( int i );             // node swapped AWAY FROM MIN until MinHeap justified
    
    inline int parent( int i ) { return (i - 1) / 2; }     // returns parent index in dynamic array heap representaion
    inline int leftChild( int i ) { return 2 * i + 1; }    // returns left leaf index in heap array ^^^
    inline int rightChild( int i ) { return 2 * i + 2; }   // returns right leaf index in heap array ^^^
    
public:

// BEGIN Node struct
// This struct describes a heap node representation of a real Vertex struct 
// (described in graphDW) with attributes tailored for dijkstra's shortest
// path algorithm: a pointer to the referenced Vertex instance, and an integer
// measure of distance from the Source Node / Start Vertex of the proposed 
// shortest path, in parent/child node "jumps" to reach the source.
struct Node {
        // attributes
        T *vertex;     // pointer to Vertex instantiation in active graph
        int distance;       // distance from SrcNode/StartVertex in Node "jumps"
        
        // default constructor (required for dynamic memory allocation)
        Node() {}
        
        // parameterized constructor
        Node( T *v, int d ) {
            vertex = v;
            distance = d;
        }
    } *heap; // END Node struct

    MinHeap( int cap );     // parameterized constructor
    ~MinHeap();             // destructor

    void insert( Node node );       // adds node ( implements private functions )
    Node extractMin();              // removes minimum value ("distance") node and adjusts heap
    bool isEmpty();                 // is da heep emtee? 
};


using namespace std;

template <typename T>
void MinHeap<T>::swapNodes( int i, int j ) {
    Node temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

template <typename T>
void MinHeap<T>::siftUp( int i ) {
    while (i > 0 && heap[parent(i)].distance > heap[i].distance) {
        swapNodes( i, parent(i) );
        i = parent(i);
    }
}

template <typename T>
void MinHeap<T>::siftDown( int i ) {
    int minIndex = i;
    int l = leftChild(i);
    if (l < size && heap[l].distance < heap[minIndex].distance) {
        minIndex = l;
    }
    int r = rightChild(i);
    if ( r < size && heap[r].distance < heap[minIndex].distance ) {
        minIndex = r;
    }
    if ( i != minIndex ) {
        swapNodes( i, minIndex );
        siftDown(minIndex);
    }
}

template <class T> 
MinHeap<T>::MinHeap( int cap ) {
    heap = new Node[cap];
    capacity = cap;
    size = 0;
}

template <typename T>
MinHeap<T>::~MinHeap() {
    delete[] heap;
}

template <class T>
void MinHeap<T>::insert( Node node ) {
    if (size == capacity) {
        return;
    }
    heap[size] = node;
    size++;
    siftUp(size - 1);
}

template <class T> 
typename MinHeap<T>::Node MinHeap<T>::extractMin() {
    Node minNode = heap[0];
    heap[0] = heap[size - 1];
    size--;
    siftDown(0);
    return minNode;
}

template <typename T>
bool MinHeap<T>::isEmpty() {
    return size == 0;
}

#endif
