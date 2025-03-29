#include "philo.h"

void	pick_fork1(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->data->dead_val == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_lock(philo->l_fork);
		philo->has_l_fork = 1;
		print_msg(philo, "has taken a fork", get_cur_time());
		pthread_mutex_lock(philo->r_fork);
		philo->has_r_fork = 1;
		print_msg(philo, "has taken a fork", get_cur_time());
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
		print_msg(philo, "has taken a fork", get_cur_time());
		pthread_mutex_lock(philo->l_fork);
		philo->has_l_fork = 1;
		print_msg(philo, "has taken a fork", get_cur_time());
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

void count_meals(t_philo *philo)
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
		print_msg(philo, "is eating", get_cur_time());
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
		print_msg(philo, "is sleeping", get_cur_time());
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
		print_msg(philo, "is thinking", get_cur_time());
	}
	else
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
}