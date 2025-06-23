/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_charlst_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:08:48 by ale-guel          #+#    #+#             */
/*   Updated: 2025/03/09 02:39:35 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

t_charlst	*get_first_elem_charlst(t_charlst *lst)
{
	while (lst && lst->prev)
	{
		lst = lst->prev;
	}
	return (lst);
}

t_charlst	*get_last_elem_charlst(t_charlst *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

t_charlst	*move_to_end_charlst(t_charlst *elem, t_charlst *lst)
{
	if (!elem)
	{
		f_all_charlst(lst);
		return (NULL);
	}
	lst = get_last_elem_charlst(lst);
	if (lst)
		lst->next = elem;
	elem->prev = lst;
	elem->next = NULL;
	return (elem);
}

t_charlst	*f_all_charlst(t_charlst *lst)
{
	t_charlst	*next;

	lst = get_first_elem_charlst(lst);
	while (lst)
	{
		next = lst->next;
		free(lst->buffer);
		free(lst);
		lst = next;
	}
	return (NULL);
}

t_charlst	*init_charlst(void)
{
	t_charlst	*lst;
	int			i;

	lst = malloc(sizeof(t_charlst));
	if (!lst)
		return (NULL);
	lst->buffer = malloc(sizeof(char) * (4096));
	if (!lst->buffer)
	{
		free(lst);
		return (NULL);
	}
	i = 0;
	while (i < 4096)
		lst->buffer[i++] = 0;
	lst->next = NULL;
	lst->prev = NULL;
	lst->size = 0;
	return (lst);
}
