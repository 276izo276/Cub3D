/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 03:13:07 by ale-guel          #+#    #+#             */
/*   Updated: 2025/03/08 00:43:51 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h> 
#include "ft_printf.h"

t_charlst	*ft_decimal(int val, t_charlst *lst, int j, int i)
{
	char		*s;
	uintptr_t	nb;

	if (val < 0)
	{
		nb = -(uintptr_t)val;
		lst = add_char_charlst(lst, '-');
		if (!lst)
			return (NULL);
	}
	else
		nb = val;
	if (nb == 0)
		return (add_char_charlst(lst, '0'));
	s = ft_decimal_to_base(nb, "0123456789");
	if (!s)
		return (f_all_charlst(lst));
	while (s && s[i] == '0')
		i++;
	while (s && s[i + j])
		lst = add_char_charlst(lst, s[i + j++]);
	free(s);
	return (lst);
}
