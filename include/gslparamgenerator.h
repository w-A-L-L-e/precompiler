/*=============================================================================
author        : Walter Schreppers
filename      : gslparamgenerator.h
created       : 8/5/2006 at 17:27:24
modified      : 
version       : 
copyright     : Walter Schreppers
bugreport(log): 
=============================================================================*/

#ifndef GSLPARAMGENERATOR_H
#define GSLPARAMGENERATOR_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "Var.h"


using namespace std;

class GslParamGenerator : public vector<Var>{

  public:
    //constructor & destructor
    //==========================
    GslParamGenerator();
    ~GslParamGenerator();

    //public members
    //==============
    string convertParameters();
    string freeMemory();
    
    void addParam( const string& name, const string& srcType, const string& targType );
    
    //operators
    //=========
    GslParamGenerator& operator=( const GslParamGenerator& );
    friend ostream& operator<<( ostream&, const GslParamGenerator& );
    friend istream& operator>>( istream&, GslParamGenerator& );

  private:
    //private members:
    //================
    void init();

    //private locals:
    //===============

}; //end of class GslParamGenerator

#endif

