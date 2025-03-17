/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:10:04 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/17 12:24:21 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int ft_init_philo_data(t_data *data, int argc, char **argv)
{
    if (ft_check_arg(argv) == -1)
        return (1);
    if (argc < 5 || argc > 6)
        return (2);
    data->num_philo = ft_atoi(argv[1]);
    if (data->num_philo > 200 || data->num_philo <= 0)
        return (3);
    data->time_to_die = ft_atoi(argv[2]);
    if (data->time_to_die <= 0)
        return (4);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->must_eat_count = ft_atoi(argv[5]);
    else
        data->must_eat_count = 0;
    data->status = 0;
    return (0);
}

void    ft_init_mutex(t_data *data)
{
    int i;

    pthread_mutex_init(&data->print_sms, NULL);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
    i = -1;
    while (++i < data->num_philo)
        pthread_mutex_init(&data->forks[i], NULL);
}

void    ft_init_philos(t_data *data)
{
    int i;
    long long start_time;

    i = 0;
    start_time = get_time_now();
    data->philos = malloc(sizeof(t_philo) * data->num_philo);
    while (i < data->num_philo)
    {
        data->philos[i].id = i;
        data->philos[i].eating = 0;
        data->philos[i].start_time = start_time;
        data->philos[i].last_meal_time = start_time;
        if (i == 0)
            data->philos[i].left_fork = &data->forks[data->num_philo - 1];
        else
            data->philos[i].left_fork = &data->forks[i - 1];
        data->philos[i].right_fork = &data->forks[i];
        data->philos[i].data = data;
        pthread_create(&data->philos[i].thread, NULL, ft_routine, &data->philos[i]);
        i++;
    }
    
}

int    ft_ini_data(t_data *data, int argc, char **argv)
{
    int check_val;

    check_val = ft_init_philo_data(data, argc, argv);
    if (check_val != 0)
        return (check_val);
    ft_init_mutex(data);
    ft_init_philos(data);
    return (0);
}