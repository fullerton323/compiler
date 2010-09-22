#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main(void){

	string file;
	cout << "Enter your test case file";
	cin >> file;

	ofstream myfile (file);
	if (myfile.is_open())
	{
		myfile << "This is test number 1.\n";
		myfile << "This is test number 2.\n";
		myfile.close();
	}
	else
		cout << "Unable to open the file";


	return 0;
}