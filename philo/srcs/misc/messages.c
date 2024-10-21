#include "../../include/philosophers.h"

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		error_message(int error_nbr);

/*----------------------------------------------------------------------------*/

void	ft_putchar_fd(char c, int fd)
{
	if (fd != -1)
	{
		write(fd, &c, 1);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd != -1 && s)
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

int	error_message(int error_nbr)
{
	if (error_nbr == 1)
		ft_putstr_fd("Error; invalid amount of arguments!\n", 2);
	else if (error_nbr == 2)
		ft_putstr_fd("Error; an invalid argument was given!\n", 2);
	else if (error_nbr == 3)
		ft_putstr_fd("Error; must have at least 1 philosopher!\n", 2);
	return (error_nbr);
}
