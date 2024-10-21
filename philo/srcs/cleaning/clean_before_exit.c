#include "../../include/philosophers.h"

void		phil_clean_before_exit(t_data *data);
static void	free_philosopher_structs(t_data *data);

/*----------------------------------------------------------------------------*/

void	phil_clean_before_exit(t_data *data)
{
	if (data->what_to_free[0] == 1)
		destoy_and_free_fork_mutexes(data);
	if (data->what_to_free[2] == 1)
		free_philosopher_structs(data);
	if (data->what_to_free[3] == 1)
		free_array((void **)data->phil_threads, data->rules.number_of_phils);
}

static void	free_philosopher_structs(t_data *data)
{
	t_philosopher	*tmp1;
	t_philosopher	*tmp2;
	int				i;

	tmp1 = data->philosopher_stack;
	i = -1;
	while (++i < data->rules.number_of_phils)
	{
		tmp2 = tmp1->next_philosopher;
		free(tmp1);
		tmp1 = tmp2;
	}
}
