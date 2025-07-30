/// File Name: patternCallManager.h
/// File Author: Chandana Jayashekar
/// Date: 2025-07-29
/// Description: 
/// This file declares the interface for functions that are used in the application.
/// This header file contains function prototypes, class declarations,
/// and structure that are defined in patternCallManager.cpp.
/// Functions declared here are called by patternMain.cpp.

#include<vector>
#include<map>
#include<string>
#include<optional>
#include<list>

using namespace std;

struct Data {
	int id;
	string name;
	string filepath;
	bool flag;
};

class patternCallManager {
	public:
	map<int, Data> getDataFromFile(const string& infile);
	map<int, Data> addDummyData(const Data& info, const map<int, Data>& data);
	void writeDataToFile(const string& filename, const list<Data>& data);

	list<Data> getById(const map<int, Data>& storedData, const int& id);
	list<Data> getByName(const map<int, Data>& storedData, const string& name);
	list<Data> getByPath(const map<int, Data>& storedData, const string& path); 
	list<Data> getByFlag(const map<int, Data>& storedData, const bool& flag); 
};
