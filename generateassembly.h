/*
 * Authors: Bryan Perez & Charles Wang
 * CPSC 323 - Fall 2010 (11:30-12:45)
 * Assignment # 3

 Description: The header file for generating the assembly. 

**/

#include <iostream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

class generateassembly{

public:

	generateassembly();
	bool addtoSymbolTable(string identifier, string type);
	bool addIdentifier(string identifier);
	bool addType(string type);
	bool checkDuplicates(string identifier);
	void StopAddingtoSymbolTable();
	void printsymboltable();


	void gen_inst(string op, string operand);

	void back_patch(string jump_addr);
	string get_instr_address();


private:

	string symboltable [300][3];
	int memoryAddress;
	int symbolrow;
	string symboltype; 
	bool addtoTable;


	string inst_table [300][3];
	int instraddress;
	
	
	stack<string> jumpstack;
	

	
};