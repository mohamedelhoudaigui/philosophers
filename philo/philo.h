/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:17:29 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/09 22:05:02 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
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

typedef struct s_philo
{
	t_data			*data;
	struct s_philo	*next;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*edit;
	int				times_eat;
	int				philo_num;
	long long		start_time;
	long long		timer;
	bool			done_eat;
}				t_philo;

// garb_col.c :
void		clear_list(t_garb *list);
void		add_node(t_garb **list, t_garb *node);
void		*gb_malloc(size_t size, int type);

// parse.c :
int			ft_atoi(const char *str);
int			check_args(int ac, char **av);
t_data		*extract_args(int ac, char **av);
bool		check_overflow(char **av);
int			ft_strncmp(char *s1, char *s2, int n);
int			ft_strlen(char *str);

// c_linked_list :
t_philo		*create_philo(t_data *data, pthread_mutex_t *print);
void		add_philo(t_philo **head, t_philo *philo);
t_philo		*create_philos(t_data *data, pthread_mutex_t *print);

// routine.c : 
void		start_sim(t_philo *philo);
void		eat(t_philo *philo);
void		take_fork(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		thinking(t_philo *philo);

// main.c :
void		destroy_all(t_philo *head);
int			main(int ac, char **av);
void		*routine(void *arg);
void		p_error(void);
void		*rout_eat(void *arg);

// time.c :
long long	get_time(void);
bool		is_dead(t_philo *philo);
void		sleep_opt(long long time);
void		grim_reaper(t_philo *philo);
bool		check_eat(t_philo *philo);

#endif
