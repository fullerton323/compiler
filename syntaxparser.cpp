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

bool syntaxparser::DeclarationList(){
	bool bDeclarationList = false;
	if (Declaration()){
			if(lexeme == ";"){
				file >> token >> lexeme;
				if(DeclarationList()){
					bDeclarationList = true;
					cout << "<DeclarationList> ::= <Declaration>;<DeclarationList>" << endl;
				}
				
				bDeclarationList = true;
				cout << "<DeclarationList> ::= <Declaration>" << endl;
			}		
	}
	else
		cout << "Error: Declaration List" << endl;
	return bDeclarationList;
}

bool syntaxparser::Declaration(){
	bool bDeclaration = false;
	if (Qualifier() && IDs()){
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

bool syntaxparser::Qualifier(){
	bool bQualifier = false;
	if (token == "int" || token =="boolean" || token == "real")
		bQualifier = true;
	file >> token >> lexeme;
	return bQualifier;
}

bool syntaxparser::IDs(){
	bool bIDs = false;
	if(token == "identifier"){
		file >> token >> lexeme;
		if (lexeme == ","){
			file >> token >> lexeme;
			if(IDs()){
				bIDs = true;
				cout << "<IDs> ::= <Identifier>, <IDs>" << endl;
			}
		}
		bIDs = true;
		cout << "<IDs> ::= <Identifier>" << endl;
	}
	else
		cout << "ERROR: <IDs>" << endl;
	return bIDs;
}

bool syntaxparser::Compound(){
	bool bCompound = false;
	if (lexeme == "{"){
		file >> token >> lexeme;
		if(StatementList()){
			if(lexeme == "}"){
				bCompound = true;
				cout << "<compound> ::= { <Statement List> }" << endl;
				file >> token >> lexeme;
			}
		}
	}
	return bCompound; 
}

bool syntaxparser::Assign(){
	bool bAssign = false;
	if (token == "identifier"){
		file >> token >> lexeme;
		if (lexeme == ":="){
			file >> token >> lexeme;
			if (Expression()){
				if(lexeme == ";"){
					bAssign = true;
					cout << "<Assign> ::= <Identifier> := <Expression>;" << endl;
				}
			}
		}
	}
	else
		cout << "ERROR: <Assign>" << endl;
	return bAssign;
}

bool syntaxparser::If(){
	bool bIf = false;
	if(token == "if"){
		file >> token >> lexeme;
		if (lexeme == "("){
			file >> token >> lexeme;
			if (Condition()){
				if (lexeme == ")"){
					if (Statement()){
						if (token == "endif"){
							file >> token >> lexeme;
							bIf = true;
							cout << "<If> ::= if ( <Condition> ) <Statement> endif" << endl;
						}
					}
				}
			}
		}
	}
	else
		cout << "Error: <If>" << endl;
	return bIf;
}

bool syntaxparser::Return(){
	bool bReturn = false;
	if (token == "return"){
		file >> token >> lexeme;
		if (lexeme == ";"){
			file >> token >> lexeme;
			bReturn = true;
			cout << "<Return> ::= return;" << endl;
		}
		else if (Expression()){
			if (lexeme == ";"){
				file >> token >> lexeme;
				bReturn = true;
				cout << "<Return> ::= return <Expression>;" << endl;
			}
		}
	}
	else
		cout << "ERROR: <Return>" << endl;
	return bReturn;
}
