/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:09:29 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/17 15:31:46 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_philo.h"

long long get_time_now(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long get_time_ms(t_philo *philo)
{
    return (get_time_now() - philo->start_time);
}

void    ft_print_status(t_philo *philo, char *arg)
{
    pthread_mutex_lock(&philo->data->print_sms);
    if (philo->data->status == 0)
    {
        printf("TIME[%lld]", get_time_ms(philo));
        printf("\t{%d}\t%s\t\n", philo->id + 1, arg);
    }
    pthread_mutex_unlock(&philo->data->print_sms);
}