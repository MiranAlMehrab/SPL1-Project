#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main ()
{
	int counter =0;
	ifstream iFile;
	ofstream oFile;
	
	iFile.open("khalamma.bmp",ios ::binary);
	//oFile.open("Copy.bmp", ios :: binary);
	
	char ch ;
	iFile.get(ch);
	
	while(!iFile.eof())
	{
		counter++;
		iFile.get(ch);
	}

	cout<<counter;

	return 0;
}
