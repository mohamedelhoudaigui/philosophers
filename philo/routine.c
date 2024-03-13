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
		philo->done_eating = true;
	philo->times_eat--;
	pthread_mutex_unlock(philo->edit);
	pthread_mutex_unlock(philo->next->fork);
	pthread_mutex_unlock(philo->fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d is sleeping\n", get_time() - philo->start_time,
		philo->philo_num + 1);
	pthread_mutex_unlock(philo->print);
	sleep_opt(philo->data->time_to_sleep);
}

void	*watch_eating(void *arg)
{
	t_philo	*philo;
	t_philo	*save;
	t_philo	*end_sim;
	int		i;
	int		number;

	i = 0;
	number = 0;
	philo = (t_philo *)arg;
	save = philo;
	end_sim = philo;
	while (philo)
	{
		if (number == philo->data->philos_num)
		{
			pthread_mutex_lock(philo->print);
			break ;
		}
		pthread_mutex_lock(philo->edit);
		if (philo->done_eating == true)
			number++;
		pthread_mutex_unlock(philo->edit);
			
		philo = philo->next;
	}
	while (end_sim && i < end_sim->data->philos_num)
	{
		end_sim->sim_end = true;
		end_sim = end_sim->next;
		i++;
	}
	destroy_all(save);
	exit(0);
}

void	start_sim(t_philo *philo)
{
	int			i;
	t_philo		*tmp;
	pthread_t	watch_eat;

	tmp = philo;
	i = 0;
	while (i < tmp->data->philos_num)
	{
		if (tmp->philo_num - 1 % 2 == 0)
			usleep(500);
		pthread_create(tmp->thread, NULL, &routine, tmp);
		pthread_detach(*tmp->thread);
		i++;
		tmp = tmp->next;
	}
	pthread_create(&watch_eat, NULL, &watch_eating, philo);
	pthread_detach(watch_eat);
	grim_reaper(philo);
}
