#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "./util/TestGenerator.h"

using namespace std;

template <class T, class U> std::istream &operator >> (std::istream &s, pair<T, U>& x){
	return s >> x.first >> x.second;
}

template <class T> std::istream &operator >> (std::istream &s, std::vector<T> &a){
	for(T &x: a) s >> x;
	return s;
}

template <class T> std::ostream &operator << (std::ostream &s, std::vector<T> &a){
	for(T &x: a) s << x << ' ';
	return s;
}

void prepare_for_remapping() {
	fstream f(".data_mapping", ios::in);
	fstream f_tmp(".data_mapping.tmp", ios::out);
	if(!f.eof()) {
		int n; f >> n;
		vector<string> a(n); f >> a;
		f_tmp << n << '\n' << a << '\n';
	}
	f.close(), f_tmp.close();
	remove(".data_mapping"), rename(".data_mapping.tmp", ".data_mapping");
}

void generate(string folder) {
	fstream config_file(".config", ios::in);
	
	int n;
	config_file >> n;
	vector<pair<int, string>> _type(n);
	config_file >> _type;
	
	int m;
	config_file >> m;
	vector<int> _size(m);
	config_file >> _size;
	config_file.close();

	config_file.open(".data_mapping", ios::app);
	config_file << _type.size() * _size.size() << '\n';
	for (auto x: _type) {
		for(auto y: _size) {
			string dest = folder + "/" + x.second + "_" + to_string(y) + ".in";
			fstream f(dest.c_str(), ios::out);
			int* a = TestGenerator::generate(y, x.first);
			f << y <<'\n';
			for(int i = 0; i < y; ++i) f << a[i] << ' ';
				f << '\n';
			delete[] a;
			f.close();
			config_file << x.second + "_" + to_string(y) << " " << dest << '\n';
			cout << "Generated: " << x.second << " - " << y << '\n';
		}
	}
	config_file.close();
}

int main(int argc, char** argv) {

	if(argc != 2) {
		cerr << "Command not found!" << '\n';
		return 1;
	}

	prepare_for_remapping();
	generate(string(argv[1]));
	return 0;
}