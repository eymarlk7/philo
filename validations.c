/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:45:59 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/29 16:20:15 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_inputs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] == '+' && ft_isdigit(argv[i][j + 1]))
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("error: invalid character - '%c'", argv[i][j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_if_args_valid(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("error: number of args invalid\n"), 1);
	else if (check_inputs(argv))
		return (printf("\n"), 1);
	else if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (printf("error: number of philosophers invalid\n"), 1);
	else if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0 || (argv[5] != NULL && ft_atoi(argv[5]) <= 0))
	{
		printf("error: number of t_die, t_eat, t_sleep");
		printf(" or tt_eat of philo invalid\n");
		return (1);
	}
	return (0);
}
