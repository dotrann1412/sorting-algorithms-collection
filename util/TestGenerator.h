#ifndef TEST_GENERATOR_H
#define TEST_GENERATOR_H

#include "func.h"

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

int* TestGenerator::generateSortedData(int n) {
	int* a = new int[n];

	for (int i = 0; i < n; i++) {
		a[i] = i;
	}

	return a;
}

int* TestGenerator::generateReverseData(int n) {
	int* a = new int[n];

	for (int i = 0; i < n; i++) {
		a[i] = n - 1 - i;
	}

	return a;
}

int* TestGenerator::generateRandomData(int n) {
	int* a = new int[n];

	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++) {
		a[i] = rand() % n;
	}

	return a;
}

int* TestGenerator::generateNearlySortedData(int n) {
	int* a = new int[n];

	for (int i = 0; i < n; i++) {
		a[i] = i;
	}

	srand((unsigned int) time(NULL));

	for (int i = 0; i < 10; i ++) {
		int r1 = rand() % n;
		int r2 = rand() % n;
		_swap(a[r1], a[r2]);
	}

	return a;
}

int* TestGenerator::generate(int size, int dataType) {

	switch (dataType) {
		case 0:	// ngẫu nhiên
			return generateRandomData(size);
		case 2:	// có thứ tự
			return generateSortedData(size);
		case 3:	// có thứ tự ngược
			return generateReverseData(size);
		case 1:	// gần như có thứ tự
			return generateNearlySortedData(size);
	}

	return nullptr;
}

#endif