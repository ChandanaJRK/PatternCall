#include <iostream>
#include "patternCallManager.h"

using namespace std;

int main()
{
	patternCallManager manager;

	const string infile = "randomData.txt";
	const string outfile = "writtenData.txt";
	
	vector<Data> getData = manager.getDataFromFile(infile);
	manager.writeDataToFile(outfile, getData);
	
	cout << "Filtered and Copied all data from " << infile << " to " << outfile << endl;
	
	return 0;
}
