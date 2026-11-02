/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA2
 * Graph.c
 * Implementation file for Graph ADT
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"


// Structs



typedef struct GraphObj{
    List* adj; // an array of List, adjacency for each vertex
    int* color; // an array of int, color for each vertex
    int* parent; // An array of ints whose 𝑖th element is the parent of vertex 𝑖
    int* distance; // An array of ints whose 𝑖th element is the distance from the (most recent) source to vertex 𝑖.
    int order; // the number of vertices, n, all arraies be length of n+1
    int size; // the number of edges
    int src; // the most recently vertex used as source for BFS
} GraphObj;




// Constructors-Destructors 
// Creates and returns a new empty Graph pointing to
// a newly created GraphObj representing a graph having
// n vertices and no edges.
Graph newGraph(int n){
    Graph G;
    G = malloc(sizeof(GraphObj));
    assert (G != NULL);
    G->adj = malloc( (n+1) * sizeof(List));
    G->color = malloc( (n+1) * sizeof(int));
    G->parent = malloc( (n+1) * sizeof(int));
    G->distance = malloc( (n+1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->src = NIL;
    for (int i = 1; i < n+1; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return G;
}


// Frees all heap memory associated with the Graoh *pG,
// and sets the handle *pG to NULL
void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL){
        
        for (int i = 1; i <= (*pG)->order; i++){
            freeList( &( ( (*pG)->adj )[i] ) );
        }

        free( ((*pG)->adj) );
        free( ((*pG)->color) );
        free( ((*pG)->parent) );
        free( ((*pG)->distance) );

        free(*pG);
        *pG = NULL;
    }
}



/*** Access functions ***/


// Return the number of vertices
int getOrder(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");  
        exit(EXIT_FAILURE); 
    }
    return (G->order);
}


// The number of edges
int getSize(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);    
    }
    return (G->size);
}


// Returns the source vertex most recently used in function BFS().
// or NIL if BFS() has not yet been called.
int getSource(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return (G->src);
}

// Return the parent of vertx u in the BFS tree created by BFS(),
// or NIL if BFS() has not yet been called.
// Pre: 1 ≤ u ≤ getOrder(G)
int getParent(Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getParent() on a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }

    return ((G->parent)[u]);
}


// Returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called.
// Pre: 1 ≤ u ≤ getOrder(G)
int getDist(Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getDist() on a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }

    return ((G->distance)[u]);
}



// Appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exits.
// Pre: getSource(G) != NIL, so BFS() must be called before getPath() is called
// Pre: 1 ≤ u ≤ getOrder(G)
void getPath(List L, Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (getSource(G) == NIL){
        fprintf(stderr, "Graph Error: calling getPath() before BFS() is called\n");
        exit(EXIT_FAILURE);
    }

    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getPath() on a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }

    // clear(L);

    if (u == G->src){
        append(L, u);
    } else if ((G->parent)[u] == NIL){
        clear(L);
        append(L, NIL);
    } else {
        getPath(L, G, (G->parent)[u]);
        append(L, u);
    }
}



/*** Manipulation procedures ***/

// Deletes all edges of G, restoring it to its original (no edge) state.
// (This is called null graph in graph theory literature)
void makeNull(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= G->order; i++){
        clear((G->adj)[i]);
    }

    G->size = 0;
}



// Inserts a new edge joinin u to v, 
// i.e u is added to the adjacency List of v, and v to the adjacency List of u
// Your program is required to maintain these lists in sorted order by increasing labels
// Prev: u, v must like in the rage 1 to getOrder(G)
void addEdge(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling addEdge() on a vertex (first) that does not exist\n");
        exit(EXIT_FAILURE);
    }

    if (v < 1 || v > getOrder(G)){
        fprintf(stderr, "Graph Error: calling addEdge() on a vertex (second) that does not exist\n");
        exit(EXIT_FAILURE);
    }

    if (u == v){
        return;
    }

    int original = G->size;

    addArc(G, u, v);
    addArc(G, v, u);

    int increment = (G->size) - (original);

    if (increment == 2){
        G->size --;
    }
}


// Inserts a new directed edge from u to v,
// i.e. v is added to the adjacenct List of u (but not u to the adjacency List of v)
// Prev: u, v must like in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling addArc() on a vertex (first) that does not exist\n");
        exit(EXIT_FAILURE);
    }

    if (v < 1 || v > getOrder(G)){
        fprintf(stderr, "Graph Error: calling addArc() on a vertex (second) that does not exist\n");
        exit(EXIT_FAILURE);
    }

    if (u == v){
        return;
    }

    List L = (G->adj)[u];

    if (length(L) == 0 ){
        append(L, v);
    } else{
    //    moveFront(L);
       bool inserted = false;
       

    //    for (int i = 0; i < length(L); i++){
       for (moveFront(L); index(L) >= 0; moveNext(L)){
        if (v < get(L)){
            insertBefore(L, v);
            inserted = true;
            break;
        } else if (v == get(L)){
            inserted = true;
            G->size--;
            break;
        } else {
            // moveNext(L);
            continue;
        }
       }
       if (!inserted){
        append(L, v);
       }
    }

    // printList(stdout, L);


    G->size++;
    
}



// Runs the BFS algorithm on the Graph G with source s, 
// setting the color, distance, parent, and source fields of G accordingly.
// Prev: s lies in the range 1 to getOrder(G)
void BFS(Graph G, int s){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (s < 1 || s > getOrder(G)){
        fprintf(stderr, "Graph Error: calling BFS() using a vertex that does not exist as source\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= getOrder(G); i++){
        (G->color)[i] = WHITE;
        (G->distance)[i] = INF;
        (G->parent)[i] = NIL;
    }

    (G->color)[s] = GRAY;
    (G->distance)[s] = 0;
    (G->parent[s]) = NIL;

    G->src = s;

    List L = newList();
    append(L, s);
    int u;
    int vertex;

    while (length(L)){
        u = front(L);
        deleteFront(L);

        List adjacency = (G->adj)[u];


        for(moveFront(adjacency); index(adjacency) >= 0; moveNext(adjacency)){
            vertex = get(adjacency);
            if ((G->color)[vertex] == WHITE){
                (G->color)[vertex] = GRAY;
                (G->distance)[vertex] = ((G->distance)[u]) + 1;
                (G->parent)[vertex] = u;
                append(L, vertex);
            }
        }
        (G->color)[u] = BLACK;
    }

    freeList(&L);
}


/*** Other operations ***/
// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){

    // FILE* out = fopen(out); ??

    for (int i = 1; i <= G->order; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);

        // fprintf(stdout, "%d: ", i);
        // printList(stdout, G->adj[i]);
    }
}