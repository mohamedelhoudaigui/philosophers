/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:17:29 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/09 22:04:14 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

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
	sem_t		*end;
	pid_t		*proc_arr;
}				t_data;

typedef struct s_philo
{
	pid_t			philo_num;
	long long		start;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*done_eat_sem;
	t_data			*data;
	bool			is_dead;
	bool			done_eat;
	int				num_to_eat;
	long long		timer;
	struct s_philo	*next;
}				t_philo;

// garb_col.c :
void		clear_list(t_garb *list);
void		add_node(t_garb **list, t_garb *node);
void		*gb_malloc(size_t size, int type);

// parse.c :
int			ft_atoi(const char *str);
int			check_args(int ac, char **av);
t_data		*extract_args(int ac, char **av);
int			ft_strlen(char *str);
int			ft_strncmp(char *s1, char *s2, int n);
bool		check_overflow(char **av);

// main.c :
int			main(int ac, char **av);
void		p_error(void);

// time.c
long long	get_time(void);
void		ft_usleep(long long time);
bool		is_dead(t_philo *philo);
void		*grim_r(void *arg);
void		sleep_philo(t_philo *philo);

// routine.c :
void		i_am_dead(t_philo *philo);
void		take_fork(t_philo *philo);
void		eat(t_philo *philo);
void		routine(t_philo *philo);

// create_philo.c :
void		create_philos(t_data *data, sem_t *print, sem_t *forks);
void		add_philo(t_philo **head, t_philo *philo);
void		clean_up(sem_t *print, sem_t *forks);
t_philo		*create_philo(t_data *data, int i, sem_t *print, sem_t *forks);

// sima_bonus.c :
sem_t		*sema_create(char *name, int value);

// wait_bonus.c :
void		kill_all(pid_t *proc_arr, t_data *data);
void		*grim(void *arg);
void		wait_philo(t_data *data, pid_t *proc_arr);

#endif
