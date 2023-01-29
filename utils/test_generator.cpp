#include "test_generator.h"

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
		case 0: return generateRandomData(size);
		case 2: return generateSortedData(size);
		case 3: return generateReverseData(size);
		case 1: return generateNearlySortedData(size);
	}

	return nullptr;
}