#include <iostream>
#include "patternCallManager.h"

using namespace std;

int main()
{
	patternCallManager manager;

	const string infile = "randomData.txt";
	const string outfile = "writtenData.txt";
	
	vector<Data> getData = manager.getDataFromFile(infile);
	getData = manager.addDummyData({1,"chandana","home/chandana/text",true},getData);
	getData = manager.addDummyData({22,"sonu","m/h/txt",0},getData);
	manager.writeDataToFile(outfile, getData);
	
	cout << "Filtered and Copied all data from " << infile << " to " << outfile << endl;
	
	return 0;
}
