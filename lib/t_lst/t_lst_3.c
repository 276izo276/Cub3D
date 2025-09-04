/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lst_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:14:39 by ale-guel          #+#    #+#             */
/*   Updated: 2025/09/04 03:42:15 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lst.h"
#include <stdlib.h>

void	set_value_t_lst(t_lst *new, void *elem, void (*f)(void *))
{
	new->prev = NULL;
	new->next = NULL;
	new->dt = elem;
	new->f = f;
}

t_lst	*add_before_lst(void *elem, t_lst *lst, void (*f)(void *))
{
	t_lst	*new;

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
	set_value_t_lst(new, elem, f);
	if (!lst)
		return (new);
	if (lst->prev)
		lst->prev->next = new;
	new->prev = lst->prev;
	new->next = lst;
	lst->prev = new;
	return (new);
}

t_lst	*add_after_lst(void *elem, t_lst *lst, void (*f)(void *))
{
	t_lst	*new;

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
	set_value_t_lst(new, elem, f);
	if (!lst)
		return (new);
	if (lst->next)
		lst->next->prev = new;
	new->next = lst->next;
	new->prev = lst;
	lst->next = new;
	return (new);
}

int	ft_strlen_lst(t_lst *lst)
{
	int	i;

	lst = get_first_elem_lst(lst);
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	move_before_lst(t_lst *elem, t_lst *lst)
{
	elem->next = lst;
	elem->prev = lst->prev;
	lst->prev = elem;
	elem->prev->next = elem;
}