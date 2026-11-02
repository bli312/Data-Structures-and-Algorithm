/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA3
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
    int* discover; // An array of ints whose 𝑖th element is the discover time of vertex 𝑖.
    int* finish; // An array of ints whose 𝑖th element is the finish time of vertex 𝑖.
    int order; // the number of vertices, n, all arraies be length of n+1
    int size; // the number of edges
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
    G->discover = malloc( (n+1) * sizeof(int));
    G->finish = malloc( (n+1) * sizeof(int));
    G->order = n;
    G->size = 0;
    for (int i = 1; i < n+1; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
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
        free( ((*pG)->discover) );
        free( ((*pG)->finish) ); 

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



// Return the parent of vertx u in the DFS tree created by DFS(),
// or NIL if DFS() has not yet been called.
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


// Return the Discover time of vertx u in the DFS tree created by DFS(),
// or NIL if DFS() has not yet been called.
// Pre: 1 <= u <=  n = getOrder(G)
int getDiscover(Graph G, int u){
        if (G == NULL){
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getDiscover() on a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }

    return ((G->discover)[u]);
}



// Return the Finish time of vertx u in the DFS tree created by DFS(),
// or NIL if DFS() has not yet been called.
// Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G , int u){
        if (G == NULL){
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: calling getFinish() on a vertex that does not exist\n");
        exit(EXIT_FAILURE);
    }

    return ((G->finish)[u]);
}




/*** Manipulation procedures ***/


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

    List L = (G->adj)[u];

    if (length(L) == 0 ){
        append(L, v);
    } else{
    //    moveFront(L);
       bool inserted = false;

    //     for (moveFront(L); index(L) >=0; moveNext(L)){
    //         if (get(L) == v){
    //             return;
    //         }
    // }
       
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


// helper function of DFS: DFS-Visit

void Visit(Graph G, List S, int u, int* time){
    (*time) ++;
    (G->discover)[u] = *time;
    (G->color)[u] = GRAY;

    List adja = (G->adj)[u];

    for (moveFront(adja); index(adja) >= 0; moveNext(adja)){
        int vertex = get(adja);
        if ((G->color)[vertex] == WHITE){
            (G->parent)[vertex] = u;
            Visit(G, S, vertex, time);
        }
    }

    (*time) ++;
    (G->finish)[u] = *time;
    (G->color)[u] = BLACK;
    prepend(S, u);
}


// Perform the depth first search algorithm on G. The List argument S has two purposes in this function.
// First it defines the order in which vertices are to be processed in the main loop of DFS
// Second when DFS is complete, it will store the vertics by decreasing finish times (hense S is cosidered to be a stack)
// Rgus S can be classified as both an input and output parameter to function DFS()
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(S) != getOrder(G)){
        fprintf(stderr, "Graph Error: calling DFS() but the order does not equal to the length\n");
        exit(EXIT_FAILURE);
    }


    for (int i = 1; i <= getOrder(G); i++){
        (G->color)[i] = WHITE;
        (G->parent)[i] = NIL;
        (G->discover)[i] = UNDEF;
        (G->finish)[i] = UNDEF;
    }

    int time = 0;

    List order = copyList(S);

    clear(S);

    for (moveFront(order); index(order) >= 0; moveNext(order)){
        int vertex = get(order);
        if ((G->color)[vertex] == WHITE){
            Visit(G, S, vertex, &time);
        }
    }

    freeList(&order);
}






/*** Other operations ***/


// Returns a reference to a new graph pbject representing the transpose of G
Graph transpose(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling transpose() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph trans = newGraph(getOrder(G));
    List adja;

    for (int i = 1; i <= getOrder(G); i++ ){
        adja = (G->adj)[i];
        for (moveFront(adja); index(adja) >= 0; moveNext(adja)){
            addArc(trans, get(adja), i);
        }
    }

    return trans;


}


// returns a reference to a new graph that is a copy of G.
Graph copyGraph(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph new = newGraph(getOrder(G));

    for (int i = 1; i <= getOrder(G); i++){
        // freeList(&(new->adj)[i]);
        // (new->adj)[i] = copyList( (G->adj)[i] );
        // printf("just freed the list\n");


        // (new->color)[i] = (G->color)[i];
        // (new->discover)[i] = (G->discover)[i];
        // (new->finish)[i] = (G->finish)[i];
        // (new->parent)[i] = (G->parent)[i];
        // (new->size) = G->size;


        List adj = (G->adj)[i];
        // printf("here is the list!\n");
        // printList(stdout, adj);

        for (moveFront(adj); index(adj) >= 0; moveNext(adj)){
            int vertex = get(adj);
            addArc(new, i, vertex);
            // printf("edges added\n");
        }

        // freeList(&adj);
    }

    (new->size) = G->size;

    return new;
}



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


