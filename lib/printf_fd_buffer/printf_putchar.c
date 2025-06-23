/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:36:11 by ale-guel          #+#    #+#             */
/*   Updated: 2025/04/16 10:28:25 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

t_charlst	*printf_putchar_fd(char c, t_charlst *lst)
{
	lst = add_char_charlst(lst, c);
	return (lst);
}
