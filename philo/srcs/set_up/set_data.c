#include "../../include/philosophers.h"

int						phil_set_data(t_data *data, int argc, char **argv);
static void				phil_set_data_variables(t_data *data);
static void				phil_data_set_rules(t_data *data,
							int argc, char **argv);
static void				set_monitor(t_data *data);

/*----------------------------------------------------------------------------*/

int	phil_set_data(t_data *data, int argc, char **argv)
{
	phil_data_set_rules(data, argc, argv);
	phil_set_data_variables(data);
	if (init_forks(data) != 0)
		return (1);
	set_monitor(data);
	if (init_phil_stack(data) == 1)
		return (5);
	return (0);
}

static void	phil_set_data_variables(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 5)
		data->what_to_free[i] = 0;
	data->philosopher_stack = NULL;
	data->forks = NULL;
	data->phil_threads = NULL;
	pthread_mutex_init(&data->set_up_failure_mutex, NULL);
	data->set_up_failure = 0;
	data->start_time = 0;
}

static void	phil_data_set_rules(t_data *data, int argc, char **argv)
{
	data->rules.number_of_phils = ft_atoi(argv[1]);
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->rules.eats_limit = ft_atoi(argv[5]);
	else
		data->rules.eats_limit = -1;
}

static void	set_monitor(t_data *data)
{
	t_monitor	*monitor;

	monitor = &data->monitor;
	monitor->rules = &data->rules;
	monitor->philosopher_stack = &data->philosopher_stack;
	monitor->set_up_failure_mutex = &data->set_up_failure_mutex;
	monitor->set_up_failure = &data->set_up_failure;
	monitor->start_time = &data->start_time;
}
