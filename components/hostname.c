/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <unistd.h>

const char*
hostname(void)
{
	static char buf[255];
	if (gethostname(buf, sizeof(buf)) < 0) {
		return NULL;
	}

	return buf;
}
