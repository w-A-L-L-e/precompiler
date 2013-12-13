/*=============================================================================
author        : Walter Schreppers
filename      : gslapigenerator.cpp
created       : 18/3/2006 at 03:45:46
modified      : 6/5/2006
version       : 
copyright     : Walter Schreppers
bugreport(log): 
=============================================================================*/

#include "gslapigenerator.h"
#include "defs.h"

#include "ParseElem.h"
#include <map>

using namespace std;

/*-----------------------------------------------------------------------------
name        : init
description : initialize private locals
parameters  : 
return      : void
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
void GslApiGenerator::init(){
  row=1;
  col=1;
  headerName="";
  functionCode="";
  funcName="";
  funcType="";
}



/*-----------------------------------------------------------------------------
name        : baseName
description : returns string without file extension
parameters  : 
return      : 
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
string GslApiGenerator::baseName( const string& s ){
  string::size_type pos;
  string result = s;
  if( (pos=s.rfind("."))!=string::npos ){
    result=s.substr( 0,pos );
  }
  return result;
}

/*-----------------------------------------------------------------------------
name        : setHeaderBaseName
description : sets a custom headerBaseName (usefull for when it differs from 
              the header filename.
parameters  : 
return      : 
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
void GslApiGenerator::setHeaderBaseName( const string& baseName ){
  headerBaseName = baseName;
}


/*-----------------------------------------------------------------------------
name        : GslApiGenerator
description : constructor
parameters  : 
return      : 
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
GslApiGenerator::GslApiGenerator( const string& headerName){
  init();
  this->headerName = headerName;
  setHeaderBaseName( baseName( headerName ) );
}


/*-----------------------------------------------------------------------------
name        : ~GslApiGenerator
description : destructor
parameters  : 
return      : 
exceptions  : 
algorithm   : trivial
-----------------------------------------------------------------------------*/
GslApiGenerator::~GslApiGenerator(){

}

/*-----------------------------------------------------------------------------
name        :dumpq
description :dump the pQueue literally to out
parameters  :ofstream& out
return      :/
exceptions  :/
algorithm   :trivial
-----------------------------------------------------------------------------*/
void GslApiGenerator::dumpq(ofstream& out){
  while(pQueue.size()>0) moveToken(out);
  pQueue.clear();
}
    
    

/*-----------------------------------------------------------------------------
name        :checkStatementEnd
description :return true if the pQueue contains a statement ending
which is open_brace, semi_colon or close_brace
Added check for bArrayConstruct to keep adding tokens if
we found the closing scope, for pending new variable declarations.
parameters  :/
return      :/
exceptions  :/
algorithm   :trivial
-----------------------------------------------------------------------------*/
bool GslApiGenerator::checkStatementEnd(){
  int tok=pQueue[pQueue.size()-1].token;
  if( (tok == open_brace)  ||
      (tok == semi_colon)  ||
      (tok == close_brace) 
    ) {
	return 1;
  }
  else{ 
	return 0;
  }
}


/*-----------------------------------------------------------------------------
name        : updatePos
description : update the line and col private locals
parameters  : const string& lexSt
return      : /
exceptions  : /
algorithm   : trivial
-----------------------------------------------------------------------------*/
void GslApiGenerator::updatePos( const string& lexStr ){
  for( string::const_iterator i=lexStr.begin(); i!=lexStr.end(); ++i ){
    if( *i == '\n' ){
      col = 1;
      row++; 
    }
    else{
      col++;
    }
  }
}

/*-----------------------------------------------------------------------------
name        :popToComma
description :skip tokens until comma or close parentheses found, 
             used in parameter parsing
parameters  :  
return      :string 
exceptions  :/
algorithm   : 
-----------------------------------------------------------------------------*/
int GslApiGenerator::popToComma(){
  while( (pQueue.size() > 0 ) && 
         (pQueue.get(0).token != close_par ) && 
         (pQueue.get(0).token != comma )
       )
  {
    pQueue.pop();
  }
  return pQueue.get(0).token;
}

/*-----------------------------------------------------------------------------
name        :getNewWord
description :skip tokens until word token found and return it
parameters  :  
return      :string 
exceptions  :/
algorithm   : 
-----------------------------------------------------------------------------*/
string GslApiGenerator::getNewWord(){
  if( pQueue.size()>0 )pQueue.pop();
  while( (pQueue.size()>0) &&(pQueue.get(0).token != sym_word )){
    pQueue.pop();
  }
  return pQueue.get(0).text;
}

/*-----------------------------------------------------------------------------
name        :getWord
description :get a word token
parameters  :  
return      :string 
exceptions  :/
algorithm   : 
-----------------------------------------------------------------------------*/
string GslApiGenerator::getWord(){
  while( (pQueue.size()>0) &&(pQueue.get(0).token != sym_word )){
    pQueue.pop();
  }
  return pQueue.get(0).text;
}

/*-----------------------------------------------------------------------------
name        :stripWhite
description :strip whitespaces
parameters  :string 
return      :string 
exceptions  :/
algorithm   : 
-----------------------------------------------------------------------------*/
string GslApiGenerator::stripWhite( const string& s ){
  string retType="";
  for( string::size_type i=0;i<s.length();i++){
    if(
        ( s[i]!=' ' ) &&
        ( s[i]!='\t') &&
        ( s[i]!='\n') &&
        ( s[i]!='\r')
        
      )
    {
      retType+=s[i];
    }
  }
  
  return retType;
}


/*-----------------------------------------------------------------------------
name        : getNewType
description : type mapping (here hard encoded for gsl but this could also be 
              done with a conversion configuration file, for now it's fine this
              way...
parameters  : string with original type
return      : string with new mpl type (also update oldtype
exceptions  :/
algorithm   : 
-----------------------------------------------------------------------------*/
string GslApiGenerator::getNewType( string& oldType ){
  map<string,string> typeMap;
  typeMap["gsl_matrix"] 	= string("MatrixPtr_m");
  typeMap["gsl_vector"] 	= string("MatrixPtr_v");
  typeMap["int"] 		= string("MatrixPtr_i");
  typeMap["gsl_permutation"] 	= string("MatrixPtr_p");
  typeMap["MpIeee"] 		= string("MatrixPtr_elem");
  typeMap["const gsl_matrix"] 		= string("const MatrixPtr_m");
  typeMap["const gsl_vector"] 		= string("const MatrixPtr_v");
  typeMap["const int"] 			= string("const MatrixPtr_i");
  typeMap["const gsl_permutation"] 	= string("const MatrixPtr_p");
  typeMap["const MpIeee"] 		= string("const MatrixPtr_elem");
  
  if( stripWhite(oldType) == "const" ){
    oldType += " " + getNewWord();
  }
  string newType=oldType+" ";
  map<string,string>::iterator pos = typeMap.find( oldType );
  if( pos != typeMap.end() ) newType=typeMap[oldType]+" ";
  
  //cout << "oldType="<<oldType<<" -> newType="<<newType<<endl;
  
  return newType;
}

string GslApiGenerator::getParamName(){
  string retTxt=getNewWord();
  cout << "param name = " << retTxt<<endl;
  return retTxt;
}


/*-----------------------------------------------------------------------------
name        :handleParams
description :reads gsl function parameters
parameters  :/
return      :/
exceptions  :/
algorithm   : 
-----------------------------------------------------------------------------*/
bool GslApiGenerator::handleParams(){
  if( pQueue.size() == 0 ) return true;
  
  string oldType = getWord();
  string strParamType = getNewType(oldType);
  functionCode+=strParamType;
  
  string strParamName = getParamName();
  functionCode+=strParamName+" ";
  
  gslParam.addParam( strParamName, oldType, strParamType );  
  
  if( popToComma() == close_par ){
    functionCode+= " )\n";
    return true;
  }
  else{
    functionCode+=" ," ;
  }
  
  //todo keep the parameters in handy for use later in the function body
  //functionParameters.add( strParamType, strParamName );
  
  //if( pQueue.get(0).token == comma ) pQueue.pop();
   
  return false;
}




/*-----------------------------------------------------------------------------
name        :functionBody
description :writes a conversion function implementation
             (api function for use in mpl) to c++ file
parameters  :ofstream& out 
return      :/
exceptions  :/
algorithm   : 
-----------------------------------------------------------------------------*/
string GslApiGenerator::functionBody(){
  ostringstream os;
  
  os << "{" << endl;
  os << gslParam.convertParameters() << endl;
  os << "  // the actual gsl function call here!!!" << endl;
  os << gslParam.freeMemory() << endl;  
  
  os << "}" << endl << endl;

  gslParam.clear(); //reset variables list
  
  return os.str();
}


/*-----------------------------------------------------------------------------
name        :functionDefinition
description :writes a conversion function definition
             (api function for use in mpl) to .h header file
parameters  :/
return      :/
exceptions  :/
algorithm   : 
-----------------------------------------------------------------------------*/
string GslApiGenerator::functionDefinition(){
  string retStr="";
  retStr+= "\n// function : " + funcName +"\n";
  retStr+= funcType+" GslApi_"+headerBaseName+"::"+funcName+"(";
  
  return retStr;
}



/*-----------------------------------------------------------------------------
name        :convertStatement
description :specific conversion of gsl headers
parameters  :ofstream& out 
return      :/
exceptions  :/
algorithm   : we only add gsl functions belonging to the current header by
using information from the header filename, functions belonging to the file 
are of the form gsl_linalg_... when the header is called gsl_linalg.h
This prefix (called headerBaseName can also be set using the -basename command
line option).
-----------------------------------------------------------------------------*/
void GslApiGenerator::convertStatement(ofstream& out){
 ParseElem pElem = pQueue.get(0);
  static string prevWord="";

  if( pElem.token == sym_word ){
    string nextWord = getWord();
//    if( (pElem.token == sym_word) && (pElem.text.find( headerBaseName  )!=string::npos)) {
    if( nextWord.find( headerBaseName )!=string::npos ){
      funcType = prevWord;
      funcName = pElem.text.substr( headerBaseName.length()+1, 
                                          (pElem.text.length()-headerBaseName.length())-1 );
      
      cout << "funcType=" << funcType << endl;
      cout << "funcName=" << funcName << endl;
    
      while( (pQueue.size()>0) &&(pQueue.get(0).token != open_par )){
        pQueue.pop();
      }
      pQueue.pop(); //the '('
    
      bool foundFunc=false;
      while( (pQueue.size()>0) && !(foundFunc=handleParams()) );
      if( foundFunc ){
         out << functionDefinition() << flush;     
         out << functionCode << flush;  //will become depricated, replaced by function
         out << functionBody() << flush;
      }
    
      functionCode="";
    }//function name
    
    prevWord = pElem.text; //this will be the returntype
  }//word found
  if( pQueue.size()>0 ) pQueue.pop();
}




/*-----------------------------------------------------------------------------
name        :showQueue
description :show queue contents on standard error stream cerr
             used for debugging purposes
parameters  :/
return      :/
exceptions  :/
algorithm   :trivial
-----------------------------------------------------------------------------*/
void GslApiGenerator::showQueue(){
      cout<<"queue contents: ";
      for(vector<ParseElem>::iterator p=pQueue.begin();p!=pQueue.end();p++){
        cout<<p->text<<" | ";
      }
      cout<<endl;
}



/*-----------------------------------------------------------------------------
name        :moveToken
description :Keep track of open_pars, etc by calling updateLocals
             remove a token from the pQueue and write it's string onto the
             ofstream out

parameters  :ofstream& out
return      :/
exceptions  :/
algorithm   :trivial
-----------------------------------------------------------------------------*/
void GslApiGenerator::moveToken(ofstream& out){
  //updateLocals();
  if(pQueue.size()>0) out<<pQueue.poptext()<<flush;
}







/*-----------------------------------------------------------------------------
name        :updateQueue
description :add last lexer token and lexer text to queue 
             if the queue contains a complete statement
             call convertStatement repeadetly until pQueue is empty or 
             does not change anymore
parameters  :/
return      :/
exceptions  :/
algorithm   :
-----------------------------------------------------------------------------*/
void GslApiGenerator::updateQueue( int token, string text, ofstream& out){
  pQueue.add(token,text);
  
  if((pQueue.size()>0)&&(checkStatementEnd())){
    pQueue.changed=1;
    while((pQueue.changed)&&(pQueue.size()>0)){ //keep on calling convertStatement until it doesn't change anything anymore
      pQueue.changed=0;    
      convertStatement(out);
    }
    
    
    
    //just dump rest of queue literally to outfile
    #ifdef _DEBUG_
      cout<<"dumping this queue literally:"<<endl;
      showQueue();
      cout<<"     at line "<<pConf->getLine()<<endl;
    #endif
    dumpq(out);
  }
}



/*-----------------------------------------------------------------------------
name        : parse
description : generate source files for mpl to use gsl (input file is gsl header)
parameters  : ofstream& out, char* lexText, int lexToken
return      : /
exceptions  : /
algorithm   : trivial
-----------------------------------------------------------------------------*/
void GslApiGenerator::parse( ofstream& out, char* lexText, int lexToken){
  string strLex="";
  strLex+=lexText;
      
  updateQueue(lexToken,lexText,out);
        
//  if(bMain){
//    if(lexToken==open_brace){
//      bMain=0;
//      setFloatPrecision(out); //the commandline precision settings (if bNoDefault == false )
//      writePrecision(out);    //precision setting in xml file =pcdata in <init> tag
///      writeInit(out);         //if init option was specified.
//    }
//  }
        
}


/*-----------------------------------------------------------------------------
name        : writeHeader 
description : writes includes and initialize code if necessary in output file
parameters  : ofstream& out
return      : /
exceptions  : /
algorithm   : trivial
-----------------------------------------------------------------------------*/
void GslApiGenerator::writeHeader( ofstream& out ){
  out << "#include \""<< headerName <<"\""<<endl;
}

/*-----------------------------------------------------------------------------
name        : writeFooter
description : appends stuff to end of generated file (maybe some memory cleanup code in future?)
parameters  : ofstream& out
return      : /
exceptions  : /
algorithm   : trivial
-----------------------------------------------------------------------------*/
void GslApiGenerator::writeFooter( ofstream& out ){
  out << "//end "<<headerBaseName<<endl;
}



