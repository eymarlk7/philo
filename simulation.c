#include "philo.h"

int	check_all_ate(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_lock);
	if (philo->data->tt_philo_eat == philo->data->n_philo)
	{
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

int	number_philo_one(t_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, "has taken a fork", get_cur_time());
		usleep(philo->data->t_die * 1000);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

int	is_philo_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_cur_time() - philo[i].last_meal >= philo->data->t_die)
	{
		print_msg(&philo[i], "die", get_cur_time());
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
	int	i;
	t_philo *philo;

	philo = (t_philo *)arg;
	while (check_dead(philo))
	{
		i = 0;
		while (i < philo->data->n_philo)
		{
			if (is_philo_dead(philo, i))
				break;
			i++;
		}
		if (philo->data->tt_eat != 0)
			if (check_all_ate(philo) == 1)
				break;
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
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}