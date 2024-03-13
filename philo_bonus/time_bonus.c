/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:36:14 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/09 22:04:07 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long long time)
{
	long long	cur_time;

	cur_time = get_time();
	while (get_time() < cur_time + time)
		usleep(100);
}

bool	is_dead(t_philo *philo)
{
	long long	philo_time;

	philo_time = philo->timer + philo->data->time_to_die;
	if (get_time() > philo_time)
	{
		philo->is_dead = true;
		return (true);
	}
	return (false);
}

void	*grim_r(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		if (philo->done_eat == true)
			return (NULL);
		if (is_dead(philo) == true)
			break ;
	}
	i_am_dead(philo);
	sem_post(philo->data->end);
	return (NULL);
}

void	sleep_philo(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%lld %d is sleeping\n", get_time() - philo->start,
		philo->philo_num + 1);
	sem_post(philo->print);
	ft_usleep(philo->data->time_to_sleep);
}
