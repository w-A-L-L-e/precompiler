This tool was used to convert the Gnu Scientific Library.

This is using flex++ and bison++ for the included xml parser (it might give you some compiling issues on latest g++).


Basic usage:
```
Walters-MacBook-Pro:Precompiler wschrep$ ./precompile 
Usage: ./precompile [options] <inputfile> <outputfile>

Options:
  -x <configfile>    specifies the conversion configuration file
  -preparse          preparse rather than precompile to generate a list of all
                     variables and functions that would normally be converted.
  -c <skipfile>      specifies a file containing functions and/or variables
                     which must not be converted
  -constants         identify all constants in C/C++ file
  -noprintf          don't convert printf statements
  -nofor             don't convert variables in for loops
  -init <initfile>   insert source code contained in <initfile> after the main(){ 

  -default           insert precision settings after the main(){ 
  -radix <size>      set the radix size, default size=2
  -precision <size>  set the precision size, default size=24
  -exp <low> <up>    set the exponent default low=-126, upper=127
  -expbits <bitsize> set the nr of bits the exponent must use
  -round <n|p|m|z>   set the rounding mode, default = n  
                      n = round to nearest
                      p = round to plus inf
                      m = round to min inf
                      z = round to zero
  -outputverbose     set verbose output 
  -outputmpieee <p|d|b|y|h|r|f>+ set the MpIeee output format, default = d 
                      p = parameter
                      d = decimal
                      b = binary
                      y = binary representation
                      h = hexidecimal representation
                      r = rational
                      f = flags
  -outputrational <d|r|f>+ set the Rational output format
                      d = decimal
                      r = rational
                      f = flags
  -gslapi            use gsl header file and give api source code for MPL as output file
  -gslbasename       sets a different basename, by default it is the name of the input file without the extension

  The options -outputmpieee and -outputrational can have more than 1
  output format flag (indicated with the +)

```


There are some crude integration/regression tests in the tests dir. Use them as examples maybe:
```
Walters-MacBook-Pro:tests wschrep$ ./regress_test.sh 
1.  testing : test.cpp  ->  ok
2.  testing : test2.cpp  ->  ok
3.  testing : test3.cpp  ->  ok
4.  testing : test4.cpp  ->  ok
5.  testing : array.cpp  ->  ok
6.  testing : functest.cpp  ->  ok
7.  testing : funcdeclare.cpp  ->  ok
8.  testing : returntest.cpp  ->  ok
9.  testing : pointtest.cpp  ->  TEST FAILED!!!
testing : functest.cpp with skip.conf -> ok
testing : functest.cpp with skip2.conf -> ok

```

