#ifndef TIME_H
#define TIME_H

#include <ctime>

class Timer
{
private:
	static std::clock_t offset;
public:
	static void start();
	static double stop();
};

#endif