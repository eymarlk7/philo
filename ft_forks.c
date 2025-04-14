/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:43:51 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 17:09:09 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_fork1(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->data->dead_val == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_lock(philo->l_fork);
		philo->has_l_fork = 1;
		print_msg(philo, YELLOW"has taken a fork"RESET, get_cur_time());
		pthread_mutex_lock(philo->r_fork);
		philo->has_r_fork = 1;
		print_msg(philo, YELLOW"has taken a fork"RESET, get_cur_time());
	}
	else
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
}

void	pick_fork2(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->data->dead_val == 0 && philo->data->n_philo != 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_lock(philo->r_fork);
		philo->has_r_fork = 1;
		print_msg(philo, YELLOW"has taken a fork"RESET, get_cur_time());
		pthread_mutex_lock(philo->l_fork);
		philo->has_l_fork = 1;
		print_msg(philo, YELLOW"has taken a fork"RESET, get_cur_time());
	}
	else
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
}

void	put_forks_on_table(t_philo *philo)
{
	if (philo->has_l_fork)
	{
		pthread_mutex_unlock(philo->l_fork);
		philo->has_l_fork = 0;
	}
	if (philo->has_r_fork)
	{
		pthread_mutex_unlock(philo->r_fork);
		philo->has_r_fork = 0;
	}
}
