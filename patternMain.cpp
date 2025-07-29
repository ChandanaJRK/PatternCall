#include <iostream>
#include "patternCallManager.h"

using namespace std;

int main()
{
	patternCallManager manager;

	const string infile = "randomData.txt";

	map<int, Data> getData = manager.getDataFromFile(infile);

	getData = manager.addDummyData({1,"chandana","home/chandana/text",true},getData);
	getData = manager.addDummyData({22,"sonu","m/h/txt",0},getData);
	
	auto dataById = manager.getById(getData,102);
	if(!dataById.empty())
		manager.writeDataToFile("data_with_ID.txt", dataById);
	else
		cout << "Pattern call with ID : 102 NOT found." << endl;
	
	auto dataByName = manager.getByName(getData,"sonu");
	if(!dataByName.empty())
		manager.writeDataToFile("data_with_Name.txt", dataByName);
	else
		cout << "Pattern call with name : sonu NOT found." << endl;

	auto dataByPath = manager.getByPath(getData,"/opt/data/file6");
	if(!dataByPath.empty())
		manager.writeDataToFile("data_with_Path.txt", dataByPath);
	else
		cout << "Pattern call with path : /opt/data/file6 NOT found." << endl;

	auto dataByFlagTrue = manager.getByFlag(getData,true);
	if(!dataByFlagTrue.empty())
		manager.writeDataToFile("data_with_Flag_true.txt", dataByFlagTrue);
	else
		cout << "Pattern call with Flag : true NOT found." << endl;	

	auto dataByFlagFalse = manager.getByFlag(getData,false);
	if(!dataByFlagFalse.empty())
		manager.writeDataToFile("data_with_Flag_false.txt", dataByFlagFalse);
	else
		cout << "Pattern call with Flag : false NOT found." << endl;	
	
	cout << "Filtered and Copied all data from " << infile << " to respective text files." << endl;
	
	return 0;
}
