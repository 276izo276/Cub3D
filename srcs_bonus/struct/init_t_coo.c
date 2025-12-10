/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_coo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:58:16 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:58:17 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "utils_bonus.h"
#include <stdlib.h>

t_coo	*init_t_coo(int y, int x)
{
	t_coo	*coo;

	coo = malloc(sizeof(t_coo));
	if (!coo)
		return (NULL);
	coo->x = x;
	coo->y = y;
	return (coo);
}
