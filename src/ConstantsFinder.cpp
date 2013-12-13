/*=============================================================================
author        : Walter Schreppers
filename      : ConstantsFinder.cpp
created       : 12/5/2003 at 16:50:57
modified      : 
version       : 
copyright     : Walter Schreppers
bugreport(log): 
=============================================================================*/

#include "ConstantsFinder.h"
#include "defs.h"

/*-----------------------------------------------------------------------------
name        : init
description : initialize private locals
parameters  : 
return      : void
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
void ConstantsFinder::init(){
  line = 1;
  col  = 1;
}


/*-----------------------------------------------------------------------------
name        : ConstantsFinder
description : constructor
parameters  : 
return      : 
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
ConstantsFinder::ConstantsFinder(){
  init();
}


/*-----------------------------------------------------------------------------
name        : ~ConstantsFinder
description : destructor
parameters  : 
return      : 
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
ConstantsFinder::~ConstantsFinder(){

}



/*-----------------------------------------------------------------------------
name        : updatePos
description : update the line and col private locals
parameters  : const string& lexSt
return      : /
exceptions  : /
algorithm   : trivial
-----------------------------------------------------------------------------*/
void ConstantsFinder::updatePos( const string& lexStr ){
  for( string::const_iterator i=lexStr.begin(); i!=lexStr.end(); ++i ){
    if( *i == '\n' ){
      col = 1;
      line++; 
    }
    else{
      col++;
    }
  }
}


/*-----------------------------------------------------------------------------
name        : find
description : find integer and decimal tokens, keep track of line and column
parameters  : ofstream& in, char* text, int token
return      : /
exceptions  : /
algorithm   : trivial
-----------------------------------------------------------------------------*/
void ConstantsFinder::find( ofstream& out, char* lexText, int lexToken ){
  string lexStr;
  lexStr += lexText;
  if( ( lexToken == integer ) || ( lexToken == decimal ) ){
    out << "constant: '" << lexStr << "' at line " << getLine() << ", col " << getCol() << endl;
  }
  updatePos( lexStr );
}

