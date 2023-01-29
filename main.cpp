#include <iostream>
#include <vector>
#include "algorithms/sort.h"
#include "utils/test_generator.h"
#include <functional>
#include <json/json.h>
#include "utils/timer.h"
#include "utils/helpers.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	vector<int> testSizes = {10, 100, 1000, 10000};
	unordered_map<int, string> testNames = TestGenerator::getNames();
	unordered_map<string, function<void(int*, int*)> > algorithms = sort::info;

	Json::Value result;
	Timer timer;

	for (std::pair<int, string> p : testNames) {
		for (int size : testSizes) {
			int* a = TestGenerator::generate(size, p.first);
			result[p.second][to_string(size)]["data"] = Json::arrayValue;

			for (int i = 0; i < size; i++) {
				result[p.second][to_string(size)]["data"].append(a[i]);
			}

			for (std::pair<string, function<void(int*, int*)> > p2 : algorithms) {
				int* b = new int[size];
				copy(a, a + size, b);
				
				timer.start();
				p2.second(b, b + size);
				double duration = timer.stop();

				bool check = is_sorted(b, b + size);

				result[p.second][p2.first][to_string(size)]["duration"]= duration;
				result[p.second][p2.first][to_string(size)]["is_sorted"] = check;


				delete[] b;
			}
			delete[] a;
		}
	}

	fstream f("./result/result.json", ios::out | ios::binary);
	f << result;
	f.close();

	return 0;
}
