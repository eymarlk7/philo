/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_to_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:02:25 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/23 19:40:54 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(&philo->data->status_lock);
	status = philo->data->status;
	pthread_mutex_unlock(&philo->data->status_lock);
	return (status);
}

void	print_msg(t_philo *philo, char *msg)
{
	if (check_philo_status(philo))
		return ;
	pthread_mutex_lock(&philo->data->write_msg);
	printf("TIME[%lld]", get_current_time() - philo->data->start_time);
	printf("\t[%d]\t%s\n", philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->write_msg);
}

int	check_all_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("error: number of args out of range\n"), 1);
	else if (check_inputs(argv) != 0)
		return (printf("error: found an invalid character\n"), 1);
	else if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (printf("error: number of philosophers invalid\n"), 1);
	else if (ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (printf("error: a number of the args invalid\n"), 1);
	if (argv[5])
		if (ft_atoi(argv[5]) <= 0)
			return (printf("error: a number of the args invalid\n"), 1);
	return (0);
}
