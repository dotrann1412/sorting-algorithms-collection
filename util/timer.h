#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <chrono>

using namespace std::chrono;

class Timer
{
private:
	static high_resolution_clock::time_point offset;

public:
	static void start();
	static double stop();
};

#endif