#include "../../include/philosophers.h"

void			*monitore_routine(void *arg);
static void		monitor_routine_start(t_monitor *monitor);
static void		monitor_routine_end(t_monitor *monitor);
static int		monitor_routine_check_phil_death(t_philosopher *phil);
static int		check_eats(t_monitor *monitor);

/*----------------------------------------------------------------------------*/

void	*monitor_routine(void *arg)
{
	t_monitor		*monitor;
	t_philosopher	*phil;
	int				i;

	monitor = (t_monitor *)arg;
	if (monitor->rules->eats_limit == 0)
		return (check_eats_exception(monitor));
	monitor_routine_start(monitor);
	while (1)
	{
		phil = *monitor->philosopher_stack;
		i = -1;
		while (++i < monitor->rules->number_of_phils)
		{
			if (monitor_routine_check_phil_death(phil) != 0)
			{
				monitor_routine_end(monitor);
				return (NULL);
			}
			phil = phil->next_philosopher;
		}
		if (monitor->rules->eats_limit != -1 && check_eats(monitor) != 0)
			return (NULL);
	}
	return (NULL);
}

/*	This function starts the simulation*/
static void	monitor_routine_start(t_monitor *monitor)
{
	int				i;
	t_philosopher	*phil;

	phil = *monitor->philosopher_stack;
	i = -1;
	while (++i < monitor->rules->number_of_phils)
	{
		pthread_mutex_lock(&phil->status_mutex);
		phil = phil->next_philosopher;
	}
	i = -1;
	while (++i < monitor->rules->number_of_phils)
	{
		phil->status = 1;
		phil = phil->next_philosopher;
	}
	i = -1;
	while (++i < monitor->rules->number_of_phils)
	{
		pthread_mutex_unlock(&phil->status_mutex);
		phil = phil->next_philosopher;
	}
	usleep(20 * 1000);
}

static void	monitor_routine_end(t_monitor *monitor)
{
	int				i;
	t_philosopher	*phil;

	phil = *monitor->philosopher_stack;
	i = 0;
	while (i < monitor->rules->number_of_phils)
	{
		pthread_mutex_lock(&phil->status_mutex);
		phil->status = 2;
		pthread_mutex_unlock(&phil->status_mutex);
		phil = phil->next_philosopher;
		i++;
	}
}

static int	monitor_routine_check_phil_death(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->last_time_eaten_mutex);
	if ((timer() - phil->last_time_eaten)
		>= phil->rules->time_to_die)
	{
		pthread_mutex_unlock(&phil->last_time_eaten_mutex);
		print_phil_state(get_time(phil), phil->phil_num + 1, 4);
		return (1);
	}
	pthread_mutex_unlock(&phil->last_time_eaten_mutex);
	return (0);
}

static int	check_eats(t_monitor *monitor)
{
	int				least_eats;
	int				i;
	t_philosopher	*phil;

	phil = *monitor->philosopher_stack;
	pthread_mutex_lock(&phil->times_eaten_mutex);
	least_eats = phil->times_eaten;
	pthread_mutex_unlock(&phil->times_eaten_mutex);
	i = 0;
	while (++i < monitor->rules->number_of_phils)
	{
		phil = phil->next_philosopher;
		pthread_mutex_lock(&phil->times_eaten_mutex);
		if (phil->times_eaten < least_eats)
			least_eats = phil->times_eaten;
		pthread_mutex_unlock(&phil->times_eaten_mutex);
	}
	if (least_eats >= monitor->rules->eats_limit)
	{
		printf("%s%ld eats amount achieved; ending simulation!\n%s",
			GREEN_TEXT, timer() - *monitor->start_time, DEFAULT_TEXT);
		monitor_routine_end(monitor);
		return (1);
	}
	return (0);
}
