#ifndef TEST_GENERATOR_H
#define TEST_GENERATOR_H

#include "helpers.h"

#include <cmath>
#include <ctime>

using namespace std;

class TestGenerator
{
private:
	static int* generateSortedData(int n);
	static int* generateRandomData(int n);
	static int* generateNearlySortedData(int n);
	static int* generateReverseData(int n);
public:
	static int* generate(int n, int dataType);
};



#endif