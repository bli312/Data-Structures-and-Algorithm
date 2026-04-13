/***
 * Leo Li
 * 2024 Fall UCSC CSE101 PA1
 * ListTest.c
 * Test for List ADT
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

int main(int argc, char *argv[]) {

  List A = newList();
  List B = newList();
  List C = NULL;
  List D = newList();
  List E = newList();
  int i;

  for (i = 1; i <= 10; i++) {
    append(A, i);
    prepend(B, i);
  }

  printList(stdout, A);
  printf("\n");
  printList(stdout, B);
  printf("\n");


  // printf("Here is teh front element of A:");
  // printf("%d", front(A));

  moveFront(A);
  moveBack(B);
  printf("Here is the cursor element in A now: %d and here is the index: %d, the data should be euqal to the front data %d\n", get(A), index(A), front(A));
  printf("Here is the cursor element in B now: %d and here is the index: %d, the data should be euqal to the back data %d\n", get(B), index(B), back(B));


  printf("\n");
  printf("Going A from front to back and going B from back to front, compare the cursor data\n");
  for (moveFront(A); index(A) >=0; moveNext(A)){
    printf("%s ", get(A) == get(B) ? "equals " : "unequal ");
    movePrev(B);
  }
  
  printf("\n");   // A: cursor at the end; B: cursor at the front
  printf("\n");

  printf("Now here is the cursor index of A: %d and B: %d\n", index(A), index(B));

  moveFront(A);
  moveBack(B);
  printf("Now here is the cursor element of A: %d and B: %d after moving the cursor back\n", get(A), get(B));

  printf("\n");


  for (i = -5; i < 0; i++){
    insertBefore(A, i);
    printf("here is the element %d inserted before the cursor %d, with the index: %d in A\n", i, get(A), index(A));
    moveNext(A);

  }

  printf("\n");

  for (i = -5; i < 0; i++){
    printf("here is the element %d inserted after the cursor %d, with the index: %d in B\n", i, get(B), index(B));
    insertAfter(B, i);
    movePrev(B);

  }

// B: 10 9 8 7 6 5 -1 4 -2 3 -3 2 -4 1 -5

  printf("\n");

  C = copyList(A);
  printf("%s\n", equals(A, B) ? "true" : "false");
  printf("%s\n", equals(B, C) ? "true" : "false");
  printf("%s\n", equals(C, A) ? "true" : "false");


  for (moveBack(B); index(B) >= 0; movePrev(B)){
    append(D, get(B));
  }

  printList(stdout, D);

  printf("%s\n", equals(D, A) ? "true" : "false");
  printf("%s\n", equals(A, D) ? "trueeeeee" : "falseeeeee");
  printf("%s\n", equals(C, D) ? "trueeeeee" : "falseeeeee");
  printf("\n");
  
// D: -5 1 -4 2 -3 3 -2 4 -1 5 6 7 8 9 10

  moveBack(D);
  deleteFront(D);
  printList(stdout, D);
  printf("\n");

  // deleteBack(D);
  // printList(stdout, D);

  delete(D);
  printList(stdout, D);
  printf("\n");
  

  printf("here is A\n");
  printList(stdout, A);
  printf("here is the length of A: %d\n", length(A));
  printf("\n");

  printf("here is B\n");
  printList(stdout, B);
  printf("here is the length of B: %d\n", length(B));
  printf("\n");

  printf("here is C\n");
  printList(stdout, C);
  printf("here is the length of C: %d\n", length(C));
  printf("\n");


  printf("here is D\n");
  printList(stdout, D);
  printf("here is the length of D: %d\n", length(D));
  printf("\n");


  freeList(&E);
  E = concatList(A, B);

  printf("here is E (concatList AB)\n");
  printList(stdout, E);
  printf("here is the length of E: %d\n", length(E));
  printf("\n");

  clear(A);

  printf("here is A after calling clear()\n");
  printList(stdout, A);
  printf("here is the length of A: %d\n", length(A));
  printf("\n");

  // moveFront(B);
  // delete(B);
  // insertAfter(B, 3);
  

  freeList(&A);
  freeList(&B);
  freeList(&C);
  freeList(&D);
  freeList(&E);

  // clear(A);
  // insertBefore(A, 3);
  // printf("hello");


  return (0);
}

/*
Output of this program:

1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
Here is the cursor element in A now: 1 and here is the index: 0, the data should be euqal to the front data 1
Here is the cursor element in B now: 1 and here is the index: 9, the data should be euqal to the back data 1

Going A from front to back and going B from back to front, compare the cursor data
equals equals equals equals equals equals equals equals equals

Now here is the cursor index of A: -1 and B: -1
Now here is the cursor element of A: 1 and B: 1 after moving the cursor back

here is the element -5 inserted before the cursor 1, with the index: 1 in A
here is the element -4 inserted before the cursor 2, with the index: 3 in A
here is the element -3 inserted before the cursor 3, with the index: 5 in A
here is the element -2 inserted before the cursor 4, with the index: 7 in A
here is the element -1 inserted before the cursor 5, with the index: 9 in A

here is the element -5 inserted after the cursor 1, with the index: 9 in B
here is the element -4 inserted after the cursor 2, with the index: 8 in B
here is the element -3 inserted after the cursor 3, with the index: 7 in B
here is the element -2 inserted after the cursor 4, with the index: 6 in B
here is the element -1 inserted after the cursor 5, with the index: 5 in B

false
false
true
-5 1 -4 2 -3 3 -2 4 -1 5 6 7 8 9 10
true
trueeeeee
trueeeeee

1 -4 2 -3 3 -2 4 -1 5 6 7 8 9 10

1 -4 2 -3 3 -2 4 -1 5 6 7 8 9

here is A
-5 1 -4 2 -3 3 -2 4 -1 5 6 7 8 9 10
here is the length of A: 15

here is B
10 9 8 7 6 5 -1 4 -2 3 -3 2 -4 1 -5 
here is the length of B: 15

here is C
-5 1 -4 2 -3 3 -2 4 -1 5 6 7 8 9 10
here is the length of C: 15

here is D
1 -4 2 -3 3 -2 4 -1 5 6 7 8 9
here is the length of D: 13

here is E (concatList AB)
-5 1 -4 2 -3 3 -2 4 -1 5 6 7 8 9 10 10 9 8 7 6 5 -1 4 -2 3 -3 2 -4 1 -5
here is the length of E: 30

here is A after calling clear()

here is the length of A: 0
*/
