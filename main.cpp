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

		while(!myinfile.eof())
		{
			tokenANDLexeme = lexer(myinfile);
			cout<<"Token\t\tLexeme"<<endl;
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


	c = file.get();

	do{
		if(isalpha(c)){
			//identifier and keyword
		} 
		else if(isdigit(c)){
			//int and real

		}
		else
		switch(c){
			case '\n':
				c = file.get();
				break;

			case ' ':
				c = file.get();
				break;

			case '$':
				lexeme = lexeme + c;
				c = file.get();
				if(c=='$'){
					lexeme = lexeme + c;
					c = file.get();
					notfound = false;
					token = "separator";
				}
				break;

			case '{':
				lexeme = lexeme + c;
				c = file.get();
				notfound = false;
				token = "separator";
				break;

			case '}':
				lexeme = lexeme + c;
				c = file.get();
				notfound = false;
				token = "separator";
				break;

			case ';':
				lexeme = lexeme + c;
				c = file.get();
				notfound = false;
				token = "separator";
				break;

			case '(':
				lexeme = lexeme + c;
				c = file.get();
				notfound = false;
				token = "separator";
				break;

			case ')':
				lexeme = lexeme + c;
				c = file.get();
				notfound = false;
				token = "separator";
				break;

			case ':':
				lexeme = lexeme + c;
				c = file.get();
				notfound = false;
				token = "separator";
				break;

			case '[':
				lexeme = lexeme + c;
				c = file.get();
				notfound = false;
				token = "separator";
				break;

			case ']':
				lexeme = lexeme + c;
				c = file.get();
				notfound = false;
				token = "separator";
				break;
			
			default:
				lexeme = lexeme + c;
				notfound = false;
				token = "unknown";
				
		}
			

	}while(notfound);

	both = token + "\t\t" + lexeme;
	

	return both;

}






