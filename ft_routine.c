/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:09:19 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/17 15:00:13 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"


void    *ft_routine(void *argv)
{
    t_philo *philo;

    philo = (t_philo *)argv;
    while (philo->data->must_eat_count == 0 || philo->eating < philo->data->must_eat_count)
    {
        ft_philo_is_dead(philo);
        if (philo->data->status == 1)
            break;
        philo_pick_forks(philo);
        philo_eating(philo);
        philo_sleeping(philo);
        philo_thiking(philo);  
    }
    philo->data->simulation_end--;
    return (NULL);
}

void    *monitor_dead(void *argv)
{
    int i;
    t_data *data;

    data = (t_data *)argv;
    while (data->simulation_end > 0)
    {
        i = 0;
        while (i < data->num_philo)
        {
            usleep(1000);
            if (get_time_now() - (data->philos[i].last_meal_time + 3) >= data->time_to_die)
            {
                if ((data->philos[i].eating != data->time_to_eat))
                {
                    ft_print_status(&data->philos[i], "died");
                    data->status = 1;
                    return (NULL);
                }
            }
            i++;
        }
        
    }
    return (NULL);
}