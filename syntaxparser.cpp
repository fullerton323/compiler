#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		filename = lexfilename;
		file.open(filename);
		lineNumber = 0;
}


void syntaxparser::exception(){

	char a;
	cout<<"\n"<<"Hit any letter to exit.."<<endl;
	cin>>a;
	exit (1);

}

void syntaxparser::error(string message){

	
	cout<<"\n"<<"Syntax Error: "<<message<<" On Line: "<< lineNumber <<endl;
	exception();

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
			Lexer(); 


			OptDeclarationList();
			StatementList();
			
			

			if( lexeme == "$$"){
				print();
				cout<<"========>>>>> Syntax is Correct! <<<<<=========="<<endl;
			}
			else if( lexeme != "$$")
				error("Missing Finishing $$");
			
		}
		else if( lexeme != "$$")
			error("Missing $$ after Function definitions");
			

	}
	else if( lexeme != "$$")
		error("Missing $$");
		

}


bool syntaxparser::OptFunctionDefinitions(){
	bool OptFunctionDefinitions =false;
	Lexer();

	//check to see if the next lexeme is a function
	if (lexeme == "function"){
		

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
	print();
	if( lexeme == "function"){
		Lexer(); print();

		if(token == "identifier"){
			Lexer(); print();

			if(lexeme == "["){
				Lexer();

				if(OptParameterList()){

					if(lexeme == "]"){
						print();
						Lexer();
						cout<<endl;
						if(OptDeclarationList()){

							if(Body()){

								bFunction = true;
							}
						}
					}else
					error("Missing ']'");
				}

			}else{
				error("Missing '[' separator");
				
			}

		}else{
				error("Missing identifier");
				
				
		}

	} 

	return bFunction;

}

bool syntaxparser::OptParameterList(){
	bool OptParameterList = false;
	//check to see if the optional parameter list is empty
	if (lexeme != "]"){
		
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
			// if we have a comma then we recursively call for more additional parameters
			ParameterList();
		}
		bParameterList= true;

	return bParameterList;
}

bool syntaxparser::Parameter(){
	
	bool Parameter = false;
	if (displayFlag){
		cout<<"<Parameter> ::= <IDS> : <Qualifier>"<<endl;
	}
	IDs();

		if(lexeme ==":"){
			print(); //print the colon
			Lexer();  //get next token 
			Qualifier();
			Parameter = true;
		}else{
			error("Missing ':'");
			
		}

	return Parameter;
}


bool syntaxparser::Qualifier(){
	bool bQualifier = false;

	 if(displayFlag){
		 cout << "<Qualifier> ::= " << lexeme << endl;
	 }

	if (lexeme == "int" || lexeme =="boolean" || lexeme == "real")
	{
		print();
		
		bQualifier = true;
		Lexer();
	}
	

	return bQualifier;
}

bool syntaxparser::Body(){
	bool body = false;

	if(lexeme == "{"){
		 print(); 
		 Lexer(); 

		 if(displayFlag)
		 cout<<endl<<"<Body> ::= { <Statement List> }"<<endl;

		 StatementList();
			
			if(lexeme == "}"){
				print();
				Lexer();

				body = true;
			}else{
				error("Missing '}'");
				
			}
		

	}else{
		error("Missing '{'");
		
	}

	return body;

}


bool syntaxparser::OptDeclarationList(){

	bool OptDeclarationList=false;

	//checks to see if next lexeme is a qualifier
	if(lexeme == "int" || lexeme == "boolean" || lexeme == "real"){
	
		if (displayFlag){
			
			cout<<endl<<"<OptDeclarationList> ::= <DeclarationList>"<<endl;
			
		}
		OptDeclarationList = true;
		
		DeclarationList();
	}
	else{ // if no optional declaration list then its empty

		if (displayFlag){
			cout<<"<OptDeclarationList> ::= <Empty>"<<endl;
		}
		
		OptDeclarationList = true;
		Empty();

	}

	return OptDeclarationList;
}


bool syntaxparser::DeclarationList(){

	bool bDeclarationList = false;
	if (displayFlag){
		cout <<endl<< "<DeclarationList> ::= <Declaration>;<DeclarationList>" << endl;
	}
	Declaration();

	//checks to see if next lexeme is a qualifier
	if(lexeme ==";"){
		Lexer();
		if(lexeme == "int" || lexeme == "boolean" || lexeme == "real"){
			Lexer();
			// if we have a semi colon then we recursively call for more additional declarations
			DeclarationList();
		}
	}
	bDeclarationList = true;

	
	return bDeclarationList;
}


bool syntaxparser::Declaration(){
	bool bDeclaration = false;

	if (displayFlag){
		cout << "<Declaration> ::= <Qualifier> <IDs>" << endl;
	}

	cout<<endl;
	Qualifier();
	cout<<endl;

	IDs();

	bDeclaration = true;

	return bDeclaration;


}


bool syntaxparser::IDs(){
	bool bIDs = false;
	if(token == "identifier"){
		print();
		Lexer();
		
		if (displayFlag){
				cout << "<IDs> ::= <Identifier>"<<endl;
			}


		
		if (lexeme == ","){
			if (displayFlag){
				cout << "<IDs> ::= <Identifier>, <IDs>" << endl;
			}
			print(); // print out the comma
			Lexer(); // get the next token to see if ID
			//print(); // print out the next token, which should be an identifier
			IDs();
			bIDs = true;
		}


		bIDs = true;
		
	}
	else
		error("Missing Identifier");
	return bIDs;
}

bool syntaxparser::StatementList(){
	bool bStatementList = false;
	if (displayFlag){
		cout<<"<Statement List> ::= <Statement> <Statement List>"<<endl;
	}
	
	if(Statement()){
		bStatementList = true;
	}
	else
		error("Missing Statement");


		if (token == "keyword" || token == "identifier"){
			bStatementList = true;
			StatementList();
		}
		

	return bStatementList;
}


bool syntaxparser::Statement(){
	bool bStatement = false;
	if (lexeme == "{"){
		bStatement = true;

		if(displayFlag)
		cout << "<Statement> ::= <Compound>" << endl;
		Compound();
	}
	else if (token == "identifier"){
		bStatement = true;

		if(displayFlag)
		cout << "<Statement> ::= <Assign>" << endl;
		Assign();
	}
	else if (lexeme == "if"){
		bStatement = true;
		if(displayFlag)
		cout << "<Statement> ::= <If>" << endl;
		If();
	}
	else if (lexeme == "return"){
		bStatement = true;

		if(displayFlag)
		cout << "<Statement> ::= <Return>" << endl;
		Return();
	}
	else if (lexeme == "write"){
		bStatement = true;
		if(displayFlag)
		cout << "<Statement> ::= <Write>" << endl;
		Write();
	}
	else if (lexeme == "read"){
		bStatement = true;

		if(displayFlag)
		cout << "<Statement> ::= <Read>" << endl;
		Read();
	}
	else if (lexeme == "while"){
		bStatement = true;

		if(displayFlag)
		cout << "<Statement> ::= <While>" << endl;
		While();
	}//else 
		//bStatement = true;

	return bStatement;
}


bool syntaxparser::Compound(){
	bool bCompound = false;
	if (lexeme == "{"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<compound> ::= { <Statement List> }" << endl;

		StatementList();

			if(lexeme == "}"){
				print();
				cout<<endl;
				bCompound = true;
				Lexer();
			}else
				error("Missing '}'");
		
	}
	return bCompound; 
}


bool syntaxparser::Assign(){
	bool bAssign = false;


	if (token == "identifier"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<Assign> ::= <Identifier> := <Expression>;" << endl;

		if (lexeme == ":="){
			print();
			cout<<endl;
			Lexer();

			Expression();
				if(lexeme == ";"){
					print();
					cout<<endl;
					Lexer();

					bAssign = true;
					
				}else
					error("Missing ';'");
			
		}
	}
	
	return bAssign;
}


bool syntaxparser::If(){
	bool bIf = false;

	if (displayFlag){
		cout << "<If> ::= if ( <Condition> ) <Statement> endif" << endl;
	}

	if(lexeme == "if"){
		print();
		cout<<endl;
		Lexer();
		if (lexeme == "("){
			print();
			cout<<endl;
			Lexer();

			Condition();


			if (lexeme == ")"){
				print();
				cout<<endl;
				Lexer();

				Statement();
					
					if(lexeme == "else"){
					print();
					cout<<endl;
					Lexer();
					bIf = true;

						Statement();

					}else
						if (lexeme == "endif"){
						print();
						cout<<endl;
						Lexer();
						bIf = true;
							
					}else
						error("Missing 'endif'");
				
			}else
				error("Missing ')'");

		}else 
			error("Missing '('");
	}

	return bIf;
}
	
	



bool syntaxparser::Return(){
	bool bReturn = false;
	if (lexeme == "return"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<Return> ::= return;" << endl;

		if (lexeme == ";"){
			print();
			cout<<endl;
			Lexer();
			bReturn = true;
			
		}
		else {

			Expression();

			if (lexeme == ";"){
				print();
				cout<<endl;
				Lexer();
				bReturn = true;

				if(displayFlag)
					cout << "<Return> ::= return <Expression>;" << endl;
			}else
					error("Missing ';'");
		}
	}
	
	return bReturn;
}


bool syntaxparser::Write(){
	bool bWrite = false;
	if (lexeme == "write"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<Write> ::= write ( <Expression> );" << endl;

		if (lexeme == "("){
			print();
			cout<<endl;
			Lexer();

			Expression();

				if (lexeme == ")"){
					print();
					cout<<endl;
					Lexer();

					if (lexeme == ";"){
						print();
						cout<<endl;
						Lexer();
						bWrite = true;
						
					}else
						error("Missing ';'");
				}else
					error("Missing ')'");
			
		}
	}
	
	return bWrite;
}


bool syntaxparser::Read(){
	bool bRead = false;
	if (lexeme == "read"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<Read> ::= read ( <IDs> );" << endl;

		if (lexeme == "("){
			print();
			cout<<endl;
			Lexer();

			IDs();

				if (lexeme == ")"){
					print();
					cout<<endl;
					Lexer();

					if (lexeme == ";"){
						print();
						cout<<endl;
						Lexer();
						bRead = true;
						
					}else
						error("Missing ';'");
				}else
					error("Missing ')'");
			
		}
	}
	
	return bRead;
}

bool syntaxparser::While(){
	bool bWhile = false;
	if (lexeme == "while"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<While> ::=( <Condition> ) <Statement>" << endl;

		if (lexeme == "("){
			print();
			cout<<endl;
			Lexer();

			Condition();

				if (lexeme == ")"){
					print();
					cout<<endl;
					Lexer();

					Statement();
					bWhile = true;
						
					
				}else
					error("Missing ')'");
			
		}
	}
	
	return bWhile;
}


bool syntaxparser::Condition(){
	bool bCondition = false;
	

	if(displayFlag){
		cout << "<Condition> :== <Expression> <Relop> <Expression>" << endl;
	}

	Expression();
	Relop();
	Expression();

	bCondition = true;

	return bCondition;
}



bool syntaxparser::Relop(){
	cout<<endl;
	bool Relop = false;

	if(lexeme == "="){
		print();
		Lexer();
		Relop = true;
		if(displayFlag)
			cout<<"<Relop> ::= =" << endl;
	}else if(lexeme =="/="){
		print();

		Lexer();
		Relop = true;
		if(displayFlag)
			cout<<"<Relop> ::= /=" << endl;
	}else if(lexeme ==">"){
		print();
		Lexer();
		Relop = true;
		if(displayFlag)
			cout<<"<Relop> ::= >" << endl;
	}else if(lexeme =="<"){
		print();
		Lexer();
		Relop = true;
		if(displayFlag)
			cout<<"<Relop> ::= <" << endl;
	}else if(lexeme =="=>"){
		print();
		Lexer();
		Relop = true;
		if(displayFlag)
			cout<<"<Relop> ::= =>" << endl;
	}else if(lexeme =="<="){
		print();
		Lexer();
		Relop = true;
		if(displayFlag)
			cout<<"<Relop> ::= <=" << endl;
	}else 
		error("Missing Relop");
	
	cout<<endl;

	return Relop;
}

bool syntaxparser::Expression(){
	bool bExpression = false;
	
	if(displayFlag)
		cout << "<Expression> ::= <Term><ExpressionPrime>" << endl;
	
	Term();
	ExpressionPrime();

	bExpression = true;

	return bExpression;
}

bool syntaxparser::ExpressionPrime(){
	bool bExpressionPrime = false;
	
	if (lexeme == "+"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<ExpressionPrime> ::= +<Term><ExpressionPrime>" << endl;
			bExpressionPrime = true;
			
			Term();
			ExpressionPrime();
			
			
		
	}
	else if (lexeme == "-"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<ExpressionPrime> ::= -<Term><ExpressionPrime>" << endl;
			bExpressionPrime = true;

			Term();
			ExpressionPrime();
			
		
	}
	else{
		bExpressionPrime = true;
		if(displayFlag)
		cout << "<ExpressionPrime> ::= e" << endl;
	}
		

	

	return bExpressionPrime;
}


bool syntaxparser::Term(){
	bool bTerm = false;

	bTerm = true;

	if(displayFlag)
	cout << "<Term> ::= <Factor><TermPrime>" << endl;
	

	Factor();  
	TermPrime();
	
	return bTerm;
}

bool syntaxparser::TermPrime(){
	bool bTermPrime = false;
	if (lexeme == "*"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<TermPrime> ::= *<Factor><TermPrime>" << endl;


		Factor(); 
		TermPrime();
		
		bTermPrime = true;
			
		
	}
	else if (lexeme == "/"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<TermPrime> ::= /<Term><FactorPrime>" << endl;
		bTermPrime = true;

		Factor();
		TermPrime();
			
			
		
	}
	else{
		bTermPrime = true;
		if(displayFlag)
			cout << "<TermPrime> ::= e" << endl;

	}
	return bTermPrime;
}


bool syntaxparser::Factor(){

	bool Factor = false;

	if(lexeme == "-"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout<<"<Factor> ::= -<Primary>"<<endl;

		Primary();

		Factor = true;
			

		
	}else {
		if(displayFlag)
			cout<<"<Factor> ::= <Primary>"<<endl;
		Primary();
		Factor = true;
		
	}
	return Factor;
}




bool syntaxparser::Primary(){
	bool Primary = false, flag=true;

	

	if(token == "identifier" ){
		print();
		cout<<endl;
		Lexer();

		

		if(lexeme == "["){
			print();
			cout<<endl;
			Lexer();

				if(displayFlag)
						cout<<"<Primary> ::= <identifier> [ <IDs> ]"<<endl;
				IDs();

				if(lexeme == "]"){
					print();
					cout<<endl;
					Lexer();
					Primary = true;
					
					
					
					

					flag = false;

				}else
					error("Missing ']'");
			

		}

		if( flag == true){
			Primary = true;

			if(displayFlag)
				cout<<"<Primary> ::= <identifier>"<<endl;
		}

	}else if(token == "integer"){
		print();
		cout<<endl;
		Lexer();
		Primary = true;

		if(displayFlag)
			cout<<"<Primary> ::= <integer>"<<endl;

	}else if(lexeme == "("){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag)
			cout << "<Primary> ::= ( <Expression> )" << endl;

		Expression();

			if (lexeme == ")"){
				print();
				cout<<endl;
				Lexer();
				Primary = true;
				
			}else
				error("Missing ')'");
		
	}else if(token == "real"){
		print();
		cout<<endl;
		Lexer();
		Primary = true;

		if(displayFlag)
			cout<<"<Primary> ::= <real>"<<endl;

	}else if(lexeme == "true"){
		print();
		cout<<endl;
		Lexer();
		Primary = true;
		if(displayFlag)
			cout<<"<Primary> ::= <true>"<<endl;
	}else if(lexeme == "false"){
		print();
		cout<<endl;
		Lexer();
		Primary = true;
		if(displayFlag)
			cout<<"<Primary> ::= <false>"<<endl;
	}else
		error("Missing Primary");

		return Primary;

}



bool syntaxparser::Empty(){
	bool bEmpty = true;
	if(displayFlag)
		cout << "<Empty> ::= e" << endl;
	return bEmpty;
}
