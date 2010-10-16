#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		string filename = lexfilename;
		ifstream file(filename);
		
}

bool FunctionDefinitions(){

}

bool syntaxparser::StatementList(){
	bool bStatementList = false;

	if(Statement() && StatementList()){

		cout<<"<Statement List> ::= <Statement>"<<endl;
		bStatementList = true;
	}
	else if(Statement()){
		cout<<"<Statement List> ::= <Statement> <Statement List>"<<endl;
		bStatementList = true;
	}

	return bStatementList;
}


bool syntaxparser::OptDeclarationList(){
	
	bool OptDeclarationList=false;

	if(DeclarationList()){

		cout<<"<OptDeclarationList> ::= <DeclarationList>"<<endl;
		OptDeclarationList = true;
	}
	else {
		cout<<"<OptDeclarationList> ::= <Empty>"<<endl;
		OptDeclarationList = true;
	}

	return OptDeclarationList;
}

bool syntaxparser::OptFunctionDefinitions(){

	bool OptFunctionDefinitions =false;

	if(FunctionDefinitions()){
		cout<<"<Opt Function Definitions> ::= <FunctionDefinitions>"<<endl;
		OptFunctionDefinitions = true;
	}
	else {
		cout<<"<Opt Function Definitions> ::= <Empty>"<<endl;
		OptFunctionDefinitions= true;
	}
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
			cout<<"Errror no Finishing $$"<<endl;
		}
		else if( lexeme != "$$")
			cout<<"Errror no $$ after Function definitions"<<endl;

	}
	else if( lexeme != "$$")
		cout<<"Errror no $$"<<endl;

}

