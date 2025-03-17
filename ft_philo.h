#ifndef PHILOSOPHERS
#define PHILOSOPHERS
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    int num_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_each_eat;
}   t_philo;


int ft_check_arg(char const **argv);
int ft_atoi(const char *nptr);

#endif