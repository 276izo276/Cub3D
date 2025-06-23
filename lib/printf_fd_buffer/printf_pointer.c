/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:50:54 by ale-guel          #+#    #+#             */
/*   Updated: 2025/03/08 02:10:35 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>
#include <stdlib.h> 
#include <unistd.h>

t_charlst	*ft_pointer(void *point, t_charlst *lst, int i)
{
	char		*s;
	uintptr_t	addr;
	int			nb;

	addr = (uintptr_t)point;
	s = ft_decimal_to_base(addr, "0123456789abcdef");
	if (!s)
		return (f_all_charlst(lst));
	nb = 0;
	while (s && s[i] == '0')
		i++;
	if (s && !s[i + nb])
	{
		free(s);
		return (add_string_charlst(lst, "(nil)"));
	}
	if (s)
		lst = add_string_charlst(lst, "0x");
	while (s && s[i + nb])
		lst = add_char_charlst(lst, s[i + nb++]);
	free(s);
	return (lst);
}
