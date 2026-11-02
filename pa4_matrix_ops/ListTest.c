/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA4
 * ListTest.c
 * Test client for List ADT
 ***/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char *argv[]) {

  List A = newList();
  List B = newList();
  List D = newList();
  int i;


  int hello[] = {1,2,3,4,5,6,7,8,9,10};

  

  for (i = 0; i <= 9; i++) {
    append(A, &hello[i]);
    prepend(B, &hello[i]);
  }


  for (moveFront(A); index(A) >=0; moveNext(A)){
   printf("here is the %dth element in AAAAA: %d\n", index(A), *(int*)get(A));
  }



  moveFront(A);
  moveBack(B);
  printf("Here is the cursor element data stored in the address (pointer) in A now: %d and here is the index: %d, the data should be euqal to the front data %d\n", *(int*)get(A), index(A), *(int*)front(A));
  printf("Here is the cursor element data stored in the address (pointer) in B now: %d and here is the index: %d, the data should be euqal to the back data %d\n", *(int*)get(B), index(B), *(int*)back(B));


  printf("\n");
  printf("Going A from front to back and going B from back to front, compare the cursor data\n");
  for (moveFront(A); index(A) >=0; moveNext(A)){
    printf("%s ", *(int*)get(A) == *(int*)get(B) ? "equals!! " : "unequal ");
    movePrev(B);
  }
  
  printf("\n");   // A: cursor at the end; B: cursor at the front
  printf("\n");

  printf("Now here is the cursor index of A: %d and B: %d\n", index(A), index(B));

  moveFront(A);
  moveBack(B);
  printf("Now here is the cursor element of A: %d and B: %d after moving the cursor back\n", *(int*)get(A), *(int*)get(B));

  printf("\n");


  int negative[] = {-5, -4, -3, -2, -1};


  for (i = 0; i <= 4; i++){
    insertBefore(A, &negative[i]);
    printf("here is the element %d inserted before the cursor %d, with the index: %d in A\n", i, *(int*)get(A), index(A));
    moveNext(A);

  }

  printf("\n");

  for (i = 0; i <= 4; i++){
    printf("here is the element %d inserted after the cursor %d, with the index: %d in B\n", i, *(int*)get(B), index(B));
    insertAfter(B, &negative[i]);
    movePrev(B);

  }

// B: 10 9 8 7 6 5 -1 4 -2 3 -3 2 -4 1 -5

  printf("\n");

  for (moveBack(B); index(B) >= 0; movePrev(B)){
    append(D, get(B));
  }


// D: -5 1 -4 2 -3 3 -2 4 -1 5 6 7 8 9 10

  moveBack(D);
  deleteFront(D);
  printf("\n");
  delete(D);
  deleteBack(D);
  printf("the index of D after calling delete: %d\n", index(D));
  printf("\n");
  

  printf("here is A\n");
  for (moveFront(A); index(A) >= 0; moveNext(A)){
   printf("%d ", *(int*)get(A));
  }
  printf("\n");
  printf("here is the length of A: %d\n", length(A));
  printf("\n");

  printf("here is B\n");
  for (moveFront(B); index(B) >= 0; moveNext(B)){
   printf("%d ", *(int*)get(B));
  }
  printf("\n");
  printf("here is the length of B: %d\n", length(B));
  printf("\n");


  printf("here is D\n");
  for (moveFront(D); index(D) >= 0; moveNext(D)){
   printf("%d ", *(int*)get(D));
  }
  printf("\n");

  printf("here is the length of D: %d\n", length(D));
  printf("\n");

  clear(A);

  printf("here is A after calling clear()\n");
  for (moveFront(A); index(A) >= 0; moveNext(A)){
   printf("%d ", *(int*)get(A));
  }

  printf("\n");
  printf("here is the length of A: %d\n", length(A));
  printf("\n");



  freeList(&A);
  freeList(&B);
  freeList(&D);

  return (0);
}

/*
Output of this program:

here is the 0th element in AAAAA: 1
here is the 1th element in AAAAA: 2
here is the 2th element in AAAAA: 3
here is the 3th element in AAAAA: 4
here is the 4th element in AAAAA: 5
here is the 5th element in AAAAA: 6
here is the 6th element in AAAAA: 7
here is the 7th element in AAAAA: 8
here is the 8th element in AAAAA: 9
here is the 9th element in AAAAA: 10
Here is the cursor element data stored in the address (pointer) in A now: 1 and here is the index: 0, the data should be euqal to the front data 1
Here is the cursor element data stored in the address (pointer) in B now: 1 and here is the index: 9, the data should be euqal to the back data 1

Going A from front to back and going B from back to front, compare the cursor data
equals!!  equals!!  equals!!  equals!!  equals!!  equals!!  equals!!  equals!!  equals!!  equals!!  

Now here is the cursor index of A: -1 and B: -1
Now here is the cursor element of A: 1 and B: 1 after moving the cursor back

here is the element 0 inserted before the cursor 1, with the index: 1 in A
here is the element 1 inserted before the cursor 2, with the index: 3 in A
here is the element 2 inserted before the cursor 3, with the index: 5 in A
here is the element 3 inserted before the cursor 4, with the index: 7 in A
here is the element 4 inserted before the cursor 5, with the index: 9 in A

here is the element 0 inserted after the cursor 1, with the index: 9 in B
here is the element 1 inserted after the cursor 2, with the index: 8 in B
here is the element 2 inserted after the cursor 3, with the index: 7 in B
here is the element 3 inserted after the cursor 4, with the index: 6 in B
here is the element 4 inserted after the cursor 5, with the index: 5 in B


the index of D after calling delete: -1

here is A
-5 1 -4 2 -3 3 -2 4 -1 5 6 7 8 9 10 
here is the length of A: 15

here is B
10 9 8 7 6 5 -1 4 -2 3 -3 2 -4 1 -5 
here is the length of B: 15

here is D
1 -4 2 -3 3 -2 4 -1 5 6 7 8 
here is the length of D: 12

here is A after calling clear()

here is the length of A: 0
*/
