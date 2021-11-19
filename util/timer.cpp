#include "timer.h"

std::clock_t Timer::offset = clock();

void Timer::start() {
	Timer::offset = clock();
}

double Timer::stop() {
	return 1.0 * (clock() - Timer::offset) / CLOCKS_PER_SEC;
}