/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA3
 * Graph.h
 * Header file for Graph ADT
 ***/


#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"


#define FORMAT "%d"
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1
#define UNDEF -2

typedef struct GraphObj* Graph;


// Constructors-Destructors 
// Creates and returns a new empty Graph pointing to
// a newly created GraphObj representing a graph having
// n vertices and no edges.
Graph newGraph(int n);


// Frees all heap memory associated with the Graoh *pG,
// and sets the handle *pG to NULL (and its Graoh argument)
void freeGraph(Graph* pG);


/*** Access functions ***/


// Return the number of vertices in G
int getOrder(Graph G);


// The number of edges
int getSize(Graph G);



// Return the parent of vertx u in the DFS tree created by DFS(),
// or NIL if DFS() has not yet been called.
// Pre: 1 ≤ u ≤ getOrder(G)
int getParent(Graph G, int u);



// Return the Discover time of vertx u in the DFS tree created by DFS(),
// or NIL if DFS() has not yet been called.
// Pre: 1 <= u <=  n = getOrder(G)
int getDiscover(Graph G, int u);


// Return the Finish time of vertx u in the DFS tree created by DFS(),
// or NIL if DFS() has not yet been called.
// Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G , int u);



/*** Manipulation procedures ***/

// Inserts a new edge joinin u to v, 
// i.e u is added to the adjacency List of v, and v to the adjacency List of u
// Your program is required to maintain these lists in sorted order by increasing labels
// Prev: u, v must like in the rage 1 to getOrder(G)
// 1 <= u <= n, 1 <= v <= n
void addEdge(Graph G, int u, int v);


// Inserts a new directed edge from u to v,
// i.e. v is added to the adjacenct List of u (but not u to the adjacency List of v)
// Prev: u, v must like in the rage 1 to getOrder(G)
// 1 <= u <= n, 1 <= v <= n
void addArc(Graph G, int u, int v);


// Perform the depth first search algorithm on G. The List argument S has two purposes in this function.
// First it defines the order in which vertices are to be processed in the main loop of DFS
// Second when DFS is complete, it will store the vertics by decreasing finish times (hense S is cosidered to be a stack)
// Rgus S can be classified as both an input and output parameter to function DFS()
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S);


/*** Other operations ***/



// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);


// Returns a reference to a new graph pbject representing the transpose of G
Graph transpose(Graph G);


// returns a reference to a new graph that is a copt of G.
Graph copyGraph(Graph G);

#endif