/*=============================================================================
author        : Walter Schreppers
filename      : gslparamgenerator.cpp
created       : 8/5/2006 at 17:27:24
modified      : 
version       : 
copyright     : Walter Schreppers
bugreport(log): 
=============================================================================*/

#include "gslparamgenerator.h"

/*-----------------------------------------------------------------------------
name        : init
description : initialize private locals
parameters  : 
return      : void
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
void GslParamGenerator::init(){

}


/*-----------------------------------------------------------------------------
name        : GslParamGenerator
description : constructor
parameters  : 
return      : 
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
GslParamGenerator::GslParamGenerator(){
  init();
}


/*-----------------------------------------------------------------------------
name        : ~GslParamGenerator
description : destructor
parameters  : 
return      : 
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
GslParamGenerator::~GslParamGenerator(){

}


/*-----------------------------------------------------------------------------
name        : operator=
description : 
parameters  : const GslParamGenerator& g
return      : GslParamGenerator&
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
GslParamGenerator& GslParamGenerator::operator=( const GslParamGenerator& g ){
  if( this != &g ){
    //copy values of private locals

  }
  return *this;
}


/*-----------------------------------------------------------------------------
name        : operator<<
description : output operator
parameters  : ostream& os, const GslParamGenerator& g
return      : ostream&
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
ostream& operator<<( ostream& os, const GslParamGenerator&  ){

  return os;
}


/*-----------------------------------------------------------------------------
name        : operator>>
description : input operator
parameters  : istream& is, GslParamGenerator& g
return      : istream&
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
istream& operator>>( istream& is, GslParamGenerator&  ){
  
  return is;
}


/*-----------------------------------------------------------------------------
name        : convertParameters
description : write conversion routines
parameters  : /
return      : string
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
string GslParamGenerator::convertParameters(){
  ostringstream os;
  
  os << "  //copying parameters from MPL representation to GSL representation :" << endl;
  for( vector<Var>::iterator i=begin(); i!=end();++i ){
    os << "  //"<< i->getName() << " = " << i->getSrcType() << endl;
  }
  os << "  //end of parameter copy" << endl;

  return os.str();
}

/*-----------------------------------------------------------------------------
name        : freeMemory
description : write deallocation routines
parameters  : /
return      : string
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
string GslParamGenerator::freeMemory(){
  ostringstream os;
  
  os << "  //deleting GSL pointers :" << endl;
  os << "  //..."<<endl;

  return os.str();
}

/*-----------------------------------------------------------------------------
name        : addParam
description : add parameter to the list
parameters  : /
return      : string
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
void GslParamGenerator::addParam( const string& name, const string& srcType, const string& targType ){
  Var param;
  param.setName( name );
  param.setSrcType ( srcType );
  param.setTargetType( targType );
  
  push_back( param );
}


