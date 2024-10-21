#include "../../include/philosophers.h"

/*	This function will start the simulation. When the simulation has started
	we create the monitoring thread that monitors the philosophers' deaths
	and possibly their eats amounts depending if an eats limit was given. */
void	start_sim(t_data *data)
{
	data->start_time = timer();
	usleep(100);
	if (pthread_create(&data->monitor.monitor_thread, NULL,
			&monitor_routine, &data->monitor) != 0)
	{
		perror("Failed to create monitor thread");
		pthread_mutex_lock(&data->set_up_failure_mutex);
		data->set_up_failure = 1;
		pthread_mutex_unlock(&data->set_up_failure_mutex);
	}
	else
		data->what_to_free[3] = 1;
}
