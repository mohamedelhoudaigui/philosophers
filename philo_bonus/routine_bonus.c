/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:37:47 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/07 20:38:58 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(sem_t **forks, unsigned int i, t_data *data, long long start)
{
	if (i % 2 == 0)
		usleep(1000);
	sem_wait(*forks);
	printf("%lld %d is eating\n", get_time() - start, i + 1);
	usleep(data->time_to_eat * 1000);
	sem_post(*forks);
	printf("%lld %d is sleeping\n", get_time() - start, i + 1);
	usleep(data->time_to_eat * 1000);
	exit(0);
	return (NULL);
}
