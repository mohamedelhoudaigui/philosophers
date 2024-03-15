/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:11:58 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/15 21:43:18 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_error(void)
{
	write(2, "input error\n", 12);
}

void	destroy_all(t_philo *head)
{
	int	i;

	pthread_mutex_destroy(head->print);
	gb_malloc(0, 1);
	i = 0;
	while (head && i < head->data->philos_num)
	{
		pthread_mutex_destroy(head->fork);
		pthread_mutex_destroy(head->edit);
		i++;
		head = head->next;
	}
	exit(0);
}

void	*rout_eat(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_eat(philo) == true)
			destroy_all(philo);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	bool	value;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->edit);
		value = philo->done_eat;
		pthread_mutex_unlock(philo->edit);
		if (value == true)
			break ;
		take_fork(philo);
		eat(philo);
		philo_sleep(philo);
		thinking(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data			*data;
	t_philo			*head;
	pthread_mutex_t	print;

	data = extract_args(ac, av);
	if (!data)
	{
		p_error();
		return (1);
	}
	pthread_mutex_init(&print, NULL);
	head = create_philos(data, &print);
	if (!head)
		return (1);
	start_sim(head);
	return (0);
}
