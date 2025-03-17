/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:09:49 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/17 15:20:16 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
#define PHILOSOPHERS

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_data
{
    int             num_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;
    _Atomic int     simulation_end;
    _Atomic int     status;
    pthread_mutex_t *forks;
    pthread_mutex_t print_sms;
    pthread_t       death;
    struct s_philo *philos;
}   t_data;

typedef struct s_philo
{
    int             id;
    _Atomic int     eating;         
    long long       start_time;
    int             meals_eaten;
    long long       last_meal_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t   thread;
    t_data          *data;
}   t_philo;




/* FUNCTIONS */
void    *ft_routine(void *argv);
int check_status_and_write(t_data *data, int argc, char **argv);
void    *monitor_dead(void *argv);
void    philo_pick_forks(t_philo *philo);
void    philo_eating(t_philo *philo);
void    philo_thiking(t_philo *philo);
void    philo_sleeping(t_philo *philo);
void    ft_philo_is_dead(t_philo *philo);
void    philo_thiking(t_philo *philo);
void    ft_print_status(t_philo *philo, char *arg);
long long get_time_now(void);
int ft_atoi(const char *nptr);
int ft_check_arg(char **argv);
int    ft_ini_data(t_data *data, int argc, char **argv);

#endif