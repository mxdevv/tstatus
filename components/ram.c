/* See LICENSE file for copyright and license details. */
#include <stdio.h>

#include <stdint.h>

uintmax_t
ram_free_kb(void)
{
	uintmax_t free;

	FILE* f = fopen("/proc/meminfo", "r");
	if (fscanf(f,
						 "MemTotal: %ju kB\n"
						 "MemFree: %ju kB\n"
						 "MemAvailable: %ju kB\n",
						 &free, &free, &free) != 3) {
		return 0;
	}

	return free;
}


uintmax_t
ram_total_kb(void)
{
	uintmax_t total;

	FILE* f = fopen("/proc/meminfo", "r");
	if (fscanf(f, "MemTotal: %ju kB\n", &total)
			!= 1) {
		return 0;
	}

	return total;
}

uintmax_t
ram_used_kb(void)
{
	uintmax_t total, free, buffers, cached;

	FILE* f = fopen("/proc/meminfo", "r");
	if (fscanf(f,
						 "MemTotal: %ju kB\n"
						 "MemFree: %ju kB\n"
						 "MemAvailable: %ju kB\n"
						 "Buffers: %ju kB\n"
						 "Cached: %ju kB\n",
						 &total, &free, &buffers, &buffers, &cached) != 5) {
		return 0;
	}

	return (total - free - buffers - cached);
}
