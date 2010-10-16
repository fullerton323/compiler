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
	

private:
	
	ifstream file;
	string lexeme, token;
};