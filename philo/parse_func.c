/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:23:48 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/15 19:09:15 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_max(int sign, unsigned long long res)
{
	if (res > 9223372036854775807 && sign == 1)
	{
		res = -1;
		return ((int)res);
	}
	else if (res > 9223372036854775807 && sign == -1)
	{
		res = 0;
		return ((int)res);
	}
	return ((int)(res * sign));
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -sign;
		i++;
	}
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = (str[i++] - '0') + (res * 10);
	return (check_max(sign, res));
}

void	assign_values(t_data *data, char **av)
{
	data->philos_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
}

bool	check_values(t_data *data)
{
	if (data->philos_num <= 0 || data->time_to_die <= 59
		|| data->time_to_eat <= 59 || data->time_to_sleep <= 59)
	{
		gb_malloc(0, 1);
		return (false);
	}
	return (true);
}
