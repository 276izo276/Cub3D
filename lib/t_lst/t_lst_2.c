/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lst_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:15:53 by ale-guel          #+#    #+#             */
/*   Updated: 2025/02/19 10:15:18 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lst.h"
#include <stdlib.h>

t_lst	*remove_f_elem_lst(t_lst *elem)
{
	t_lst	*return_value;

	return_value = NULL;
	if (elem->prev)
	{
		elem->prev->next = elem->next;
		return_value = elem->prev;
	}
	if (elem->next)
	{
		elem->next->prev = elem->prev;
		return_value = elem->next;
	}
	f_elem_lst(elem);
	return (return_value);
}

void	f_elem_lst(t_lst *elem)
{
	elem->f(elem->dt);
	free(elem);
}

void	f_all_lst(t_lst *lst)
{
	t_lst	*next;

	lst = get_first_elem_lst(lst);
	while (lst)
	{
		next = lst->next;
		f_elem_lst(lst);
		lst = next;
	}
}

t_lst	*move_to_end_lst(t_lst *elem, t_lst *lst)
{
	lst = get_last_elem_lst(lst);
	if (lst)
		lst->next = elem;
	elem->prev = lst;
	elem->next = NULL;
	return (elem);
}

t_lst	*move_to_start_lst(t_lst *elem, t_lst *lst)
{
	lst = get_first_elem_lst(lst);
	if (lst)
		lst->prev = elem;
	elem->next = lst;
	elem->prev = NULL;
	return (elem);
}
