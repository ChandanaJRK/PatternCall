#include "patternCallManager.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<Data> getDataFromFile(const string& filename){
	ifstream inputfile(filename);
	string line;
	vector<Data> storedData;
	
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
	
			storedData.push_back(d);
		} catch(...) {
			continue;
		}
	}
	return storedData;
}

void writeDataToFile(const string& filename, const vector<Data>& data){
	ofstream outputfile(filename);
	for(const auto& d : data){
		outputfile << d.id << "," << d.name << "," << d.filepath << "," << (d.flag ? "true" : "false") << "\n";
	}
}
