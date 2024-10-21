#include "../../include/philosophers.h"

void	join_threads(t_data *data);
void	join_monitor(t_data *data);
void	join_threads_if_failure(t_data *data, pthread_t **phil_threads,
			int failure_idx);

/*----------------------------------------------------------------------------*/

void	join_threads(t_data *data)
{
	int	i;

	join_monitor(data);
	i = -1;
	while (++i < data->rules.number_of_phils)
	{
		if (pthread_join(*data->phil_threads[i], NULL) != 0)
			perror("\tjoining thread error");
	}
	printf("%sall philosopher threads joined!\n%s", YELLOW_TEXT, DEFAULT_TEXT);
}

void	join_monitor(t_data *data)
{
	pthread_join(data->monitor.monitor_thread, NULL);
	printf("%smonitor thread joined!%s\n", YELLOW_TEXT, DEFAULT_TEXT);
}

void	join_threads_if_failure(t_data *data, pthread_t **phil_threads,
	int failure_idx)
{
	int	i;

	pthread_mutex_lock(&data->set_up_failure_mutex);
	data->set_up_failure = 1;
	pthread_mutex_unlock(&data->set_up_failure_mutex);
	i = -1;
	while (++i < failure_idx)
		pthread_join(*phil_threads[i], NULL);
	printf("%sall philosopher threads joined!\n%s", YELLOW_TEXT, DEFAULT_TEXT);
}
