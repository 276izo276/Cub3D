/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:27:05 by ale-guel          #+#    #+#             */
/*   Updated: 2025/03/08 02:10:02 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h> 
#include "ft_printf.h"

t_charlst	*ft_minhex(unsigned int val, t_charlst *lst)
{
	char		*s;
	int			j;
	int			i;

	j = 0;
	if (val == 0)
	{
		return (add_char_charlst(lst, '0'));
	}
	s = ft_decimal_to_base(val, "0123456789abcdef");
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

t_charlst	*ft_majhex(unsigned int val, t_charlst *lst)
{
	char		*s;
	int			j;
	int			i;

	j = 0;
	if (val == 0)
	{
		return (add_char_charlst(lst, '0'));
	}
	s = ft_decimal_to_base(val, "0123456789ABCDEF");
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
