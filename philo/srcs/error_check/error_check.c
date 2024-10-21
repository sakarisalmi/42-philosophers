#include "../../include/philosophers.h"

int			phil_error_check(int argc, char **argv);
static int	check_for_positive_integers(int argc, char **argv);

/*----------------------------------------------------------------------------*/

int	phil_error_check(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (check_for_positive_integers(argc, argv) != 0)
		return (2);
	if (ft_atoi(argv[1]) <= 0)
		return (3);
	return (0);
}

static int	check_for_positive_integers(int argc, char **argv)
{
	int	i;
	int	result;

	i = 1;
	while (i < argc)
	{
		if (check_if_integer(argv[i]) == 1)
			return (1);
		if (argv[i][0] == '-' || argv[i][0] == '+')
			result = check_if_string_is_digits(argv[i] + 1);
		else
			result = check_if_string_is_digits(argv[i]);
		if (check_if_negative_integer(argv[i]) != 0)
			result = 1;
		if (result == 1)
			return (1);
		i++;
	}
	return (0);
}
