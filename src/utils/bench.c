#include "utils/bench.h"

#include <time.h>

uint64_t now_ms()
{
	struct timespec ts;

	timespec_get(&ts, TIME_UTC);

	return (uint64_t) ts.tv_sec * 1000ULL + (uint64_t) ts.tv_nsec / 1000000ULL;
}

uint64_t now_ns()
{
	struct timespec ts;

	timespec_get(&ts, TIME_UTC);

	return (uint64_t) ts.tv_sec * 1000000000ULL + (uint64_t) ts.tv_nsec;
}

