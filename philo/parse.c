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

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	if (i != n)
		return (s1[i] - s2[i]);
	return (0);
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
	i = 1;
	while (av[i])
	{
		if (ft_strncmp(av[i], "2147483647", ft_strlen(av[i])) > 0)
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
	data->philos_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		data->num_to_eat = ft_atoi(av[5]);
	else
		data->num_to_eat = -1;
	if (data->philos_num <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
