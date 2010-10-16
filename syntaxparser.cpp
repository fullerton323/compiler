#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		string filename = lexfilename;
		ifstream file(filename);
		
}




bool syntaxparser::body(){
	bool body = false;

	if(lexeme == "{"){
		file >> token >> lexeme;

		if(StatementList()){
			
			if(lexeme == "}"){
				file >> token >> lexeme;

				body = true;
				cout<<"<Body> ::= { <Statement List> }"<<endl;
			}
		}

	}

	return body;

}

bool syntaxparser::Parameter(){
	
	bool Parameter = false;

	if(IDs()){

		if(lexeme ==":"){

			if(Qualifier()){
				Parameter = true;
				cout<<"<Parameter> ::= <IDS> : <Qulifier>"<<endl;

			}
		}
	}

	return Parameter;
}

bool syntaxparser::ParameterList(){

	bool bParameterList= false;

	if(Parameter()){

		if(lexeme ==","){
			file >> token >> lexeme;

			if(ParameterList()){
				bParameterList= true;
				cout<<"<Parameter List> ::= <Parameter> , <Parameter List>"<<endl;

			}
			bParameterList= true;
			cout<<"<Parameter List> ::= <Parameter>"<<endl;
		}
	}

	return bParameterList;
}



bool syntaxparser::OptParameterList(){
	bool OptParameterList = false;

	if(ParameterList()){
		cout<<"<Opt Parameter List> ::= <Parameter List>"<<endl;
		OptParameterList = true;
	}else{
		cout<<"<Opt Parameter List> ::= <empty>"<<endl;
	}
	

	return OptParameterList;
}

bool syntaxparser::Function(){
	
	bool bFunction = false;

	
	if( lexeme == "function"){
		file >> token >> lexeme;

		if(token == "identifier"){
			file >> token >> lexeme;

			if(lexeme == "["){
				file >> token >> lexeme;

				if(OptParameterList()){

					if(lexeme == "]"){
						file >> token >> lexeme;

						if(OptDeclarationList()){

							if(Body()){

								bFunction = true;
								cout<<"<Function> ::= function <identifier> [ <Opt Parameter List> ] <Opt Declaration List> <Body>"<<endl;

							}
						}
					}
				}

			}else{
				cout<<"Missing '[' separator"<<endl;
			}

		}else{
				cout<<"Not an identifier"<<endl;
			}

	} else {
		cout<<"No keyword 'function'"<<endl;
	 }

	return bFunction;

}

bool syntaxparser::FunctionDefinitions(){
	bool bFunctionDefinitions = false;

	if(Function()){
		if (FunctionDefinitions()){
			bFunctionDefinitions = true;
			cout<<"<Function Definitions> ::= <Function><Function Definitions>"<<endl;
		}
		
		bFunctionDefinitions = true;
		cout << "<Function Definitions> ::= <Function>" << endl;
	}	
	return bFunctionDefinitions;
}

bool syntaxparser::StatementList(){
	bool bStatementList = false;

	if(Statement()){
		if (StatementList()){
			bStatementList = true;
			cout<<"<Statement List> ::= <Statement> <Statement List>"<<endl;
		}
		
		bStatementList = true;
		cout<<"<Statement List> ::= <Statement>"<<endl;
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

	return OptFunctionDefinitions;
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
