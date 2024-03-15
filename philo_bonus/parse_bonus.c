/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:23:08 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/15 19:13:30 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	check_overflow(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_strlen(av[i]) > 10)
			return (false);
		i++;
	}
	return (true);
}

t_data	*extract_args(int ac, char **av)
{
	t_data	*data;

	if (check_args(ac, av) == 1)
		return (NULL);
	if (check_overflow(av) == false)
		return (NULL);
	data = gb_malloc(sizeof(t_data), 0);
	if (!data)
		return (NULL);
	assign_values(data, av);
	if (av[5] != NULL)
	{
		data->num_to_eat = ft_atoi(av[5]);
		if (data->num_to_eat <= 0)
		{
			gb_malloc(0, 1);
			return (NULL);
		}
	}
	else
		data->num_to_eat = -1;
	if (check_values(data) == false)
		return (NULL);
	return (data);
}
