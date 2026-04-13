/***
 * Leo Li
 * 2024 Fall UCSC CSE101 PA1
 * List.c
 * Implementation file for List ADT
 ***/


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

// Structs

// Private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
    Node before;
    int data;
    Node next;
    /* data */
} NodeObj;

typedef struct ListObj{
    Node front;
    Node cursor;
    Node back;
    int index;
    int length;
} ListObj;

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    assert (N != NULL);
    N -> before = NULL;
    N -> data = data;
    N -> next = NULL;
    return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL
void freeNode(Node* pN){
    if (pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}


// Constructors-Destructor
// Creates and returns a new empty list
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    assert (L != NULL);
    L -> front = NULL;
    L -> cursor = NULL;
    L -> back = NULL;
    L -> index = -1;
    L -> length = 0;
    return (L);
}


// Frees all heap memory associated with *pL,
// and sets *pL to NULL

void freeList (List* pL){
    if (pL != NULL && *pL != NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access functions

// Returns the number of elements in L.
int length(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
}


// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
        if (L == NULL){
        fprintf(stderr, "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->index);
}


// Returns front element of L. Pre: length() > 0
int front(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0){
        fprintf(stderr, "List Error: calling front() on an empty List\n");
        exit(EXIT_FAILURE);       
    }
    return(L->front->data);
}

// Returns back element of L. Pre: length() > 0
int back(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0){
        fprintf(stderr, "List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}

// Returns cursor element of L. Pre: length() > 0, index >= 0
int get(List L){
    if (L == NULL){
        fprintf(stderr, "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length <= 0){
        fprintf(stderr, "List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    if (L->index < 0){
        fprintf(stderr, "List Error: calling get() on a List without a cursor\n");
        exit(EXIT_FAILURE);        
    }
    return(L->cursor->data);
}


// Returns true iff Lists A and B contain the same
// sequence of elements, returns false otherwise.
bool equals(List A, List B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    bool eq;
    Node N, M;

    eq = (A->length == B->length);
    N = A->front;
    M = B->front;
    while (eq && N != NULL){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }

    return eq;
}


// Manipulation procedures


// Resets L to its original empty state.
void clear(List L){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    L -> cursor = NULL;
    L -> index = -1;
    while(L->length != 0){
        deleteFront(L);
    }

    L->back = NULL;
    L->front = NULL;
}


// Overwrites the cursor element's data with x.
// Pre: length()>0, index >= 0.
void set(List L, int x){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    (L->cursor->data) = x;

}


// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if ( L->length == 0 ){
        fprintf(stderr, "List Error: calling moveFront() on an empty List\n");
        exit(EXIT_FAILURE);      
    }

    L->cursor = L->front;
    L->index = 0;

}


// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if ( L->length == 0 ){
        fprintf(stderr, "List Error: calling moveBack() on an empty List\n");
        exit(EXIT_FAILURE);      
    }
    L->cursor = L->back;
    L->index = (L->length)-1;
}


// If cursor is defined and not at fornt, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if ((L->cursor != NULL) && (L->front != L->cursor)){
        L->cursor = L->cursor->before;
        L->index --;
        return;
    }

    if ((L->cursor != NULL) && (L->front == L->cursor)){
        L->cursor = NULL;
        L->index = -1;
    }
}


// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if ((L->cursor != NULL) && (L->back != L->cursor)){
        L->cursor = L->cursor->next;
        L->index ++;
        return;
    }

    if ((L->cursor != NULL) && (L->back == L->cursor)){
        L->cursor = NULL;
        L->index = -1;
    }
}



// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x){  
    if ( L == NULL){
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    if (L->length == 0){
        L ->front = N;
        L ->back = N;
    } else {
        N->next = L->front;
        L->front->before = N;
        L->front = N;
    }

    if (L->cursor != NULL){
        L->index++;
    }

    L->length++;
}



// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x){  
    if ( L == NULL){
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    if (L->length == 0){
        L -> front = N;
        L -> back = N;
    } else {
        L->back->next = N;
        N->before = L->back;
        L->back = N;
    }
    L->length++;
}


// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if ( L->length <= 0){
        fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    if ( L->index == -1){
        fprintf(stderr, "List Error: calling insertBefore() on a List without cursor\n");
        exit(EXIT_FAILURE);
    }


    if( (L->cursor) == (L->front) ){
        prepend(L, x);
    } else {
        Node N = newNode(x);
        N->before = L->cursor->before;
        N->next = L->cursor;
        L->cursor->before->next = N;
        L->cursor->before = N;
        L->length++;

        if (L->cursor != NULL){
        L->index++;
        }
    }

}



// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if ( L->length <= 0){
        fprintf(stderr, "List Error: calling insertAfter() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    if ( L->index == -1){
        fprintf(stderr, "List Error: calling insertAfter() on a List without cursor\n");
        exit(EXIT_FAILURE);
    }



    if( (L->cursor) == (L->back) ){
        append(L, x);
    } else {
        Node N = newNode(x);
        L->cursor->next->before = N;
        N->next = L->cursor->next;
        L->cursor->next = N;
        N->before = L->cursor;
        L->length++;
    }

}

// Delete the front element. Pre: length()>0
void deleteFront(List L){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if ( L->length <= 0){
        fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    Node N = NULL;
    N = L->front;

    if (L->front == L->cursor){
        L->cursor = NULL;
        L->index = -1;
    }

    if (L->length>1){
        L->front = L->front->next;
        L->front->before = NULL;
    } else {
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
    }

    if (L->index > -1){
        L->index --;
    }
    L->length--;
    freeNode(&N);
}


// Delete the back element. Pre: length()>0
void deleteBack(List L){
    if ( L == NULL){
        fprintf(stderr,"List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if ( L->length <= 0){
        fprintf(stderr,"List Error: calling deleteBack() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    Node N = NULL;
    N = L->back;

    if (L->back == L->cursor){
        L->cursor = NULL;
        L->index = -1;
    }

    if (L->length>1){
        L->back = L->back->before;
        L->back->next = NULL;

    } else {
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
    }
    L->length--;
    freeNode(&N);
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
    if ( L == NULL){
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if ( L->length <= 0){
        fprintf(stderr, "List Error: calling delete() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    if ( L->index == -1){
        fprintf(stderr, "List Error: calling delete() on a List without cursor\n");
        exit(EXIT_FAILURE);
    }

    if (L->index == 0){
        deleteFront(L);
        L->index = -1;
        L->cursor = NULL;
    } else if ( (L->index) == ( (L->length)-1) ){
        deleteBack(L);
        L->index = -1;
        L->cursor = NULL;
    } else {
        Node N = NULL;
        N = L->cursor;
        L->cursor->before->next = L->cursor->next;
        L->cursor->next->before = L->cursor->before;

        L->cursor = NULL;
        L->index = -1;

        freeNode(&N);
        L->length--;

    }

}



// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
    Node N = NULL;
    if ( L == NULL){
        fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    for (N = L->front; N != NULL; N = N->next){
        fprintf(out, "%d ", N->data);
    }
    fprintf(stdout, "\n");
}


// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    List nL = newList();
    Node N = NULL;
    for (N = L->front; N != NULL; N = N->next){
        append(nL, N->data);
    }
    return nL;
}



// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B){
    List nL = newList();
    Node N = NULL;
    Node M = NULL;
    for (N = A->front; N != NULL; N = N->next){
        append(nL, N->data);
    }

    for (M = B->front; M != NULL; M = M->next){
        append(nL, M->data);
    }

    return nL;
}