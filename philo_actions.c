/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:44:30 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 17:12:17 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	number_philo_one(t_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, YELLOW"has taken a fork"RESET, get_cur_time());
		usleep(philo->data->t_die * 1000);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

static void	count_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_lock);
	philo->last_meal = get_cur_time();
	if (philo->data->tt_eat != 0)
	{
		if (++philo->tt_meals == philo->data->tt_eat)
			++philo->data->tt_philo_eat;
	}
	pthread_mutex_unlock(philo->eat_lock);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->data->dead_val == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		print_msg(philo, GREEN"is eating"RESET, get_cur_time());
		usleep(philo->data->t_eat * 1000);
		put_forks_on_table(philo);
		count_meals(philo);
	}
	else
	{
		put_forks_on_table(philo);
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->data->dead_val == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		print_msg(philo, MAGENTA"is sleeping"RESET, get_cur_time());
		usleep(philo->data->t_sleep * 1000);
	}
	else
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
}

void	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->data->dead_val == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		print_msg(philo, BLUE"is thinking"RESET, get_cur_time());
	}
	else
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
}
