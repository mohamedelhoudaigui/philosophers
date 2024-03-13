/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:47:55 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/09 15:00:12 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*create_philo(t_data *data, int i, sem_t *print, sem_t *forks)
{
	t_philo	*philo;
	sem_t	*end;

	end = sema_create("sem", 1);
	philo = gb_malloc(sizeof(t_philo), 0);
	philo->data = data;
	philo->philo_num = i;
	philo->num_to_eat = data->num_to_eat;
	philo->is_dead = false;
	philo->done_eat = false;
	philo->print = print;
	philo->forks = forks;
	philo->start = get_time();
	philo->timer = get_time();
	philo->end = end;
	philo->next = NULL;
	return (philo);
}

void	add_philo(t_philo **head, t_philo *philo)
{
	t_philo	*d_head;

	if (!head || !philo)
		return ;
	d_head = *head;
	if (d_head == NULL)
	{
		*head = philo;
		return ;
	}
	while (d_head->next)
		d_head = d_head->next;
	d_head->next = philo;
}

void	clean_up(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->print);
	sem_unlink("forks");
	sem_unlink("print");
	while (philo->next != NULL)
	{
		sem_close(philo->end);
		sem_unlink("sem");
		philo = philo->next;
	}
	gb_malloc(0, 1);
}

void	create_philos(t_data *data, sem_t *print, sem_t *forks)
{
	int			i;
	pid_t		*proc_arr;
	t_philo		*philo;
	t_philo		*new_philo;

	proc_arr = gb_malloc(sizeof(pid_t) * data->philos_num, 0);
	if (proc_arr == NULL)
		return ;
	data->proc_arr = proc_arr;
	philo = NULL;
	i = 0;
	sem_wait(data->end);
	while (i < data->philos_num)
	{
		new_philo = create_philo(data, i, print, forks);
		add_philo(&philo, new_philo);
		proc_arr[i] = fork();
		if (proc_arr[i] == 0)
			routine(new_philo);
		i++;
	}
	wait_philo(data, philo, proc_arr);
}
