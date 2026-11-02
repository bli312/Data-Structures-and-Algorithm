/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA4
 * Sparse.c
 * Read an input file, initialize and build the Array-of-Lists representation of Matrices 
 * A and B, then calculate and print a set of matrices (after some operations) to the output file
 ***/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"



int main (int argc, char* argv[]){
    if (argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* in;
    FILE* out;

    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    if (out == NULL){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int size, line_a, line_b;
    int row, column;
    double data;

    fscanf(in, "%d %d %d\n", &size, &line_a, &line_b);

    Matrix A = newMatrix(size);
    Matrix B = newMatrix(size);
    Matrix C, D, E, F, G, H, I, J;

    for (int i = 0; i < line_a; i++){
        fscanf(in, "%d %d %lf", &row, &column, &data);
        changeEntry(A, row, column, data);
    }

    for (int j = 0; j <line_b; j++){
        fscanf(in, "%d %d %lf", &row, &column, &data);
        changeEntry(B, row, column, data);
    }


    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");


    fprintf(out, "(1.5)*A =\n");
    C = scalarMult(1.5, A);
    printMatrix(out, C);
    fprintf(out, "\n");


    fprintf(out, "A+B =\n");
    D = sum(A, B);
    printMatrix(out, D);
    fprintf(out, "\n");


    fprintf(out, "A+A =\n");
    E = sum(A, A);
    printMatrix(out, E);
    fprintf(out, "\n");


    fprintf(out, "B-A =\n");
    F = diff(B, A);
    printMatrix(out, F);
    fprintf(out, "\n");


    fprintf(out, "A-A =\n");
    G = diff(A, A);
    printMatrix(out, G);
    fprintf(out, "\n");


    fprintf(out, "Transpose(A) =\n");
    H = transpose(A);
    printMatrix(out, H);
    fprintf(out, "\n");


    fprintf(out, "A*B =\n");
    I = product(A, B);
    printMatrix(out, I);
    fprintf(out, "\n");


    fprintf(out, "B*B =\n");
    J = product(B, B);
    printMatrix(out, J);
    // fprintf(out, "\n");


    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);


    fclose(in);
    fclose(out);
    return 0;
}
