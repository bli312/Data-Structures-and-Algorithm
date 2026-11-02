/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA5
 * Shuffle.cpp
 * Shuffling a list, and returns how many times a list need to be shuffled to return original
 ***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D){

    if (D.length() == 1){
        return;
    }

    List prev;
    List later;
    int n = D.length();
    prev.moveBack();
    later.moveBack();
    D.moveFront();

    if (D.length()%2 == 1){

        for (int i = 0; i < (n-1)/2; i++){
            prev.insertBefore(D.peekNext());
            D.moveNext();
        }
        for (int j = (n-1)/2; j<n; j++ ){
            later.insertBefore(D.peekNext());
            D.moveNext();
        }

        D.clear();
        prev.moveFront();
        later.moveFront();
        int element;
        
        for (int k = 0; k<n; k++){
            if (k%2 == 0){  // longer first
                element = later.peekNext();
                later.moveNext();
                D.insertBefore(element);
            } else {
                element = prev.peekNext();
                prev.moveNext();
                D.insertBefore(element);
            }
        }

        // cout<<D<<endl;

    } else{  // length is even
        D.moveFront();

        // set pre
        for (int i = 0; i < (n/2); i++){
            prev.insertBefore(D.peekNext());
            D.moveNext();
        }
        // set later
        for (int j = n/2; j<n; j++ ){
            later.insertBefore(D.peekNext());
            D.moveNext();
        }

        D.clear();
        prev.moveFront();
        later.moveFront();
        int element;

        for (int k = 0; k<n; k++){
            if (k%2 == 0){  // later first
                element = later.peekNext();
                later.moveNext();
                D.insertBefore(element);
            } else {
                element = prev.peekNext();
                prev.moveNext();
                D.insertBefore(element);
            }
        }

        // cout<<"here is prev in even" <<prev<<endl;
        // cout<<"here is later in even" <<later<<endl;
        // cout<<"here is n; "<<n<<endl;
        // cout<<"D after a shuffle"<<D<<endl;

    }


    return;

}



int main(int argc, char* argv[]){
    if (argc != 2){
        cout<<"Usage:" <<argv[0]<< "<<<deck_size>" <<endl;
        exit(EXIT_FAILURE);
    }


    int total =stoi(argv[1]);
    int current;

    cout<<"deck size       shuffle count"<<endl;
    cout<<"------------------------------"<<endl;


    for (int i = 1; i <= total; i++){
        List deck;
        List result;
        current = i;
        deck.moveBack();

        for (int j = 0; j < current; j++){
            deck.insertBefore(j);
        }

        int count = 0;
        result = deck;

        while (true){
            shuffle(deck);
            count ++;
            if (deck == result){
                break;
            }
        }

        cout<<" "<<i<<"\t\t"<<count<<endl;
        

        
    }
    return 0;
}