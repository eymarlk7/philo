/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:45:22 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 16:18:21 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_atoi(char *ptr)
{
	int	signal;
	int	result;

	signal = 1;
	result = 0;
	while (*ptr == 32 || (*ptr >= 9 && *ptr <= 13))
		ptr++;
	if (*ptr == 43 || *ptr == 45)
	{
		if (*ptr == 45)
			signal = -1;
		ptr++;
	}
	while (ft_isdigit(*ptr))
	{
		result = result * 10 + (*ptr - '0');
		ptr++;
	}
	return (result * signal);
}

size_t	get_cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
