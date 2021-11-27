#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <map>
#include <vector>
#include <string>

#include "command.h"

using namespace std;

int main(int argc, char** argv) {
	if(argc <= 1) {
		cerr << "Command not found! Try: " << argv[0] << " --help for more infomation" << '\n';
		return 1;
	}

	cout << fixed << setprecision(6);
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	vector<string> command;
	
	for(int i = 0; i < argc; ++i)
		command.push_back(string(argv[i]));

	if(command[1] == "--statistic")
		statistic_mode(command[2]);//use to run everythings with all data file in .data_mapping
	else if(command[1] == "--rebuild-dataset")
		generate_dataset(command[2]);
	else if(command[1] == "--help")
		help();
	else if(argc > 2)
		query_processes(command);
	else
		cerr << "Command not found! Try: " << argv[0] << " --help for more infomation" << '\n';
	
	return 0;
}
