#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		filename = lexfilename;
		file.open(filename);
		lineNumber = 0;
		
}


bool syntaxparser::Lexer(){

	bool flag = true;

	file >> token >> lexeme;

	
		while(token == "EndofLine")
		{
			lineNumber++;
			file >> token >> lexeme;
			
		}


	cout<< left << "Token: " << setw(14) <<token << "Lexeme: " << setw(14) << lexeme <<endl; 
	
	return flag;
}

void syntaxparser::Rat10F(){
	Lexer();


	

	
	if( lexeme == "$$"){
		Lexer();


		OptFunctionDefinitions();
		

		if( lexeme == "$$"){
			Lexer();


			OptDeclarationList();
			StatementList();
			
			

			if( lexeme == "$$"){
				Lexer();
			}
			else if( lexeme != "$$")
			cout<<"Errror no Finishing $$"<<endl;
		}
		else if( lexeme != "$$")
			cout<<"Errror no $$ after Function definitions"<<endl;

	}
	else if( lexeme != "$$")
		cout<<"Errror no $$"<<endl;

}


bool syntaxparser::OptFunctionDefinitions(){

	bool OptFunctionDefinitions =false;

	if(FunctionDefinitions()){
		cout<<"<Opt Function Definitions> ::= <FunctionDefinitions>"<<endl;
		OptFunctionDefinitions = true;
	}
	else if(Empty()) {

		cout<<"<Opt Function Definitions> ::= <Empty>"<<endl;
		OptFunctionDefinitions= true;
	}

	return OptFunctionDefinitions;
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

bool syntaxparser::Function(){
	
	bool bFunction = false;

	
	if( lexeme == "function"){
		Lexer();

		if(token == "identifier"){
			Lexer();

			if(lexeme == "["){
				Lexer();

				if(OptParameterList()){

					if(lexeme == "]"){
						Lexer();

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

bool syntaxparser::OptParameterList(){
	bool OptParameterList = false;

	if(ParameterList()){
		cout<<"<Opt Parameter List> ::= <Parameter List>"<<endl;
		OptParameterList = true;
	}else if(Empty()){
		cout<<"<Opt Parameter List> ::= <empty>"<<endl;
	}
	

	return OptParameterList;
}

bool syntaxparser::ParameterList(){

	bool bParameterList= false, flag=false;

	if(Parameter()){

		if(lexeme ==","){
			Lexer();

			if(ParameterList()){
				bParameterList= true;
				cout<<"<Parameter List> ::= <Parameter> , <Parameter List>"<<endl;
				flag=true;

			}

			bParameterList= true;
			if(flag == false)
			cout<<"<Parameter List> ::= <Parameter>"<<endl;
		}
		bParameterList= true;
	}

	return bParameterList;
}

bool syntaxparser::Parameter(){
	
	bool Parameter = false;

	if(IDs()){

		if(lexeme ==":"){
			Lexer();
			if(Qualifier()){
				Parameter = true;
				cout<<"<Parameter> ::= <IDS> : <Qulifier>"<<endl;

			}
		}else{
			cout<<"Missing ':'"<<endl;
		}
	}

	return Parameter;
}


bool syntaxparser::Qualifier(){
	bool bQualifier = false;
	if (lexeme == "int" || lexeme =="boolean" || lexeme == "real")
	{
		bQualifier = true;
		Lexer();
	}
	

	return bQualifier;
}

bool syntaxparser::Body(){
	bool body = false;

	if(lexeme == "{"){
		Lexer();

		if(StatementList()){
			
			if(lexeme == "}"){
				Lexer();

				body = true;
				cout<<"<Body> ::= { <Statement List> }"<<endl;
			}else{
				cout<<"Missing ']'"<<endl;
			}
		}

	}else{
		cout<<"Missing '{'"<<endl;
	}

	return body;

}


bool syntaxparser::OptDeclarationList(){
	
	bool OptDeclarationList=false;

	if(DeclarationList()){

		cout<<"<OptDeclarationList> ::= <DeclarationList>"<<endl;
		OptDeclarationList = true;
	}
	else if(Empty()){
		cout<<"<OptDeclarationList> ::= <Empty>"<<endl;
		OptDeclarationList = true;
	}

	return OptDeclarationList;
}


bool syntaxparser::DeclarationList(){
	bool bDeclarationList = false;
	if (Declaration()){
			if(lexeme == ";"){
				Lexer();
				if(DeclarationList()){
					bDeclarationList = true;
					cout << "<DeclarationList> ::= <Declaration>;<DeclarationList>" << endl;
				}
				
				bDeclarationList = true;
				cout << "<DeclarationList> ::= <Declaration>" << endl;
			}		
	}
	
	return bDeclarationList;
}

bool syntaxparser::Declaration(){
	bool bDeclaration = false;
	if (Qualifier() && IDs()){
		bDeclaration = true;
		cout << "<Declaration> ::= <Qualifier> <IDs>" << endl;
	}
	
	return bDeclaration;
}


bool syntaxparser::IDs(){
	bool bIDs = false;
	if(token == "identifier"){
		Lexer();
		if (lexeme == ","){
			Lexer();
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


bool syntaxparser::Compound(){
	bool bCompound = false;
	if (lexeme == "{"){
		Lexer();
		if(StatementList()){
			if(lexeme == "}"){
				bCompound = true;
				cout << "<compound> ::= { <Statement List> }" << endl;
				Lexer();
			}
		}
	}
	return bCompound; 
}


bool syntaxparser::Assign(){
	bool bAssign = false;
	if (token == "identifier"){
		Lexer();
		if (lexeme == ":="){
			Lexer();
			if (Expression()){
				if(lexeme == ";"){
					Lexer();
					bAssign = true;
					cout << "<Assign> ::= <Identifier> := <Expression>;" << endl;
				}
			}
		}
	}
	
	return bAssign;
}


bool syntaxparser::If(){
	bool bIf = false;
	if(token == "if"){
		Lexer();
		if (lexeme == "("){
			Lexer();
			if (Condition()){
				if (lexeme == ")"){
					Lexer();
					if (Statement()){
						if (token == "endif"){
							Lexer();
							bIf = true;
							cout << "<If> ::= if ( <Condition> ) <Statement> endif" << endl;
						}
					}
				}
			}
		}
	}
	
	return bIf;
}


bool syntaxparser::Return(){
	bool bReturn = false;
	if (lexeme == "return"){
		Lexer();
		if (lexeme == ";"){
			Lexer();
			bReturn = true;
			cout << "<Return> ::= return;" << endl;
		}
		else if (Expression()){
			if (lexeme == ";"){
				Lexer();
				bReturn = true;
				cout << "<Return> ::= return <Expression>;" << endl;
			}
		}
	}
	
	return bReturn;
}


bool syntaxparser::Write(){
	bool bWrite = false;
	if (token == "write"){
		Lexer();
		if (lexeme == "("){
			Lexer();
			if (Expression()){
				if (lexeme == ")"){
					Lexer();
					if (lexeme == ";"){
						Lexer();
						bWrite = true;
						cout << "<Write> ::= write ( <Expression> );" << endl;
					}
				}
			}
		}
	}
	
	return bWrite;
}


bool syntaxparser::Read(){
	bool bRead = false;
	if (token == "read"){
		Lexer();
		if (lexeme == "("){
			Lexer();
			if (IDs()){
				if (lexeme == ")"){
					Lexer();
					if (lexeme == ";"){
						Lexer();
						bRead = true;
						cout << "<Read> ::= read ( <IDs> );" << endl;
					}
				}
			}
		}
	}
	
	return bRead;
}

bool syntaxparser::While(){
	bool bWhile = false;
	if (token == "while"){
		Lexer();
		if (lexeme == "("){
			Lexer();
			if (Condition()){
				if (lexeme == ")"){
					Lexer();
					if (Statement()){
						bWhile = true;
						cout << "<While> ::=( <Condition> ) <Statement>" << endl;
					}
				}
			}
		}
	}
	
	return bWhile;
}


bool syntaxparser::Condition(){
	bool bCondition = false;
	if (Expression() && Relop() && Expression()){
		bCondition = true;
		cout << "<Condition> :== <Expression> <Relop> <Expression>" << endl;
	}
	else
		cout << "ERROR: <Condition>" << endl;
	return bCondition;
}



bool syntaxparser::Relop(){

	bool Relop = false;

	if(lexeme == "="){
		Lexer();
		Relop = true;
		cout<<"<Relop> ::= =" << endl;
	}else if(lexeme =="/="){
		Lexer();
		Relop = true;
		cout<<"<Relop> ::= /=" << endl;
	}else if(lexeme ==">"){
		Lexer();
		Relop = true;
		cout<<"<Relop> ::= >" << endl;
	}else if(lexeme =="<"){
		Lexer();
		Relop = true;
		cout<<"<Relop> ::= <" << endl;
	}else if(lexeme =="=>"){
		Lexer();
		Relop = true;
		cout<<"<Relop> ::= =>" << endl;
	}else if(lexeme =="<="){
		Lexer();
		Relop = true;
		cout<<"<Relop> ::= <=" << endl;
	}else 
		cout<<"Missing Relop"<<endl;

	return Relop;
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
		Lexer();
		if (Term() && ExpressionPrime()){
			bExpressionPrime = true;
			cout << "<ExpressionPrime> ::= +<Term><ExpressionPrime>" << endl;
		}
	}
	else if (lexeme == "-"){
		Lexer();
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
	
	return bTerm;
}

bool syntaxparser::TermPrime(){
	bool bTermPrime = false;
	if (lexeme == "*"){
		Lexer();
		if (Factor() && TermPrime()){
			bTermPrime = true;
			cout << "<TermPrime> ::= *<Factor><TermPrime>" << endl;
		}
	}
	else if (lexeme == "/"){
		Lexer();
		if (Factor() && TermPrime()){
			bTermPrime = true;
			cout << "<TermPrime> ::= /<Term><FactorPrime>" << endl;
		}
	}
	else
		cout << "<TermPrime> ::= e" << endl;
	return bTermPrime;
}


bool syntaxparser::Factor(){

	bool Factor = false;

	if(lexeme == "-"){
		Lexer();

		if(Primary()){
			Factor = true;
			cout<<"<Factor> ::= -<Primary>"<<endl;

		}
	}else if(Primary()){
		Factor = true;
		cout<<"<Factor> ::= <Primary>"<<endl;
	}
	return Factor;
}




bool syntaxparser::Primary(){
	bool Primary = false, flag=true;

	if(token == "identifier" ){
		Lexer();


		if(lexeme == "["){
			Lexer();

			if(IDs()){

				if(lexeme == "]"){
					Lexer();
					Primary = true;
					cout<<"<Primary> ::= <identifier> [ <IDs> ]"<<endl;
					flag = false;

				}
			}

		}

		if( flag == true){
			Primary = true;
			cout<<"<Primary> ::= <identifier>"<<endl;
		}

	}else if(token == "integer"){
		Lexer();
		Primary = true;
		cout<<"<Primary> ::= <integer>"<<endl;

	}else if(token == "real"){
		Lexer();
		Primary = true;
		cout<<"<Primary> ::= <real>"<<endl;
	}else if(token == "true"){
		Lexer();
		Primary = true;
		cout<<"<Primary> ::= <true>"<<endl;
	}else if(token == "false"){
		Lexer();
		Primary = true;
		cout<<"<Primary> ::= <false>"<<endl;
	}else
		cout<<"Missing Primary"<<endl;

		return Primary;

}



bool syntaxparser::Empty(){
	bool bEmpty = true;
	cout << "<Empty> ::= e" << endl;
	return bEmpty;
}
