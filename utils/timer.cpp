#include "timer.h"

high_resolution_clock::time_point Timer::offset = high_resolution_clock::now();

void Timer::start() {
	Timer::offset = high_resolution_clock::now();
}

double Timer::stop() {
	duration<double> execution_time = duration_cast<duration<double>>(high_resolution_clock::now() - offset);
	return 1.0 * execution_time.count();
}