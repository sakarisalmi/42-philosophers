#include "../../include/philosophers.h"

void	free_threads_if_failure(pthread_t **thread_array, int failure_idx);
void	destoy_and_free_fork_mutexes(t_data *data);
void	free_array(void	**array, int failure_idx);

/*----------------------------------------------------------------------------*/

/*	This function is used if there is some kind of failure when creating the
	philosopher_threads. The malloc_successful variable tells whether
	the thread at the failure_idx was malloced or not; if not, we don't free
	that thread, and if so, we free it. */
void	free_threads_if_failure(pthread_t **thread_array, int failure_idx)
{
	int	i;

	i = -1;
	while (++i < failure_idx)
		free(thread_array[i++]);
	free(thread_array);
}

/*	This function will destroy and free all the forks.
	All of the fork mutexes have to be unlocked before using this function. */
void	destoy_and_free_fork_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.number_of_phils)
	{
		pthread_mutex_destroy(data->forks[i]);
		free(data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	free_array(void	**array, int failure_idx)
{
	int	i;

	i = 0;
	while (i < failure_idx)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
