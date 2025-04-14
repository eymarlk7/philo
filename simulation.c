/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:45:14 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 17:14:19 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_ate(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_lock);
	if (philo->data->tt_philo_eat == philo->data->n_philo)
	{
		printf(GREEN"All the philosophers have finished eating\n"RESET);
		pthread_mutex_lock(philo->dead_lock);
		philo->data->dead_val = 1;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(philo->eat_lock);
		return (1);
	}
	else
		pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

static int	is_philo_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_cur_time() - philo[i].last_meal >= philo->data->t_die)
	{
		print_msg(&philo[i], RED"die"RESET, get_cur_time());
		pthread_mutex_lock(philo->dead_lock);
		philo->data->dead_val = 1;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(philo->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

void	*check_all_thrads(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_dead(philo))
	{
		i = 0;
		while (i < philo->data->n_philo)
		{
			if (is_philo_dead(philo, i))
				break ;
			i++;
		}
		if (philo->data->tt_eat != 0)
			if (check_all_ate(philo) == 1)
				break ;
		usleep(1000);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (number_philo_one(philo) == 1)
		return (NULL);
	while (check_dead(philo))
	{
		if (philo->id % 2 == 0)
			pick_fork1(philo);
		else
		{
			usleep(1000);
			pick_fork2(philo);
		}
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (NULL);
}
