#include "components/ram.c"
#include "components/cpu.c"
#include "components/hostname.c"

#include <termios.h>

#include <unistd.h>

struct termios termd, termc;

int main()
{
	tcgetattr(STDIN_FILENO, &termd);
	termc = termd;
	termc.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &termc);

	fputs("\e[?25l", stdout);

	while(1) {
		printf("\e[1;1H");

		/*printf("ram_free: %juM\n", ram_free_kb() / 1024);
		printf("ram_used: %juM\n", ram_used_kb() / 1024);
		printf("ram_total: %juM\n", ram_total_kb() / 1024);*/

		printf("ram: %ju->%ju(%ju)", ram_free_kb() / 1024,
																 ram_used_kb() / 1024,
																 ram_total_kb() / 1024);

		printf(" cpu: %.2lf%%(%.2lfghz)", cpu_perc() * 100.f,
				                      (double)cpu_freq_khz() / 1000000);

		printf("\n");

		printf("hostname: %s\n", hostname());

		printf("\n========================\n");

		sleep(1);
	}

	fputs("\e[?25h", stdout);

	tcsetattr(STDIN_FILENO, TCSANOW, &termd);
}
