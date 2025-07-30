/// File Name: patternCallManager.cpp
/// File Author: Chandana Jayashekar
/// Date: 2025-07-29
/// Description: 
/// This file implements the interface declared in patternCallManager.h.
/// It contains the function definitions used by patternMain.cpp to perform
/// core operations such as Read/Write data from/to a file, add dummy data,
/// and Retriving data by specific ID, Name, Path or a Flag.

#include "patternCallManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * @brief Reads and parses data from a file into a map.
 * 
 * Opens the file specified by the filename, reads its contents,
 * and extracts Data objects mapped by an integer key.
 * 
 * @param filename The path to the input file containing data.
 * @return std::map<int, Data> A map associating integer keys with Data objects.
 *         Returns an empty map if the file cannot be read or is invalid.
 */
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

/**
 * @brief Writes a list of Data objects to a file.
 * 
 * Serializes and saves each Data item from the provided list into
 * the file specified by filename. If the file exists, it may be overwritten.
 * 
 * @param filename The path to the file where data will be written.
 * @param data The list of Data objects to write to the file.
 */
void patternCallManager::writeDataToFile(const string& filename, const list<Data>& data){
	ofstream outputfile(filename);
	if(!data.empty())
	{
		for(const Data& d : data)
		outputfile << d.id << "," << d.name << "," << d.filepath << "," << (d.flag ? "true" : "false") << "\n";
	}
}

/**
 * @brief Adds a dummy Data entry to a copy of the given data map.
 * 
 * Creates and returns a new map containing all entries from the input map,
 * plus an additional dummy Data object provided by `info`. The new entry
 * is inserted with a unique integer key.
 * 
 * @param info The Data object to add as a dummy entry.
 * @param data The original map of Data objects.
 * @return std::map<int, Data> A new map including the dummy data entry.
 */
map<int, Data> patternCallManager::addDummyData(const Data& info, const map<int, Data>& data){
	map<int,Data> newData = data;
	newData[info.id] = info; //inserts or overwrites
	return newData;
}

/**
 * @brief Retrieves Data objects matching a specific ID.
 * 
 * Searches the provided map of stored Data objects and returns a list
 * containing the Data entry associated with the given ID.
 * If the ID is not found, the returned list will be empty.
 * 
 * @param storedData A map of Data objects keyed by integer IDs.
 * @param specificId The ID to search within the stored data.
 * @return std::list<Data> A list containing the matching Data object, or an empty list if not found.
 */
list<Data> patternCallManager::getById(const map<int, Data>& storedData, const int& specificId){
	list<Data> result;
	auto it = storedData.find(specificId);
	if(it != storedData.end())
		result.push_back(it->second);
	return result;
}

/**
 * @brief Retrieves a list of Data objects that match the given name.
 * 
 * Iterates through the provided data map and collects all entries
 * where the Data object's name matches the specified name.
 * 
 * @param storedData A map of Data objects indexed by integer keys.
 * @param name The name to search within the Data objects.
 * @return std::list<Data> A list of Data objects that have a matching name.
 */
list<Data> patternCallManager::getByName(const map<int, Data>& storedData, const string& name){
	list<Data> result;
	for (const auto& [id, data] : storedData ){
		if((data.name) == name)
			result.push_back(data);  
	}
	return result;
} 

/**
 * @brief Retrieves a list of Data objects that match the specified path.
 * 
 * Searches through the provided map of stored Data and returns a list
 * of entries whose internal path (or matching criteria) corresponds
 * to the given path string.
 * 
 * @param storedData A map of Data objects indexed by an integer key.
 * @param path The path string used to filter matching Data entries.
 * @return std::list<Data> A list of Data objects that match the specified path.
 */
list<Data> patternCallManager::getByPath(const map<int, Data>& storedData, const string& path){
	list<Data> result;
	for (const auto& [id, data] : storedData){
		if((data.filepath) == path)
			result.push_back(data);
	}
	return result;
}

/**
 * @brief Retrieves a list of Data objects filtered by a specific flag.
 * 
 * Iterates through the provided map of stored Data entries and selects
 * those where a specific boolean flag matches the given value.
 * 
 * @param storedData A map of Data objects indexed by integer keys.
 * @param flag The boolean flag to filter Data entries by.
 * @return std::list<Data> A list of Data objects that match the given flag.
 */
list<Data> patternCallManager::getByFlag(const map<int, Data>& storedData, const bool& flag){
	list<Data> result;
	for (const auto& [id, data] : storedData){
		if((data.flag) == flag)
			result.push_back(data);
	}
	return result;
}
