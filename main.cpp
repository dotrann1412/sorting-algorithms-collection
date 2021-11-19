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
#include "./util/TestGenerator.h"

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

void load_data(vector<pair<string, string>>& data_file, 
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

void statistic() {
	vector<pair<string, string>> data_file;
	vector<string> algo;

	load_data(data_file, algo);
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

void help() {

}

void comparison_mode(vector<string>& command) {
	int command_size = command.size();
	if(command.size() < 5) {
		cerr << "Command not found! Try " << command[0] << " --help for get more infomation!" << '\n';
		return;
	}

	cout << "COMPARE MODE" << '\n';

	void (*_sort_1)(int*, int*, long long&) = _parse(command[2]),
		 (*_sort_2)(int*, int*, long long&) = _parse(command[3]);

	_replace(command[2], '-', ' ');
	_replace(command[3], '-', ' ');

	cout << "Algorithm: " << command[2] << " | " << command[3] << '\n';
	cout << "Input file: " << command[4] << '\n';

	if(!_sort_1 || !_sort_2) {
		cerr << "Sort Algorithm not found" << '\n';
		return;
	}

	if(command_size == 5) {
		int* sz;
		int* a = get_array(command[5], sz);
		int* b = new int[sz];
		memcpy(b, a, sz * sizeof(int));


	}
}

void algorithms_mode(vector<string>& command) {
	cout << "ALGORITHM MODE" << '\n';
	int command_size = command.size();
	void (*_sort)(int*, int*, long long&) = _parse(command[2]);
	long long cmpCount = 0;

	if(!_sort) {
		cerr << "Algorithm not found" << '\n';
		return;
	}

	//load configuration setting 
	fstream file_config(".config", ios::in);
	int config_size; file_config >> config_size;
	vector<pair<string, string>> config(config_size);
	file_config >> config;
	file_config.close();

	_replace(command[2], '-', ' ');
	cout << "Algorithm: " << command[2] << '\n';

	//use for config output parameter
	bool time_tracking = true, comparison_tracking = true;
	
	if(command[command_size - 1] == "-time") comparison_tracking = false;
	else if(command[command_size - 1] == "-comp") time_tracking = false;

	double duration = 0;

	if(command_size == 5) {
		if(isInteger(command[3])) { //command 3
			int sz = parseInt(command[3]);
			cout << "Input size: " << sz << '\n';

			for(int i = 0; i < config_size; ++i) {
				cout << "Input order: " << config[i].second << '\n';
				int* a = TestGenerator::generate(sz, i);

				printArray(a, a + sz, "input_" + to_string(i + 1) + ".txt");
				
				cmpCount = 0; //reset cmpCount
				Timer::start();
				_sort(a, a + sz, cmpCount);
				duration = Timer::stop();

				cout << "-----------------------------------------\n";
				if(time_tracking) cout << "Running time: " << duration << " (s)" << '\n';
				if(comparison_tracking) cout << "Comparison: " << cmpCount << '\n';
				cout << '\n';
				delete[] a;
			} 

			return;	
		} else { //command 1
			int sz = 0;
			int* a = get_array(command[3], sz);
			cout << "Input file: " << command[3] << '\n';
			cout << "Input size: " << sz << '\n';
			

			cmpCount = 0;
			Timer::start();
			_sort(a, a + sz, cmpCount);
			duration = Timer::stop();

			printArray(a, a + sz, "Output.txt");
			delete[] a;
		}

	} else { //command 2
		if(!isInteger(command[3])) {
			cout << "Input size error" << '\n';
			return;
		}

		int sz = parseInt(command[3]);
		cout << "Input size: " << sz << '\n';

		int type_input_order = 0;
		for(int i = 0; i < config_size; ++i) if(config[i].first == command[4]) {
			type_input_order = i;
			break;
		}

		cout << "Input order: " << config[type_input_order].second << '\n';

		int* a = TestGenerator::generate(sz, type_input_order);

		cmpCount = 0;
		Timer::start();
		_sort(a, a + sz, cmpCount);
		duration = Timer::stop();

		printArray(a, a + sz, "Output.txt");
		delete[] a;
	}

	cout << "-----------------------------------------\n";
	if(time_tracking) cout << "Running time: " << duration << " (s)" << '\n';
	if(comparison_tracking) cout << "Comparison: " << cmpCount << '\n';

	cout << '\n';
}

void query_processes(vector<string>& command) {
	int n = command.size();
	if(command[1] == "-a") algorithms_mode(command);
	else if(command[1] == "-c") comparison_mode(command);
	else {
		cerr << "Command not found! Try: " << command[0] << " --help for more infomation" << '\n';
		return;
	}
}

int main(int argc, char** argv) {
	if(argc <= 1) {
		cerr << "Command not found! Try: " << argv[0] << " --help for more infomation" << '\n';
		return 1;
	}

	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	vector<string> command;
	
	for(int i = 0; i < argc; ++i)
		command.push_back(string(argv[i]));

	if(command[1] == "--statistic") {
		statistic();
		//use to run everythings with all data file in .data_mapping
	} else if(command[1] == "--rebuild-data") {
		system(string("prepare " + command[2]).c_str());
	} else if(command[1] == "--help") {
		help();
	} else if(argc > 2) {
		query_processes(command);
	} else {
		cerr << "Command not found! Try: " << argv[0] << " --help for more infomation" << '\n';
	}
	return 0;
}


