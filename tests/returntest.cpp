void bla(){
  return;
}


double parentfunc1(){
  double a;
  a=1.2;
  funccall();
  return 3;
}

double parentfunc2(){
  double a;
  a=1.2;
  funccall();
  funccall2( funccall3( funccall4(4.1) ) ); 
  return 3;
}

int parentfunc1b(){
  double a;
  a=1.2;
  funccall();
  return 3;
}

int parentfunc2b(){
  double a;
  a=1.2;
  funccall();
  funccall2( funccall3( funccall4(4.1) ) ); 
  return 3;
}

int main(){
  parentfunc1();
  parentfunc2();
  return 0;
}

