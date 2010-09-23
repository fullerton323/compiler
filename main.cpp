#include <iostream>
#include <fstream>
#include <string>

using namespace std;


string lexer(ifstream &file);

int main(void){

	string infile, outfile;
	string tokenANDLexeme;


	cout << "Enter the output file ";
	cin >> outfile;
	cout << "Enter the input file ";
	cin >>infile;

	ifstream myinfile(infile);
	ofstream myoutfile(outfile);

	if (myinfile.is_open())
	{
		cout<<"Token\t\tLexeme"<<endl;
		while(!myinfile.eof())
		{
			tokenANDLexeme = lexer(myinfile);
			cout<<tokenANDLexeme<<endl;
		}
		
		myinfile.close();
		myoutfile.close();
	}
	else
		cout << "Unable to open the file";


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
		} 
		else if(isdigit(c)){
			//int and real
			if(token != "identifier"){
				lexeme += c;
				token = "digit";
				string peek;
				peek = file.peek();
				if(peek == ".")
				{
					token = "real";
				}
			}

		}
		else
		switch(c){
			case '\n':
				break;

			case ' ':
				notfound = false;
				both = token + "\t\t" + lexeme;
				return both;
				break;

			case '$':
				lexeme = lexeme + c;
				if(c=='$'){
					lexeme = lexeme + c;
					c = file.get();
					notfound = false;
					token = "separator";
				}
				break;

			case '{':
				lexeme += c;
				notfound = false;
				token = "separator";
				break;

			case '}':
				notfound = false;
				if (token == "digit"){
					file.putback(c);
				}
				else{
					token = "separator";
					lexeme += c;
				}
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
				notfound = false;
				if (token == "digit"){
					file.putback(c);
				}
				else{
					token = "separator";
					lexeme += c;
				}
				break;

			case ':':
				lexeme = lexeme + c;
				notfound = false;
				token = "separator";
				break;

			case '[':
				lexeme = lexeme + c;
				notfound = false;
				token = "separator";
				break;

			case ']':
				notfound = false;
				if (token == "digit"){
					file.putback(c);
				}
				else{
					token = "separator";
					lexeme += c;
				}
				break;
			
			default:
				lexeme = lexeme + c;
				notfound = false;
				//token = "unknown";
				
		}			

	}while(notfound);

	both = token + "\t\t" + lexeme;
	

	return both;

}






