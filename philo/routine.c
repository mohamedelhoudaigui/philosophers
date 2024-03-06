/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 01:14:22 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/06 03:44:26 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is thinking\n", get_time() - philo->start_time,
		philo->philo_num + 1);
	pthread_mutex_unlock(philo->print);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->print);
	printf("%lld %d has taken a fork\n", get_time() - philo->start_time,
		philo->philo_num + 1);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->next->fork);
	pthread_mutex_lock(philo->print);
	printf("%lld %d has taken a fork\n", get_time() - philo->start_time,
		philo->philo_num + 1);
	pthread_mutex_unlock(philo->print);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is eating\n", get_time() - philo->start_time,
		philo->philo_num + 1);
	pthread_mutex_unlock(philo->print);
	sleep_opt(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
	pthread_mutex_lock(philo->edit);
	philo->timer += philo->data->time_to_die;
	philo->times_eat -= 1;
	pthread_mutex_unlock(philo->edit);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is sleeping\n", get_time() - philo->start_time,
		philo->philo_num + 1);
	pthread_mutex_unlock(philo->print);
	sleep_opt(philo->data->time_to_sleep);
}

void	start_sim(t_philo *philo)
{
	int		i;
	t_philo	*tmp;

	tmp = philo;
	i = 0;
	while (tmp && i < tmp->data->philos_num)
	{
		if (i % 2 == 0)
			usleep(100);
		pthread_create(tmp->thread, NULL, &routine, tmp);
		pthread_detach(*tmp->thread);
		i++;
		tmp = tmp->next;
	}
	grim_reaper(philo);
}
