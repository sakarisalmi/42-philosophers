#include "../../include/philosophers.h"

int	main(int argc, char **argv)
{
	int				error_nbr;
	t_data			data;

	error_nbr = phil_error_check(argc, argv);
	if (error_nbr != 0)
		return (error_message(error_nbr));
	if (phil_set_data(&data, argc, argv) == 0)
	{
		data.phil_threads = init_threads(&data);
		if (data.phil_threads)
		{
			countdown();
			start_sim(&data);
			join_threads(&data);
		}
	}
	phil_clean_before_exit(&data);
	printf("%sprogram ended successfully\n%s", GREEN_TEXT, DEFAULT_TEXT);
	return (0);
}
