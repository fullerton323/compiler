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
	bool body();
	bool Qualifier();
	bool IDs();
	bool Compound();
	bool Assign();
	bool If();
	bool Return();
	bool Write();
	bool Read();
	bool While();

private:
	
	ifstream file;
	string lexeme, token;
};