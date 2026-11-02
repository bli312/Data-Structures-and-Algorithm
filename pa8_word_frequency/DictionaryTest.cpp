/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA8
 * Dictionary.cpp
 * Test client for Dictionary ADT
 ***/


//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string As[] = { // words to insert
      "cigar",
      "awake",
      "blush",
      "major",
      "serve",
      "model",
      "grade",
      "quiet",
      "quite",
      "majorr",
      "alive",
      "marry",
      "pride",
      "proud",
      "staff",
      "paper",
      "adobe",
      "mimic",
      "first", 
      "crazy", // 20
      "maxim",
      "ivory",
      "panel",
      "agree", 
      "error", // 25
      "cross",
      "erase",
      "world",
      "great",
      "hopefully", // 30
      "yeahyeahyeah",
      "random",
      "strings",
      "ohyeah",
      "homework",  // 35
      "pa7",
      "cse101",
      "datastructure",
      "fallquarter", 
      "here",   // 40
      "is",
      "the",
      "second",
      "dictionary",
      "with",   // 45
      "fewer",
      "words",
      "and",
      "let",
      "us",      // 50
      "play",
      "with", // duplicated
      "this",
      "dictionary",  //duplicated
      "too",      // 55 line, 53 words
   };

   string Bs[] =   { // words to delete
                     "agree",
                     "cross",
                     "hopefully",
                     "majorr",
                     "strings",
                     "world",
                     "ohyeah", // 7 
                     "second",
                     "let",
                     "fewer",
                     "and",
                     "cigar", // 12
                     "this",
                     "model",
                     "quiet", // 15
                  };

   string Cs[] =  { // words to check contains()
                     "fallquarter", 
                     "here",
                     "is",
                     "the",
                     "second",   // 5
                     "dictionary",
                     "with",   
                     "fewer",
                     "words",
                     "major", // 10
                     "serve",
                     "model",
                     "fewer",
                     "and",
                     "cigar",  // 15 
                     "grade",
                     "quiet",
                     "quite",
                     "majorr",
                     "alive", // 20
                     "marry",
                     "somethingrandom",
                     "toseeif",
                     "containscancatch",
                     "wordsthatdonotexist", // 25
                     "almostthere",
                  };

   Dictionary A;
   Dictionary B;

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<55; i++){
      A.setValue(As[i], i+1);
   }

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "here is A.to_string" << endl << A.to_string()<<endl;
   cout << "here is A.pre()"<<endl<<A.pre_string()<<endl<<endl;

   // call operator =()
   B = A;
   cout << "operator creates identical trees: " << endl;
   cout << ((B.pre_string()==A.pre_string())?"true":"false") << endl;
   cout << endl;


   // call copy constructor
   Dictionary C = B;
   cout << "copy constructor creates identical trees: " << endl;
   cout << ((C.pre_string()==B.pre_string())?"true":"false") << endl;
   cout << endl;



   // remove some pairs from A
   cout << "remove some pairs from A" << endl;
   for(int i=0; i<15; i++){ 
    //   cout<<"here is i: "<<i<<endl;
      A.remove(Bs[i]);
   }

   cout << "here is A.pre() (new)"<<endl<<A.pre_string()<<endl<<endl;


   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl<<endl;

   // check operator==()
   cout << "now check the == operator" << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   cout << "now check the equal function" << endl;
   cout << "A.equals(B) is " << (A.equals(B)?"true":"false") << endl;
   cout << "B.equals(C) is " << (B.equals(C)?"true":"false") << endl;
   cout << "C.equals(A) is " << (C.equals(A)?"true":"false") << endl << endl;

   for (int i = 0; i < 26; i++){
      if (A.contains(Cs[i])){
         cout << "A.getValue( \"" << Cs[i] << "\" = " << A.getValue(Cs[i]) << endl;
         A.getValue(Cs[i]) = (200+i);
         cout << "A.getValue( \"" << Cs[i] << "\" = " << A.getValue(Cs[i]) << endl;
      } else {
         cout << "opps, word " << Cs[i] << " does not exist " << endl;
      }
   }
   
   cout<<endl;

   cout << "A.size() = " << A.size() << endl  << A << endl << endl;


   // try to call set value on B, to words that already exist
   B.setValue("panel", 1000);
   B.setValue("datastructure",1001);
   B.setValue("cigar",1002);
   B.setValue("great",1003);
   B.setValue("here",1004);
   B.setValue("with",1005);
   B.setValue("us",1006);




   // operate current-related function on Dictionary B
   cout << "operate current-related function on Dictionary B and C" << endl << endl;

   cout << "now traverse B forwards" << endl;
   cout << "B has current is " << (B.hasCurrent()?"true":"false") << endl;
   B.begin();
   B.begin();
   B.begin();
   cout << "moved current to begin and here is the first key:value pair -- " << B.currentKey() << " : " << B.currentVal()<<endl;
   while (B.hasCurrent()){
      cout << "move next and here is the key:value pair -- " << B.currentKey() << " : " << B.currentVal()<<endl;
      B.next();
   }
   cout << "now B has current is " << (B.hasCurrent()?"true":"false") << endl<<endl<<endl;



   cout << "now traverse C backwards" << endl;
   cout << "C has current is " << (C.hasCurrent()?"true":"false") << endl;
   C.end();
   C.end();
   C.end();
   cout << "moved current to begin and here is the first key:value pair -- " << C.currentKey() << " : " << C.currentVal()<<endl;
   while (C.hasCurrent()){
      cout << "move next and here is the key:value pair -- " << C.currentKey() << " : " << C.currentVal()<<endl;
      C.prev();
   }
   cout << "now C has current is " << (C.hasCurrent()?"true":"false") << endl << endl;


   // clear()
   cout << "now call clear() on C" << endl;
   C.clear();
   cout << "C.size() = " << C.size() << endl  << C << endl<<endl;


   // check exceptions for getValue(), currentKey(), currentVal(), remove(), next(), prev()
   cout << "now test pre-condition errors:" << endl;

   cout << "now B contains \"blahhhhhhhhhh\": " << ( B.contains("blahhhhhhhhhh")?"true":"false") <<endl;
   try{
      A.getValue("blahhhhhhhhhh");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   caught the error! continue!" << endl;
   }

   try{
      B.remove("blahhhhhhhhhhhh");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   caught the error! continue!" << endl;
   }


   cout << "now B has current is " << ( B.hasCurrent() ? "true":"false") << endl <<endl;
   try{
      B.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   caught the error! continue!" << endl;
   }


   try{
      B.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   caught the error! continue!" << endl;
   }  

   try{
      B.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   caught the error! continue!" << endl;
   }

   try{
      B.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   caught the error! continue!" << endl;
   }
   cout << endl;  


   cout << "passed all the test! This is the last PA in CSE 101! Yeahhh" << endl << endl;
   return( EXIT_SUCCESS );
}