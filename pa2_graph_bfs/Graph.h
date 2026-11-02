/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA2
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
#define INF -2

typedef struct GraphObj* Graph;


// Constructors-Destructors 
// Creates and returns a new empty Graph pointing to
// a newly created GraphObj representing a graph having
// n vertices and no edges.
Graph newGraph(int n);


// Frees all heap memory associated with the Graoh *pG,
// and sets the handle *pG to NULL
void freeGraph(Graph* pG);


/*** Access functions ***/


// Return the number of vertices
int getOrder(Graph G);


// The number of edges
int getSize(Graph G);


// Returns the source vertex most recently used in function BFS().
// or NIL if BFS() has not yet been called.
int getSource(Graph G);


// Return the parent of vertx u in the BFS tree created by BFS(),
// or NIL if BFS() has not yet been called.
// Pre: 1 ≤ u ≤ getOrder(G)
int getParent(Graph G, int u);


// Returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called.
// Pre: 1 ≤ u ≤ getOrder(G)
int getDist(Graph G, int u);



// Appends to the LIst L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exits.
// Pre: getSource(G) != NIL, so BFS() must be called before getPath() is called
// Pre: 1 ≤ u ≤ getOrder(G)
void getPath(List L, Graph G, int u);



/*** Manipulation procedures ***/

// Deletes all edges of G, restoring it to its original (no edge) state.
// (This is called null graph in graph theory literature)
void makeNull(Graph G);

// Inserts a new edge joinin u to v, 
// i.e u is added to the adjacency List of v, and v to the adjacency List of u
// Your program is required to maintain these lists in sorted order by increasing labels
// Prev: u, v must like in the rage 1 to getOrder(G)
void addEdge(Graph G, int u, int v);


// Inserts a new directed edge from u to v,
// i.e. v is added to the adjacenct List of u (but not u to the adjacency List of v)
// Prev: u, v must like in the rage 1 to getOrder(G)
void addArc(Graph G, int u, int v);


// Runs the BFS algorithm on the Graph G with source s, 
// setting the color, distance, parent, and source fields of G accordingly.
// Prev: s lies in the range 1 to getOrder(G)
void BFS(Graph G, int s);


/*** Other operations ***/
// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);


#endif