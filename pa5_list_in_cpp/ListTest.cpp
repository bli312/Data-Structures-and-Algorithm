/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA5
 * ListTest.cpp
 * Test client for List ADT
 ***/

//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include<cassert>

using namespace std;

int main(){
   List A, B, C;

   for (int i = 0; i < 10; i ++){
      A.insertBefore(i);
      B.insertAfter(i);
   }


   cout<<"here is A: "<<A<<endl;
   cout<<"here is B: "<<B<<endl;

   cout<<endl;

   cout<<"here is the cursor pos of A: "<<A.position()<<endl;
   cout<<"here is the cursor pos of B: "<<B.position()<<endl;

   
   cout<<"now check the elements of A and B, they should be equal to each other from diffent directions"<<endl;


   assert(A.front() == B.back());


   for (int i = 0; i < 10; i++){
      assert(A.peekPrev() == B.peekNext());
      cout<<"assert "<<A.peekPrev()<<" = "<<B.peekNext()<<endl;
      cout<<"Position of A: "<<A.position()<<"; position of B: "<<B.position()<<endl;
      A.movePrev();
      B.moveNext();
   }
   cout<<"Position of A: "<<A.position()<<"; position of B: "<<B.position()<<endl;
   cout<<endl;
   cout<<endl;
   cout<<"now check the overwrite expression, equal methon and == operator"<<endl;
   cout<<endl;
   C = A;     // 0 1 2 3 4 5 6 7 8 9
   List D = B;     // 9 8 7 6 5 4 3 2 1 0
   assert(A.equals(C));
   assert(B == D);


   cout<<"here is C after calling C = A: "<<C<<endl;
   cout<<"here is D after calling List D = B: "<<D<<endl;
   cout<<"Pos A and C: "<<A.position()<<" "<<C.position()<<endl;
   cout<<"Pos B and D: "<<B.position()<<" "<<D.position()<<endl;

   cout<<endl;
   cout<<endl;
   cout<<"now test setBefore() and setAfter() by operating on C and D"<<endl;
   cout<<endl;

   D.moveBack();
   D.movePrev();

   for (int i = 0; i < 9; i ++){
      if ( i%3 == 0){
         C.setAfter(1);
         D.setBefore(3);
      } else if ( i % 3 == 1){
         C.setAfter(2);
         D.setBefore(2);
      } else {
         C.setAfter(3);
         D.setBefore(1);
      }

      C.moveNext();
      D.movePrev();
   }

   cout<<"now here is C: "<<C<<endl;
   cout<<"now here is D: "<<D<<endl;

   cout<<"Pos C: "<<C.position()<<"; Pos D: "<<D.position()<<endl;

   cout<<endl;
   cout<<endl;

   List E = C.concat(D);
   List F = D.concat(C);
   cout<<"here is E after calling C.concat(D): "<<E<<endl;
   cout<<"here is F after calling C.concat(D): "<<F<<endl;
   cout<<"Pos E: "<<E.position()<<"; Pos F: "<<F.position()<<endl;
   cout<<endl;
   cout<<endl;

   E.moveBack();

   cout<<"start iterating E from back to front, pos E: "<<E.position()<<endl;


   for (int i = 0; i < E.length(); i++){
      if (E.peekPrev() == 0){
         E.eraseBefore();
      } else if (E.peekNext() == 9){
         E.setAfter(10);
      }
      E.movePrev();
   }

   cout<<"finished iterating E"<<endl;
   cout<<endl;

   cout<<"start iterating F from front to back, pos F: "<<F.position()<<endl;

   for (int i = 0; i < F.length(); i++){
      if (F.peekNext() == 9){
         F.eraseAfter();
         if (F.position() == F.length()){
            break;
         }
      } else if (F.peekNext() == 0){
         F.setAfter(100);
      }
      F.moveNext();
   }
   cout<<"finished iterating F"<<endl;
   cout<<endl;


   cout<<"here is E after calling some earseBefore() and setBefore(): "<<E<<endl;
   cout<<"here is F after calling some earseAfter() and setAfter(): "<<F<<endl;
   cout<<"Pos E: "<<E.position()<<"; Pos F: "<<F.position()<<endl;
   cout<<"length E: "<<E.length()<<"; length F: "<<F.length()<<endl;
   cout<<endl;
   cout<<endl;


   int find_after_e = E.findNext(10);
   int find_before_f = F.findPrev(100);

   cout<<"trying to find 10(find next) in E, here is the cursor pos: "<<E.position()<<" ; here is the number function returns: "<<find_after_e<<endl;
   cout<<"trying to find 100 in F(find prev), here is the cursor pos: "<<F.position()<<" ; here is the number function returns: "<<find_before_f<<endl;
   cout<<endl;



   cout<<"testing insertAfter() and insertBefore()"<<endl;
   cout<<endl;

   for (int i = 1; i <= 5; i++){
      E.insertBefore(-i);
      F.insertAfter(-i);
   }

   cout<<"here is E after calling insertBefore() from -1 to -5: "<<E<<endl;
   cout<<"here is F after calling insertAfter() from -1 to -5: "<<F<<endl;
   cout<<endl;
   cout<<endl;

   find_after_e = E.findNext(10);
   find_before_f = F.findPrev(100);

   cout<<"find 10 (find next) in E again, here is the cursor pos: "<<E.position()<<" ; here is the number function returns: "<<find_after_e<<endl;
   cout<<"find 100 (find prev) in F again, here is the cursor pos: "<<F.position()<<" ; here is the number function returns: "<<find_before_f<<endl;
   cout<<endl;
   cout<<endl;

   try{
      E.moveNext();
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   E cursor should be at the back, try to call moveNext(), should catch the error" << endl;
   }

   try{
      F.movePrev();
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   F cursor should be at the front, try to call movePrev(), should catch the error" << endl;
   }


   cout<<endl;
   cout<<endl;


   cout<<"now test cleanup()"<<endl;

   int find_before_e = E.findPrev(-3);
   cout<<"find -3 in E (findPrev), move the cursor before -3; cursor pos: "<<E.position()<<"; number returned: "<<find_before_e<<endl;
   cout<<"here is E before calling cleanup(): "<<E<<endl;
   cout<<endl;

   E.cleanup();
   cout<<"here is E after calling cleanup(): "<<E<<endl;
   cout<<"here is the cursor pos: "<<E.position()<<" and the peekNext(): "<<E.peekNext()<<endl;



   cout<<endl;
   cout<<endl;


   cout<<"here is F, trying to remove all negative numbers: "<<F<<endl;

   int count = 0;

   for (int i = 0; i <F.length(); i++){
      if (F.peekNext() < 0){
         F.eraseAfter();
         count ++;
         if (count == 5){
            break;
         }
         continue;
      }
      F.moveNext();
   }

   cout<<"here is F now: "<<F<<endl;
   cout<<"here is the cursor_pos: "<<F.position()<<"; and peekNext()"<<F.peekNext()<<endl;
   cout<<endl;
   F.cleanup();
   cout<<"here is F after calling cleanup(): "<<F<<endl;
   cout<<"here is the cursor pos: "<<F.position()<<" and peekNext(): "<<F.peekNext()<<endl;


   E.clear();

   cout<<"here is E after calling clear(): "<<E<<endl;
   cout<<endl;
   cout<<endl;

   cout<<"now operating on E, catching some errors"<<endl;

   try{
      E.front();
   } catch (std::length_error&e){
      cout << e.what() << endl;
      cout << "   E is empty, catch the error and continue" << endl;
   }
   cout<<endl;


   cout<<"try to catch multiple errors, first try to catch range_error, the length"<<endl;

   try{
      E.back();
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   E is empty, catch the range error and continue" << endl;
   } catch (std::length_error&e){
      cout << e.what() << endl;
      cout << "   E is empty, catch the length errorrrrrrrrrrrr and continue" << endl;
   }

   cout<<"looks like it catch the length error!!"<<endl;
   cout<<endl;


   try{
      E.peekPrev();
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   E is empty, catch the error and continue" << endl;
   }
   cout<<endl;

   try{
      E.movePrev();
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   E is empty, catch the error and continue" << endl;
   }
   cout<<endl;

   try{
      E.setBefore(1);
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   F cursor at the back, catch the error and continue" << endl;
   }
   cout<<endl;


   try{
      E.eraseBefore();
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   F cursor at the back, catch the error and continue" << endl;
   }

   cout<<endl;
   cout<<endl;

   cout<<"now moveing cursor at F to the back, catching some errors"<<endl;
   F.moveBack();

   try{
      F.peekNext();
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   F cursor at the back, catch the error and continue" << endl;
   }
   cout<<endl;

   try{
      F.moveNext();
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   F cursor at the back, catch the error and continue" << endl;
   }
   cout<<endl;


   try{
      F.setAfter(1);
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   F cursor at the back, catch the error and continue" << endl;
   }
   cout<<endl;


   try{
      F.eraseAfter();
   } catch (std::range_error&e){
      cout << e.what() << endl;
      cout << "   F cursor at the back, catch the error and continue" << endl;
   }
   cout<<endl;


   cout<<"that is it!!"<<endl;
   cout<<endl;  
   return( EXIT_SUCCESS );
}