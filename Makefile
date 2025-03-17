NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	ft_philo.c \
		ft_philo_utils.c

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