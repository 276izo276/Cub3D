/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 06:37:43 by ale-guel          #+#    #+#             */
/*   Updated: 2025/04/16 10:28:19 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"

t_charlst	*call_func(char c, va_list args, t_charlst *lst)
{
	if (c == 'c')
		return (printf_putchar_fd(va_arg(args, int), lst));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *), lst));
	if (c == 'p')
		return (ft_pointer(va_arg(args, void *), lst, 0));
	if (c == 'd' || c == 'i')
		return (ft_decimal(va_arg(args, int), lst, 0, 0));
	if (c == 'u')
		return (ft_unsigned(va_arg(args, unsigned int), lst));
	if (c == 'x')
		return (ft_minhex(va_arg(args, unsigned int), lst));
	if (c == 'X')
		return (ft_majhex(va_arg(args, unsigned int), lst));
	if (c == '%')
		return (printf_putchar_fd('%', lst));
	return (0);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	int			i;
	va_list		args;
	t_charlst	*lst;

	i = 0;
	if (!str)
		return (-1);
	lst = init_charlst();
	if (!lst)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			lst = call_func(str[i + 1], args, lst);
			i += 2;
		}
		else
			lst = printf_putchar_fd(str[i++], lst);
		if (!lst)
			return (-1);
	}
	va_end(args);
	return (empty_buffer(lst, 0, fd));
}
