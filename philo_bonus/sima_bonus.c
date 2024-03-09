/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sima_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:14:57 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/08 16:17:47 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*sema_create(char *name, int value)
{
	sem_t	*sema;

	sem_unlink(name);
	sema = sem_open(name, O_CREAT, 0777, value);
	return (sema);
}
