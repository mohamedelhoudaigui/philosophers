/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:11:58 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/06 03:44:32 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_philo *head)
{
	int	i;

	pthread_mutex_destroy(head->print);
	i = 0;
	while (head && i < head->data->philos_num)
	{
		pthread_mutex_destroy(head->fork);
		pthread_mutex_destroy(head->edit);
		i++;
		head = head->next;
	}
	gb_malloc(0, 1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		thinking(philo);
		take_fork(philo);
		eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*head;

	data = extract_args(ac, av);
	if (!data)
	{
		p_error();
		return (1);
	}
	head = create_philos(data);
	if (!head)
		return (1);
	start_sim(head);
	destroy_all(head);
	return (0);
}
