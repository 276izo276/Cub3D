/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 03:47:17 by ale-guel          #+#    #+#             */
/*   Updated: 2025/03/08 00:47:25 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h> 
#include "ft_printf.h"

t_charlst	*ft_unsigned(unsigned int val, t_charlst *lst)
{
	char		*s;
	int			j;
	int			i;
	uintptr_t	nb;

	j = 0;
	nb = val;
	if (nb == 0)
		return (add_char_charlst(lst, '0'));
	s = ft_decimal_to_base(nb, "0123456789");
	if (!s)
		return (f_all_charlst(lst));
	i = 0;
	while (s && s[i] == '0')
		i++;
	while (s && s[i + j])
		lst = add_char_charlst(lst, s[i + j++]);
	free(s);
	return (lst);
}
