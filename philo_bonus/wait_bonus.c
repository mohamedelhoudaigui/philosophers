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

void	kill_all(pid_t *proc_arr, t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < data->philos_num)
	{
		kill(proc_arr[i], SIGKILL);
		i++;
	}
	(void)philo;
	// clean_up(philo);
	exit(0);
}

void	*grim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->end);
	return (kill_all(philo->data->proc_arr, philo->data, philo), NULL);
}

void	wait_philo(t_data *data, t_philo *philo, pid_t *proc_arr)
{
	pthread_t	grim_t;

	pthread_create(&grim_t, NULL, &grim, philo);
	pthread_detach(grim_t);
	while (philo)
	{
		sem_wait(philo->end);
		philo = philo->next;
	}
	kill_all(proc_arr, data, philo);
}
