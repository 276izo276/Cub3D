/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:00:55 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/03 22:29:33 by samaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*gnl_copy(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = gnl_strlen(buffer);
	j = 0;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = buffer[j];
		j++;
	}
	str[j] = 0;
	return (str);
}

t_gnl	*add_elem_lst(t_gnl *lst, char *elem, int end)
{
	t_gnl	*new;

	lst = get_elem_lst(lst, end);
	if (!elem)
		return (empty_lst(lst, 0, 0, 0), NULL);
	new = malloc(sizeof(t_gnl));
	if (!new)
		return (free(elem), empty_lst(lst, 0, 0, 0), NULL);
	new->content = elem;
	if (!end)
	{
		if (lst)
			lst->prev = new;
		new->prev = NULL;
		new->next = lst;
	}
	else
	{
		if (lst)
			lst->next = new;
		new->prev = lst;
		new->next = NULL;
	}
	return (new);
}

t_gnl	*get_elem_lst(t_gnl *lst, int end)
{
	if (!end)
	{
		while (lst && lst->prev)
		{
			lst = lst->prev;
		}
		return (lst);
	}
	else
	{
		while (lst && lst->next)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (lst);
}

char	*empty_lst(t_gnl *lst, int print, size_t nb_read, size_t size)
{
	char	*str;
	t_gnl	*next;

	str = NULL;
	lst = get_elem_lst(lst, 0);
	if (lst && print)
		str = malloc(sizeof(char) * (nb_read + 1));
	nb_read = 0;
	while (lst)
	{
		next = lst->next;
		size = -1;
		if (str && print)
			while (lst && lst->content && lst->content[++size])
				str[size + nb_read] = lst->content[size];
		nb_read += size;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = next;
	}
	if (str)
		str[nb_read] = 0;
	return (str);
}
