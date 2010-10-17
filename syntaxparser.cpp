#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		string filename = lexfilename;
		ifstream file(filename);
		
}




bool syntaxparser::Body(){
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

bool syntaxparser::Write(){
	bool bWrite = false;
	if (token == "write"){
		file >> token >> lexeme;
		if (lexeme == "("){
			file >> token >> lexeme;
			if (Expression()){
				if (lexeme == ")"){
					file >> token >> lexeme;
					if (lexeme == ";"){
						file >> token >> lexeme;
						bWrite = true;
						cout << "<Write> ::= write ( <Expression> );" << endl;
					}
				}
			}
		}
	}
	else
		cout << "ERROR: <WRITE>" << endl;
	return bWrite;
}

bool syntaxparser::Read(){
	bool bRead = false;
	if (token == "read"){
		file >> token >> lexeme;
		if (lexeme == "("){
			file >> token >> lexeme;
			if (IDs()){
				if (lexeme == ")"){
					file >> token >> lexeme;
					if (lexeme == ";"){
						file >> token >> lexeme;
						bRead = true;
						cout << "<Read> ::= read ( <IDs> );" << endl;
					}
				}
			}
		}
	}
	else
		cout << "ERROR: <READ>;" << endl;
	return bRead;
}

bool syntaxparser::While(){
	bool bWhile = false;
	if (token == "while"){
		file >> token >> lexeme;
		if (lexeme == "("){
			file >> token >> lexeme;
			if (Condition()){
				if (lexeme == ")"){
					file >> token >> lexeme;
					if (Statement()){
						bWhile = true;
						cout << "<While> ::=( <Condition> ) <Statement>" << endl;
					}
				}
			}
		}
	}
	else
		cout << "ERROR: <While>" << endl;
	return bWhile;
}

bool syntaxparser::Expression(){
	bool bExpression = false;
	if (Term() && ExpressionPrime()){
		bExpression = true;
		cout << "<Expression> ::= <Term><ExpressionPrime>" << endl;
	}
	else
		cout << "ERROR: <Expression>" << endl;
	return bExpression;
}

bool syntaxparser::ExpressionPrime(){
	bool bExpressionPrime = false;
	if (lexeme == "+"){
		file >> token >> lexeme;
		if (Term() && ExpressionPrime()){
			bExpressionPrime = true;
			cout << "<ExpressionPrime> ::= +<Term><ExpressionPrime>" << endl;
		}
	}
	else if (lexeme == "-"){
		file >> token >> lexeme;
		if (Term() && ExpressionPrime()){
			bExpressionPrime = true;
			cout << "<ExpressionPrime> ::= -<Term><ExpressionPrime>" << endl;
		}
	}
	else
		cout << "<ExpressionPrime> ::= e" << endl;
	return bExpressionPrime;
}

bool syntaxparser::Term(){
	bool bTerm = false;
	if (Factor() && TermPrime()){
		bTerm = true;
		cout << "<Term> ::= <Factor><TermPrime>" << endl;
	}
	else
		cout << "ERROR: <Term>" << endl;
	return bTerm;
}

bool syntaxparser::TermPrime(){
	bool bTermPrime = false;
	if (lexeme == "*"){
		file >> token >> lexeme;
		if (Factor() && TermPrime()){
			bTermPrime = true;
			cout << "<TermPrime> ::= *<Factor><TermPrime>" << endl;
		}
	}
	else if (lexeme == "/"){
		file >> token >> lexeme;
		if (Factor() && TermPrime()){
			bTermPrime = true;
			cout << "<TermPrime> ::= /<Term><FactorPrime>" << endl;
		}
	}
	else
		cout << "<TermPrime> ::= e" << endl;
	return bTermPrime;
}

bool syntaxparser::Empty(){
	bool bEmpty = True;
	cout << "<Empty> ::= e" << endl;
}