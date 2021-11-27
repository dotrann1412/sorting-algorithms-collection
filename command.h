#ifndef COMMAND_H
#define COMMAND_H

#include "./util/timer.h"
#include "./util/func.h"
#include "./util/test_generator.h"
#include "./sorting_algorithms/sort.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <map>
#include <vector>
#include <string>

void generate_dataset(string folder);

void load_mapping_data(vector<pair<string, string>>& data_file, 
	vector<string>& algo, string file_config = ".data_mapping");

void statistic_mode(string file_config);

void help();

void comparison_mode(vector<string>& command);

void algorithms_mode(vector<string>& command);

void query_processes(vector<string>& command);

void generate_dataset(string folder);

#endif