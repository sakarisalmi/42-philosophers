#include "../../include/philosophers.h"

int	ft_atoi(const char *str)
{
	int		str_val;
	long	result;
	int		sign;

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
		if (result < (long)-2147483648)
			return (0);
		else if (result > (long)2147483647 && sign != -1)
			return (-1);
		str++;
	}
	return (result * sign);
}
