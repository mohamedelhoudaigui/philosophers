/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:57:21 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/09 15:00:47 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all(pid_t *proc_arr, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		kill(proc_arr[i], SIGKILL);
		i++;
	}
}

void	*grim(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->end);
	kill_all(data->proc_arr, data);
	return (NULL);
}

void	wait_philo(t_data *data, pid_t *proc_arr)
{
	int			i;
	pthread_t	grim_t;

	pthread_create(&grim_t, NULL, &grim, data);
	i = 0;
	while (i < data->philos_num)
	{
		waitpid(proc_arr[i], NULL, 0);
		i++;
	}
}
