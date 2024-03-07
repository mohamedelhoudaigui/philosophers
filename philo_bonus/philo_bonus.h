/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:17:29 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/06 04:32:45 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_garb
{
	void			*addr;
	struct s_garb	*next;
}				t_garb;

typedef struct s_data
{
	int			philos_num;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	num_to_eat;
}				t_data;

// garb_col.c :
void		clear_list(t_garb *list);
void		add_node(t_garb **list, t_garb *node);
void		*gb_malloc(size_t size, int type);

// parse.c :
int			ft_atoi(const char *str);
int			check_args(int ac, char **av);
t_data		*extract_args(int ac, char **av);
void		p_error(void);

// main.c :
int			main(int ac, char **av);

// time.c
long long	get_time();
void	ft_usleep(long long time);

// routine.c :
void	*routine(sem_t **forks, unsigned int i, t_data *data, long long start);

// create_philo.c :
void	create_philo(t_data *data);

#endif
