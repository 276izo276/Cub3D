/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:51:36 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:51:37 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>

int	border_case_top(t_aff *aff)
{
	if (aff->dx < aff->base_x - (32 - aff->ray))
	{
		aff->dist_x = abs_value(aff->base_x - (32 - aff->ray) - aff->dx);
		aff->dist_y = abs_value(aff->base_y - (32 - aff->ray) - aff->dy);
	}
	else if (aff->dx > aff->base_x + (32 - aff->ray))
	{
		aff->dist_x = abs_value(aff->base_x + (32 - aff->ray) - aff->dx);
		aff->dist_y = abs_value(aff->base_y - (32 - aff->ray) - aff->dy);
	}
	else
		return (1);
	return (0);
}

int	border_case_bottom(t_aff *aff)
{
	if (aff->dx < aff->base_x - (32 - aff->ray))
	{
		aff->dist_x = abs_value(aff->base_x - (32 - aff->ray) - aff->dx);
		aff->dist_y = abs_value(aff->base_y + (32 - aff->ray) - aff->dy);
	}
	else if (aff->dx > aff->base_x + (32 - aff->ray))
	{
		aff->dist_x = abs_value(aff->base_x + (32 - aff->ray) - aff->dx);
		aff->dist_y = abs_value(aff->base_y + (32 - aff->ray) - aff->dy);
	}
	else
		return (1);
	return (0);
}

int	border_case_spell(double x, double y, double base_x, double base_y)
{
	t_aff	aff;

	aff.dist_x = abs_value(base_x - x);
	aff.dist_y = abs_value(base_y - y);
	aff.ray = 10;
	aff.base_x = base_x;
	aff.base_y = base_y;
	aff.dy = y;
	aff.dx = x;
	if (aff.dy < aff.base_y - (32 - aff.ray))
	{
		if (border_case_top(&aff))
			return (1);
	}
	else if (aff.dy > base_y + (32 - aff.ray))
	{
		if (border_case_bottom(&aff))
			return (1);
	}
	else
		return (1);
	if (sqrt(aff.dist_x * aff.dist_x + aff.dist_y * aff.dist_y) > aff.ray)
		return (0);
	return (1);
}
