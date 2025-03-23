/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:11:34 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/23 17:31:51 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_inputs(t_data *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->tt_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->tt_eat = ft_atoi(argv[5]);
	else
		data->tt_eat = 0;
	data->status = 0;
}

static void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return ;
	while (i < data->n_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
}

static void	init_all_mutex(t_data *data)
{
	pthread_mutex_init(&data->write_msg, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&data->status_lock, NULL);
	init_forks(data);
}

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return ;
	while (i < data->n_philo)
	{
		data->philo[i].id = i;
		data->philo[i].meals_eaten = 0;
		if (i == 0)
			data->philo[i].l_fork = &data->forks[data->n_philo - 1];
		else
			data->philo[i].l_fork = &data->forks[i - 1];
		data->philo[i].r_fork = &data->forks[i];
		data->philo[i].data = data;
		i++;
	}
}

void	init_data(t_data *data, char **argv)
{
	init_inputs(data, argv);
	init_all_mutex(data);
	init_philos(data);
}
