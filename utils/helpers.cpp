#include "helpers.h"

void _replace(std::string& s, char src, char dest) {
	for(char& c: s) 
		if(c == src) c = dest;
}

int* get_array(std::string file) {

	std::fstream f(file.c_str(), std::ios::in);
	
	int n; f >> n;
	int* a = new int[n];
	for(int i = 0; i < n; f >> a[i], ++i);
	f.close();
	return a;
}

int* get_array(std::string file, int& n) {

	std::fstream f(file.c_str(), std::ios::in);
	f >> n;
	int* a = new int[n];
	for(int i = 0; i < n; f >> a[i], ++i);
	f.close();
	return a;
}

void toLower(std::string& s) {
	for(auto& x: s) if(x >= 'A' && x <= 'Z') x += 32;
}

void toUpper(std::string& s) {
	for(auto& x: s) if(x >= 'a' && x <= 'z') x -= 32;
}

bool isInteger(std::string& s) {
	for(auto x: s) if(x < '0' || x > '9') return false;
	return true;
}

int parseInt(std::string& s) {
	int num = 0;
	for(auto x: s) (num *= 10) += x - '0';
	return num;
}

void printArray(int* begin, int* end, std::ostream& s) {
	for(int* i = begin; i < end; ++i) s << (*i) << ' ';
		s << '\n';
}

void printArray(int* begin, int* end, std::string s) {
	std::fstream f(s, std::ios::out);
	f << end - begin << '\n';
	for(int* i = begin; i < end; ++i)
		f << *i << ' ';
	f << '\n';
	f.close();
}

bool is_sorted(int* first, int* last) {
	for(int* i = first; i < last - 1; ++i)
		if(*i > *(i + 1)) return false;
	return true;
}