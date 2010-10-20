/*
 * Authors: Bryan Perez & Charles Wang
 * CPSC 323 - Fall 2010 (11:30-12:45)
 * Assignment # 1 - Lexer

 Description: The following program is the lexer or parser of the compiler. 
 Input: A text file defined by the user
 Output: Tokens and Lexemes are printed out to a file defined by the user

**/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "syntaxparser.h"

using namespace std;


string lexer(ifstream &file);

int main(void){

	string infile, outfile;
	string tokenANDLexeme;

	cout << "Enter the input file ";
	cin >>infile;
	cout << "Enter the output file ";
	cin >> outfile;
	

	ifstream myinfile(infile);
	ofstream myoutfile(outfile);

	if (myinfile.is_open())
	{
		
		while(!myinfile.eof())
		{
			tokenANDLexeme = lexer(myinfile);
			myoutfile<<tokenANDLexeme<<endl;
		}
		
		
	}
	else
		cout << "Unable to open the file";

	myinfile.close();
	myoutfile.close();
	
	/****************************************************************/

	syntaxparser parser(outfile);

	parser.Rat10F();




	return 0;
}










string lexer(ifstream &file){
	
	char c;
	string lexeme = "", token ="", both="";
	bool notfound = true;


	do{
		c = file.get();

		///////////////////////////////////////////////////////////////////
		/// Identifier DFSM
		///////////////////////////////////////////////////////////////////
		if(isalpha(c)){
		
		
			/* state 2*/
			lexeme += c;
			token = "identifier";
			notfound = false;
				
					/* state 3*/			/* state 4*/			/* state 5*/
			while(isalpha(file.peek()) || isdigit(file.peek()) || file.peek()=='_'){
				
				c = file.get();
				lexeme += c;
			}

			int size= lexeme.size();

			if(lexeme[size-1] == '_'){

				token = "unknown";

			}
			///////////////////////////////////////////////////////////////////


			

			///////////////////////////////////////////////////////////////////
			// Keyword
			///////////////////////////////////////////////////////////////////
			if(lexeme=="function")
				token = "keyword";
			else if(lexeme=="int")
				token = "keyword";
			else if(lexeme=="boolean")
				token = "keyword";
			else if(lexeme=="real")
				token = "keyword";
			else if(lexeme=="if")
				token = "keyword";
			else if(lexeme=="else")
				token = "keyword";
			else if(lexeme=="return")
				token = "keyword";
			else if(lexeme=="write")
				token = "keyword";
			else if(lexeme=="read")
				token = "keyword";
			else if(lexeme=="while")
				token = "keyword";
			else if(lexeme=="endif")
				token = "keyword";
			else if(lexeme=="function")
				token = "true";
			else if(lexeme=="false")
				token = "keyword";

		} 

		///////////////////////////////////////////////////////////////////
		// Interger aand Real DFSM
		///////////////////////////////////////////////////////////////////
		/*For real and integer we combined both DFSM into one. Which either recieves a digit or a '.' */
		else if(isdigit(c)){
		
				
			    lexeme += c;
				token = "integer";
				notfound = false;

				
				while(isdigit(file.peek()) || file.peek()=='.'){
					
					c = file.get();
					lexeme += c;
					
					if( c=='.' )
						token = "real";

				}
		///////////////////////////////////////////////////////////////////

		}
		///////////////////////////////////////////////////////////////////
		// Operator, Separator and Unkown
		///////////////////////////////////////////////////////////////////
		else
		switch(c){
			case 'ÿ':
				lexeme = lexeme + c;
				notfound = false;
				token = "EndofFile";

			case '\n':
				lexeme = lexeme + c;
				notfound = false;
				token = "EndofLine";
				break;

			case '\t':
				break;

			case ' ':
				break;

			case '$':
				lexeme = lexeme + c;
				if(file.peek()=='$'){
					c = file.get();
					lexeme = lexeme + c;
					notfound = false;
					token = "separator";
				}else{
					notfound = false;
					token = "unknown";
				}
				break;

			case '{':
				lexeme += c;
				notfound = false;
				token = "separator";
				break;

			case '}':
				notfound = false;
				token = "separator";
				lexeme += c;
				break;

			case ';':
				lexeme = lexeme + c;
				notfound = false;
				token = "separator";
				break;

			case '(':
				lexeme = lexeme + c;
				notfound = false;
				token = "separator";
				break;

			case ')':
				lexeme = lexeme + c;
				notfound = false;
				token = "separator";
				break;

			case ':':
				lexeme = lexeme + c;
				notfound = false;
				token = "separator";

				if(file.peek()=='='){
					c = file.get();
					lexeme += c;
					token = "operator";
				}

				break;

			case '[':
				lexeme = lexeme + c;
				notfound = false;
				token = "separator";
				break;

			case ']':
				lexeme = lexeme + c;
				notfound = false;
				token = "separator";
				break;

			case ',':
				lexeme = lexeme + c;
				notfound = false;
				token = "separator";
				break;

			case '=':
				lexeme = lexeme + c;
				notfound = false;
				token = "operator";

				if(file.peek()=='>'){
					c = file.get();
					lexeme += c;
				}
				break;

			case '>':
				lexeme = lexeme + c;
				notfound = false;
				token = "operator";
				break;

			case '<':
				lexeme = lexeme + c;
				notfound = false;
				token = "operator";

				if(file.peek()=='='){
					c = file.get();
					lexeme += c;
				}
				break;

			case '/':
				lexeme = lexeme + c;
				notfound = false;
				token = "operator";

				if(file.peek()=='='){
					c = file.get();
					lexeme += c;
				}
				break;

			case '*':
				lexeme = lexeme + c;
				notfound = false;
				token = "operator";
				break;

			case '+':
				lexeme = lexeme + c;
				notfound = false;
				token = "operator";
				break;

			case '-':
				lexeme = lexeme + c;
				notfound = false;
				token = "operator";
				break;

			default:
				lexeme = lexeme + c;
				notfound = false;
				token = "unknown";
				
		}			

	}while(notfound);

	both = token + " " + lexeme;
	

	return both;

}






