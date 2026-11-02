/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA3
 * FindComponents.c
 * To find all strongly connected components (SCCs) in a Graph ADT
 ***/


#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "List.h"


int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE* in;
    FILE* out;

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w"); 
    // out = stdout;

    if (in == NULL){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    if (out == NULL){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // find size and create the graph
    int size;
    fscanf(in, "%d\n", &size); 

    // printf("%d\n", size); 
    Graph G = newGraph(size);
    // find size and create the graph

    // add edges
    int a, b;
    fscanf(in, "%d %d\n", &a, &b);
    while ( a != 0 && b != 0 ){
        // printf("%d %d\n",a, b);
        addArc(G, a, b);
        fscanf(in, "%d %d\n", &a, &b);
    }
    // add edges


    // print the graph
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");
    // print the graph

    // printf("%d %d\n",a, b);    // will print 0 0

    // run DFS

    List L = newList();

    for (int i = 1; i <= size; i++){
        append(L, i);
    }


    // printf("here is the size of the graph: %d\n", size);
    // printf("here is the length of the L: %d\n", length(L));
    DFS(G, L);
    Graph trans = transpose(G);
    // printf("here is the size of the transpose %d\n", getOrder(trans));
    // printf("here is the length of the L again: %d\n", length(L));
    // printList(out, L);
    DFS(trans, L);

    // now L is a stack that contains the SCCs, read from the bottom
    List path = newList();
    int count = 1;
    int num = 0;

    for (moveFront(L); index(L) >= 0; moveNext(L)){
        int vertex = get(L);
        if (getParent(trans, vertex) == NIL){
            num ++;
        }
    }

    fprintf(out, "G contains %d strongly connected components:\n", num);

    for (moveBack(L); index(L) >= 0; movePrev(L)){
        while (getParent(trans, get(L)) != NIL){
            prepend(path, get(L));
            movePrev(L);
        }

        prepend(path, get(L));  // while loop stops at the parent of the tree

        fprintf(out, "Component %d: ", count);
        printList(out, path);
        // fprintf(out, "\n");
        clear(path); // clear the path list for next use
        count ++;
    }



    // fprintf(out, "\n");

    freeGraph(&G);
    freeGraph(&trans);
    freeList(&L);
    freeList(&path);

    fclose(in);
    fclose(out);
    return 0;
}