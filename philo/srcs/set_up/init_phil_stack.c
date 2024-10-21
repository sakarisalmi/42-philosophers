#include "../../include/philosophers.h"

int			init_phil_stack(t_data *data);
static void	free_phil_stack_in_failure(t_philosopher *phils, int failure_idx);

/*----------------------------------------------------------------------------*/

int	init_phil_stack(t_data *data)
{
	int				i;
	t_philosopher	*node;

	i = -1;
	while (++i < data->rules.number_of_phils)
	{
		node = create_phil_node(data, i);
		if (!node)
		{
			free_phil_stack_in_failure(data->philosopher_stack, i);
			pthread_mutex_lock(&data->set_up_failure_mutex);
			data->set_up_failure = 1;
			pthread_mutex_unlock(&data->set_up_failure_mutex);
			data->philosopher_stack = NULL;
			return (1);
		}
		push_phil_to_stack_back(&data->philosopher_stack, node);
	}
	phil_stack_set_next_phil_to_last_node(&data->philosopher_stack);
	data->what_to_free[1] = 1;
	return (0);
}

static void	free_phil_stack_in_failure(t_philosopher *phils, int failure_idx)
{
	int				i;
	t_philosopher	*phil_tmp1;
	t_philosopher	*phil_tmp2;

	i = 0;
	phil_tmp1 = phils;
	while (i < failure_idx)
	{
		phil_tmp2 = phil_tmp1->next_philosopher;
		free(phil_tmp1);
		phil_tmp1 = phil_tmp2;
		i++;
	}
	phils = NULL;
}
