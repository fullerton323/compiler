#include"syntaxparser.h"


syntaxparser::syntaxparser(string lexfilename){
		string filename = lexfilename;
		ifstream file(filename);
		
}

bool FunctionDefinitions(){

}

bool syntaxparser::StatementList(){
	
	if(Statement())
		cout<<"<Statement>"<<endl;
	else if(Statement() && StatementList()){
		cout<<"<Statement> <Statement List>"<<endl;
	}
}


bool syntaxparser::OptDeclarationList(){
	
	if(DeclarationList())
		cout<<"<DeclarationList>"<<endl;
	else 
		cout<<"<Empty>"<<endl;
}

bool syntaxparser::OptFunctionDefinitions(){

	if(FunctionDefinitions())
		cout<<"<FunctionDefinitions>"<<endl;
	else 
		cout<<"<Empty>"<<endl;
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
	Declaration();
	Declaration();
	DeclarationList();
}

bool syntaxparser::Declaration(){

}

bool syntaxparser::Statement(){

}
