/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:58:37 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:58:38 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	fill_itoa(char **str, int index, long long int nb)
{
	if (nb >= 10)
	{
		index = fill_itoa(str, index, nb / 10);
	}
	(*str)[index] = nb % 10 + 48;
	return (index + 1);
}

char	*ft_itoa(int nb)
{
	char			*str;
	int				i;
	unsigned int	nnb;

	str = malloc(sizeof(char) * 13);
	if (!str)
		return (NULL);
	i = 0;
	while (i < 13)
	{
		str[i++] = 0;
	}
	if (nb < 0)
	{
		nnb = -nb;
		str[0] = '-';
		fill_itoa(&str, 1, nnb);
	}
	else
		fill_itoa(&str, 0, nb);
	return (str);
}
