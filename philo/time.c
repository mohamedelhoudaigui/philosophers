/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 01:48:08 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/09 20:19:50 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	is_dead(t_philo *philo)
{
	long long	philo_time;

	pthread_mutex_lock(philo->edit);
	philo_time = philo->timer;
	pthread_mutex_unlock(philo->edit);
	if (get_time() > philo_time + philo->data->time_to_die)
		return (true);
	return (false);
}

void	sleep_opt(long long time)
{
	long long	cur_time;

	cur_time = get_time();
	while (get_time() < cur_time + time)
		usleep(100);
}

bool	check_eat(t_philo *philo)
{
	t_philo	*base;

	base = philo;
	while (base->next != philo)
	{
		if (base->done_eat == false)
			return (false);
		base = base->next;
	}
	return (true);
}

void	grim_reaper(t_philo *philo)
{
	while (philo)
	{
		if (philo->done_eat == false)
		{
			if (is_dead(philo) == true)
			{
				pthread_mutex_lock(philo->print);
				printf("%lld %d died\n", get_time() - philo->start_time,
					philo->philo_num + 1);
				return ;
			}
		}
		philo = philo->next;
	}
}
