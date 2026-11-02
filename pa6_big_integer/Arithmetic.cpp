/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA6
 * Arithmetic.cpp
 * A set of large number calculation
 ***/


#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 3){
        cerr<<"Usage: Arithmetic <input file> <output file>"<<endl;
        return EXIT_FAILURE;
    }

    ifstream in;
    ofstream out;

    in.open(argv[1]);
    out.open(argv[2]);

    if (!in.is_open()){
        cerr <<"Unable to open file " << argv[1] << "for reading"<<endl;
        exit(1);
    }

    if (!out.is_open()){
        cerr <<"Unable to open file " << argv[2] << "for writing"<<endl;
        exit(1);
    }

    string s;
    in >> s;
    BigInteger A = BigInteger(s);
    in >> s;
    BigInteger B = BigInteger(s);

    // out<<"here is A: "<<A<<endl;
    // out<<"here is B: "<<B<<endl;

    BigInteger C = A + B;
    BigInteger D = A - B;
    BigInteger E = A - A;


    BigInteger two = BigInteger(2);
    BigInteger three = BigInteger(3);

    BigInteger helper1 = three * A;
    BigInteger helper2 = two * B;


    BigInteger F = helper1 - helper2;
    BigInteger G = A * B;

    BigInteger H = A * A;
    BigInteger I = B * B;

    BigInteger a_fourth = H * H;
    BigInteger b_fourth = I * I;
    BigInteger b_fifth = b_fourth * B;
    BigInteger nine = BigInteger(9);
    BigInteger sixteen = BigInteger(16);

    BigInteger first = nine * a_fourth;
    BigInteger second = sixteen * b_fifth;

    BigInteger J = first + second;


    out<<A<<endl;
    out<<endl;

    out<<B<<endl;
    out<<endl;

    out<<C<<endl;
    out<<endl;

    out<<D<<endl;
    out<<endl;

    out<<E<<endl;
    out<<endl;

    out<<F<<endl;
    out<<endl;

    out<<G<<endl;
    out<<endl;

    out<<H<<endl;
    out<<endl;

    out<<I<<endl;
    out<<endl;

    out<<J<<endl;
    out<<endl;

    in.close();
    out.close();
    return EXIT_SUCCESS;
}