/*
 * Authors: Bryan Perez & Charles Wang
 * CPSC 323 - Fall 2010 (11:30-12:45)
 * Assignment # 2 - Syntax Analyzer

 Description: The header file for the Syntax Analyzer. 

**/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class syntaxparser{

public:

	syntaxparser(string lexfilename, string profile);

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

	string lexeme, token, lexemeBuffer, tokenBuffer;
	string filename;
	ifstream file;
	int lineNumber;
	bool displayFlag;
	ofstream outfile;
};