NAME = philo
LIBRARY = philo_library.a

INCLUDES = include/

CC = cc
CFLAGS = -Wall -Werror -Wextra
OPTFLAGS = -O3 -march=native -flto -ffast-math
AR = ar rcs

#----------------------------------------------------------------------------#

SRCS_DIR = srcs/
OBJS_DIR = objs/

SET_UP_DIR = set_up/
SET_UP_FILES = init_forks init_phil_stack init_phil_threads set_data \
				phil_stack_utils
				
ERROR_CHECK_DIR = error_check/
ERROR_CHECK_FILES = error_check error_check_utils

MISC_DIR = misc/
MISC_FILES = main messages start_sim countdown ft_atoi ft_bzero ft_calloc ft_isdigit

CLEANING_DIR = cleaning/
CLEANING_FILES = clean_before_exit clean_utils1

THREADS_DIR = threads/
THREADS_FILES = phil_routine phil_routine_utils1 phil_routine_utils2 \
				join_threads monitor_routine monitor_routine_utils1

FILES += $(addprefix $(SET_UP_DIR), $(SET_UP_FILES))
FILES += $(addprefix $(ERROR_CHECK_DIR), $(ERROR_CHECK_FILES))
FILES += $(addprefix $(MISC_DIR), $(MISC_FILES))
FILES += $(addprefix $(THREADS_DIR), $(THREADS_FILES))
FILES += $(addprefix $(CLEANING_DIR), $(CLEANING_FILES))

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

#----------------------------------------------------------------------------#
# colors

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
COLOUR_CYAN=\033[0;36m
COLOUR_END=\033[0m

#----------------------------------------------------------------------------#

OBJSF = .cache_exists

all: $(NAME)

$(NAME): $(OBJS)
		@$(AR) $(LIBRARY) $(OBJS)
		@$(CC) $(CFLAGS) $(OPTFLAGS) -L. $(LIBRARY) $(SRCS) -o $(NAME)
		@echo "$(COLOUR_GREEN)$(NAME) has been compiled!$(COLOUR_END)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJSF)
		@$(CC) $(CFLAGS) $(OPTFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJSF):
		@mkdir -p $(OBJS_DIR)
		@mkdir -p $(OBJS_DIR)$(SET_UP_DIR)
		@mkdir -p $(OBJS_DIR)$(ERROR_CHECK_DIR)
		@mkdir -p $(OBJS_DIR)$(MISC_DIR)
		@mkdir -p $(OBJS_DIR)$(THREADS_DIR)
		@mkdir -p $(OBJS_DIR)$(CLEANING_DIR)

clean:
			@echo "$(COLOUR_BLUE)Cleaning $(NAME)...$(COLOUR_END)"
			@rm -rf $(OBJS_DIR)
			@rm -f $(OBJSF)

fclean: clean
			@echo "$(COLOUR_YELLOW)FCleaning $(NAME)...$(COLOUR_END)"
			@rm -f $(NAME)
			@rm -f $(LIBRARY)

re: fclean all

.PHONY: 	all clean fclean re
