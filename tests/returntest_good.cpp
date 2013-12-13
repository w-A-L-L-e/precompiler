#include <iostream>
#include <iomanip>
using namespace std;

#include "BigInt.hh"
#include "MpIeee.hh"
#include "ArithmosIO.hh"
#include <vector>

void bla(){
  return;
}


MpIeee parentfunc1(){
  MpIeee a;
  a=MpIeee( "1.2" );
  funccall();
  return MpIeee( "3" );
}

MpIeee parentfunc2(){
  MpIeee a;
  a=MpIeee( "1.2" );
  funccall();
  funccall2( funccall3( funccall4(4.1) ) ); 
  return MpIeee( "3" );
}

BigInt parentfunc1b(){
  MpIeee a;
  a=MpIeee( "1.2" );
  funccall();
  return BigInt( "3" );
}

BigInt parentfunc2b(){
  MpIeee a;
  a=MpIeee( "1.2" );
  funccall();
  funccall2( funccall3( funccall4(4.1) ) ); 
  return BigInt( "3" );
}

int main(){
  parentfunc1();
  parentfunc2();
  return 0;
}

