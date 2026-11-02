/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA8
 * WordFrequency.cpp
 * Read each line of the file, separate words based on the given delim, and count the frequency
 ***/


#include<iostream>
#include<string>
#include<stdexcept>
#include <fstream>
#include"Dictionary.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 3){
        cerr<<"Usage: WordFrenquency <input file> <output file>"<<endl;
        return EXIT_FAILURE;
    }

    ifstream in;
    ofstream out;

    in.open(argv[1]);
    out.open(argv[2]);

    if (!in.is_open()){
        cerr << "Unable to open file " << argv[1] << "for reading" << endl;
        return EXIT_FAILURE;
    }

    if (!out.is_open()){
        cerr << "Unable to open file " << argv[2] << "for writing" << endl;
        return EXIT_FAILURE;
    }

    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

    string line, token, tokenBuffer;
    size_t begin, end, len;
    int line_count = 0;
    Dictionary D;

    while (getline(in, line)){
        line_count++;
        len = line.length();

        // get tokens in this line
        // token_count = 0;
        tokenBuffer = "";

        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);

        while( token!="" ){  // we have a token
            // update token buffer
            // tokenBuffer += token;
            // token_count++;

            transform(token.begin(), token.end(), token.begin(), ::tolower);
            // out << token << "\n";

            if (D.contains(token)){
                D.getValue(token)++;
            } else {
                D.setValue(token, 1);
            }


            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);


        }

        // out << "line " << line_count << " contains " << token_count<<" ";
        // out << " token" << (token_count==1?"":"s") << endl;

        // out << tokenBuffer << endl;

    }

    out << D;


    in.close();
    out.close();
    return EXIT_SUCCESS;




}


