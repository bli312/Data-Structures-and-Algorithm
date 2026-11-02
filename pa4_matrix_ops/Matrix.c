/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA4
 * Matrix.c
 * Implementation file for Matrix ADT
 ***/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"


typedef struct EntryObj* Entry;

typedef struct EntryObj{
    int column;
    double data;
} EntryObj;


typedef struct MatrixObj{
    int size;
    int NNZ;
    List* row;
} MatrixObj;



// newEnrty() (private)
// Returns reference to new Entry object. Initializes column and value fields.
Entry newEntry(int column, double value){
    Entry E = malloc(sizeof(EntryObj));
    assert (E != NULL);
    E->column = column;
    E->data = value;
    return E;
}


// freeEntry() (private)
// Frees heap memory pointed to by *pE, sets *pE to NULL
void freeEntry(Entry* pE){
    if (pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
    }
}


// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    assert (M != NULL);
    M->size = n;
    M->NNZ = 0;
    M->row = malloc( (n+1) * sizeof(List) );
    for (int i = 1; i <= n; i++){
        (M->row)[i] = newList();
    }
    return M;
}


// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if (pM != NULL && *pM != NULL){
        makeZero(*pM);
        for (int i = 1; i <= (*pM)->size; i++){
            freeList( &( ((*pM)->row)[i] ) );
            (*pM)->row[i] = NULL;
        }
        free((*pM)->row);
        free((*pM));
        *pM = NULL;
    }
}



// Access functions

// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");  
        exit(EXIT_FAILURE); 
    }
    return (M->size);
}


// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix reference\n");  
        exit(EXIT_FAILURE); 
    }
    return (M->NNZ);
}


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling equals() on NULL Matrix reference (A)\n");  
        exit(EXIT_FAILURE); 
    }

    if (B == NULL){
        fprintf(stderr, "Matrix Error: calling equals() on NULL Matrix reference (B)\n");  
        exit(EXIT_FAILURE); 
    }

    if (size(A) != size(B)){
        return 0;
    }


    Entry entryA;
    Entry entryB;
    List rowA;
    List rowB;

    for (int i = 1; i <= size(A); i++){
        rowA = (A->row)[i];
        rowB = (B->row)[i];


        if (length(rowA) != length(rowB)){
            return 0;
        }

        if (length(rowA) == 0){
            continue;
        } else {
            while(index(rowA) >= 0 && index(rowB) >= 0){
                entryA = get(rowA);
                entryB = get(rowB);
                if ( (entryA->column) != (entryB->column) ){
                    return 0;
                } else if ( (entryA->data) != (entryB->data)){
                    return 0;
                }

                moveNext(rowA);
                moveNext(rowB);

                if (index(rowA) == -1 && index(rowB) != -1){
                    return 0;
                }
                if (index(rowA) != -1 && index(rowB) == -1){
                    return 0;
                }              
            }
        } 
        
    }
    return 1;

}




// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");  
        exit(EXIT_FAILURE); 
    }

    for (int i = 1; i <= size(M); i++){
        List A = (M->row)[i];
        while(length(A) != 0){
            Entry E = front(A);
            freeEntry(&E);
            deleteFront(A);
        }
    }
    M->NNZ = 0;
    
}


// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");  
        exit(EXIT_FAILURE); 
    }

    if (i < 1 || i > size(M)){
        fprintf(stderr, "Matrix Error: calling makeZero() on a non-exist column\n");
        exit(EXIT_FAILURE);
    }

    if (j < 1 || j > size(M)){
        fprintf(stderr, "Matrix Error: calling makeZero() on a non-exist row\n");
        exit(EXIT_FAILURE);
    }


    if (x != 0){
        bool existed = false;
        List R = (M->row)[i];
        if (length(R) == 0){
            Entry A = newEntry(j, x);
            append(R, A);
            M->NNZ++;
            return;
        }
        for (moveFront(R); index(R) >= 0; moveNext(R)){
            Entry E = get(R);
            if ( (E->column) == j ){
                E->data = x;
                existed = true;
                break;
            }
        }
        if (!existed){
            Entry A = newEntry(j, x);
            bool inserted = false;
            for (moveFront(R); index(R) >= 0; moveNext(R)){
                Entry B = get(R);
                if (j < (B->column) ){
                    insertBefore(R, A);
                    inserted = true;
                    break;
                } 
            }
            if (!inserted){
                append(R, A);
            }
            M->NNZ++;
        }
    } else {  // x == 0
        List R = (M->row)[i];
        for (moveFront(R); index(R) >= 0; moveNext(R)){
            Entry E = get(R);
            if ( (E->column) == j ){
                // free(E);
                freeEntry(&E);
                delete(R);
                M->NNZ--;
                return;
            }
        }
    }
}


// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");  
        exit(EXIT_FAILURE); 
    }

    int n = size(A);
    Matrix result = newMatrix(n);
    // result->NNZ = A->NNZ;
    List std_row;

    for (int i = 1; i <= n; i ++){
        std_row = A->row[i];
        List row = result->row[i];
        // List row = result->row[i];

        for (moveFront(std_row); index(std_row) >= 0; moveNext(std_row)){
            Entry std_entry = get(std_row);
            int column = std_entry->column;
            double data = std_entry->data;
            Entry new = newEntry(column, data);
            append(row, new);
            // changeEntry(result, i, column, data);
        }
    }
    result->NNZ = A->NNZ;
    return result;
}


// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");  
        exit(EXIT_FAILURE); 
    }
    int n = size(A);
    Matrix result = newMatrix(n);
    List std_row;
    List row;

    for (int i = 1; i <= n; i++){
        std_row = A->row[i];
        if (length(std_row) != 0){
            for (moveFront(std_row); index(std_row) >= 0; moveNext(std_row)){
                Entry std_entry = get(std_row);
                int column = std_entry->column;
                double data = std_entry->data;
                Entry E = newEntry(i, data);
                row = result->row[column];
                append(row, E);
                // changeEntry(result, column, i, data);
            }
        }
    }
    result->NNZ = A->NNZ;
    return result;
}


// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");  
        exit(EXIT_FAILURE); 
    }

    int n = size(A);
    Matrix new = newMatrix(n);

    if (x == 0){
        return new;
    }

    List std_row;
    List row;
    for (int i = 1; i <= n; i++){
        std_row = A->row[i];
        row = new->row[i];
        for (moveFront(std_row); index(std_row) >= 0; moveNext(std_row)){
            Entry std_entry = get(std_row);
            int column = std_entry->column;
            double data = std_entry->data;
            double new_data = data * x;
            // changeEntry(new, i, column, new_data);
            Entry E = newEntry(column, new_data);
            append(row, E);
        }
    }
    new->NNZ = A->NNZ;
    return new;
    
}


// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix (A) reference\n");  
        exit(EXIT_FAILURE); 
    }

    if (B == NULL){
        fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix (B) reference\n");  
        exit(EXIT_FAILURE); 
    }

    if ( size(A) != size(B) ){
        fprintf(stderr, "Matrix Error: calling sum() when the sizes of A and B are different\n");  
        exit(EXIT_FAILURE); 
    }

    if (A == B) return scalarMult(2, A);

    int n = size(A);
    List rowA, rowB;
    Matrix result = newMatrix(n);
    Entry A_entry, B_entry;
    int A_column, B_column;
    double new_data;
    Entry E;
    List row;
    int nnz = 0;
    for (int i = 1; i <= n; i++){
        rowA = (A->row)[i];
        rowB = (B->row)[i];
        moveFront(rowA);
        moveFront(rowB);
        while (index(rowA) >= 0 && index(rowB) >= 0){
            A_entry = get(rowA);
            A_column = A_entry->column;
            B_entry = get(rowB);
            B_column = B_entry->column;

            if (A_column < B_column){
                row = result->row[i];
                E = newEntry(A_column, A_entry->data);
                append(row, E); 
                // changeEntry(result, i, A_column, A_entry->data);
                nnz++;
                moveNext(rowA);
            } else if (A_column > B_column){
                row = result->row[i];
                E = newEntry(B_column, B_entry->data);
                append(row, E);
                // changeEntry(result, i, B_column, B_entry->data);
                nnz++;
                moveNext(rowB);
            } else {
                new_data = A_entry->data + B_entry->data;
                if (new_data != 0){
                    row = result->row[i];
                    E = newEntry(A_column, new_data);
                    append(row, E);
                    nnz++;
                }
                // changeEntry(result, i, A_column, new_data);
                moveNext(rowA);
                moveNext(rowB);
            }
        }
        while (index(rowA) >= 0){
            A_entry = get(rowA);

            A_column = A_entry->column;
            row = result->row[i];
            E = newEntry(A_column, A_entry->data);
            append(row, E);
            nnz++;
            // changeEntry(result, i, A_column, A_entry->data);
            moveNext(rowA);
        }

        while (index(rowB) >= 0){
            B_entry = get(rowB);

            B_column = B_entry->column;
            row = result->row[i];
            E = newEntry(B_column, B_entry->data);
            append(row, E);
            nnz++;

            // changeEntry(result, i, B_column, B_entry->data);
            moveNext(rowB);
        }
    }

    result->NNZ = nnz;

    return result;
}


// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix (A) reference\n");  
        exit(EXIT_FAILURE); 
    }

    if (B == NULL){
        fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix (B) reference\n");  
        exit(EXIT_FAILURE); 
    }


    if ( size(A) != size(B) ){
        fprintf(stderr, "Matrix Error: calling diff() when the sizes of A and B are different\n");  
        exit(EXIT_FAILURE); 
    }
    Matrix C = scalarMult(-1, B);
    Matrix result = sum(A, C);
    freeMatrix(&C);
    return result;
}



// vectorDot()
// returns the result of the product of two vectors
// private helper function for product()
double vectorDot(List P, List Q){
    if (P == NULL){
        fprintf(stderr, "Matrix Helper Function Error: calling vectorDot() on NULL List (A) reference\n");  
        exit(EXIT_FAILURE); 
    }

    if (Q == NULL){
        fprintf(stderr, "Matrix Helper Function Error: calling vectorDot() on NULL List (B) reference\n");  
        exit(EXIT_FAILURE); 
    }

    // if (length(P) != length(Q)){
    //     fprintf(stderr, "Matrix Helper Function Error: calling vectorDot() on two vectors with different length\n");  
    //     exit(EXIT_FAILURE); 
    // }

    if (length(P) == 0 || length(Q) == 0){
        return 0;
    }

    Entry Pstd_entry;
    Entry Qstd_entry;
    int pcolumn;
    int qcolumn;
    double new_data = 0;
    moveFront(Q);
    moveFront(P);


    while (index(P) >= 0 && index(Q) >=0){
        Pstd_entry = get(P);
        Qstd_entry = get(Q);

        pcolumn = Pstd_entry->column;
        qcolumn = Qstd_entry->column;

        if (pcolumn < qcolumn){
            // new_data += (Pstd_entry->data) * (0);
            moveNext(P);
        } else if (pcolumn > qcolumn){
            // new_data += (0) * (Qstd_entry->data);
            moveNext(Q);
        } else {
            new_data += (Pstd_entry->data) * (Qstd_entry->data);
            moveNext(P);
            moveNext(Q);
        }
    }

    return new_data;
}


// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling product() on NULL Matrix (A) reference\n");  
        exit(EXIT_FAILURE); 
    }

    if (B == NULL){
        fprintf(stderr, "Matrix Error: calling product() on NULL Matrix (B) reference\n");  
        exit(EXIT_FAILURE); 
    }

    if ( size(A) != size(B) ){
        fprintf(stderr, "Matrix Error: calling product() when the sizes of A and B are different\n");  
        exit(EXIT_FAILURE); 
    }


    int n = size(A);
    Matrix new = newMatrix(n);
    List Astd_row;
    List Bstd_column;
    double new_data;
    Entry E;
    List row;
    int nnz = 0;

    Matrix T = transpose(B);
    for (int i = 1; i <= n; i++){
        Astd_row = A->row[i];
        row = new->row[i];
        if (length(Astd_row) != 0){
            for (int j = 1; j <= n; j++){
                Bstd_column = T->row[j];
                new_data = vectorDot(Astd_row, Bstd_column);
                if (new_data != 0){
                    E = newEntry(j, new_data);
                    append(row, E);
                    nnz++;
                }
                // changeEntry(new, i, j, new_data);
            }            
        }
    }
    freeMatrix(&T);
    new->NNZ = nnz;
    return new;
}



// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");  
        exit(EXIT_FAILURE); 
    }


    for (int i = 1; i<=size(M); i++){
        List A = M->row[i];
        if (length(A) != 0){
            fprintf(out, "%d: ", i);
            for (moveFront(A); index(A) >= 0; moveNext(A)){
                Entry E = get(A);
                fprintf(out, "(%d, %.1f) ", E->column, E->data);
            }
            fprintf(out, "\n");
        }
    }
}

