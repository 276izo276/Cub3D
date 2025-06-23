/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_charlst_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:06:54 by ale-guel          #+#    #+#             */
/*   Updated: 2025/03/09 03:55:22 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

void	fill_str(t_charlst *lst, char *str)
{
	size_t	i;
	int		j;

	lst = get_first_elem_charlst(lst);
	j = 0;
	while (lst)
	{
		i = 0;
		while (i < (size_t)lst->size)
		{
			str[4096 * j + i] = lst->buffer[i];
			i++;
		}
		j++;
		lst = lst->next;
	}
}

int	empty_buffer(t_charlst *lst, size_t size, int fd)
{
	char	*str;

	lst = get_first_elem_charlst(lst);
	while (lst && lst->next)
	{
		size += lst->size;
		lst = lst->next;
	}
	if (lst)
		size += lst->size;
	lst = get_first_elem_charlst(lst);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
	{
		f_all_charlst(lst);
		return (-1);
	}
	str[size] = 0;
	fill_str(lst, str);
	write(fd, str, size);
	f_all_charlst(lst);
	free(str);
	return (size);
}

t_charlst	*add_char_charlst(t_charlst *lst, char c)
{
	while (lst && lst->size == 4096 && lst->next)
		lst = lst->next;
	if (lst && lst->size == 4096)
		lst = move_to_end_charlst(init_charlst(), lst);
	if (!lst)
		return (NULL);
	lst->buffer[lst->size] = c;
	lst->size++;
	return (lst);
}

t_charlst	*add_string_charlst(t_charlst *lst, char *str)
{
	int	i;

	i = 0;
	while (lst && str && str[i])
	{
		lst = add_char_charlst(lst, str[i]);
		i++;
	}
	return (lst);
}
