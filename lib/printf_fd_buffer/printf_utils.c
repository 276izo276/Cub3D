/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:41:35 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/03 22:21:14 by samaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

size_t	printf_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_decimal_to_base(size_t decimal, char *base)
{
	char		*ptr;
	char		*result;
	size_t		i;
	int			nb;

	nb = printf_strlen(base);
	i = 0;
	result = malloc(sizeof(char) * 65);
	if (!result)
		return (NULL);
	ptr = result + 64;
	while (i < 64)
		result[i++] = '0';
	*ptr = '\0';
	while (decimal != 0)
	{
		*--ptr = base[decimal % nb];
		decimal /= nb;
	}
	return (result);
}
