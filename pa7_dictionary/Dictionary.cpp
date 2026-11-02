/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA7
 * Dictionary.cpp
 * Implementation file for Dictionary ADT
 ***/


#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
#include <limits>

#define MAX std::numeric_limits<int>::max()


Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}


// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if (R != nil){
        inOrderString(s, R->left);
        // s.append(R->key + " : " + std::to_string(R->val) + " \n");
        s += (R->key + " : " + std::to_string(R->val) + "\n");
        inOrderString(s, R->right);
    }

}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R != nil){
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if (R != nil){
        if (R == N){
            return;
        }
        this->setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if (R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        num_pairs--;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if (R == nil){
        return R;
    }

    if (k == R->key){
        return R;
    }

    if (k > R->key){
        return search(R->right, k);
    } else {
        return search(R->left, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if (R == nil){
        return R;
    }

    while (R->left != nil){
        R = R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if (R == nil){
        return R;
    }

    while (R->right != nil){
        R = R->right;
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if (N == nil){
        return N;
    }

    if (N->right != nil){
        return findMin(N->right);
    }

    Node* M = N->parent;
    while (M != nil && N == M->right){
        N = M;
        M = M->parent;
    }

    return M;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if (N == nil){
        return N;
    }

    if (N->left != nil){
        return findMax(N->left);
    }

    Node* M = N->parent;
    while (M != nil && N == M->left){
        N = M;
        M = M->parent;
    }

    return M;
}



// Class Constructors & Destructors ----------------------------------------

Dictionary::Dictionary(){
    nil = new Node("AAA", MAX);
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("AAA", MAX);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary(){
    this->clear();
    delete nil;
}



// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    return ( search(root, k) != nil );
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if (!contains(k)){
        throw std::logic_error ("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    Node* M = search(root, k);
    return M->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    return (current != nil && current != nullptr);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if (!hasCurrent()){
        throw std::logic_error ("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if (!hasCurrent()){
        throw std::logic_error ("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    current = nil;
    root = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    if (contains(k)){
        getValue(k) = v;
        return;
    } else {
        Node* y = nil;
        Node* x = root;
        Node* z = new Node(k, v);
        z->parent = nil;
        z->left = nil;
        z->right = nil;
        while (x != nil){
            y = x;
            if (k < x->key){
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y==nil){ // Tree was empty
            root = z;
        } else if (k < y->key){
            y->left = z;
        } else {
            y->right = z;
        }
        num_pairs++;
    }
}


void Dictionary::Transplant(Dictionary::Node* u, Dictionary::Node* v){
    if (u->parent == nil){ // if u.parent == nil (-> value == MAX)
        this->root = v; // 
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nil){ // if v != nil
        v->parent = u->parent;
    }
}



// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if (!contains(k)){
        throw std::logic_error ("Dictionary: remove(): key \"" + k + "\" does not exist");
    }

    Node* to_delete = search(root, k);
    if (to_delete->left == nil){ // case 1 or case 2.1 (right only)
        this->Transplant(to_delete, to_delete->right);
    } else if (to_delete->right == nil){
        this->Transplant(to_delete, to_delete->left);
    } else {
        Node* y = findMin(to_delete->right);
        if (y->parent != to_delete){
            this->Transplant(y, y->right);
            y->right = to_delete->right;
            y->right->parent = y;
        }
        this->Transplant(to_delete, y);
        y->left = to_delete->left;
        y->left->parent = y;
    }

    if (current->key == k){
        current = nil;
    }

    delete to_delete;
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if (!hasCurrent()){
        throw std::logic_error ("Dictionary: next(): current undefined");
    }

    Node* n = findNext(current);
    current = n;
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if (!hasCurrent()){
        throw std::logic_error ("Dictionary: prev(): current undefined");
    }

    Node* n = findPrev(current);
    current = n;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;

}



// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    return (to_string() == D.to_string());

    // std::string s1 = "";
    // std::string s2 = "";
    // this->inOrderString(s1, root);
    // D.inOrderString(s2, D.root);
    // return (s1==s2);
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream <<D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if (this != &D){
        Dictionary temp = D;

        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}
