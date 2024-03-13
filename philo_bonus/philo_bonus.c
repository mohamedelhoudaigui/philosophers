/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:05:47 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/08 22:42:34 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	*data;
	sem_t	*print;
	sem_t	*forks;
	sem_t	*end;		

	data = extract_args(ac, av);
	if (!data)
	{
		p_error();
		return (1);
	}
	print = sema_create("print", 1);
	end = sema_create("end", 1);
	forks = sema_create("forks", data->philos_num);
	data->end = end;
	create_philos(data, print, forks);
	return (0);
}
