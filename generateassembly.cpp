#include "generateassembly.h"


generateassembly::generateassembly()
{
		memoryAddress=1000;
		symbolrow=0;
		instraddress =0;
		addtoTable=true;
}





bool generateassembly::addIdentifier(string identifier){
	
	if(addtoTable){
		string s;
		stringstream out;
		out << memoryAddress;
		s=out.str();

		symboltable[symbolrow][0]=identifier;
		symboltable[symbolrow][1]=s;
		symboltable[symbolrow][2]=symboltype;
		

		memoryAddress++;
		symbolrow++;
	}

	return true;
}

bool generateassembly::addType(string type){

	

	symboltype = type;

	return true;

}

// returns false if duplicates are found
bool generateassembly::checkDuplicates(string identifier){

	bool NOduplicate=true;
	int counter =0;

	for(int y=0; y<symbolrow; y++){
		
			if(symboltable[y][0] == identifier){
				counter++;
				
			}
		
	}

	if(counter>1){
		NOduplicate =false;
		cout<<"NOduplicate is false"<<endl;
	}

	return NOduplicate;

}


void generateassembly::printsymboltable(){

	for(int y=0; y<symbolrow; y++){
		for(int x=0; x<3; x++)
		{
			cout<<symboltable[y][x]<<" ";
		}
		cout<<endl;
	}
}


void generateassembly::StopAddingtoSymbolTable(){

	addtoTable=false;
}


void generateassembly::gen_inst(string op, string operand){

	string s;
	stringstream out;
	out << instraddress;
	s=out.str();

	inst_table[instraddress][0] = s;
	inst_table[instraddress][1] = op;
	inst_table[instraddress][2] = operand;

	instraddress++;
		
}



