#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		string filename = lexfilename;
		ifstream file(filename);
		
}


bool syntaxparser::Function(){
	
	bool bFunction = false;

	file >> token >> lexeme;
	if( lexeme == "function");


}

bool syntaxparser::FunctionDefinitions(){
	bool bFunctionDefinitions = false;

	if(Function() && FunctionDefinitions()){
		bFunctionDefinitions = true;
		cout<<"<Function Definitions> ::= <Function><Function Definitions>"<<endl;
	}else if(Function()){
		bFunctionDefinitions = true;
		cout<<"<Function Definitions> ::= <Function><Function Definitions>"<<endl;

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

bool syntaxparser::DeclarationList(){
	bool bDeclarationList = false;
	if (Declaration() && DeclarationList()){
		bDeclarationList = true;
		cout << "<DeclarationList> ::= <Declaration>;<DeclarationList>" << endl;
	}
	else if (Declaration()){
		bDeclarationList = true;
		cout << "<DeclarationList> ::= <Declaration>" << endl;
	}
	else
		cout << "Error: Declaration List" << endl;
	return DeclarationList;
}

bool syntaxparser::Declaration(){
	bool bDeclaration = false;
	if (Qualifer() && IDs()){
		bDeclaration = true;
		cout << "<Declaration> ::= <Qualifier> <IDs>" << endl;
	}
	else
		cout << "Error: Declaration" << endl;
	return bDeclaration;
}

bool syntaxparser::Statement(){
	bool bStatement = false;
	if (Compound()){
		bStatement = true;
		cout << "<Statement> ::= <Compound>" << endl;
	}
	else if (Assign()){
		bStatement = true;
		cout << "<Statement> ::= <Assign>" << endl;
	}
	else if (If()){
		bStatement = true;
		cout << "<Statement> ::= <If>" << endl;
	}
	else if (Return()){
		bStatement = true;
		cout << "<Statement> ::= <Return>" << endl;
	}
	else if (Write()){
		bStatement = true;
		cout << "<Statement> ::= <Write>" << endl;
	}
	else if (Read()){
		bStatement = true;
		cout << "<Statement> ::= <Read>" << endl;
	}
	else if (While()){
		bStatement = true;
		cout << "<Statement> ::= <While>" << endl;
	}
	else
		cout << "Error : <Statement>" << endl;
	return bStatement;
}
