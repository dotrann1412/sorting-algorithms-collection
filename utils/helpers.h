#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

template <class T>
void _swap(T& a, T& b) {
	T c = a; a = b, b = c;
}

template <class T>
T _min(T a, T b) {
	return a < b ? a : b;
}

template <class T>
T _max(T a, T b) {
	return a > b ? a : b;
}

template <class T, class U> 
std::istream &operator >> (std::istream &s, std::pair<T, U>& x){
	return s >> x.first >> x.second;
}

template <class T> 
std::istream &operator >> (std::istream &s, std::vector<T> &a){
	for(T &x: a) s >> x;
	return s;
}

template <class T> 
std::ostream &operator << (std::ostream &s, std::vector<T> &a){
	for(T &x: a) s << x << ' ';
	return s;
}

void _replace(std::string&, char, char);
int* get_array(std::string file);
int* get_array(std::string file, int& n);
void toLower(std::string& s);
void toUpper(std::string& s);
bool isInteger(std::string& s);
int parseInt(std::string& s);
void printArray(int*, int*, std::ostream&);
void printArray(int*, int*, std::string);

#endif