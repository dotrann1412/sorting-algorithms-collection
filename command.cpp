#include "command.h"

#include <thread>

void load_mapping_data(vector<pair<string, string>>& data_file, 
	vector<string>& algo, string file_name) {
	fstream config_file(file_name, ios::in);
	
	int n; config_file >> n;
	algo.assign(n, "");
	config_file >> algo;
	
	int m; config_file >> m;
	data_file.assign(m, pair<string, string>("", ""));
	config_file >> data_file;
	for(auto& x: data_file) 
		_replace(x.first, '_', ' ');

	config_file.close();
}

void statistic_mode(string file_config) {
	vector<pair<string, string>> data_file;
	vector<string> algo;

	load_mapping_data(data_file, algo, file_config);
	stringstream ss;
	ss << fixed << setprecision(6);

	Timer time_machine;

	for(auto x: algo) {
		string _x = x;
		_replace(_x, '-', ' ');
		ss << _x;
		cout << x << '\n';
		void (*_sort)(int*, int*, long long&) = _parse(x);

		for(auto y: data_file) {
			int n;
			int* a = get_array(y.second, n);

			time_machine.start();
			long long cmpCount = 0;
			_sort(a, a + n, cmpCount);
			double st = time_machine.getTimeDuration();

			bool ck = true;
			for(int i = 0; i < n - 1; ++i) {
				if(a[i] > a[i + 1]) {
					ck = false;
					break;
				}
			}

			delete[] a;

			//if runtime error -> the result will be include character '#' at last
			ss << "," << st << "-" << cmpCount << (ck ? "" : "#");

			cout << '\t' << y.first << ": " << st << (ck ? "" : "#") << " (s) - cmp: " << cmpCount << '\n';
			cout.flush();

		}
		ss << "\n";
	}

	fstream statistic_result("./result/statistic_result.csv", ios::app);
	statistic_result << ss.str();
	statistic_result.close();

	std::cerr << "Statistic done!" << '\n';
}

void help() {
	fstream f(".help", ios::in);
	string s;
	while(!f.eof()) 
		getline(f, s), cout << s << '\n';
	f.close();
}

void comparison_mode(vector<string>& command) {
	int command_size = command.size();
	if(command.size() < 5) {
		cerr << "Command not found! Try " << command[0] << " --help for get more infomation!" << '\n';
		return;
	}

	cout << "COMPARE MODE" << '\n';

	void (*_sort_1)(int*, int*, long long&) = _parse(command[2]),
		 (*_sort_2)(int*, int*, long long&) = _parse(command[3]);

	_replace(command[2], '-', ' ');
	_replace(command[3], '-', ' ');

	if(!_sort_1 || !_sort_2) {
		cerr << "Sort Algorithm not found" << '\n';
		return;
	}

	cout << "Algorithm: " << command[2] << " | " << command[3] << '\n';
	cout << "Input file: " << command[4] << '\n';

	double duration_1, duration_2;
	long long cmpCount_1 = 0, cmpCount_2 = 0;

	Timer time_machine;

	if(command_size == 5) {
		int sz;
		int* a = get_array(command[4], sz);
		int* b = new int[sz];
		memcpy(b, a, sz * sizeof(int));

		cout << "Input size: " << sz << '\n';

		time_machine.start();
		_sort_1(a, a + sz, cmpCount_1);
		duration_1 = time_machine.getTimeDuration();

		time_machine.start();
		_sort_2(b, b + sz, cmpCount_2);
		duration_2 = time_machine.getTimeDuration();

		delete[] a, b;

	} else { //command 5
		//load configuration setting 
		fstream file_config(".config", ios::in);
		int config_size; file_config >> config_size;
		vector<pair<string, string>> config(config_size);
		file_config >> config;
		file_config.close();

		int type_input_order = -1;
		for(int i = 0; i < config_size; ++i)
			if(command[5] == config[i].first) {
				type_input_order = i;
				break;
			}

		if(type_input_order == -1) {
			cerr << "Data format not found" << '\n';
			return;
		}

		cout << "Input Order: " << config[type_input_order].second << '\n';

		int sz = parseInt(command[4]);
		int* a = TestGenerator::generate(sz, type_input_order);
		int* b = new int[sz];
		memcpy(b, a, sz * sizeof(int));


		time_machine.start();
		_sort_1(a, a + sz, cmpCount_1);
		duration_1 = time_machine.getTimeDuration();

		time_machine.start();
		_sort_2(b, b + sz, cmpCount_2);
		duration_2 = time_machine.getTimeDuration();

		delete[] a, b;
	}

	cout << "-----------------------------------------\n";
	cout << "Running time: " << duration_1 << " | " << duration_2 << '\n';
	cout << "Comparison: " << cmpCount_1 << " | " << cmpCount_2 << '\n';
}

void algorithms_mode(vector<string>& command) {
	cout << "ALGORITHM MODE" << '\n';
	int command_size = command.size();
	void (*_sort)(int*, int*, long long&) = _parse(command[2]);
	long long cmpCount = 0;

	if(!_sort) {
		cerr << "Algorithm not found" << '\n';
		return;
	}

	//load configuration setting 
	fstream file_config(".config", ios::in);
	int config_size; file_config >> config_size;
	vector<pair<string, string>> config(config_size);
	file_config >> config;
	file_config.close();

	_replace(command[2], '-', ' ');
	cout << "Algorithm: " << command[2] << '\n';

	//use for config output parameter
	bool time_tracking = true, comparison_tracking = true;
	
	if(command[command_size - 1] == "-time") comparison_tracking = false;
	else if(command[command_size - 1] == "-comp") time_tracking = false;

	Timer time_machine;
	double duration = 0;

	if(command_size == 5) {
		if(isInteger(command[3])) { //command 3
			int sz = parseInt(command[3]);
			cout << "Input size: " << sz << '\n';

			for(int i = 0; i < config_size; ++i) {
				cout << "Input order: " << config[i].second << '\n';
				int* a = TestGenerator::generate(sz, i);

				printArray(a, a + sz, "input_" + to_string(i + 1) + ".txt");
				
				cmpCount = 0; //reset cmpCount
				time_machine.start();
				_sort(a, a + sz, cmpCount);
				duration = time_machine.getTimeDuration();

				cout << "-----------------------------------------\n";
				if(time_tracking) cout << "Running time: " << duration << " (s)" << '\n';
				if(comparison_tracking) cout << "Comparison: " << cmpCount << '\n';
				cout << '\n';
				delete[] a;
			} 

			return;	
		} else { //command 1
			int sz = 0;
			int* a = get_array(command[3], sz);
			cout << "Input file: " << command[3] << '\n';
			cout << "Input size: " << sz << '\n';
			

			cmpCount = 0;
			time_machine.start();
			_sort(a, a + sz, cmpCount);
			duration = time_machine.getTimeDuration();

			printArray(a, a + sz, "Output.txt");
			delete[] a;
		}

	} else { //command 2
		if(!isInteger(command[3])) {
			cout << "Input size error" << '\n';
			return;
		}

		int type_input_order = -1;
		for(int i = 0; i < config_size; ++i) if(config[i].first == command[4]) {
			type_input_order = i;
			break;
		}

		if(type_input_order == -1) {
			cerr << "Data format not found" << '\n';
			return;
		}

		int sz = parseInt(command[3]);
		cout << "Input size: " << sz << '\n';

		cout << "Input order: " << config[type_input_order].second << '\n';

		int* a = TestGenerator::generate(sz, type_input_order);

		cmpCount = 0;
		time_machine.start();
		_sort(a, a + sz, cmpCount);
		duration = time_machine.getTimeDuration();

		printArray(a, a + sz, "Output.txt");
		delete[] a;
	}

	cout << "-----------------------------------------\n";
	if(time_tracking) cout << "Running time: " << duration << " (s)" << '\n';
	if(comparison_tracking) cout << "Comparison: " << cmpCount << '\n';

	cout << '\n';
}

void query_processes(vector<string>& command) {
	int n = command.size();
	if(command[1] == "-a") algorithms_mode(command);
	else if(command[1] == "-c") comparison_mode(command);
	else {
		cerr << "Command not found! Try: " << command[0] << " --help for more infomation" << '\n';
		return;
	}
}

void generate_dataset(string folder) {
	fstream f(".data_mapping", ios::in);
	fstream f_tmp(".data_mapping.tmp", ios::out);
	if(!f.eof()) {
		int n; f >> n;
		vector<string> a(n); f >> a;
		f_tmp << n << '\n' << a << '\n';
	}
	f.close(), f_tmp.close();
	remove(".data_mapping"), rename(".data_mapping.tmp", ".data_mapping");

	fstream config_file(".config", ios::in);

	int n;
	config_file >> n;
	vector<pair<string, string>> _type(n);
	config_file >> _type;
	
	int m;
	config_file >> m;
	vector<int> _size(m);
	config_file >> _size;
	config_file.close();

	config_file.open(".data_mapping", ios::app);
	config_file << _type.size() * _size.size() << '\n';
	for(int i = 0; i < _type.size(); ++i) {
		for(auto y: _size) {
			string dest = folder + "/" + _type[i].second + "_" + to_string(y) + ".in";
			fstream f(dest.c_str(), ios::out);
			int* a = TestGenerator::generate(y, i);
			f << y <<'\n';
			for(int i = 0; i < y; ++i) f << a[i] << ' ';
				f << '\n';
			delete[] a;
			f.close();
			config_file << _type[i].second + "_" + to_string(y) << " " << dest << '\n';
			cout << "Generated: " << _type[i].second << " - " << y << '\n';
		}
	}
	config_file.close();
}