#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main(void){

	string infile, outfile;
	cout << "Enter the output file";
	cin >> outfile;
	cout << "Enter the input file";
	cin >>infile;

	ifstream myinfile(infile);
	outstream myoutfile(outfile);

	if (myinfile.is_open())
	{

		while(!myinfile.eof())
		{

		}
		
		myinfile.close();
	}
	else
		cout << "Unable to open the file";


	return 0;
}



