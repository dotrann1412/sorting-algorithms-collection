#ifndef TIME_H
#define TIME_H

#include <time.h>

class Timer
{
private:
	static double offset;
public:
	static void start();
	static double stop();
};

#endif