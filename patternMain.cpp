#include <iostream>
#include "patternManager.h"

using namespace std;

int main()
{
	string infile = "randomData.txt";
	string outfile = "writtenData.txt";
	
	vector<Data> getData = getDataFromFile(infile);
	writeDataToFile(getData);
	
	cout << "Copied data from " << infile << "to " << outfile << endl;
	
	return 0;
}
