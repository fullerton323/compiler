#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class syntaxparser{

public:

	syntaxparser(string lexfilename);

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

private:
	
	
	string lexeme, token;
	string filename;
	ifstream file;
};