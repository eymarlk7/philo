/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:43:43 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 16:30:37 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo_threads(t_philo *philo, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < n_philo)
		pthread_join(philo[i++].thread, NULL);
}

void	create_all_threads(t_data data, t_philo *philo)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, check_all_thrads, philo);
	create_philo_threads(philo, data.n_philo);
	pthread_join(monitor, NULL);
}
