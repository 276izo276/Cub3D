/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:41:03 by ale-guel          #+#    #+#             */
/*   Updated: 2025/04/16 10:28:30 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"

t_charlst	*ft_putstr(char *str, t_charlst *lst)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		return (add_string_charlst(lst, "(null)"));
	}
	while (str && str[i])
	{
		lst = printf_putchar_fd(str[i++], lst);
	}
	return (lst);
}
