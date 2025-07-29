#include "patternCallManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

map<int, Data> patternCallManager::getDataFromFile(const string& filename){
	ifstream inputfile(filename);
	string line;
	map<int, Data> storedData;
	
	while (getline(inputfile,line)){
		stringstream str(line);
		Data d;
		string id,flagstr;
		
		try{

			if(!getline(str, id, ',')) continue;
			d.id = stoi(id);

			if(!getline(str, d.name, ',')) continue;

			if(!getline(str, d.filepath, ',')) continue;

			if(!getline(str, flagstr, ',')) continue;
			d.flag = (flagstr == "true");
	
			storedData[d.id] = d; 
		} catch(const exception& e) {
			cout << "Exception occured " << e.what() << endl;
			continue;
		}
	}
	return storedData;
}

void patternCallManager::writeDataToFile(const string& filename, const list<Data>& data){
	ofstream outputfile(filename);
	if(!data.empty())
	{
		for(const Data& d : data)
		outputfile << d.id << "," << d.name << "," << d.filepath << "," << (d.flag ? "true" : "false") << "\n";
	}
}

map<int, Data> patternCallManager::addDummyData(const Data& info, const map<int, Data>& data){
	map<int,Data> newData = data;
	newData[info.id] = info; //inserts or overwrites
	return newData;
}

list<Data> patternCallManager::getById(const map<int, Data>& storedData, int id){
	list<Data> result;
	auto it = storedData.find(id);
	if(it != storedData.end())
		result.push_back(it->second);
	return result;
}

list<Data> patternCallManager::getByName(const map<int, Data>& storedData, const string& name){
	list<Data> result;
	for (const auto& [id, data] : storedData ){
		if((data.name) == name)
			result.push_back(data);  
	}
	return result;
} 

list<Data> patternCallManager::getByPath(const map<int, Data>& storedData, const string& path){
	list<Data> result;
	for (const auto& [id, data] : storedData){
		if((data.filepath) == path)
			result.push_back(data);
	}
	return result;
}

list<Data> patternCallManager::getByFlag(const map<int, Data>& storedData, const bool& flag){
	list<Data> result;
	for (const auto& [id, data] : storedData){
		if((data.flag) == flag)
			result.push_back(data);
	}
	return result;
}