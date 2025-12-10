/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_visu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:48:20 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:48:21 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>
#include "enemy_bonus.h"

static int	handle_ray_x_gen(t_data *data, t_ray *ray)
{
	if (ray->delta_x < 0)
	{
		if (handle_ray_x_left_gen(data, ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_x_right_gen(data, ray) == 1)
			return (1);
	}
	return (0);
}

static int	handle_ray_y_gen(t_data *data, t_ray *ray)
{
	if (ray->delta_y < 0)
	{
		if (handle_ray_y_top_gen(data, ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_y_down_gen(data, ray) == 1)
			return (1);
	}
	return (0);
}

void	launch_ray_enemy(t_ray *ray, t_data *data)
{
	while (1)
	{
		if (ray->delta_x > 0)
			ray->rx = (64 - ray->coo_x) / ray->delta_x;
		else
			ray->rx = -ray->coo_x / ray->delta_x;
		if (ray->delta_y > 0)
			ray->ry = (64 - ray->coo_y) / ray->delta_y;
		else
			ray->ry = -ray->coo_y / ray->delta_y;
		if (ray->rx < ray->ry)
		{
			if (handle_ray_x_gen(data, ray) == 1)
				break ;
		}
		else
		{
			if (handle_ray_y_gen(data, ray) == 1)
				break ;
		}
	}
}

void	fill_ray_enemy(t_enemy *enemy, t_ray *ray, double deg)
{
	ray->deg = deg;
	ray->start_case_x = enemy->center.case_x;
	ray->start_case_y = enemy->center.case_y;
	ray->start_coo_x = enemy->center.coo_x;
	ray->start_coo_y = enemy->center.coo_y;
	ray->coo_y = enemy->center.coo_y;
	ray->coo_x = enemy->center.coo_x;
	ray->case_y = enemy->center.case_y;
	ray->case_x = enemy->center.case_x;
	ray->deg = fmod(ray->deg, 360);
	ray->rad = ray->deg * (M_PI / 180);
	ray->delta_y = cos(ray->rad);
	ray->delta_x = sin(ray->rad);
}
