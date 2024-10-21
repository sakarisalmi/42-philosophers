#include "../../include/philosophers.h"

pthread_t			**init_threads(t_data *data);
static pthread_t	**malloc_phil_threads(t_data *data);
static int			create_phil_threads(t_data *data, pthread_t **phil_threads);

/*----------------------------------------------------------------------------*/

pthread_t	**init_threads(t_data *data)
{
	pthread_t	**phil_threads;

	phil_threads = malloc_phil_threads(data);
	if (!phil_threads)
		return (NULL);
	if (create_phil_threads(data, phil_threads) != 0)
	{
		free_threads_if_failure(phil_threads, data->rules.number_of_phils);
		return (NULL);
	}
	data->what_to_free[2] = 1;
	return (phil_threads);
}

static pthread_t	**malloc_phil_threads(t_data *data)
{
	pthread_t	**phil_threads;
	int			i;

	i = -1;
	phil_threads = ft_calloc(data->rules.number_of_phils, sizeof(pthread_t *));
	if (!phil_threads)
		return (NULL);
	while (++i < data->rules.number_of_phils)
	{
		phil_threads[i] = ft_calloc(1, sizeof(pthread_t));
		if (!phil_threads[i])
		{
			free_threads_if_failure(phil_threads, i);
			return (NULL);
		}
	}
	return (phil_threads);
}

static int	create_phil_threads(t_data *data, pthread_t **phil_threads)
{
	int				i;
	t_philosopher	*phil;

	phil = data->philosopher_stack;
	i = -1;
	while (++i < data->rules.number_of_phils)
	{
		if (pthread_create(phil_threads[i],
				NULL, &phil_routine, phil) != 0)
		{
			perror("failed to create philosopher thread");
			pthread_mutex_lock(&data->set_up_failure_mutex);
			data->set_up_failure = 1;
			pthread_mutex_unlock(&data->set_up_failure_mutex);
			join_threads_if_failure(data, phil_threads, i);
			return (1);
		}
		phil = phil->next_philosopher;
	}
	return (0);
}
