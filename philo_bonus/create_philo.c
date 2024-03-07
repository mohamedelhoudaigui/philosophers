/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:47:55 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/07 20:40:59 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philo(t_data *data)
{
	int			i;
	pid_t		*proc_arr;
	long long	start;
	sem_t		*forks;

	proc_arr = gb_malloc(sizeof(pid_t) * data->philos_num, 0);
	if (proc_arr == NULL)
		return ;
	start = get_time();
	// forks = gb_malloc(sizeof(sem_t), 0);
	forks = sem_open("./forks", O_CREAT, 0777, data->philos_num / 2);
	i = 0;
	while (i < data->philos_num)
	{
		proc_arr[i] = fork();
		i++;
	}
	i = 0;
	while (i < data->philos_num)
	{
		if (proc_arr[i] == 0)
			routine(&forks, i, data, start);
		i++;
	}
	i = 0;
	while (i < data->philos_num)
	{
		waitpid(proc_arr[i], NULL, 0);
		i++;
	}
	sem_close(forks);
	sem_unlink("./forks");
}
