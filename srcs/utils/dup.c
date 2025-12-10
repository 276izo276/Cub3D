/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:46:06 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:46:07 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

char	*ft_strndup(char *s, int size)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = 0;
	i = 0;
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

char	*rmbn_dup(char *line)
{
	char	*str;
	int		i;
	int		size;

	size = 0;
	while (line[size] && line[size] != '\n')
		size++;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
	{
		free(line);
		return (NULL);
	}
	str[size] = 0;
	i = 0;
	while (i < size)
	{
		str[i] = line[i];
		i++;
	}
	free(line);
	return (str);
}
