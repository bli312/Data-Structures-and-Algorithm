/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA6
 * BigInteger.cpp
 * Implementation file for BigInteger ADT
 ***/


#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"

const ListElement base=1000000000;
const int power=9;

// const ListElement base=100;
// const int power=2;

// Class Constructors & Destructors -------------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().

BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.

BigInteger::BigInteger(long x){
    if (x < 0){
        signum = -1;
        x = -x;
    } else if (x > 0){
        signum = 1;
    } else {
        signum = 0;
        digits.insertAfter(0);
        return;
    }

    while (x > 0){
        digits.insertAfter(x%base);
        x /= base;
    }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    if (s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    int start;
    int end = s.length()-1;

    if (s[0] == '+'){
        if (s.length() == 1){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        signum = 1;
        start = 1;
    } else if (s[0] == '-'){
        if (s.length() == 1){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        signum = -1;
        start = 1;
    } else {
        signum = 1;
        start = 0;
    }


    for (int i = start; s[i] != '\0'; i++){
        if ( !isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    int save = 0;
    while (end >= start){
        for (int i = 0; i < power-1; i++){
            if (end <= start){
                save = i;
                break;
            }
            end --;
            save = i+1;
        }

        std::string current = "";
        int save_end = end;
        for (int i = 0; i <= save; i ++){
            current += s[end];
            end++;
        }
        digits.insertAfter(std::stol(current));
        end = save_end - 1;
    }

    // std::cout<<"here is the digits"<<digits<<std::endl;

    digits.moveFront();
    while (digits.peekNext() == 0){
        digits.eraseAfter();
        if (digits.position() == digits.length()){
            break;
        }
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    this->digits = N.digits;

}


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.

int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    if (signum < N.signum){
        return -1;
    }

    if (signum > N.signum){
        return 1;
    }

    BigInteger subs = this->sub(N);
    return (subs.sign());
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    signum = -signum;
}


// Helper functions --------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    L.moveFront();
    ListElement e;
    if (L.position() != L.length()){
        for (int i = 0; i < L.length(); i ++){
            e = L.peekNext();
            L.setAfter(-1 * e);
            L.moveNext();
        }
    }
}


// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    L.moveBack();
    ListElement ele;
    while (L.position() != 0){
        ele = L.peekPrev();
        L.setBefore(ele * m);
        L.movePrev();
    }
}



// helper function normalize()
// returns 1 if positive, 0 if 0, -1 if negative
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
    L.moveBack();
    ListElement ele;
    int remainder = 0;
    int quotient = 0;
    for (int i = 0; i < L.length(); i++){
        ele = L.peekPrev() + quotient;
        // std::cout<<"element is: "<<ele<<std::endl;
        if (ele >= base){
            remainder = ele % base;
            quotient  = ele / base;
            L.setBefore(remainder);
            // std::cout<<"remainder is: "<<remainder<<std::endl;
            // std::cout<<"quotient is: "<<quotient<<std::endl;
            // std::cout<<"here is the current list"<<L<<std::endl;
        } else if (ele >=0 && ele < base){
            quotient = 0;
            remainder = ele;
            // std::cout<<"remainder is~~~: "<<remainder<<std::endl;
            // std::cout<<"here is the current list"<<L<<std::endl;
            L.setBefore(remainder);
            L.movePrev();
            continue;
        } else { // ele < 0
            if (i == L.length()-1){
                L.setBefore(ele);
                break;
            }

            remainder = (base - ( (-ele)%base )) % base;
            quotient= 0;
            while (1){
               ele = ele + base;
               quotient --;
               if (ele >= 0){
                  break;
               }
            }
            // quotient = ele / base;

            L.setBefore(remainder);
            // std::cout<<"remainder is!!!: "<<remainder<<std::endl;
            // std::cout<<"quotient is!!!: "<<quotient<<std::endl;
            // std::cout<<"here is the current list"<<L<<std::endl;
        }
        L.movePrev();
    }

    // std::cout<<"the end of quotient and remainder! "<<std::endl;
    // std::cout<<"here is the final list"<<L<<std::endl;
    // std::cout<<std::endl;
    // std::cout<<std::endl;
    // std::cout<<std::endl;

    if (quotient > 0){
        L.moveFront();
        if (quotient >= base){
            while (quotient >= base){ // if quotient is really large
                remainder = quotient % base;
                quotient = quotient / base;
                L.insertAfter(remainder);
            }
        }
        
        L.insertAfter(quotient);
    }

    // remove pre 0s
    L.moveFront();
    if (L.position() != L.length()){
        while (L.peekNext() == 0){
            L.eraseAfter();
            if (L.position() == L.length()){
                break;
            }
        }
    }

    if (L.length() == 0){
        return 0;
    }

    L.moveFront();
    if (L.peekNext() < 0){
        negateList(L);
        // cout<<"here is the L negateed: "<<L<<endl;
        normalizeList(L);
        return -1;
    }

    return 1;
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    scalarMultList(B, sgn);
    // std::cout<<"hereeeeeeee is my B from sumList by ScalarMyltlist!: "<<B<<std::endl;
    // std::cout<<"and here is the sign: "<<sgn<<std::endl;
    S.clear();
    A.moveBack();
    B.moveBack();

    while (A.position() != 0 && B.position() != 0){
        ListElement ele = A.peekPrev() + B.peekPrev();
        S.insertAfter(ele);
        A.movePrev();
        B.movePrev();
    }

    while (A.position() != 0){
        ListElement ele = A.peekPrev();
        S.insertAfter(ele);
        A.movePrev();
    }

    while (B.position() != 0){
        ListElement ele = B.peekPrev();
        S.insertAfter(ele);
        B.movePrev();
    }
}


// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    L.moveBack();
    for (int i = 0; i < p; i++){
        L.insertBefore(0);
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger result;
    if (signum == 0){
        result = N;
        return result;
    }
    if (N.signum == 0){
        result = *this;
        return result;
    }

    List D = digits;

    if (signum == -1){
        negateList(D);
    }
    // std::cout<<"here is the N.signum frim add function!: "<<N.signum<<std::endl;
    sumList(result.digits, D, N.digits, N.signum);
    int sign = normalizeList(result.digits);
    // std::cout<<"here is the sign: "<<sign<<std::endl;

    result.signum = sign;
    return result;

}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger result;
    BigInteger temp = N;
    temp.negate();
    result = this->add(temp);
    return result;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger result;
    if (signum == 0 || N.signum == 0){
        return result;
    }

    BigInteger A = *this;
    BigInteger B = N;


    List B_List = N.digits;
    List A_List;
    List sum;

    B_List.moveBack();
    for (int i = 0; i < B_List.length(); i++){
        A_List = A.digits;
        ListElement scalar = B_List.peekPrev();
        scalarMultList(A_List, scalar);
        shiftList(A_List, i);
        sumList(sum, A_List, sum, 1);
        normalizeList(sum);
        B_List.movePrev();
    }

    result.digits = sum;
    if (signum != N.signum){
        result.signum = -1;
    } else {
        result.signum = 1;
    }

    return result;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    if (signum == 0){
        return "0";
    }

    std::string s = "";

    if (signum == 1){
        s = "";
    } else {
        s = "-";
    }

    for (int i = 0; i < digits.length(); i++){
    // while (digits.position() != digits.length()){
        std::string temp = std::to_string(digits.peekNext());
        if (i != 0){
            int length = temp.length();
            for (int j = 0; j < (int) (power-length); j++){
                temp = "0" + temp;
            }
        }
        s += temp;
        digits.moveNext();
    }
    return s;

    // s += digits.to_string();
    // return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream <<N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    // if (A.signum != B.signum){
    //     return false;
    // }

    // List A_list = A.digits;
    // List B_list = B.digits;
    // bool eq = (A_list.equals(B.digits));

    // return eq;

    return (A.compare(B) == 0);

    // return ( (A.digits.equals(B.digits)));
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == -1);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    // if (A.compare(B) == 1){
    //     return false;
    // }

    // return true;

    return (A.compare(B) <= 0);

    // return (A.compare(B) == -1 || A.compare(B) == 0);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == 1);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) >= 0);
    // return (A.compare(B) == 1 || A.compare(B) == 0);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}