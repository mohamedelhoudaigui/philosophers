/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_linked_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:24:43 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/09 20:07:40 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(t_data *data, pthread_mutex_t *print)
{
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*edit;

	philo = gb_malloc(sizeof(t_philo), 0);
	thread = gb_malloc(sizeof(pthread_t), 0);
	fork = gb_malloc(sizeof(pthread_mutex_t), 0);
	edit = gb_malloc(sizeof(pthread_mutex_t), 0);
	if (!philo || !thread || !fork || !edit)
		return (NULL);
	pthread_mutex_init(edit, NULL);
	pthread_mutex_init(fork, NULL);
	philo->data = data;
	philo->next = NULL;
	philo->thread = thread;
	philo->fork = fork;
	philo->edit = edit;
	philo->print = print;
	philo->start_time = get_time();
	philo->timer = get_time();
	philo->times_eat = data->num_to_eat;
	philo->done_eat = false;
	return (philo);
}

void	add_philo(t_philo **head, t_philo *philo)
{
	t_philo	*base;

	if (!head || !philo)
		return ;
	base = *head;
	if (!base)
	{
		philo->next = philo;
		*head = philo;
		return ;
	}
	while (base->next != *head)
		base = base->next;
	philo->next = *head;
	base ->next = philo;
}

t_philo	*create_philos(t_data *data, pthread_mutex_t *print)
{
	int				i;
	t_philo			*head;
	t_philo			*new_philo;

	i = 0;
	head = NULL;
	while (i < data->philos_num)
	{
		new_philo = create_philo(data, print);
		if (!new_philo)
			return (NULL);
		new_philo->philo_num = i;
		i++;
		add_philo(&head, new_philo);
	}
	return (head);
}
