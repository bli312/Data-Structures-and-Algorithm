/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA4
 * MatrixTest.c
 * Test client for Matrix ADT
 ***/





// //-----------------------------------------------------------------------------
// //  MatrixClient.c 
// //  A test client for the Matrix ADT
// //-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
#include<assert.h>
     
int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C = newMatrix(n);
   Matrix D, E, F, G, H, I, J, K, L;
//    Matrix H;
//    Matrix F;
//    Matrix D;
//    Matrix E;
//    Matrix G;

   changeEntry(A, 1,1,5); 
   changeEntry(A, 1,2,7);
   changeEntry(A, 1,3,2); 
   changeEntry(A, 2,1,3);
   changeEntry(A, 2,2,9);
   changeEntry(A, 2,3,4);
   changeEntry(A, 3,1,10.8); 
   changeEntry(A, 3,2,2.9);
   changeEntry(A, 3,3,5.7);


   changeEntry(B, 1,1,3);
   changeEntry(B, 1,2,0); 
   changeEntry(B, 1,3,0);
   changeEntry(B, 2,1,0);
   changeEntry(B, 2,2,7); 
   changeEntry(B, 2,3,0);
   changeEntry(B, 3,1,0);
   changeEntry(B, 3,2,0); 
   changeEntry(B, 3,3,2.1);


   changeEntry(C, 1,1,0);
   changeEntry(C, 1,2,0); 
   changeEntry(C, 1,3,0);
   changeEntry(C, 2,1,0);
   changeEntry(C, 2,2,0); 
   changeEntry(C, 2,3,0);
   changeEntry(C, 3,1,0);
   changeEntry(C, 3,2,0); 
   changeEntry(C, 3,3,0);


   printf("The size of A is: %d, the NNZ in A is %d, This is A:\n",size(A), NNZ(A));
   assert(size(A) == n);
   assert(NNZ(A) == 9);
   printMatrix(stdout, A);
   printf("\n");

   printf("The size of B is: %d, the NNZ in B is %d, This is B:\n",size(B), NNZ(B));
   assert(size(B) == 100000);
   assert(NNZ(B) == 3);
   printMatrix(stdout, B);
   printf("\n");

   printf("The size of C is: %d, the NNZ in C is %d, This is C:\n",size(C), NNZ(C));
   assert(size(C) == 100000);
   assert(NNZ(C) == 0);
   printMatrix(stdout, C);
   printf("\n");


   D = sum(A, B);
   printf("The size of A+B is: %d, the NNZ in A+B is %d, This is A+B:\n",size(D), NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = sum(A, C);
   printf("The size of A+C is: %d, the NNZ in A+C is %d, This is A+C:\n",size(E), NNZ(E));
   printMatrix(stdout, E);
   assert(equals(A, E));
   printf("\n");


   F = diff(A, A);
   printf("The size of A-A is: %d, the NNZ in A-A is %d, This is A-A:\n",size(F), NNZ(F));
   printMatrix(stdout, F);
   assert(equals(F, C));
   printf("\n");


   G = diff(B, A);
   printf("The size of B-A is: %d, the NNZ in B-A is %d, This is B-A:\n",size(G), NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = diff(A, C);
   printf("The size of A-C is: %d, the NNZ in A-C is %d, This is A-C:\n",size(H), NNZ(H));
   printMatrix(stdout, H);
   printf("\n");
   assert(equals(H, A));
   assert(equals(C, F));

   makeZero(H);
   printf("The size of A-C(makezero) is: %d, the NNZ in A-C(makezero) is %d, This is A-C(makezero):\n",size(H), NNZ(H));
   printMatrix(stdout, H);
   printf("\n");
   assert(equals(C, H));

   I = copy(A);
   printf("The size of the copy of A is: %d, the NNZ in the copy of A is %d, This is the copy of A:\n",size(I), NNZ(I));
   printMatrix(stdout, I);
   printf("\n");
   assert(equals(A, I));
   
   J = transpose(A);
   printf("The size of A(transpose) is: %d, the NNZ in A(transpose) is %d, This is A(transpose):\n",size(J), NNZ(J));
   printMatrix(stdout, J);
   printf("\n");
   Matrix X = transpose(B);
   Matrix Y = transpose(J);
   assert(equals(X, B));
   assert(equals(Y, A));


   K = product(A, B);
   printf("The size of A*B is: %d, the NNZ in A*B is %d, This is A*B:\n",size(K), NNZ(K));
   assert(NNZ(A) == NNZ(K));
   printMatrix(stdout, K);
   printf("\n");

   L = scalarMult(1.1, B);
   printf("The size of 1.1*B is: %d, the NNZ in 1.1*B is %d, This is 1.1*B:\n",size(L), NNZ(L));
   assert(NNZ(L) == NNZ(B));
   printMatrix(stdout, L);
   printf("\n");


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
   freeMatrix(&K);
   freeMatrix(&L);
   freeMatrix(&X);
   freeMatrix(&Y);


   return EXIT_SUCCESS;
}

/*
Output of this program:
The size of A is: 100000, the NNZ in A is 9, This is A:
1: (1, 5.0) (2, 7.0) (3, 2.0) 
2: (1, 3.0) (2, 9.0) (3, 4.0) 
3: (1, 10.8) (2, 2.9) (3, 5.7) 

The size of B is: 100000, the NNZ in B is 3, This is B:
1: (1, 3.0) 
2: (2, 7.0) 
3: (3, 2.1) 

The size of C is: 100000, the NNZ in C is 0, This is C:

The size of A+B is: 100000, the NNZ in A+B is 9, This is A+B:
1: (1, 8.0) (2, 7.0) (3, 2.0) 
2: (1, 3.0) (2, 16.0) (3, 4.0) 
3: (1, 10.8) (2, 2.9) (3, 7.8) 

The size of A+C is: 100000, the NNZ in A+C is 9, This is A+C:
1: (1, 5.0) (2, 7.0) (3, 2.0) 
2: (1, 3.0) (2, 9.0) (3, 4.0) 
3: (1, 10.8) (2, 2.9) (3, 5.7) 

The size of A-A is: 100000, the NNZ in A-A is 0, This is A-A:

The size of B-A is: 100000, the NNZ in B-A is 9, This is B-A:
1: (1, -2.0) (2, -7.0) (3, -2.0) 
2: (1, -3.0) (2, -2.0) (3, -4.0) 
3: (1, -10.8) (2, -2.9) (3, -3.6) 

The size of A-C is: 100000, the NNZ in A-C is 9, This is A-C:
1: (1, 5.0) (2, 7.0) (3, 2.0) 
2: (1, 3.0) (2, 9.0) (3, 4.0) 
3: (1, 10.8) (2, 2.9) (3, 5.7) 

The size of A-C(makezero) is: 100000, the NNZ in A-C(makezero) is 0, This is A-C(makezero):

The size of the copy of A is: 100000, the NNZ in the copy of A is 9, This is the copy of A:
1: (1, 5.0) (2, 7.0) (3, 2.0) 
2: (1, 3.0) (2, 9.0) (3, 4.0) 
3: (1, 10.8) (2, 2.9) (3, 5.7) 

The size of A(transpose) is: 100000, the NNZ in A(transpose) is 9, This is A(transpose):
1: (1, 5.0) (2, 3.0) (3, 10.8) 
2: (1, 7.0) (2, 9.0) (3, 2.9) 
3: (1, 2.0) (2, 4.0) (3, 5.7) 

The size of A*B is: 100000, the NNZ in A*B is 9, This is A*B:
1: (1, 15.0) (2, 49.0) (3, 4.2) 
2: (1, 9.0) (2, 63.0) (3, 8.4) 
3: (1, 32.4) (2, 20.3) (3, 12.0) 

The size of 1.1*B is: 100000, the NNZ in 1.1*B is 3, This is 1.1*B:
1: (1, 3.3) 
2: (2, 7.7) 
3: (3, 2.3) 
*/


