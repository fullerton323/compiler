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
	void StatementList();

private:
	
	ifstream file;
	string lexeme, token;
};