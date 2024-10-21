#include "../../include/philosophers.h"

/*	This function handles the edge case where the "eats amount" argument is set
	to zero: we print out that the eats amount has been achieved, and we change
	the set_up_failure int to 1, so that the philosophers' threads will
	end the simulation.	*/
void	*check_eats_exception(t_monitor *monitor)
{
	printf("%s0 eats amount achieved; ending simulation!\n%s",
		GREEN_TEXT, DEFAULT_TEXT);
	pthread_mutex_lock(monitor->set_up_failure_mutex);
	*monitor->set_up_failure = 1;
	pthread_mutex_unlock(monitor->set_up_failure_mutex);
	return (NULL);
}
