/*
 * Authors: Bryan Perez & Charles Wang
 * CPSC 323 - Fall 2010 (11:30-12:45)
 * Assignment # 3

 Description: The implementation file for for Syntax parser class. 

**/

#include"syntaxparser.h"

// Constructor for the Syntax Parser
// Parameters: The files names of the lexical analyzer output and the production rules output
// Purpose: Initialize the file streams, the line counter

syntaxparser::syntaxparser(string lexfilename, string productionfile){
		filename = lexfilename;
		file.open(filename);
		lineNumber = 0; //default set to 0
		filename = productionfile;
		outfile.open(productionfile);

		
}

// Method for handling the exceptions
// Parameters: None
// Purpose: Exits the program if an error is found

void syntaxparser::exception(){
	char a;
	cout<<"\n"<<"Hit any letter to exit.."<<endl;
	cin>>a;
	exit (1);
}

// Method for displaying syntax errors
// Parameters: A string value containing an error message
// Purpose: Displays the Syntax error message to the user and then throws the exception to exit

void syntaxparser::error(string message){
	cout<<"\n"<<"Syntax Error: "<<message<<" On Line: "<< lineNumber << " Found: " << lexeme << endl;
	exception();
}

//Method for toggling the production rules to be displayed
// Parameters: None
// Purpose: Allows the user to choose a yes/no option for displaying production rules

void syntaxparser::setDisplay(){
	bool flag = true;
	char c;
	while (flag){
		cout << "Would you like to display the production rules? (y/n) : ";
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

// Purpose of Lexer Method: Gets the next token and lexeme values,
//							increases the line counter if end of line

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

// Purpose of print method: prints the current token and lexeme values

void syntaxparser::print(){
	cout<<  endl << left << "Token: " << setw(14) <<token << "Lexeme: " << setw(14) << lexeme <<endl;
	outfile <<  endl << left << "Token: " << setw(14) <<token << "Lexeme: " << setw(14) << lexeme <<endl;
}

// Purpose of printproduction method: Writes out the production rule to file
// Input parameter: A string containing the production rule

void syntaxparser::printproduction(string message){
	outfile << message << endl;
}

// Purpose of RAT10F method: Parses and analyzes for correct syntax of the RAT10F language

void syntaxparser::Rat10F(){
	setDisplay();
	Lexer(); print();
	if( lexeme == "$$"){
		if (displayFlag){
			cout << "<Rat10F> ::= $$<Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$" << endl;
			printproduction("<Rat10F> ::= $$<Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$");
		}	
		OptFunctionDefinitions();
		if( lexeme == "$$"){
			Lexer(); 
			OptDeclarationList();

			project3.StopAddingtoSymbolTable(); 
			
			StatementList();

			project3.printsymboltable(); //// for debuging project3
			project3.printInstTable(); // printing the project3 instruction table for debugging
			
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

// Purpose of OptFunctionDefintions Method: Test the Optional Functional Definition method

bool syntaxparser::OptFunctionDefinitions(){
	bool OptFunctionDefinitions =false;
	Lexer();
	//check to see if the next lexeme is a function
	if (lexeme == "function"){
		if (displayFlag){
			cout<<"<Opt Function Definitions> ::= <FunctionDefinitions>"<<endl;
			printproduction("<Opt Function Definitions> ::= <FunctionDefinitions>");
		}
		OptFunctionDefinitions = true;
		FunctionDefinitions(); // call the function
	}
	else{ // if no optional function definitions then its empty
		if (displayFlag){
			cout<<"<Opt Function Definitions> ::= <Empty>"<<endl;
			printproduction("<Opt Function Definitions> ::= <Empty>");
		}
		Empty(); //call the empty function
		OptFunctionDefinitions= true;
	}
	return OptFunctionDefinitions;
}

// Purpose: FunctionDefintitions method: Test production rule for Function Definitions

bool syntaxparser::FunctionDefinitions(){
	bool bFunctionDefinitions = false;
	if (displayFlag){
		cout << "<Function Definitions> ::= <Function><Function Definitions>" << endl;
		printproduction("<Function Definitions> ::= <Function><Function Definitions>");
	}
	if(Function()){
		if (FunctionDefinitions()){
			bFunctionDefinitions = true;		
		}
		bFunctionDefinitions = true;
		if (displayFlag){
			cout << "<Function Definitions> ::= <Function>" << endl;
			printproduction("<Function Definitions> ::= <Function>");
		}
	}	
	return bFunctionDefinitions;
}

// Purpose: Function Method - Tests the production rule for Function

bool syntaxparser::Function(){
	bool bFunction = false;
	if (displayFlag){
		cout<<"<Function> ::= function <identifier> [ <Opt Parameter List> ] <Opt Declaration List> <Body>"<<endl;
		printproduction("<Function> ::= function <identifier> [ <Opt Parameter List> ] <Opt Declaration List> <Body>");
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

// Purpose: Tests the production rule for optional parameter list

bool syntaxparser::OptParameterList(){
	bool OptParameterList = false;
	//check to see if the optional parameter list is empty
	if (lexeme != "]"){
		
		if (displayFlag){
			cout<<"<Opt Parameter List> ::= <Parameter List>"<<endl;
			printproduction("<Opt Parameter List> ::= <Parameter List>");
		}
		ParameterList();		
		OptParameterList = true;
	}else if(lexeme == "]"){
		if (displayFlag){
			cout<<"<Opt Parameter List> ::= <empty>"<<endl;
			printproduction("<Opt Parameter List> ::= <empty>");
		}
		Empty();
		OptParameterList = true;
	}
	return OptParameterList;
}

// Purpose: Tests the production rule for Parameter list

bool syntaxparser::ParameterList(){
	bool bParameterList= false, flag=false;
	if (displayFlag){
		cout << "<Parameter List> ::= <Parameter> , <Parameter List>"<< endl;
		printproduction("<Parameter List> ::= <Parameter> , <Parameter List>");
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

// Purpose: Tests the production rule for Parameter

bool syntaxparser::Parameter(){
	bool Parameter = false;
	if (displayFlag){
		cout<<"<Parameter> ::= <IDS> : <Qualifier>"<<endl;
		printproduction("<Parameter> ::= <IDS> : <Qualifier>");
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

// Purpose: Tests the production rule for Qualifier

bool syntaxparser::Qualifier(){
	bool bQualifier = false;
	 if(displayFlag){
		 cout << "<Qualifier> ::= " << lexeme << endl;
		 printproduction("<Qualifier> ::= " + lexeme);
	 }
	if (lexeme == "int" || lexeme =="boolean" || lexeme == "real")
	{
		project3.addType(lexeme);
		print();		
		bQualifier = true;
		Lexer();
	}
	return bQualifier;
}

// Purpose: Tests the production rule for Body
bool syntaxparser::Body(){
	bool body = false;
	if(lexeme == "{"){
		 print(); 
		 Lexer(); 
		 if(displayFlag){
			cout<<endl<<"<Body> ::= { <Statement List> }"<<endl;
			printproduction("<Body> ::= { <Statement List> }");
		 }
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

// Purpose: Tests the production rule for Optional Declaration List

bool syntaxparser::OptDeclarationList(){
	bool OptDeclarationList=false;

	//checks to see if next lexeme is a qualifier
	if(lexeme == "int" || lexeme == "boolean" || lexeme == "real"){
	
		if (displayFlag){
			cout<<endl<<"<OptDeclarationList> ::= <DeclarationList>"<<endl;
			printproduction("<OptDeclarationList> ::= <DeclarationList>");
		}
		OptDeclarationList = true;
		DeclarationList();
	}
	else{ // if no optional declaration list then its empty

		if (displayFlag){
			cout<<"<OptDeclarationList> ::= <Empty>"<<endl;
			printproduction("<OptDeclarationList> ::= <Empty>");
		}
		OptDeclarationList = true;
		Empty();
	}
	return OptDeclarationList;
}

// Purpose: Tests the production rule for Declaration List
bool syntaxparser::DeclarationList(){
	bool bDeclarationList = false;
	if (displayFlag){
		cout <<endl<< "<DeclarationList> ::= <Declaration>;<DeclarationList>" << endl;
		printproduction("<DeclarationList> ::= <Declaration>;<DeclarationList>");
	}
	Declaration();

	//checks to see if next lexeme is a qualifier
	if(lexeme ==";"){
		Lexer();
		if(lexeme == "int" || lexeme == "boolean" || lexeme == "real"){
			project3.addType(lexeme);
			Lexer();
			// if we have a semi colon then we recursively call for more additional declarations

			
			
			DeclarationList();
		}
	}
	else
		error("Missing ;");

	bDeclarationList = true;
	return bDeclarationList;
}

// Purpose: Tests the production rule for Declaration

bool syntaxparser::Declaration(){
	bool bDeclaration = false;
	if (displayFlag){
		cout << "<Declaration> ::= <Qualifier> <IDs>" << endl;
		printproduction("<Declaration> ::= <Qualifier> <IDs>");
	}
	cout<<endl;
	Qualifier();
	cout<<endl;
	IDs();
	bDeclaration = true;
	return bDeclaration;
}

// Purpose: Tests the production rule for IDs
bool syntaxparser::IDs(){
	bool bIDs = false;
	if(token == "identifier"){
		
		if(project3.checkDuplicates(lexeme)){
			project3.addIdentifier(lexeme);
		}
		else
			error("Already declared variable");

		string addr;
		addr = project3.get_address(lexeme);
		project3.gen_inst("PUSHM", addr);
		
		print();
		Lexer();

		
		
		
		if (displayFlag){
				cout << "<IDs> ::= <Identifier>"<<endl;
				printproduction("<IDs> ::= <Identifier>");
			}	
		if (lexeme == ","){
			if (displayFlag){
				cout << "<IDs> ::= <Identifier>, <IDs>" << endl;
				printproduction("<IDs> ::= <Identifier>, <IDs>");
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

// Purpose: Tests the production rule for Statement List

bool syntaxparser::StatementList(){
	bool bStatementList = false;
	if (displayFlag){
		cout<<"<Statement List> ::= <Statement> <Statement List>"<<endl;
		printproduction("<Statement List> ::= <Statement> <Statement List>");
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

//Purpose: Tests the production rule for Statement

bool syntaxparser::Statement(){
	bool bStatement = false;
	if (lexeme == "{"){
		bStatement = true;
		if(displayFlag){
			cout << "<Statement> ::= <Compound>" << endl;
			printproduction("<Statement> ::= <Compound>");
		}
		Compound();
	}
	else if (token == "identifier"){
		bStatement = true;
		if(displayFlag){
			cout << "<Statement> ::= <Assign>" << endl;
			printproduction("<Statement> ::= <Assign>");
		}
		Assign();
	}
	else if (lexeme == "if"){
		bStatement = true;
		if(displayFlag){
			cout << "<Statement> ::= <If>" << endl;
			printproduction("<Statement> ::= <If>");
		}
		If();
	}
	else if (lexeme == "return"){
		bStatement = true;

		if(displayFlag){
			cout << "<Statement> ::= <Return>" << endl;
			printproduction("<Statement> ::= <Return>");
		}
		Return();
	}
	else if (lexeme == "write"){
		bStatement = true;
		if(displayFlag){
			cout << "<Statement> ::= <Write>" << endl;
			printproduction("<Statement> ::= <Write>");
		}
		Write();
	}
	else if (lexeme == "read"){
		bStatement = true;

		if(displayFlag){
			cout << "<Statement> ::= <Read>" << endl;
			printproduction("<Statement> ::= <Read>");
		}
		Read();
	}
	else if (lexeme == "while"){
		bStatement = true;

		if(displayFlag){
			cout << "<Statement> ::= <While>" << endl;
			printproduction("<Statement> ::= <While>");
		}
		While();
	}
	return bStatement;
}

// Purpose: Tests the production rule for Compound
bool syntaxparser::Compound(){
	bool bCompound = false;
	if (lexeme == "{"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag){
			cout << "<compound> ::= { <Statement List> }" << endl;
			printproduction("<compound> ::= { <Statement List> }");
		}
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

// Purpose: Tets the production rule for Assign

bool syntaxparser::Assign(){
	bool bAssign = false;
	if (token == "identifier"){
		print();
		// Save the token 
		string assign_save;
		assign_save = lexeme;
		cout<<endl;
		Lexer();

		if(displayFlag){
			cout << "<Assign> ::= <Identifier> := <Expression>;" << endl;
			printproduction("<Assign> ::= <Identifier> := <Expression>;");
		}

		if (lexeme == ":="){
			print();
			cout<<endl;
			Lexer();

			Expression();
			string addr;
			addr = project3.get_address(assign_save);
			project3.gen_inst("POPM", addr);
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

//Purpose: Tests the production rule for If

bool syntaxparser::If(){
	bool bIf = false;
	if (displayFlag){
		cout << "<If> ::= if ( <Condition> ) <Statement> endif" << endl;
		printproduction("<If> ::= if ( <Condition> ) <Statement> endif");
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
						if (lexeme == "endif"){
						print();
						cout<<endl;
						Lexer();
						bIf = true;	
						}
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
	
// Purpose: Tests the production rule for Return	

bool syntaxparser::Return(){
	bool bReturn = false;
	if (lexeme == "return"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag){
			cout << "<Return> ::= return;" << endl;
			printproduction("<Return> ::= return;");
		}

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

				if(displayFlag){
					cout << "<Return> ::= return <Expression>;" << endl;
					printproduction("<Return> ::= return <Expression>;");
				}
			}else
				error("Missing ';'");
		}
	}
	return bReturn;
}

// Purpose: Tests the production rule for Write

bool syntaxparser::Write(){
	bool bWrite = false;
	if (lexeme == "write"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag){
			cout << "<Write> ::= write ( <Expression> );" << endl;
			printproduction("<Write> ::= write ( <Expression> );");
		}

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

// Purpose: Tests the production rule for Read
bool syntaxparser::Read(){
	bool bRead = false;
	if (lexeme == "read"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag){
			cout << "<Read> ::= read ( <IDs> );" << endl;
			printproduction("<Read> ::= read ( <IDs> );");
		}

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

// Purpose: Tests the production rule for While

bool syntaxparser::While(){
	bool bWhile = false;
	if (lexeme == "while"){
		print();
		cout<<endl;
		string addr;
		addr = project3.get_instr_address();
		project3.gen_inst("Label", "-999");
		Lexer();

		if(displayFlag){
			cout << "<While> ::=( <Condition> ) <Statement>" << endl;
			printproduction("<While> ::=( <Condition> ) <Statement>");
		}

		if (lexeme == "("){
			print();
			cout<<endl;
			Lexer();
			Condition();

				if (lexeme == ")"){
					print();
					cout<<endl;
					Lexer();


					project3.gen_inst("JUMP", addr);
					project3.back_patch( addr);

					Statement();
					bWhile = true;
				}else
					error("Missing ')'");	
		}
	}
	return bWhile;
}

// Purpose: Tests the production rule for condition

bool syntaxparser::Condition(){
	bool bCondition = false;
	if(displayFlag){
		cout << "<Condition> :== <Expression> <Relop> <Expression>" << endl;
		printproduction("<Condition> :== <Expression> <Relop> <Expression>");
	}
	Expression();
	Relop();
	Expression();
	bCondition = true;
	return bCondition;
}

// Purpose: Tests the production rule for Relop

bool syntaxparser::Relop(){
	cout<<endl;
	bool Relop = false;
	if(lexeme == "="){
		print();
		Lexer();
		Relop = true;
		if(displayFlag){
			cout<<"<Relop> ::= =" << endl;
			printproduction("<Relop> ::= =");
		}
	}else if(lexeme =="/="){
		print();
		Lexer();
		Relop = true;
		if(displayFlag){
			cout<<"<Relop> ::= /=" << endl;
			printproduction("<Relop> ::= /=");
		}
	}else if(lexeme ==">"){
		print();
		Lexer();
		Relop = true;
		if(displayFlag){
			cout<<"<Relop> ::= >" << endl;
			printproduction("<Relop> ::= >");
		}
	}else if(lexeme =="<"){
		print();
		Lexer();

		string addr;
		project3.gen_inst("LES", "-999");
		addr = project3.get_instr_address();
		project3.push_jumpstack(addr);
		project3.gen_inst("JUMPZ", "-999");

		Relop = true;
		if(displayFlag){
			cout<<"<Relop> ::= <" << endl;
			printproduction("<Relop> ::= <");
		}
	}else if(lexeme =="=>"){
		print();
		Lexer();
		Relop = true;
		if(displayFlag){
			cout<<"<Relop> ::= =>" << endl;
			printproduction("<Relop> ::= =>");
		}
	}else if(lexeme =="<="){
		print();
		Lexer();
		Relop = true;
		if(displayFlag){
			cout<<"<Relop> ::= <=" << endl;
			printproduction("<Relop> ::= <=");
		}
	}else 
		error("Missing Relop");
	
	cout<<endl;
	return Relop;
}

// Purpose: Tests the production rule for Expression

bool syntaxparser::Expression(){
	bool bExpression = false;
	if(displayFlag){
		cout << "<Expression> ::= <Term><ExpressionPrime>" << endl;
		printproduction("<Expression> ::= <Term><ExpressionPrime>");
	}
	Term();
	ExpressionPrime();
	bExpression = true;
	return bExpression;
}

// Purpose: Tests the production rule for Expression Prime

bool syntaxparser::ExpressionPrime(){
	bool bExpressionPrime = false;	
	if (lexeme == "+"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag){
			cout << "<ExpressionPrime> ::= +<Term><ExpressionPrime>" << endl;
			printproduction("<ExpressionPrime> ::= +<Term><ExpressionPrime>");
		}
			bExpressionPrime = true;		
			Term();
			project3.gen_inst("ADD", "-999");
			ExpressionPrime();
	}
	else if (lexeme == "-"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag){
			cout << "<ExpressionPrime> ::= -<Term><ExpressionPrime>" << endl;
			printproduction("<ExpressionPrime> ::= -<Term><ExpressionPrime>");
		}
			bExpressionPrime = true;
			Term();
			project3.gen_inst("SUB", "-999");
			ExpressionPrime();
	}
	else{
		bExpressionPrime = true;
		if(displayFlag){
			cout << "<ExpressionPrime> ::= epsilon" << endl;
			printproduction("<ExpressionPrime> ::= epsilon");
		}
	}
	return bExpressionPrime;
}

// Purpose: Tests the production rule for term
bool syntaxparser::Term(){
	bool bTerm = false;
	if(displayFlag){
		cout << "<Term> ::= <Factor><TermPrime>" << endl;
		printproduction("<Term> ::= <Factor><TermPrime>");
	}
	Factor();  
	TermPrime();
	bTerm = true;
	return bTerm;
}


// Purpose: Tests the production rule for Term Prime

bool syntaxparser::TermPrime(){
	bool bTermPrime = false;
	if (lexeme == "*"){
		print();
		cout<<endl;
		Lexer();
		if(displayFlag){
			cout << "<TermPrime> ::= *<Factor><TermPrime>" << endl;
			printproduction("<TermPrime> ::= *<Factor><TermPrime>");
		}
		Factor();
		project3.gen_inst("MUL","-999");
		TermPrime();	
		bTermPrime = true;		
	}
	else if (lexeme == "/"){
		print();
		cout<<endl;
		Lexer();
		if(displayFlag){
			cout << "<TermPrime> ::= /<Term><FactorPrime>" << endl;
			printproduction("<TermPrime> ::= /<Term><FactorPrime>");
		}
		bTermPrime = true;
		Factor();
		project3.gen_inst("DIV", "-999");
		TermPrime();
	}
	else{
		bTermPrime = true;
		if(displayFlag){
			cout << "<TermPrime> ::= epsilon" << endl;
			printproduction("<TermPrime> ::= epsilon");
		}
	}
	return bTermPrime;
}

// Purpose: Tests the production rule for Factor
bool syntaxparser::Factor(){
	bool Factor = false;
	if(lexeme == "-"){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag){
			cout<<"<Factor> ::= -<Primary>"<<endl;
			printproduction("<Factor> ::= -<Primary>");
		}
		Primary();
		Factor = true;
	}else {
		if(displayFlag){
			cout<<"<Factor> ::= <Primary>"<<endl;
			printproduction("<Factor> ::= <Primary>");
		}
		Primary();
		Factor = true;		
	}
	return Factor;
}

// Purpose: Tests the production rule for Primary

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

				if(displayFlag){
						cout<<"<Primary> ::= <identifier> [ <IDs> ]"<<endl;
						printproduction("<Primary> ::= <identifier> [ <IDs> ]");
				}
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

			if(displayFlag){
				cout<<"<Primary> ::= <identifier>"<<endl;
				printproduction("<Primary> ::= <identifier>");
			}
		}
	}else if(token == "integer"){
		print();
		cout<<endl;
		Lexer();
		Primary = true;

		if(displayFlag){
			cout<<"<Primary> ::= <integer>"<<endl;
			printproduction("<Primary> ::= <integer>");
		}
	}else if(lexeme == "("){
		print();
		cout<<endl;
		Lexer();

		if(displayFlag){
			cout << "<Primary> ::= ( <Expression> )" << endl;
			printproduction("<Primary> ::= ( <Expression> )");
		}

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

		if(displayFlag){
			cout<<"<Primary> ::= <real>"<<endl;
			printproduction("<Primary> ::= <real>");
		}

	}else if(lexeme == "true"){
		print();
		cout<<endl;
		Lexer();
		Primary = true;
		if(displayFlag){
			cout<<"<Primary> ::= <true>"<<endl;
			printproduction("<Primary> ::= <true>");
		}
	}else if(lexeme == "false"){
		print();
		cout<<endl;
		Lexer();
		Primary = true;
		if(displayFlag){
			cout<<"<Primary> ::= <false>"<<endl;
			printproduction("<Primary> ::= <false>");
		}
	}else
		error("Missing Primary");

		return Primary;
}

// Purpose: Tests the production rule for Empty

bool syntaxparser::Empty(){
	bool bEmpty = true;
	if(displayFlag){
		cout << "<Empty> ::= epsilon" << endl;
		printproduction("<Empty> ::= epsilon");
	}
	return bEmpty;
}
