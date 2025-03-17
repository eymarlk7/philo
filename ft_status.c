/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:19:24 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/17 15:36:34 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void    philo_pick_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        ft_print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        ft_print_status(philo, "has taken a fork");
    }
    else
    {
        usleep(2000);
        pthread_mutex_lock(philo->right_fork);
        ft_print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        ft_print_status(philo, "has taken a fork");
    }
}
void    philo_eating(t_philo *philo)
{
    philo->eating++;
    philo->last_meal_time = get_time_now();
    ft_print_status(philo, "is eating");
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    philo_thiking(t_philo *philo)
{
    ft_print_status(philo, "is thiking");
}

void    philo_sleeping(t_philo *philo)
{
    ft_print_status(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
}

void    ft_philo_is_dead(t_philo *philo)
{
    if (philo->id == 0 && philo->data->num_philo == 1)
    {
        ft_print_status(philo, "is thinking");
        pthread_mutex_lock(philo->left_fork);
        ft_print_status(philo, "has taken a fork");
        usleep(philo->data->time_to_die * 1000);
        pthread_mutex_unlock(philo->left_fork);
        ft_print_status(philo, "died");
        philo->data->status = 1;
    } 
}