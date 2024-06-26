/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 01:14:22 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/16 23:00:37 by mel-houd         ###   ########.fr       */
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
	philo->timer = get_time();
	if (philo->times_eat == 0)
		philo->done_eat = true;
	philo->times_eat -= 1;
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is sleeping\n", get_time() - philo->start_time,
		philo->philo_num + 1);
	pthread_mutex_unlock(philo->print);
	sleep_opt(philo->data->time_to_sleep);
}

void	start_sim(t_philo *philo, t_data *data)
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
		if (pthread_create(tmp->thread, NULL, &routine, tmp) != 0)
			exit(0);
		pthread_detach(*tmp->thread);
		i++;
		tmp = tmp->next;
	}
	if (data->num_to_eat != -1)
	{
		if (pthread_create(&check_t, NULL, &rout_eat, philo) != 0)
			exit(0);
		pthread_detach(check_t);
	}
	grim_reaper(philo);
	destroy_all(philo);
}
