#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	size_t		t_die;
	size_t		t_eat;
	size_t		t_sleep;
	int		tt_eat;
	int		n_philo;
	int		dead_val;
	int		tt_philo_eat;
}	t_data;

typedef struct s_philo
{
	int		id;
	int		tt_meals;
	int		has_l_fork;
	int		has_r_fork;
	size_t		last_meal;
	size_t		start_time;
	pthread_t	thread;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*last_meal_lock;
	t_data		*data;
}	t_philo;


int	ft_isdigit(int c);
int	ft_atoi(char *ptr);
size_t	get_cur_time(void);

int	check_dead(t_philo *philo);

void    ini_mutex_lock(t_data *data);
void    init_inputs(t_data *data, char **argv);
void	init_forks(t_data *data, pthread_mutex_t *forks);
void	init_philos(t_philo *philo, t_data *data, pthread_mutex_t *forks);


void	pick_fork1(t_philo *philo);
void	pick_fork2(t_philo *philo);
void	put_forks_on_table(t_philo *philo);
void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void	philo_thinking(t_philo *philo);
void	print_msg(t_philo *philo, char *msg, size_t time);

void	*check_all_thrads(void *arg);
void	create_philo_threads(t_philo *philo, int n_philo);

#endif