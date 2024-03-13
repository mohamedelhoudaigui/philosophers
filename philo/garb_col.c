/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_col.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:44:19 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/06 03:41:10 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_list(t_garb *list)
{
	t_garb	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		free(tmp->addr);
		list = list->next;
		free(tmp);
	}
}

void	add_node(t_garb **list, t_garb *node)
{
	t_garb	*head;

	if (!list || !node)
		return ;
	head = *list;
	node->next = NULL;
	if (!head)
	{
		*list = node;
		return ;
	}
	while (head->next != NULL)
		head = head->next;
	head->next = node;
}

void	*gb_malloc(size_t size, int type)
{
	static t_garb	*list;
	t_garb			*node;
	void			*addr;

	if (type == 1)
		clear_list(list);
	else if (type == 0)
	{
		addr = malloc(size);
		node = malloc(sizeof(t_garb));
		if (!addr || !node)
		{
			clear_list(list);
			return (NULL);
		}
		node->addr = addr;
		add_node(&list, node);
		return (addr);
	}
	return (NULL);
}
