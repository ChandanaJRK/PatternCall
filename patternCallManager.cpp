#include "patternCallManager.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<Data> getDataFrommFile(const string& filename){
	ifstream inputfile(filename);
	string line;
	vector<Data> storedData;
	
	while (getline(filename,line)){
		stringstream str(line);
		Data d;
		string flagstr;
		
		getline(str, d.id, ",");
		getline(str, d.name, ",");
		getline(str, d.filepath, ",");
		getline(str, flagstr, ",");
		d.flag = (flagstr == "true");
		
		storedData.push_back(d);
	}
	return storedData;
}

void writeDataToFile(const string& filename, const vector<Data>& data){
	ofstream outputfile(filename);
	for(const auto& d : data){
		outputfile << d.id << "," << d.name << "," << d.filepath << "," << d.flag ? "true" : "false" << "\n";
	}
}
