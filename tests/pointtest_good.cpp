#include <iostream>
#include <iomanip>
using namespace std;

#include "BigInt.hh"
#include "MpIeee.hh"
#include "ArithmosIO.hh"
#include <vector>

int main(){
  MpIeee * a=  new MpIeee(MpIeee( "2" ));
  MpIeee * pb=  new MpIeee(MpIeee( "2" )+*a);

  return 0;
}