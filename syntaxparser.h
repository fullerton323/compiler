/*
 * Authors: Bryan Perez & Charles Wang
 * CPSC 323 - Fall 2010 (11:30-12:45)
 * Assignment # 3

 Description: The header file for the Syntax Analyzer. 

**/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "generateassembly.h"

using namespace std;

class syntaxparser{

public:

	syntaxparser(string lexfilename, string productionfile, string assemblyfile);

	void Rat10F();
	bool OptFunctionDefinitions();
	bool OptDeclarationList();
	bool StatementList();
	bool FunctionDefinitions();
	bool DeclarationList();
	bool Declaration();
	bool Statement();
	bool Function();
	bool OptParameterList();
	bool ParameterList();
	bool Parameter();
	bool Body();
	bool Qualifier();
	bool IDs();
	bool Compound();
	bool Assign();
	bool If();
	bool Return();
	bool Write();
	bool Read();
	bool While();
	bool Condition();
	bool Relop();
	bool Factor();
	bool Primary();
	bool Expression();
	bool ExpressionPrime();
	bool Term();
	bool TermPrime();
	bool Empty();
	bool Lexer();
	void setDisplay();
	void print();
	void exception();
	void error(string message);
	void printproduction(string message);

private:

	string lexeme, token; //variables to store the lexeme and token values
	string filename; // stores the filename
	ifstream file;
	int lineNumber; // holds the line number for error purposes
	bool displayFlag; // flag for displaying production rules
	ofstream outfile;
	generateassembly project3;
	string assemblyfilename;
};