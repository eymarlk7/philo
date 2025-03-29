#include "philo.h"

void    clean_all(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->eat_lock);
	// pthread_mutex_destroy(&data->last_meal_lock);
	while (i < data->n_philo)
		pthread_mutex_destroy(&forks[i++]);
}

int main(int argc, char *argv[])
{
	t_data data;
	t_philo *philo;
	pthread_mutex_t *forks;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
		return(1);
	init_inputs(&data, argv);
	philo = malloc(sizeof(t_philo) * data.n_philo);
	forks = malloc(sizeof(pthread_mutex_t) * data.n_philo);
	ini_mutex_lock(&data);
	init_forks(&data, forks);
	init_philos(philo, &data, forks);
	pthread_create(&monitor, NULL, check_all_thrads, philo);
	create_philo_threads(philo, data.n_philo);
	pthread_join(monitor, NULL);
	clean_all(&data, forks);
	free(forks);
	free(philo);
    return 0;
}
