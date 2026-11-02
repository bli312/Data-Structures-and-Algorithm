/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA5
 * List.cpp
 * Implementation file for List ADT
 ***/


#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include <limits>

#define MAX std::numeric_limits<int>::max()
#define MIN std::numeric_limits<int>::min()

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.

List::List(){
    frontDummy = new Node(MIN);
    backDummy = new Node(MAX);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

}

List::List(const List& L){
    frontDummy = new Node(MIN);
    backDummy = new Node(MAX);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;


    if (L.length() != 0){
        Node* N = L.frontDummy;
        N = N->next;
        while(N!=L.backDummy){
            insertBefore(N->data);
            N = N->next; 
        }
    }

    moveFront();

}


List::~List(){
    this->clear();
    delete frontDummy;
    delete backDummy;
    // return;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if (length() == 0){
        throw std::length_error("List: front(): empty List");
    }

    return (frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if (length() == 0){
        throw std::length_error("List: back(): empty List");
    }

    return (backDummy->prev->data);
}


// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return (pos_cursor);
}


// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if (position() >= length()){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return (afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if (position() <= 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return (beforeCursor->data);
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while(length() > 0){
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    beforeCursor= backDummy->prev;
    afterCursor= backDummy;
    pos_cursor = length();
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if (position() >= length()){
        throw std::range_error("List: moveNext(): cursor at back");
    }

    beforeCursor= beforeCursor->next;
    afterCursor= afterCursor->next;
    pos_cursor ++;

    return beforeCursor->data;

}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if (position() <= 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }

    beforeCursor=beforeCursor->prev;
    afterCursor=afterCursor->prev;
    pos_cursor --;

    return (afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* node = new Node(x);

    afterCursor->prev = node;
    node->next = afterCursor;
    afterCursor = node;
    node->prev = beforeCursor;
    beforeCursor->next = node;

    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* node = new Node(x);

    node->prev=beforeCursor;
    node->next=afterCursor;
    beforeCursor->next=node;
    afterCursor->prev=node;
    beforeCursor=node;

    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if (position() >= length()){
        throw std::range_error("List: setAfter(): cursor at back");
    }

    afterCursor->data = x;

}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if (position() <= 0){
        throw std::range_error("List: setBefore(): cursor at front");
    }

    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if (position() >= length()){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }

    Node* temp = afterCursor;

    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = afterCursor->next;

    delete temp;

    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if (position() <= 0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }

    Node* temp = beforeCursor;

    beforeCursor->prev->next = afterCursor;
    afterCursor->prev = beforeCursor->prev;
    beforeCursor=beforeCursor->prev;

    delete temp;

    num_elements--;
    pos_cursor--;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    while (pos_cursor != length()){
        if (peekNext() == x){
            moveNext();
            return position();
        }
        moveNext();
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    while (pos_cursor != 0){
        if (peekPrev() == x){
            movePrev();
            return position();
        }
        movePrev();
    }
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    Node* cursor = frontDummy->next;
    Node* to_delete;
    Node* savebefore = beforeCursor;
    Node* saveafter = afterCursor;
    int current_pos = 0;
    int count = 0;
    while (cursor != backDummy){
        count++;
        current_pos = count;   // the pos of compare
        
        Node* compare = cursor->next;
        while (compare != backDummy){
            if (compare->data == cursor->data){
                to_delete = compare;
                compare->prev->next = compare->next;
                compare->next->prev = compare->prev;

                if (to_delete == savebefore){
                    beforeCursor = to_delete->prev;
                }

                if (to_delete == saveafter){
                    afterCursor = to_delete->next;
                }

                compare = compare->next;
                delete to_delete;
                num_elements--;

                if (current_pos < pos_cursor){
                    pos_cursor--;
                }
            } else {
                compare = compare->next;
                current_pos++;
            }

        }
        cursor = cursor->next;

    }
    // std::cout << "here is the backdummy: "<<backDummy->data <<std::endl;
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List result;

    Node* M = this->frontDummy->next;
    Node* N = L.frontDummy->next;

    while (M != backDummy){
        result.insertBefore(M->data);
        M = M->next;
    }

    while (N != L.backDummy){
        result.insertBefore(N->data);
        N = N->next;
    }

    result.moveFront();

    return result;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "(";

    for (N=frontDummy->next; N!=backDummy; N=N->next){
        s += std::to_string(N->data);
        if (N->next != backDummy){
            s += ", ";
        }
    }

    s += ")";

    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eq = false;
    Node* M = nullptr;
    Node* N = nullptr;

    eq = (this->num_elements == R.num_elements);
    M = this->frontDummy->next;
    N = R.frontDummy->next;

    while (eq && M!=backDummy){
        eq = (M->data == N->data);
        M = M->next;
        N = N->next;
    }

    return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if (this != &L){
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);

    }

    return *this;
}