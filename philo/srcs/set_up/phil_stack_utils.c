#include "../../include/philosophers.h"

t_philosopher	*create_phil_node(t_data *data, int nbr);
static void		set_phil_values(t_data *data, t_philosopher *phil, int nbr);
void			push_phil_to_stack_back(t_philosopher **stack,
					t_philosopher *new_node);
void			phil_stack_set_next_phil_to_last_node(t_philosopher **stack);

/*----------------------------------------------------------------------------*/

t_philosopher	*create_phil_node(t_data *data, int nbr)
{
	t_philosopher			*phil_node;

	phil_node = ft_calloc(1, sizeof(t_philosopher));
	if (!phil_node)
	{
		perror("Allocation failure!");
		return (NULL);
	}
	set_phil_values(data, phil_node, nbr);
	phil_node->own_fork = data->forks[nbr];
	phil_node->next_fork = data->forks[(nbr + 1) % data->rules.number_of_phils];
	phil_node->set_up_failure_mutex = &data->set_up_failure_mutex;
	phil_node->set_up_failure = &data->set_up_failure;
	phil_node->times_eaten = 0;
	return (phil_node);
}

static void	set_phil_values(t_data *data, t_philosopher *phil, int nbr)
{
	phil->rules = &data->rules;
	phil->phil_num = nbr;
	phil->has_grabbed_forks = 0;
	pthread_mutex_init(&phil->status_mutex, NULL);
	phil->status = 0;
	phil->next_philosopher = NULL;
	phil->start_time = &data->start_time;
	pthread_mutex_init(&phil->last_time_eaten_mutex, NULL);
	pthread_mutex_init(&phil->times_eaten_mutex, NULL);
	phil->times_eaten = 0;
}

void	push_phil_to_stack_back(t_philosopher **stack,
	t_philosopher *new_node)
{
	t_philosopher	*tmp;

	if (!*stack)
		*stack = new_node;
	else
	{
		tmp = *stack;
		while (tmp->next_philosopher != NULL)
			tmp = tmp->next_philosopher;
		tmp->next_philosopher = new_node;
	}
}

/*	This function sets the last philosopher's next philosopher to the first
	philosopher in the stack. */
void	phil_stack_set_next_phil_to_last_node(t_philosopher **stack)
{
	t_philosopher	*first_phil;
	t_philosopher	*tmp;

	first_phil = *stack;
	tmp = *stack;
	while (tmp->next_philosopher != NULL)
		tmp = tmp->next_philosopher;
	tmp->next_philosopher = first_phil;
}
