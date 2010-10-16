#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		string filename = lexfilename;
		ifstream file(filename);
		
}

bool FunctionDefinitions(){

}

bool syntaxparser::StatementList(){
	
	if(Statement())
		cout<<"<Statement>"<<endl;
	else if(Statement() && StatementList()){
		cout<<"<Statement> <Statement List>"<<endl;
	}
}


bool syntaxparser::OptDeclarationList(){
	
	if(DeclarationList())
		cout<<"<DeclarationList>"<<endl;
	else 
		cout<<"<Empty>"<<endl;
}

bool syntaxparser::OptFunctionDefinitions(){

	if(FunctionDefinitions())
		cout<<"<FunctionDefinitions>"<<endl;
	else 
		cout<<"<Empty>"<<endl;
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
