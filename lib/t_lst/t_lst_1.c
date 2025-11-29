/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lst_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:28:23 by ale-guel          #+#    #+#             */
/*   Updated: 2025/11/29 11:13:01 by samaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lst.h"
#include <stdlib.h>

t_lst	*add_end_lst(void *elem, t_lst *lst, void (*f)(void *))
{
	t_lst	*new;

	if (!f)
		return (NULL);
	if (!elem)
	{
		f_all_lst(lst);
		return (NULL);
	}
	new = malloc(sizeof(t_lst));
	if (!new)
	{
		f(elem);
		f_all_lst(lst);
		return (NULL);
	}
	lst = get_last_elem_lst(lst);
	if (lst)
		lst->next = new;
	new->f = f;
	new->prev = lst;
	new->next = NULL;
	new->dt = elem;
	return (new);
}

t_lst	*add_start_lst(void *elem, t_lst *lst, void (*f)(void *))
{
	t_lst	*new;

	if (!f)
		return (NULL);
	if (!elem)
		return (f_all_lst(lst), NULL);
	new = malloc(sizeof(t_lst));
	if (!new)
		return (f(elem), f_all_lst(lst), NULL);
	lst = get_first_elem_lst(lst);
	if (lst)
		lst->prev = new;
	new->f = f;
	new->prev = NULL;
	new->next = lst;
	new->dt = elem;
	return (new);
}

t_lst	*get_first_elem_lst(t_lst *lst)
{
	while (lst && lst->prev)
	{
		lst = lst->prev;
	}
	return (lst);
}

t_lst	*get_last_elem_lst(t_lst *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_lst	*remove_elem_lst(t_lst *elem)
{
	t_lst	*return_value;

	return_value = NULL;
	if (elem && elem->prev)
	{
		elem->prev->next = elem->next;
		return_value = elem->prev;
	}
	if (elem && elem->next)
	{
		elem->next->prev = elem->prev;
		return_value = elem->next;
	}
	if (elem)
	{
		elem->next = NULL;
		elem->prev = NULL;
	}
	return (return_value);
}
