/// File Name: patternMain.cpp
/// File Author: Chandana Jayashekar
/// Date: 2025-07-29
/// Description: 
/// Thia file contains the entry point (main function) of the application.
/// Coordinates program execution by calling functions defined
/// in other modules such as patternCallManager.cpp.

#include <iostream>
#include "patternCallManager.h"

using namespace std;

int main()
{
	patternCallManager manager;

	//File name to read the data
	const string infile = "randomData.txt";

	//Read the data from the file and store it in a map
	map<int, Data> getData = manager.getDataFromFile(infile);

	//Adding the Dummy data's to the existing map
	getData = manager.addDummyData({1,"chandana","home/chandana/text",true},getData);
	getData = manager.addDummyData({22,"sonu","m/h/txt",0},getData);
	
	//Get all the data by a specific "ID" and writting the data to a different file
	auto dataById = manager.getById(getData,102);
	if(!dataById.empty())
		manager.writeDataToFile("data_with_ID.txt", dataById);
	else
		cout << "Pattern call with ID : 102 NOT found." << endl;
	
	//Get all the data by a specific "name" and writting the data to a different file
	auto dataByName = manager.getByName(getData,"sonu");
	if(!dataByName.empty())
		manager.writeDataToFile("data_with_Name.txt", dataByName);
	else
		cout << "Pattern call with name : sonu NOT found." << endl;

	//Get all the data by a specific "path" and writting the data to a different file
	auto dataByPath = manager.getByPath(getData,"/opt/data/file6");
	if(!dataByPath.empty())
		manager.writeDataToFile("data_with_Path.txt", dataByPath);
	else
		cout << "Pattern call with path : /opt/data/file6 NOT found." << endl;

	//Get all the data if the flag is "true" and writting the data to a different file
	auto dataByFlagTrue = manager.getByFlag(getData,true);
	if(!dataByFlagTrue.empty())
		manager.writeDataToFile("data_with_Flag_true.txt", dataByFlagTrue);
	else
		cout << "Pattern call with Flag : true NOT found." << endl;	

	//Get all the data if the flag is "false" and writting the data to a different file
	auto dataByFlagFalse = manager.getByFlag(getData,false);
	if(!dataByFlagFalse.empty())
		manager.writeDataToFile("data_with_Flag_false.txt", dataByFlagFalse);
	else
		cout << "Pattern call with Flag : false NOT found." << endl;	
	
	cout << "Filtered and Copied all data from " << infile << " to respective text files." << endl;
	
	return 0;
}
