
/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA7
 * DictionaryTest.cpp 
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
#include<cassert>

using namespace std;

int main(){

   string As[] = {
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
      "first", //19
      "crazy",
      "maxim",
      "ivory",
      "panel",
      "agree", //24
      "error",
      "cross",
      "erase",
      "world",
      "great",
      "hopefully",
      "yeahyeahyeah",
      "random",
      "strings",
      "ohyeah",
      "homework",
      "pa7",
      "cse101",
      "datastructure",
      "fallquarter", //39
   };


   string Bs[] =   {
                     "here",
                     "is",
                     "the",
                     "second",
                     "dictionary",
                     "with",
                     "fewer",
                     "words",
                     "and",
                     "let",
                     "us",
                     "play",
                     "with", // duplicated
                     "this",
                     "dictionary",  //duplicated
                     "too",      // 16 line, 14 words
                  };

   Dictionary A;
   Dictionary B;
   Dictionary D;

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<39; i++){
    // cout<<"here is number: "<<i<<endl
      A.setValue(As[i], i+1);
   }

   for (int i=0; i<16;i++){
      D.setValue(Bs[i],i+21);
   }
   
   // call operator=()
   B = A;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "D.size() = " << D.size() << endl  << D << endl;

   cout << "call the equal function by operator"<<endl;
   cout << "A==B is " << (A==B?"true":"false") <<endl;
   cout << "D==B is " << (D==B?"true":"false") <<endl<<endl;

   cout <<"call the equal function"<<endl;
   assert(A.equals(B));
   cout <<"pass the A.equals(B) assertion"<<endl;


   try{
      if (!(B.equals(D))){
         throw logic_error("B does not equal D");
      }
      cout <<"B euqals D"<<endl<<endl;
   } catch(logic_error& e){
      cout<<e.what()<<endl;
      cout <<"caught the error, B does not equal to D"<<endl<<endl;
   }


   B.setValue("cigar", 101);
   B.setValue("awake", 102);
   B.setValue("major", 103);
   B.setValue("serve", 104);
   B.setValue("world", 105);
   B.setValue("newword", 10000);

   // call copy constructor
   Dictionary C = B;

   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   cout << "call the equal function (B==C)by operator"<<endl;
   cout << "B==C is " << (B==C?"true":"false") <<endl;   // true
   cout << "A==C is " << (A==C?"true":"false") <<endl;   // false
   cout << "A==B is " << (A==B?"true":"false") <<endl<<endl;  // false

   cout <<"call the equal function"<<endl;
   assert(C.equals(B));
   cout <<"pass the C.equals(B) assertion"<<endl;

   // perform alterations on A
   cout << A.getValue("first") << endl;
   A.getValue("first") *= 20; // change the value associated with "first"
   cout <<"here is the value changed: "<<A.getValue("first") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl; //38
   cout << A.pre_string() << endl;


   cout<<"assert A contains As[i]"<<endl;
   for (int i =0; i<A.size();i++){
      assert(A.contains(As[i]));
   }
   cout<<"pass the assertion"<<endl<<endl;

   // remove some pairs from A
   for(int i=0; i<10; i++){
      cout << "removing " << As[i] << " from Dictionary A" << endl; 
      A.remove(As[i]);
   }

   cout << "after remove loop" << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   cout<<" do forward iteration on A "<<endl;
   for(A.begin(); A.hasCurrent(); A.next()){
      string s = A.currentKey();
      int x = A.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;


   cout<<" do reverse iteration on B"<<endl;
   for(B.end(); B.hasCurrent(); B.prev()){
      string s = B.currentKey();
      int x = B.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   B.clear();

   cout<<"here is B after calling clear function"<<endl;
   cout<<"B.size(): "<<B.size()<<endl<<B<<endl<<endl;
   
   // check exceptions
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;  

   return( EXIT_SUCCESS );
}