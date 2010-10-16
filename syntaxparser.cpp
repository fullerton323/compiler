#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		string filename = lexfilename;
		ifstream file(filename);
		
}

void syntaxparser::StatementList(){

}


void syntaxparser::OptDeclarationList(){
	
}

void syntaxparser::OptFunctionDefinitions(){

}

void syntaxparser::Rat10F(){
	
	file >> token >> lexeme;
	cout<<"$$ <Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$"<<endl;

	
	if( lexeme == "$$"){
		OptFunctionDefinitions();
		file >> token >> lexeme;
		if( lexeme == "$$"){
			OptDeclarationList();
			StatementList();
			file >> token >> lexeme;
			if( lexeme == "$$");
			else if( lexeme != "$$")
			cout<<"Errror no $$"<<endl;
		}
		else if( lexeme != "$$")
			cout<<"Errror no $$"<<endl;

	}
	else if( lexeme != "$$")
		cout<<"Errror no $$"<<endl;

}

