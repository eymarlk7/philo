NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	main.c \
	init.c \
	utils.c \
	routine.c \
	check_to_print.c \
	start_simulation.c 

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
