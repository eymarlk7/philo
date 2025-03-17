/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:09:41 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/17 15:16:29 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// void ft_print_data(t_data *data, int argc)
// {
//     printf("num_philo: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\n",
//         data->num_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep);
//     if (argc == 6)
//         printf("must_each_eat: %d\n", data->must_eat_count);
// }

void    ft_starting_simulation(t_data *data)
{
    int i;

    i = 0;
    pthread_create(&data->death, NULL, monitor_dead, data);
    while (i < data->num_philo)
        pthread_join(data->philos[i++].thread, NULL);
    pthread_join(data->death, NULL);
    i = 0;
    while (i < data->num_philo)
        pthread_mutex_destroy(&data->forks[i++]);
    free(data->forks);
    free(data->philos);
    
    
}

int main(int argc, char *argv[])
{
    t_data data;

    if (check_status_and_write(&data, argc, argv) != 0)
        return (1);
    ft_starting_simulation(&data);
    return 0;
}
