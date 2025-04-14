/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:44:48 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 17:12:00 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define RESET   "\033[0m"

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	t_mutex	eat_lock;
	t_mutex	dead_lock;
	t_mutex	write_lock;
	size_t	t_die;
	size_t	t_eat;
	size_t	t_sleep;
	int		tt_eat;
	int		n_philo;
	int		dead_val;
	int		tt_philo_eat;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			tt_meals;
	int			has_l_fork;
	int			has_r_fork;
	size_t		last_meal;
	size_t		start_time;
	pthread_t	thread;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	t_mutex		*eat_lock;
	t_mutex		*dead_lock;
	t_mutex		*write_lock;
	t_data		*data;
}	t_philo;

int		ft_isdigit(int c);
int		ft_atoi(char *ptr);
size_t	get_cur_time(void);

int		check_dead(t_philo *philo);
int		number_philo_one(t_philo *philo);
int		check_if_args_valid(int argc, char **argv);

void	init_data(t_data data, char **argv);

void	pick_fork1(t_philo *philo);
void	pick_fork2(t_philo *philo);
void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void	philo_thinking(t_philo *philo);
void	put_forks_on_table(t_philo *philo);

void	*philo_routine(void *arg);
void	*check_all_thrads(void *arg);

void	create_all_threads(t_data data, t_philo *philo);
void	print_msg(t_philo *philo, char *msg, size_t time);

void	clean_all(t_data *data, t_mutex *forks);

#endif
