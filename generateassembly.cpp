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

	if(addtoTable){

		for(int y=0; y<symbolrow; y++){
		
				if(symboltable[y][0] == identifier){
					counter++;
				}
		
		}

		if(counter>0){
			NOduplicate =false;
			cout<<"NOduplicate is false"<<endl;
		}

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


void generateassembly::back_patch(string jump_addr){

	string addr;
	int temp;

	addr = jumpstack.top();
	jumpstack.pop();

	temp = GetIntVal(addr);

	inst_table[temp][2]= jump_addr;

}

int GetIntVal(string strConvert) { 
  int intReturn; 

 
  intReturn = atoi(strConvert.c_str()); 

  return(intReturn); 
}



void generateassembly::push_jumpstack(string instr_address){

	jumpstack.push(instr_address);
	
}


string generateassembly::get_instr_address(){
	
	string s;
	stringstream out;
	out << instraddress;
	s=out.str();

	return s;


}

string generateassembly::get_address(string identifier){
	
	string address; //local variable to store address
	for (int i =0; i < symbolrow; i++){
		if (symboltable[i][0] == identifier){
			address = symboltable[i][1];
			break;
		}
		else
			address = "0"; // if not found set the address to the 0 location
	}
	return address;

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





