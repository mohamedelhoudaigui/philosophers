/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 01:14:22 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/09 22:05:44 by mel-houd         ###   ########.fr       */
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
	pthread_mutex_lock(philo->edit);
	philo->timer = get_time();
	pthread_mutex_unlock(philo->edit);
	sleep_opt(philo->data->time_to_eat);
	pthread_mutex_lock(philo->edit);
	if (philo->times_eat == 0)
		philo->done_eat = true;
	philo->times_eat -= 1;
	pthread_mutex_unlock(philo->edit);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->next->fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is sleeping\n", get_time() - philo->start_time,
		philo->philo_num + 1);
	pthread_mutex_unlock(philo->print);
	sleep_opt(philo->data->time_to_sleep);
}

void	*rout_eat(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_eat(philo) == true)
			destroy_all(philo);
	}
}

void	start_sim(t_philo *philo)
{
	int			i;
	t_philo		*tmp;
	pthread_t	check_t;

	tmp = philo;
	i = 0;
	while (i < tmp->data->philos_num)
	{
		if (tmp->philo_num - 1 % 2 == 0)
			usleep(1000);
		pthread_create(tmp->thread, NULL, &routine, tmp);
		pthread_detach(*tmp->thread);
		i++;
		tmp = tmp->next;
	}
	if (philo->times_eat != -1)
	{
		pthread_create(&check_t, NULL, &rout_eat, philo);
		pthread_detach(check_t);
	}
	grim_reaper(philo);
	destroy_all(philo);
}
