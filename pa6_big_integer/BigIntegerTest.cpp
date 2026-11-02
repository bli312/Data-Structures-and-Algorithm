/***
 * Leo Li
 * bli312
 * 2024 Fall CSE101 PA6
 * BigIntegerTest.cpp 
 * Test client for BigInteger ADT
 ***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
#include"List.h"

using namespace std;



int main(){



   string s1 = "0000000000000000000000000000000000000123456789";
   string s2 = "-000000000000000000000000000000000330293847502398475";
   string s3 = "9876545439000000345634560000000002000034565430000000006543654365346534";

   //BigInteger N;
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s2);
   BigInteger C = BigInteger(s3);
   BigInteger D = BigInteger(123456789);
   BigInteger E = BigInteger(123456789000000000);
   BigInteger F = B;

   cout << endl;

   cout << "A = " << A <<" and the sign is: "<< A.sign() << endl;
   cout << "B = " << B <<" and the sign is: "<< B.sign() << endl;
   cout << "C = " << C <<" and the sign is: "<< C.sign() << endl;
   cout << "D = " << D <<" and the sign is: "<< D.sign() << endl;
   cout << "E = " << E <<" and the sign is: "<< E.sign() << endl;
   cout << "F = " << F <<" and the sign is: "<< F.sign() << endl;
   cout << endl;

   cout << "Now test the compare function by directly calling the function! " << endl;
   cout << "A and B: " << A.compare(B) << endl;
   cout << "A and C: " << A.compare(C) << endl;
   cout << "A and D: " << A.compare(D) << endl;
   cout << "A and E: " << A.compare(E) << endl;
   cout << "A and F: " << A.compare(F) << endl;

   // A = D
   // B = F
   // E == 1000000000 * A (/D)

   cout << "Now test the compare function by using the operator! " << endl;
   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   cout << "(A >= C): " << ((A>=C)?"True":"False") << endl;
   cout << "(A == D): " << ((A==D)?"True":"False") << endl;
   cout << "(A <= E): " << ((A<=E)?"True":"False") << endl;
   cout << "(A < E): " << ((A<E)?"True":"False") << endl;
   cout << "(A > F): " << ((A>F)?"True":"False") << endl;


   // Expected output:
   // false
   // false
   // false
   // true
   // true

   // false
   // true
   // true
   // true
   // true

   // A = D
   // B = F
   // E == 1000000000 * A (/D)

   BigInteger G = B - F;
   B.makeZero();
   cout << "G = B-F = " << B <<" and the sign is: "<< G.sign() << endl;
   cout << "after making 0, B = " << B <<" and the sign is: "<< B.sign() << endl;
   cout << "(G==B) = " << ((G==B)?"True":"False") << endl;

   A.negate();
   cout << "after negating, A = " << A <<" and the sign is: "<< A.sign() << endl;
   BigInteger H = A + D;
   cout << "H = A+D = " << H <<" and the sign is: "<< H.sign() << endl;
   BigInteger I;
   cout<<"now declaring a new BigInteger Object I."<<endl;

   cout << "(H==I) = " << ((H==I)?"True":"False") << endl;
   cout << "(H==0) = " << ((H==0)?"True":"False") << endl;

   cout << "A = " << A <<" and the sign is: "<< A.sign() << endl;
   cout << "B = " << B <<" and the sign is: "<< B.sign() << endl;
   cout << "C = " << C <<" and the sign is: "<< C.sign() << endl;
   cout << "D = " << D <<" and the sign is: "<< D.sign() << endl;
   cout << "E = " << E <<" and the sign is: "<< E.sign() << endl;
   cout << "F = " << F <<" and the sign is: "<< F.sign() << endl;
   cout << "G = " << G <<" and the sign is: "<< G.sign() << endl;
   cout << "H = " << H <<" and the sign is: "<< H.sign() << endl;
   cout << "I = " << I <<" and the sign is: "<< I.sign() << endl<<endl;

   cout << "now testing the arithmetic functions by directly calling fuctions"<< endl;
   BigInteger J = D.add(E);
   BigInteger K = D.add(F);
   BigInteger L = D.sub(F);
   BigInteger M = K.add(L);
   BigInteger N = D.mult(2);
   BigInteger O = D.mult(BigInteger(2));

   cout << "J = D.add(E) = " << J <<" and the sign is: "<< J.sign() << endl;
   cout << "K = D.add(F) = " << K <<" and the sign is: "<< K.sign() << endl;
   cout << "L = D.sub(F) = " << L <<" and the sign is: "<< L.sign() << endl;
   cout << "M = K.add(L) = " << M <<" and the sign is: "<< M.sign() << endl;
   cout << "N = D.mult(2) = " << N <<" and the sign is: "<< N.sign() << endl;
   cout << "O = D.mult(BigInteger(2)) = " << O <<" and the sign is: "<< O.sign() << endl<<endl;

   cout << "(M== 2 * D) = " << ((M==(2*D))?"True":"False") << endl;
   cout << "(M== N) = " << ((M==N)?"True":"False") << endl;
   cout << "(M== O) = " << ((M==O)?"True":"False") << endl<<endl;

   cout << "now testing the arithmetic functions by using operators"<< endl;

   BigInteger P = K + L;  // P == 2D
   BigInteger Q = M - N;  // Q == 0
   cout << "Q = M - N = " << Q <<" and the sign is: "<< Q.sign() << endl<<endl;
   cout << "(P == 2*D) = " << ((P == 2*D)?"True":"False") << endl;
   D *= 1000000000;   // D == E
   M -= N;
   N += O;  // N = 2 * O

   cout << "D *= 1000000000:  " << D <<" and the sign is: "<< D.sign() << endl;
   cout << "M -= N:   " << M <<" and the sign is: "<< M.sign() << endl;
   cout << "N += O:   " << N <<" and the sign is: "<< N.sign() << endl;
   cout << "P = K + L = " << P <<" and the sign is: "<< P.sign() << endl;

   cout << "here is Q: " << Q << " and here is the sign: " << Q.sign() <<endl;
   BigInteger Z = BigInteger(0);
   cout << "here is Z by calling Z = BigInteger(0): " << Z << "; and here is the sign: "<< Z.sign()<< endl;


   cout<<Q.compare(Z) << "here is the result by calling compare " << endl;

   cout << "(Q == Z) = " << ((Q == Z)?"True":"False") << endl;

   cout << "(Q == BigInteger(0)) = " << ((Q == BigInteger(0))?"True":"False") << endl;
   cout << "(D == E) = " << ((D == E)?"True":"False") << endl;
   cout << "(N == 2 * O) = " << ((N==(2*O))?"True":"False") << endl<<endl;

   cout << "Now testing exceptions" << endl;


   try{
      BigInteger R = BigInteger("");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger R = BigInteger("+");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger R = BigInteger("12329837492387492837492$4982379487293847");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger R = BigInteger("5298374902837409+82734098729287349827398");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;

   return EXIT_SUCCESS;
}