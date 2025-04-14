/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:44:15 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 16:21:57 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_data *data, t_mutex *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->eat_lock);
	while (i < data->n_philo)
		pthread_mutex_destroy(&forks[i++]);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (check_if_args_valid(argc, argv))
		return (1);
	init_data(data, argv);
	return (0);
}
