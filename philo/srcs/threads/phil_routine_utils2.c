#include "../../include/philosophers.h"

int				phil_thread_sleep(t_philosopher *phil);
void			phil_release_grabbed_forks(t_philosopher *phil);
long			get_time(t_philosopher *phil);
void			precise_usleep(t_philosopher *phil, suseconds_t sleep_time);
void			print_phil_state(long action_time,
					int phil_number, int phil_state_to_print);

/*----------------------------------------------------------------------------*/

int	phil_thread_sleep(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->status_mutex);
	if (phil->status != 1)
	{
		pthread_mutex_unlock(&phil->status_mutex);
		return (1);
	}
	pthread_mutex_unlock(&phil->status_mutex);
	print_phil_state(get_time(phil), phil->phil_num + 1, 2);
	precise_usleep(phil, phil->rules->time_to_sleep);
	pthread_mutex_lock(&phil->status_mutex);
	if (phil->status != 1)
	{
		pthread_mutex_unlock(&phil->status_mutex);
		return (1);
	}
	pthread_mutex_unlock(&phil->status_mutex);
	print_phil_state(get_time(phil), phil->phil_num + 1, 3);
	return (0);
}

void	phil_release_grabbed_forks(t_philosopher *phil)
{
	pthread_mutex_unlock(phil->own_fork);
	pthread_mutex_unlock(phil->next_fork);
	phil->has_grabbed_forks = 0;
}

/*	This function returns the time since the start of the simulation. */
long	get_time(t_philosopher *phil)
{
	long		current_time;
	long		result;

	current_time = timer();
	result = current_time - *phil->start_time;
	return (result);
}

/*	This function is used to get an accurate sleep time for philosophers'
	eating and sleeping times */
void	precise_usleep(t_philosopher *phil, int sleep_time)
{
	long	function_start_time;
	long	current_time;	

	function_start_time = timer();
	while (1)
	{
		pthread_mutex_lock(&phil->status_mutex);
		if (phil->status != 1)
		{
			pthread_mutex_unlock(&phil->status_mutex);
			return ;
		}
		pthread_mutex_unlock(&phil->status_mutex);
		current_time = timer();
		if (current_time >= function_start_time + sleep_time)
			return ;
		usleep(500);
	}
}

/*	This function is used to print the state change for the philosophers.
	This function was added so that nothing get's printed out after a
	death of a philosopher. */
void	print_phil_state(long action_time,
	int phil_number, int phil_state_to_print)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	static int				death_state = 0;
	static char				*state_msg[5] = {
	[0] = "has taken a fork\n", [1] = "is eating\n",
	[2] = "is sleeping\n", [3] = "is thinking\n",
	[4] = "died\n" };

	pthread_mutex_lock(&print_mutex);
	if (death_state == 1)
	{
		pthread_mutex_unlock(&print_mutex);
		return ;
	}
	if (phil_state_to_print == 4)
	{
		death_state = 1;
		printf("%s%ld %d %s%s", RED_TEXT, action_time, phil_number,
			state_msg[4], DEFAULT_TEXT);
	}
	else
		printf("%ld %d %s", action_time, phil_number,
			state_msg[phil_state_to_print]);
	pthread_mutex_unlock(&print_mutex);
}
