/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA2
 * FindPath.c
 * Using functions to find the shortest route from one vertex to another
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
    while ( a != 0 && b != 00 ){
        // printf("%d %d\n",a, b);
        addEdge(G, a, b);
        fscanf(in, "%d %d\n", &a, &b);
    }
    // add edges


    // print the graph
    printGraph(out, G);
    fprintf(out, "\n");


    // print the graph


    // printf("%d %d\n",a, b);    // will print 0 0

    // find paths and print them
    int c, d;
    fscanf(in, "%d %d\n", &c, &d);  // the first pair
    while ( c != 0 || d != 0){
        if (c != getSource(G)){
            BFS(G, c);
        }
        List path = newList();
        getPath(path, G, d);
        if (front(path) != NIL){
            fprintf(out, "The distance from %d to %d is %d\n", c, d, getDist(G, d));
            fprintf(out, "A shortest %d-%d path is: ", c, d);
            printList(out, path);
            fprintf(out, "\n");
            // fprintf(out, "\n");
        } else {
            fprintf(out, "The distance from %d to %d is infinity\n", c, d);
            fprintf(out, "No %d-%d path exists\n\n", c, d);
        }
        freeList(&path);

        fscanf(in, "%d %d\n", &c, &d);
    }
    // find paths and print them

    // fprintf(out, "\n");
    // fprintf(out, "\n");
    // fprintf(out, "\n");
    // fprintf(out, "\n");
    // fprintf(out, "\n");
    // fprintf(out, "\n");
    // fprintf(out, "\n");

    freeGraph(&G);
    

    fclose(in);
    fclose(out);


    return 0;

}