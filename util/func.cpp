#include "func.h"
#include <fstream>

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

void toLower(std::string& s) {
	for(auto& x: s) if(x >= 'A' && x <= 'Z') x += 32;
}

void toUpper(std::string& s) {
	for(auto& x: s) if(x >= 'a' && x <= 'z') x -= 32;
}
