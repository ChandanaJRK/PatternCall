#include<vector>
#include<string>

using namespace std;

struct Data {
	int id;
	string name;
	string filepath;
	bool flag;
};

vector<Data> getDataFromFile(const string& filename);
void writeDataToFile(const string& filename, const vector<Data>& data);
