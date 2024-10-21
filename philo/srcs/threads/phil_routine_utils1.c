#include "../../include/philosophers.h"

int		phil_routine_grab_forks(t_philosopher *phil,
			pthread_mutex_t *own_fork, pthread_mutex_t *next_fork);
int		phil_routine_eat(t_philosopher *phil);
int		phil_routine_wait(t_philosopher *phil);
long	timer(void);

/*----------------------------------------------------------------------------*/

/*	this function handles the philosopher's attempt to grab forks to eat.
	If there is only one philosopher (and thus one fork), the philosopher will
	grab the only fork and wait for their death. */
int	phil_routine_grab_forks(t_philosopher *phil,
	pthread_mutex_t *own_fork, pthread_mutex_t *next_fork)
{
	pthread_mutex_lock(&phil->status_mutex);
	{
		if (phil->status != 1)
		{
			pthread_mutex_unlock(&phil->status_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&phil->status_mutex);
	if (own_fork == next_fork)
	{
		pthread_mutex_lock(own_fork);
		print_phil_state(get_time(phil), phil->phil_num + 1, 0);
		precise_usleep(phil, phil->rules->time_to_die);
		pthread_mutex_unlock(own_fork);
		return (1);
	}
	pthread_mutex_lock(own_fork);
	print_phil_state(get_time(phil), phil->phil_num + 1, 0);
	pthread_mutex_lock(next_fork);
	print_phil_state(get_time(phil), phil->phil_num + 1, 0);
	phil->has_grabbed_forks = 1;
	return (0);
}

int	phil_routine_eat(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->status_mutex);
	if (phil->status != 1)
	{
		pthread_mutex_unlock(&phil->status_mutex);
		return (1);
	}
	pthread_mutex_unlock(&phil->status_mutex);
	pthread_mutex_lock(&phil->last_time_eaten_mutex);
	phil->last_time_eaten = timer();
	pthread_mutex_unlock(&phil->last_time_eaten_mutex);
	print_phil_state(get_time(phil), phil->phil_num + 1, 1);
	pthread_mutex_lock(&phil->times_eaten_mutex);
	phil->times_eaten += 1;
	pthread_mutex_unlock(&phil->times_eaten_mutex);
	precise_usleep(phil, phil->rules->time_to_eat);
	phil_release_grabbed_forks(phil);
	return (0);
}

/*	This function makes it so that the simulation doesn't start
	until everything is ready. When the simulation starts (phil->status == 1)
	the philosopher's last time eaten will be set to be the sim start time. */
int	phil_routine_wait(t_philosopher *phil)
{
	while (1)
	{
		pthread_mutex_lock(&phil->status_mutex);
		if (phil->status == 1)
		{
			pthread_mutex_unlock(&phil->status_mutex);
			break ;
		}
		pthread_mutex_unlock(&phil->status_mutex);
		pthread_mutex_lock(phil->set_up_failure_mutex);
		if (*phil->set_up_failure == 1)
		{
			pthread_mutex_unlock(phil->set_up_failure_mutex);
			return (1);
		}
		pthread_mutex_unlock(phil->set_up_failure_mutex);
	}
	pthread_mutex_lock(&phil->last_time_eaten_mutex);
	phil->last_time_eaten = *phil->start_time;
	pthread_mutex_unlock(&phil->last_time_eaten_mutex);
	return (0);
}

/*	This function returns the current time in milliseconds. This function
	will make other functions that need to measure time more readable! */
long	timer(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
