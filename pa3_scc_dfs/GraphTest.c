/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA3
 * GraphTest.c
 * Test for Graph ADT
 ***/

#include<assert.h>
#include"Graph.h"
#include"List.h"


int main(void){

    Graph G = newGraph(8);
    addArc(G, 1, 2);
    addArc(G, 1, 5);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 6, 7);
    addArc(G, 3, 4);
    addArc(G, 3, 8);
    addArc(G, 6, 5);
    addArc(G, 8, 4);
    addArc(G, 3, 2);
    addArc(G, 3, 6);
    addArc(G, 3, 7);
    addArc(G, 8, 7);
    addArc(G, 8, 7);
    addArc(G, 8, 7);
    addArc(G, 8, 7);
    addArc(G, 8, 7);
    addArc(G, 8, 7);
    addArc(G, 8, 7);


    assert(getOrder(G) == 8);
    assert(getSize(G) == 13);


    List S = newList();
    for (int i =  1; i<= 8; i++){
        append(S, i);
    }


    printf("here is the list of parent of vertices in G before running DFS()\n");
    for (int j = 1; j <= 8; j++){
        printf("%d ", getParent(G, j));
    }
    printf("\n");

    // supposed output: -1 -1 -1 -1 -1 -1 -1 -1

    printf("here is the list of discover time of vertices in G before running DFS()\n");
    for (int j = 1; j <= 8; j++){
        printf("%d ", getDiscover(G, j));
    }
    printf("\n");

    // suppoded output: -2 -2 -2 -2 -2 -2 -2 -2

    printf("here is the list of finish time of vertices in G before running DFS()\n");
    for (int j = 1; j <= 8; j++){
        printf("%d ", getFinish(G, j));
    }
    printf("\n");

    // supposed output: -2 -2 -2 -2 -2 -2 -2 -2


    DFS(G, S);

    printf("here is the list of parent of vertices in G after running DFS()\n");
    for (int j = 1; j <= 8; j++){
        printf("%d ", getParent(G, j));
    }
    printf("\n");

    // supposed output: -1 1 -1 3 2 2 6 3

    printf("here is the list of discover time of vertices in G after running DFS()\n");
    for (int j = 1; j <= 8; j++){
        printf("%d ", getDiscover(G, j));
    }
    printf("\n");

    // suppoded output: 1 2 11 12 3 5 6 14

    printf("here is the list of finish time of vertices in G after running DFS()\n");
    for (int j = 1; j <= 8; j++){
        printf("%d ", getFinish(G, j));
    }
    printf("\n");

    // supposed output: 10 9 16 13 4 8 7 15



    Graph T = transpose(G);

    assert(getOrder(T) == 8);
    assert(getSize(T) == 13);


    printf("here is the adjacency list of G and T\n");
    printGraph(stdout, G);
    printf("\n");
    printGraph(stdout, T);

    // 1: 2 5 
    // 2: 5 6 
    // 3: 2 4 6 7 8 
    // 4: 
    // 5: 
    // 6: 5 7 
    // 7: 
    // 8: 4 7 

    // 1: 
    // 2: 1 3 
    // 3: 
    // 4: 3 8 
    // 5: 1 2 6 
    // 6: 2 3 
    // 7: 3 6 8 
    // 8: 3 


    Graph C = copyGraph(G);
    Graph D = copyGraph(T);

    printf("here is the adjacency list of the copy of G and T\n");
    printGraph(stdout, C);
    printf("\n");
    printGraph(stdout, D);
    printf("\n");



    addArc(C, 4, 5);
    printf("added an arc from 4 to 5 in C\n");
    assert( getSize(C) == (getSize(G) + 1));
    printGraph(stdout, C);
    printf("\n");
    // 1: 2 5 
    // 2: 5 6 
    // 3: 2 4 6 7 8 
    // 4: 5
    // 5: 
    // 6: 5 7 
    // 7: 
    // 8: 4 7 

    printf("but here is the original graph - G\n");
    printGraph(stdout, G);
    printf("\n");

    addArc(D, 1, 3);
    printf("added an arc from 1 to 3 in D\n");
    printGraph(stdout, D);
    assert( getSize(D) == (getSize(T) + 1));
    // 1: 3
    // 2: 1 3 
    // 3: 
    // 4: 3 8 
    // 5: 1 2 6 
    // 6: 2 3 
    // 7: 3 6 8 
    // 8: 3 

    printf("but here is the original graph - T\n");
    printGraph(stdout, T);


    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    freeGraph(&C);
    freeGraph(&D);
    
    return 0;
}


// //-----------------------------------------------------------------------------
// // GraphClient.c
// // Test client for the Graph ADT
// //-----------------------------------------------------------------------------
// #include<stdio.h>
// #include<stdlib.h>
// #include"List.h"
// #include"Graph.h"


// int main(int argc, char* argv[]){
//    int i, n=8;
//    List S = newList();
//    Graph G = newGraph(n);
//    Graph T=NULL, C=NULL;

//    for(i=1; i<=n; i++) append(S, i);

//    addArc(G, 1,2);
//    addArc(G, 1,5);
//    addArc(G, 2,5);
//    addArc(G, 2,6);
//    addArc(G, 3,2);
//    addArc(G, 3,4);
//    addArc(G, 3,6);
//    addArc(G, 3,7);
//    addArc(G, 3,8);
//    addArc(G, 6,5);
//    addArc(G, 6,7);
//    addArc(G, 8,4);
//    addArc(G, 8,7);
//    printGraph(stdout, G);

//    DFS(G, S);
//    fprintf(stdout, "\n");
//    fprintf(stdout, "x:  d  f  p\n");
//    for(i=1; i<=n; i++){
//       fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
//    }
//    fprintf(stdout, "\n");
//    printList(stdout, S);
//    fprintf(stdout, "\n");

//    T = transpose(G);
//    C = copyGraph(G);
//    fprintf(stdout, "\n");
//    printGraph(stdout, C);
//    fprintf(stdout, "\n");
//    printGraph(stdout, T);
//    fprintf(stdout, "\n");

//    DFS(T, S);
//    fprintf(stdout, "\n");
//    fprintf(stdout, "x:  d  f  p\n");
//    for(i=1; i<=n; i++){
//       fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
//    }
//    fprintf(stdout, "\n");
//    printList(stdout, S);
//    fprintf(stdout, "\n");

//    freeList(&S);
//    freeGraph(&G);
//    freeGraph(&T);
//    freeGraph(&C);
//    return(0);
// }