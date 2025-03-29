NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	main.c \
		init.c \
		utils.c \
		validations.c \
		philo_actions.c \
		check_to_print.c \
		simulation.c 

OBJS = $(SRCS:.c=.o)

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)
	rm -f $(OBJS)

clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY:all clean fclean re