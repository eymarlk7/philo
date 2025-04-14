/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_to_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:43:33 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 16:01:33 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->data->dead_val == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	else
		pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	print_msg(t_philo *philo, char *msg, size_t time)
{
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_val == 0)
	{
		if (philo->data->tt_eat != 0 && philo->tt_meals < philo->data->tt_eat)
			printf("%lu \t%d\t%s\n", time - philo->start_time, philo->id, msg);
		else if (philo->data->tt_eat == 0)
			printf("%lu \t%d\t%s\n", time - philo->start_time, philo->id, msg);
	}
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(&philo->data->dead_lock);
}
