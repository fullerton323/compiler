#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class syntaxparser{

public:

	syntaxparser(string lexfilename);

	void Rat10F();
	void OptFunctionDefinitions();
	void OptDeclarationList();
	bool StatementList();
	bool DeclarationList();
	bool Declaration();
	bool Statement();

private:
	
	ifstream file;
	string lexeme, token;
};