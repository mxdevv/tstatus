/* See LICENSE file for copyright and license details. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uintmax_t
cpu_freq_khz(void)
{
	uintmax_t freq;

	/* in kHz */
	FILE* f = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", "r");
	if (fscanf(f,
						 "%ju", &freq) != 1) {
		return 0;
	}

	return freq;
}

double
cpu_perc(void)
{
	static long double a[7];
	long double b[7], sum;

	memcpy(b, a, sizeof(b));
	/* cpu user nice system idle iowait irq softirq */
	FILE* f = fopen("/proc/stat", "r");
	if (fscanf(f, "%*s %Lf %Lf %Lf %Lf %Lf %Lf %Lf",
						 &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6])
			!= 7) {
		return -0.1;
	}
	if (b[0] == 0) {
		return -0.1;
	}

	sum = (b[0] + b[1] + b[2] + b[3] + b[4] + b[5] + b[6]) -
				(a[0] + a[1] + a[2] + a[3] + a[4] + a[5] + a[6]);

	if (sum == 0) {
		return -0.1;
	}

	return ((b[0] + b[1] + b[2] + b[5] + b[6]) -
			   	(a[0] + a[1] + a[2] + a[5] + a[6])) / sum;
}
