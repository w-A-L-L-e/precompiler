/*=============================================================================
author        : Walter Schreppers
filename      : gslapigenerator.h
created       : 18/3/2006 at 03:45:46
modified      : 
version       : 
copyright     : Walter Schreppers
bugreport(log): 
=============================================================================*/

#ifndef GSLAPIGENERATOR_H
#define GSLAPIGENERATOR_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "ParseQueue.h"
#include "gslparamgenerator.h"

using namespace std;

class GslApiGenerator {

  public:
    //constructor & destructor
    //==========================
    GslApiGenerator( const string& );
    ~GslApiGenerator();

    //public members
    //==============
    void parse( ofstream& out, char* lexText, int lexToken );
    void writeHeader(  ofstream& out );
    void writeFooter(  ofstream& out );
    void setHeaderBaseName( const string& baseName );
    
  private:
    //private members:
    //================
    void init();
    void updatePos( const string& );
    string baseName( const string& );
    void convertStatement(ofstream& out);
    void showQueue();
    void updateQueue(int token, string text, ofstream& out);
    bool checkStatementEnd();
    void dumpq( ofstream& out );
    void moveToken( ofstream& out );
    bool handleParams();
    string getNewType(string&);
    string getNewWord();
    string getWord();
    int popToComma();
    string getParamName();
    string stripWhite( const string& );
    string functionDefinition();
    string functionBody();           

    //private locals:
    //===============
    unsigned int row, col;
    string headerName,headerBaseName,funcName,funcType;
    ParseQueue pQueue;
    string functionCode;
    GslParamGenerator gslParam;
    
}; //end of class GslApiGenerator

#endif

