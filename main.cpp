#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <map>
#include <vector>
#include <string>

#include "./sorting_algorithms/sort.h"
#include "./util/timer.h"
#include "./util/func.h"

using namespace std;

template <class T, class U> istream &operator >> (istream &s, pair<T, U>& x){
	return s >> x.first >> x.second;
}

template <class T> istream &operator >> (istream &s, vector<T> &a){
	for(T &x: a) s >> x;
	return s;
}

template <class T> ostream &operator << (ostream &s, vector<T> &a){
	for(T &x: a) s << x << ' ';
	return s;
}

void read_data(vector<pair<string, string>>& data_file, 
	vector<string>& algo) {
	fstream config_file(".data_mapping", ios::in);
	
	int n; config_file >> n;
	algo.assign(n, "");
	config_file >> algo;
	
	int m; config_file >> m;
	data_file.assign(m, pair<string, string>("", ""));
	config_file >> data_file;
	for(auto& x: data_file) 
		_replace(x.first, '_', ' ');

	config_file.close();
}

void printArray(int* begin, int* end, ostream& s) {
	for(int* i = begin; i < end; ++i) s << *i << ' ';
		s << '\n';
}

void statistic() {
	vector<pair<string, string>> data_file;
	vector<string> algo;

	read_data(data_file, algo);
	cerr << algo << '\n';
	fstream statistic_result("./result/statistic_result.csv", ios::out);

	int row = 1;
	statistic_result << fixed << setprecision(6);
	cout << fixed << setprecision(6);

	statistic_result << "Num,Algorithms";

	string trash;
	for(auto& x: data_file) 
		statistic_result << "," << x.first;
	statistic_result << "\n";
	for(auto x: algo) {
		string _x = x;
		_replace(_x, '-', ' ');
		statistic_result << row++ << "," << _x;
		cout << x << '\n';
		void (*_sort)(int*, int*, long long&) = _parse(x);
		for(auto y: data_file) {
			stringstream ss;
			ss << y.first; ss >> trash;
			int n; ss >> n;

			int* a = get_array(y.second);
			Timer::start();
			long long cmpCount = 0;
			_sort(a, a + n, cmpCount);
			double st = Timer::stop();

			bool ck = true;
			for(int i = 0; i < n - 1; ++i) {
				if(a[i] > a[i + 1]) {
					ck = false;
					break;
				}
			}

			delete[] a;

			statistic_result << "," << st << "-" << cmpCount << (ck ? "" : "#");
			statistic_result.flush();

			cout << '\t' << y.first << ": " << st << (ck ? "" : "#") << " (s) - cmp: " << cmpCount << '\n';
			cout.flush();

		}
		statistic_result << "\n";
	}

	statistic_result.close();
	std::cerr << "Statistic done!" << '\n';
}

void query_processes() {

}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	vector<string> command;
	
	for(int i = 0; i < argc; ++i)
		command.push_back(string(argv[i]));

	if(command[1] == "--statistic") {
		statistic();
		//use to run everythings with all data file in .data_mapping
	} else if(command[1] == "--rebuild-data") {
		system(string("repair " + command[2]).c_str());
	} else {

	}
	return 0;
}


