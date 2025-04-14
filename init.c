/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:44:02 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 16:13:53 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_inputs(t_data *data, char **argv)
{
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->n_philo = ft_atoi(argv[1]);
	if (argv[5])
		data->tt_eat = ft_atoi(argv[5]);
	else
		data->tt_eat = 0;
	data->dead_val = 0;
	data->tt_philo_eat = 0;
}

static void	ini_mutex_lock_and_forks(t_data *data, t_mutex *forks)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	while (i < data->n_philo)
		pthread_mutex_init(&forks[i++], NULL);
}

static void	init_philos(t_philo *philo, t_data *data, t_mutex *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].dead_lock = &data->dead_lock;
		philo[i].write_lock = &data->write_lock;
		philo[i].eat_lock = &data->eat_lock;
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % data->n_philo];
		philo[i].has_l_fork = 0;
		philo[i].has_r_fork = 0;
		philo[i].tt_meals = 0;
		philo[i].start_time = get_cur_time();
		philo[i].last_meal = get_cur_time();
		philo[i].data = data;
		i++;
	}
}

void	init_data(t_data data, char **argv)
{
	t_philo	*philo;
	t_mutex	*forks;

	init_inputs(&data, argv);
	philo = malloc(sizeof(t_philo) * data.n_philo);
	forks = malloc(sizeof(t_mutex) * data.n_philo);
	ini_mutex_lock_and_forks(&data, forks);
	init_philos(philo, &data, forks);
	create_all_threads(data, philo);
	clean_all(&data, forks);
	free(forks);
	free(philo);
}
