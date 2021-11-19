#include "timer.h"

double Timer::offset = clock();

void Timer::start() {
	Timer::offset = clock();
}

double Timer::stop() {
	return (clock() - Timer::offset) / CLOCKS_PER_SEC;
}