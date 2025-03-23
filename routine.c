/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:21:57 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/23 18:08:34 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	if_one_philo(t_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, "has taken a fork");
		usleep(philo->data->t_die * 1000);
		pthread_mutex_unlock(philo->l_fork);
		print_msg(philo, "died");
		pthread_mutex_lock(&philo->data->status_lock);
		philo->data->status = 1;
		pthread_mutex_unlock(&philo->data->status_lock);
	}
}

void	pick_fork(t_philo *philo)
{
	if (check_philo_status(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, "has taken a fork");
	}
	else
	{
		usleep(400);
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, "has taken a fork");
	}
}

void	philo_eating(t_philo *philo)
{
	if (check_philo_status(philo))
		return ;
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	print_msg(philo, "is eating");
	usleep(philo->data->t_eat * 800);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleeping(t_philo *philo)
{
	if (check_philo_status(philo))
		return ;
	print_msg(philo, "is sleeping");
	usleep(philo->data->t_sleep * 800);
}

void	philo_thinking(t_philo *philo)
{
	if (check_philo_status(philo))
		return ;
	print_msg(philo, "is thinking");
}
