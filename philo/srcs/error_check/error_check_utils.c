#include "../../include/philosophers.h"

int	check_if_string_is_digits(char *str);
int	check_if_integer(const char *str);
int	check_if_negative_integer(char *argv_str);

/*----------------------------------------------------------------------------*/

int	check_if_string_is_digits(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*	This function is a modified ft_atoi that simply checks
	if the given number is larger than an integer or not
	 
	HUOM: do I need this? not sure, check later */
int	check_if_integer(const char *str)
{
	int				str_val;
	unsigned long	result;
	int				sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
	str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		str_val = *str - '0';
		result *= 10;
		result += str_val;
		if ((result > (unsigned long)2147483647 && sign == 1)
			|| (result > (unsigned long)2147483648 && sign == -1))
			return (1);
		str++;
	}
	return (0);
}

int	check_if_negative_integer(char *argv_str)
{
	if (ft_atoi(argv_str) < 0)
		return (1);
	else
		return (0);
}
