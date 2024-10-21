#include "../../include/philosophers.h"

void		*phil_routine(void *arg);

/*----------------------------------------------------------------------------*/

void	*phil_routine(void *arg)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)arg;
	if (phil_routine_wait(phil) != 0)
		return (NULL);
	if (phil->phil_num % 2 == 1)
	{
		print_phil_state(get_time(phil), phil->phil_num + 1, 3);
		precise_usleep(phil, phil->rules->time_to_eat);
	}
	while (1)
	{
		if (phil_routine_grab_forks(phil, phil->own_fork,
				phil->next_fork) != 0)
			break ;
		if (phil_routine_eat(phil) != 0)
			break ;
		if (phil_thread_sleep(phil) != 0)
			break ;
	}
	if (phil->has_grabbed_forks == 1)
		phil_release_grabbed_forks(phil);
	return (NULL);
}
