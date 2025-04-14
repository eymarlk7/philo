NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	main.c \
		init.c \
		utils.c \
		ft_forks.c \
		validations.c \
		philo_actions.c \
		check_to_print.c \
		ft_create_threads.c \
		simulation.c 

OBJS = $(SRCS:.c=.o)

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY:all clean fclean re
