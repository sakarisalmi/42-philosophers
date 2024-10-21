#include "../../include/philosophers.h"

void	countdown(void)
{
	int	i;

	printf("%ssimulation starting in...\n", YELLOW_TEXT);
	i = 5;
	while (i > 0)
	{
		printf("%d\n", i--);
		usleep(1000 * 1000);
	}
	printf("%s", DEFAULT_TEXT);
}
