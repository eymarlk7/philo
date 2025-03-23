/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:38:27 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/23 18:21:01 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				tt_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				tt_eat;
	int				status;
	long long		start_time;
	pthread_t		monitor;
	pthread_mutex_t	write_msg;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	status_lock;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_data;

int		ft_atoi(char *ptr);
int		get_current_time(void);
int		check_inputs(char **argv);
int		check_all_args(int argc, char **argv);
int		check_philo_status(t_philo *philo);

void	init_data(t_data *data, char **argv);
void	print_msg(t_philo *philoi, char *msg);
void	init_data(t_data *data, char **argv);

void	if_one_philo(t_philo *philo);
void	pick_fork(t_philo *philo);
void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void	philo_thinking(t_philo *philo);
void	start_simulation(t_data *data);

#endif
