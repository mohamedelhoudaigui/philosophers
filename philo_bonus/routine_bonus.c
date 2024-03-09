/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:37:47 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/09 15:00:05 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	i_am_dead(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%lld %d died\n", get_time() - philo->start, philo->philo_num + 1);
	sem_post(philo->data->end);
}

void	take_fork(t_philo *philo)
{
	if (philo->num_to_eat == 0)
		exit(0);
	sem_wait(philo->print);
	printf("%lld %d is thinking\n", get_time() - philo->start,
		philo->philo_num + 1);
	sem_post(philo->print);
	sem_wait(philo->forks);
	sem_wait(philo->print);
	printf("%lld %d has taken a fork\n", get_time() - philo->start,
		philo->philo_num + 1);
	sem_post(philo->print);
	sem_wait(philo->forks);
	sem_wait(philo->print);
	printf("%lld %d has taken a fork\n", get_time() - philo->start,
		philo->philo_num + 1);
	sem_post(philo->print);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%lld %d is eating\n", get_time() - philo->start,
		philo->philo_num + 1);
	sem_post(philo->print);
	ft_usleep(philo->data->time_to_eat);
	philo->num_to_eat -= 1;
	philo->timer += philo->data->time_to_die;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	sleep_philo(t_philo *philo)
{
	sem_wait(philo->print);
	printf("%lld %d is sleeping\n", get_time() - philo->start,
		philo->philo_num + 1);
	sem_post(philo->print);
	ft_usleep(philo->data->time_to_sleep);
}

void	routine(t_philo *philo)
{
	pthread_t	grim;

	pthread_create(&grim, NULL, &grim_r, philo);
	if (philo->philo_num % 2 == 2)
		usleep(1000);
	while (true)
	{
		take_fork(philo);
		eat(philo);
		sleep_philo(philo);
	}
}
