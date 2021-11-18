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
	for(auto& x: algo) 
		_replace(x, '_', ' ');
	
	int m; config_file >> m;
	data_file.assign(m, pair<string, string>("", ""));
	config_file >> data_file;
	for(auto& x: data_file) 
		_replace(x.first, '_', ' ');

	config_file.close();
}

int* get_array(string file) {
	fstream f(file.c_str(), ios::in);
	
	int n; f >> n;
	int* a = new int[n];
	for(int i = 0; i < n; f >> a[i], ++i);
	f.close();
	return a;
}

void statistic(vector<pair<string, string>>& data_file,
	vector<string>& algo) {
	fstream statistic_result("./result/statistic_result.csv", ios::out);
	int row = 1;
	
	statistic_result << fixed << setprecision(6);
	statistic_result << "Num,Sort Algorithms Name";

	string trash;
	for(auto& x: data_file) 
		statistic_result << "," << x.first;
	statistic_result << "\n";
	for(auto x: algo) {
		statistic_result << row++ << "," << x;
		cout << x << '\n';
		void (*_sort)(int*, int*) = parse(x);
		for(auto y: data_file) {
			stringstream ss;
			ss << y.first; ss >> trash;
			int n; ss >> n;

			int* a = get_array(y.second);
			Timer::start();
			_sort(a, a + n);
			double st = Timer::stop();

			bool ck = true;
			for(int i = 0; i < n - 1; ++i) {
				if(a[i] > a[i + 1]) {
					ck = false;
					break;
				}
			}

			delete[] a;

			statistic_result << "," << st << (ck ? "" : "#");
			statistic_result.flush();
			cout << '\t' << y.first << ": " << st << " (s)" << (ck ? "" : "#") << '\n';
			cout.flush();
		}
		statistic_result << "\n";
	}
	statistic_result.close();
}

int main(int argc, char** argv) {
	srand(time(nullptr));
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	vector<pair<string, string>> data_file;
	vector<string> algo;
	
	vector<string> command;
	for(int i = 1; i < argc; ++i)
		command.push_back(string(argv[i]));

	read_data(data_file, algo);
	statistic(data_file, algo);

	std::cerr << "statistic done!" << '\n';
	return 0;
}