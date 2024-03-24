# dijkstras-algorithm

For this project, Dijkstra’s algorithm implemented to find the shortest path in a directed + weighted graph. Key objectives include implementing a Minimum Heap priority queue and storing and processing data in a graph abstraction. In the given test files, 00 describes a basic list of weighted + directed edges with letter id vertices and the desired start and end vertices and 01 describes the same although with a greater edge count and vertex names as airport ids for an elementary flight path calculation. The project includes: 01) a Weighted + Directed Graph abstraction whose building blocks include structs Edge, VertexTrack, and Vertex; 02) a standard Minimum Heap object with an attributed Node struct for priority queue abstraction; and 03) a final graph object with Vertex components for shortest path navigation via Dijkstra's algorithm called as a member function. 

GRAPH COMPONENTS (file: graphComp)
 - describes fundamental structs for a weighted & directed graph
 - defines building blocks + minimal navigation required for djikstra's algorithm
 - components in order: Edge, VertexTrack (navigation), & Vertex
   
 1. VertexTrack struct: This struct holds a vertex id and count of its In-Degrees: the number of unique edges with an outdegree at named vertex
 
 2. Edge struct: This struct describes a single path between two vertices
 
 3. Vertex struct: This struct describes Vertices as building blocks of the actual graph abstraction. Out-Degrees and NOT In-Degrees are attributed as this is all that's needed from our pal dijkstra. A dynamic array of Edge struct pointers is also necessary for processing along with a boolean indicator set to false after its first input data point appearance, an int measure of distance from the source of desired shortest path and a pointer  to the vertex last processed (only used in attempted navigation). 

MINIMUM HEAP ABSTRACTION
- struct and class attributes for a Minimum Heap
- optimized for implementation in dijkstra's algorithm
- components in order: building block Node struct & MinHeap class attributes
  
1. Node struct: This struct describes a heap node representation of a real Vertex struct (described in graphDW) with attributes tailored for dijkstra's shortest path algorithm: a pointer to the referenced Vertex instance, and an integer measure of distance from the Source Node / Start Vertex of the proposed shortest path, in parent/child node "jumps" to reach the source. The Node struct is fully defined in declaration of the heap attribute of MinHeap
   
3. MinHeap Class: This class describes the minimum heap to be implemented in the final dijkstra's shortest path processing. With the exception of it's (core) component Node struct being variable constrained the the explicit Vertex pointer attribute, the MinHeap class is a standard Minimum Heap-Binary Tree with overall complexities of O(log(N)) for both insertion or deletion of a node and O(1) in retrieval of the minimum value node. 
a. MinHeap Total Complexity: O(log(N)) * O(1) = O(log(N))


