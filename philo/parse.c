/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:23:08 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/06 03:41:53 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_error(void)
{
	write(2, "input error\n", 12);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5)
		return (1);
	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '\0')
			return (1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_data	*extract_args(int ac, char **av)
{
	t_data	*data;

	if (check_args(ac, av) == 1)
		return (NULL);
	data = gb_malloc(sizeof(t_data), 0);
	if (!data)
		return (NULL);
	data->philos_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		data->num_to_eat = ft_atoi(av[5]);
	else
		data->num_to_eat = -1;
	if (data->philos_num <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
