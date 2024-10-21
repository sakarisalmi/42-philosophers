#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define YELLOW_TEXT	"\033[0;33m"
# define RED_TEXT		"\033[0;31m"
# define GREEN_TEXT		"\033[0;32m"
# define PURPLE_TEXT	"\033[0;35m"
# define DEFAULT_TEXT	"\033[0;37m"

/*----------------------------------------------------------------------------*/

typedef struct s_rules
{
	int	number_of_phils;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eats_limit;
}	t_rules;

typedef struct s_monitor
{
	t_rules					*rules;
	struct s_philosopher	**philosopher_stack;
	pthread_mutex_t			*set_up_failure_mutex;
	int						*set_up_failure;
	pthread_t				monitor_thread;
	long					*start_time;
}	t_monitor;

typedef struct s_philosopher
{
	int						phil_num;
	t_rules					*rules;
	pthread_mutex_t			status_mutex;
	int						status;
	pthread_mutex_t			*own_fork;
	pthread_mutex_t			*next_fork;
	int						has_grabbed_forks;
	pthread_mutex_t			times_eaten_mutex;
	int						times_eaten;
	pthread_mutex_t			last_time_eaten_mutex;
	long					last_time_eaten;
	struct s_philosopher	*next_philosopher;
	pthread_mutex_t			*set_up_failure_mutex;
	int						*set_up_failure;
	long					*start_time;
}	t_philosopher;

typedef struct s_data
{
	int						what_to_free[4];
	pthread_t				**phil_threads;
	t_philosopher			*philosopher_stack;
	pthread_mutex_t			**forks;
	t_rules					rules;
	t_monitor				monitor;
	pthread_mutex_t			set_up_failure_mutex;
	int						set_up_failure;
	long					start_time;
}	t_data;

/*---------------- Functions by sub-directory ----------------*/

// messages.c
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
int				error_message(int error_nbr);

// error_check.c
int				phil_error_check(int argc, char **argv);

// error_check_utils.c
int				check_if_string_is_digits(char *str);
int				check_if_integer(const char *str);
int				check_if_negative_integer(char *argv_str);

// set_data.c
int				phil_set_data(t_data *data, int argc, char **argv);

// init_forks.c
int				init_forks(t_data *data);

// init_phil_stack.c
int				init_phil_stack(t_data *data);

// phil_stack_utils.c
t_philosopher	*create_phil_node(t_data *data, int nbr);
void			push_phil_to_stack_back(t_philosopher **stack,
					t_philosopher *new_node);
void			phil_stack_set_next_phil_to_last_node(t_philosopher **stack);

// init_phil_threads.c
pthread_t		**init_threads(t_data *data);

// phil_routine.c
void			*phil_routine(void *arg);

// phil_routine_utils1.c
int				phil_routine_grab_forks(t_philosopher *phil,
					pthread_mutex_t *own_fork, pthread_mutex_t *next_fork);
int				phil_routine_eat(t_philosopher *phil);
int				phil_routine_wait(t_philosopher *phil);
long			timer(void);

// phil_routine_utils2.c
int				phil_thread_sleep(t_philosopher *phil);
void			phil_release_grabbed_forks(t_philosopher *phil);
long			get_time(t_philosopher *phil);
void			precise_usleep(t_philosopher *phil, int sleep_time);
void			print_phil_state(long action_time,
					int phil_number, int phil_state_to_print);

// clean_and_exit.c
void			phil_clean_before_exit(t_data *data);

// clean_utils1.c
void			free_threads_if_failure(pthread_t **thread_array,
					int failure_idx);
void			destoy_and_free_fork_mutexes(t_data *data);
void			free_array(void	**array, int failure_idx);

// start_sim.c
void			start_sim(t_data *data);

// join_threads.c
void			join_threads(t_data *data);
void			join_monitor(t_data *data);
void			join_threads_if_failure(t_data *data,
					pthread_t **phil_threads, int failure_idx);

// countdown.c
void			countdown(void);

// ft_atoi.c
int				ft_atoi(const char *str);

// ft_bzero.c
void			ft_bzero(void *s, size_t n);

// ft_calloc.c
void			*ft_calloc(size_t count, size_t size);

// ft_isdigit.c
int				ft_isdigit(int c);

// monitor_routine.c
void			*monitor_routine(void *arg);

// monitor_routine_utils1.c
void			*check_eats_exception(t_monitor *monitor);

#endif