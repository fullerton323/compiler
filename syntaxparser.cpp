#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		filename = lexfilename;
		file.open(filename);
		lineNumber = 0;
		
}

void syntaxparser::setDisplay(){
	bool flag = true;
	char c;
	while (flag){
		cout << "Would you like to display the syntax rules? (y/n) : ";
		cin >> c;
		switch (c){
		case 'y':
			displayFlag = true;
			flag = false;
			break;
		case 'Y':
			displayFlag = true;
			flag = false;
			break;
		case 'n':
			displayFlag = false;
			flag = false;
			break;
		case 'N':
			displayFlag = false;
			flag = false;
			break;
		default:
			cout << "Please enter in a correct value (y/n)! " << endl;
			break;
		}
	}
}

bool syntaxparser::Lexer(){

	bool flag = true;

	file >> token >> lexeme;

	
		while(token == "EndofLine")
		{
			lineNumber++;
			file >> token >> lexeme;
			
		} 
	
	return flag;
}

void syntaxparser::print(){
	cout<<  endl << left << "Token: " << setw(14) <<token << "Lexeme: " << setw(14) << lexeme <<endl;
}

void syntaxparser::Rat10F(){
	setDisplay();
	Lexer(); print();

	if( lexeme == "$$"){
		if (displayFlag){
			cout << "<Rat10F> ::= $$<Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$" << endl;
		}
		
		OptFunctionDefinitions();
		
		if( lexeme == "$$"){
			Lexer(); print();


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
	Lexer();

	//check to see if the next lexeme is a function
	if (lexeme == "function"){
		print();
		if (displayFlag){
			cout<<"<Opt Function Definitions> ::= <FunctionDefinitions>"<<endl;
		}
		OptFunctionDefinitions = true;
		FunctionDefinitions(); // call the function
	}
	else{ // if no optional function definitions then its empty
		if (displayFlag){
			cout<<"<Opt Function Definitions> ::= <Empty>"<<endl;
		}
		Empty(); //call the empty function
		OptFunctionDefinitions= true;
	}
	return OptFunctionDefinitions;
}

bool syntaxparser::FunctionDefinitions(){
	bool bFunctionDefinitions = false;
	if (displayFlag){
		cout << "<Function Definitions> ::= <Function><Function Definitions>" << endl;
	}
	if(Function()){
		if (FunctionDefinitions()){
			bFunctionDefinitions = true;
			
		}
		
		bFunctionDefinitions = true;
		if (displayFlag){
			cout << "<Function Definitions> ::= <Function>" << endl;
		}
	}	
	return bFunctionDefinitions;
}

bool syntaxparser::Function(){
	
	bool bFunction = false;
	if (displayFlag){
		cout<<"<Function> ::= function <identifier> [ <Opt Parameter List> ] <Opt Declaration List> <Body>"<<endl;
	}
	
	if( lexeme == "function"){
		Lexer(); print();

		if(token == "identifier"){
			Lexer(); print();

			if(lexeme == "["){
				Lexer();

				if(OptParameterList()){

					if(lexeme == "]"){
						Lexer();

						if(OptDeclarationList()){

							if(Body()){

								bFunction = true;
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

	} 

	return bFunction;

}

bool syntaxparser::OptParameterList(){
	bool OptParameterList = false;
	//check to see if the optional parameter list is empty
	if (lexeme != "]"){
		print();
		if (displayFlag){
			cout<<"<Opt Parameter List> ::= <Parameter List>"<<endl;
		}
		ParameterList();		
		OptParameterList = true;
	}else if(lexeme == "]"){
		if (displayFlag){
			cout<<"<Opt Parameter List> ::= <empty>"<<endl;
		}
		Empty();
		OptParameterList = true;
	}
	return OptParameterList;
}

bool syntaxparser::ParameterList(){

	bool bParameterList= false, flag=false;
	if (displayFlag){
		cout << "<Parameter List> ::= <Parameter> , <Parameter List>"<< endl;
	}
	Parameter();

		if(lexeme ==","){
			Lexer();

			if(ParameterList()){
				bParameterList= true;
				flag=true;

			}

			bParameterList= true;
			if(flag == false){
			cout<<"<Parameter List> ::= <Parameter>"<<endl;
		}
		bParameterList= true;
	}

	return bParameterList;
}

bool syntaxparser::Parameter(){
	
	bool Parameter = false;
	if (displayFlag){
		cout<<"<Parameter> ::= <IDS> : <Qualifier>"<<endl;
	}
	IDs();

		if(lexeme ==":"){
			Lexer(); print();
			Qualifier();
			Parameter = true;
		}else{
			cout<<"Missing ':'"<<endl;
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

		//check to see if the next token is a comma
		Lexer();
		if (lexeme == ","){
			if (displayFlag){
				cout << "<IDs> ::= <Identifier>, <IDs>" << endl;
			}
			print(); // print out the comma
			Lexer(); // get the next token to see if ID
			print(); // print out the next token, which should be an identifier
			IDs();
			bIDs = true;
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
	else
	{
		// << "Error: Statement List" << endl;
		bStatementList = true;
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
	}else 
		cout<<"NO statement"<<endl;
		
	

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
	if(lexeme == "if"){
		Lexer();
		if (lexeme == "("){
			Lexer();
			if (Condition()){
				if (lexeme == ")"){
					Lexer();
					if (Statement()){
						if (lexeme == "endif"){
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
	if (lexeme == "write"){
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
	if (lexeme == "read"){
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
	if (lexeme == "while"){
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
		bExpressionPrime = true;
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
		bTermPrime = true;
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

	}else if(lexeme == "("){
		Lexer();
		if (Expression()){
			if (lexeme == ")"){
				Lexer();
				Primary = true;
				cout << "<Primary> ::= ( <Expression> )" << endl;
			}
		}
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
