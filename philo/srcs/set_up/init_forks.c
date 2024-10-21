#include "../../include/philosophers.h"

int			init_forks(t_data *data);
static void	free_forks_in_failure(pthread_mutex_t **forks, int failure_idx);
static void	destoy_fork_mutexes_in_failure(pthread_mutex_t **forks,
				int failure_idx);

/*----------------------------------------------------------------------------*/

int	init_forks(t_data *data)
{
	int	i;

	data->forks = ft_calloc(data->rules.number_of_phils,
			sizeof(pthread_mutex_t *));
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->rules.number_of_phils)
	{
		data->forks[i] = ft_calloc(1,
				sizeof(pthread_mutex_t));
		if (!data->forks[i])
		{
			free_forks_in_failure(data->forks, i);
			return (3);
		}
		if (pthread_mutex_init(data->forks[i], NULL) != 0)
		{
			free_forks_in_failure(data->forks, i);
			destoy_fork_mutexes_in_failure(data->forks, i);
			return (4);
		}
	}
	data->what_to_free[0] = 1;
	return (0);
}

static void	free_forks_in_failure(pthread_mutex_t **forks, int failure_idx)
{
	int	i;

	i = 0;
	while (i < failure_idx)
	{
		free(forks[i]);
		i++;
	}
	free(forks);
}

static void	destoy_fork_mutexes_in_failure(pthread_mutex_t **forks,
	int failure_idx)
{
	int	i;

	i = 0;
	while (i < failure_idx)
	{
		pthread_mutex_destroy(forks[i]);
		i++;
	}
}
