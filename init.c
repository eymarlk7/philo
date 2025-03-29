#include "philo.h"

void    init_inputs(t_data *data, char **argv)
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

void    ini_mutex_lock(t_data *data)
{
	pthread_mutex_init(&data->dead_lock, NULL);   
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);    
}

void	init_forks(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		pthread_mutex_init(&forks[i++], NULL);
}

void	init_philos(t_philo *philo, t_data *data, pthread_mutex_t *forks)
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
