/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:57:01 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/23 19:41:21 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->write_msg);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->status_lock);
	free(data->forks);
	free(data->philo);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->tt_eat == 0 || philo->meals_eaten < philo->data->tt_eat)
	{
		if_one_philo(philo);
		pthread_mutex_lock(&philo->data->status_lock);
		if (philo->data->status == 1)
		{
			pthread_mutex_unlock(&philo->data->status_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->status_lock);
		pick_fork(philo);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	philo->data->tt_philo--;
	return (NULL);
}

static int	check_dead(t_data *data, int i)
{
	if ((get_current_time() - data->philo[i].last_meal) >= data->t_die)
	{
		if ((data->philo[i].meals_eaten != data->tt_eat))
		{
			print_msg(data->philo, "die");
			pthread_mutex_lock(&data->status_lock);
			data->status = 1;
			pthread_mutex_unlock(&data->status_lock);
			return (1);
		}
	}
	return (0);
}

static void	*check_all_philo(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (data->tt_philo > 0)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->eat_lock);
			if (check_dead(data, i))
			{
				pthread_mutex_unlock(&data->eat_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->eat_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	pthread_create(&data->monitor, NULL, check_all_philo, data);
	while (i < data->n_philo)
	{
		data->philo[i].last_meal = data->start_time;
		pthread_create(&data->philo[i].thread, NULL,
			philo_routine, &data->philo[i]);
		pthread_detach(data->philo[i].thread);
		i++;
	}
	pthread_join(data->monitor, NULL);
	destroy_all(data);
}
