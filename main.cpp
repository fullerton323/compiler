#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

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


	///////////////////////////////////////////////////
	////  Below is for testing
	///////////////////////////////////////////////////
	ifstream file(outfile);
	string token, lexeme;

	cout<<setw(10)<<"TOKEN\t\t"<<"LEXEME"<<endl;
	cout<<"-----------------------------------"<<endl;
	do{

		file>>token>>lexeme;
		cout<<left<<setw(15)<<token<<setw(30)<<lexeme<<endl;

	}while(!file.eof());
	file.close();
	///////////////////////////////////////////////////



	return 0;
}


string lexer(ifstream &file){
	
	char c;
	string lexeme = "", token ="", both="";
	bool notfound = true;


	do{
		c = file.get();

		if(isalpha(c)){
			//identifier and keyword

			lexeme += c;
			token = "identifier";
			notfound = false;

			while(isalpha(file.peek()) || isdigit(file.peek()) || file.peek()=='_'){
				
				c = file.get();
				lexeme += c;
			}

			int size= lexeme.size();

			if(lexeme[size-1] == '_'){

				token = "unknown";
				//lexeme.resize(size-1);
				//file.unget();
			}


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
		else if(isdigit(c)){
			//integer and real

			    lexeme += c;
				token = "integer";
				notfound = false;

				while(isdigit(file.peek()) || file.peek()=='.'){
					
					c = file.get();
					lexeme += c;
					
					if( c=='.' )
						token = "real";

				}


		}
		else
		switch(c){
			case '\n':
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






