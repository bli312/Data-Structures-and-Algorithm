/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA2
 * GraphTest.c
 * Test for Graph ADT
 ***/

#include<assert.h>
#include"Graph.h"
#include"List.h"


int main(void){

    printf("here is a test for indirected graph:  \n\n");
    Graph G = newGraph(6);


    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);
    addEdge(G, 5, 4);
    addEdge(G, 2, 5);
    addEdge(G, 6, 2);
    addEdge(G, 5, 2);
    addEdge(G, 5, 5);

    printf("here is the order: %d\n",getOrder(G));
    printf("here is the size: %d\n", getSize(G));


    // FILE* out = fopen("hello.txt", "w");
    printGraph(stdout, G);
    List A = newList();
    List B = newList();
    List C = newList();
    List D = newList();
    // fclose(out);

    BFS(G, 1);
    printf("here is the source: %d\n", getSource(G));
    printf("here is the distance from 1 (src) to 5: %d\n", getDist(G, 5));
    getPath(A, G, 5);
    printf("here is the path for A\n");
    printList(stdout, A);


    BFS(G, 3);
    printf("here is the source: %d\n", getSource(G));
    printf("here is the distance from 3 (src) to 6: %d\n", getDist(G, 6));
    getPath(B, G, 6);
    printf("here is the path for B\n");
    printList(stdout, B);


    BFS(G, 2);
    printf("here is the source: %d\n", getSource(G));
    printf("here is the distance from 2 (src) to 3: %d\n", getDist(G, 3));
    getPath(C, G, 3);
    printf("here is the path for C\n");
    printList(stdout, C);

    BFS(G, 4);
    printf("here is the source: %d\n", getSource(G));
    printf("here is the distance from 4 (src) to 4: %d\n", getDist(G, 4));
    getPath(D, G, 4);
    printf("here is the path for D\n");
    printList(stdout, D);


    makeNull(G);
    printf("Just make the graph to NULL\n");
    assert(getSize(G) == 0);
    assert(getOrder(G) == 6);
    printGraph(stdout, G);

    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&D);
    freeGraph(&G);



    printf("Now here is a test for directed graph\n");

    Graph DG = newGraph(5);


    addArc(DG, 1, 4);
    addArc(DG, 2, 1);
    addArc(DG, 2, 5);
    addArc(DG, 3, 2);
    addArc(DG, 3, 5);
    addArc(DG, 4, 2);
    addArc(DG, 4, 5);
    addArc(DG, 4, 5);


    printf("here is the order: %d\n",getOrder(DG));
    printf("here is the size: %d\n", getSize(DG));

    printGraph(stdout, DG);
    // List DA = newList();


    for (int j = 1; j <= getOrder(DG); j++){
        BFS(DG, j);
        printf("here is the source: %d\n\n", getSource(DG));
        for (int i = 1; i <= getOrder(DG); i++){
            List DA = newList();
            printf("here is the distance from %d (src) to %d: %d\n", j, i, getDist(DG, i));
            getPath(DA, DG, i);
            printf("here is the path for DG\n");
            printList(stdout, DA);
            freeList(&DA);
        }
    }

    makeNull(DG);
    printf("Just make the graph to NULL\n");
    assert(getSize(DG) == 0);
    assert(getOrder(DG) == 5);
    printGraph(stdout, DG);

    printf("here we go!\n");


    // freeList(&DA);
    freeGraph(&DG);
    return 0;
}