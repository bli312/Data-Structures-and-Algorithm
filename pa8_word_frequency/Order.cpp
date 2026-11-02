/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA8
 * Order.cpp
 * Read each line of the input file as a (unique) single string, and insert it into
 * the Dictionary ADT as a key. Print it inorder to the output file.
 ***/


#include<iostream>
#include<string>
#include<stdexcept>
#include <fstream>
#include"Dictionary.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 3){
        cerr<<"Usage: Order <input file> <output file>"<<endl;
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

    int i = 1;
    string s;
    Dictionary D;
    while (getline(in, s)){
        D.setValue(s, i);
        i++;
    }

    out << D.to_string() << endl;
    out << D.pre_string() << endl;

    in.close();
    out.close();
    return EXIT_SUCCESS;


    


}