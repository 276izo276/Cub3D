/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_segment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:51:51 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:51:52 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"

void	calc_end_point(t_hitray *ray)
{
	if (ray->delta_x > 0)
		ray->rx = (ray->ax + ray->radius * 50 - ray->cx) / ray->delta_x;
	else
		ray->rx = -ray->cx / ray->delta_x;
	if (ray->delta_y > 0)
		ray->ry = (ray->ay + ray->radius * 50 - ray->cy) / ray->delta_y;
	else
		ray->ry = -ray->cy / ray->delta_y;
	if (ray->rx < ray->ry)
	{
		if (ray->delta_x < 0)
			ray->dx = 0;
		else
			ray->dx = ray->ax + ray->radius * 50;
		ray->dy = ray->cy + ray->rx * ray->delta_y;
	}
	else
	{
		if (ray->delta_y < 0)
			ray->dy = 0;
		else
			ray->dy = ray->ay + ray->radius * 50;
		ray->dx = ray->cx + ray->ry * ray->delta_x;
	}
}

void	calc_scal(t_hitray *ray)
{
	double	value;

	ray->hit = false;
	value = (ray->bx - ray->ax) * (ray->cy - ray->ay) - (ray->by - ray->ay)
		* (ray->cx - ray->ax);
	if (value < 0)
		value = -value;
	if (value < 0.000001)
		return ;
	if (ray->ax == ray->cx && ray->ay == ray->cy)
		return ;
	ray->delta = (ray->bx - ray->ax) * (ray->bx - ray->ax) + (ray->by - ray->ay)
		* (ray->by - ray->ay);
	ray->delta_u = (ray->dx - ray->ax) * (ray->bx - ray->ax) + (ray->dy
			- ray->ay) * (ray->by - ray->ay);
	if (ray->delta_u > ray->delta || ray->delta_u < 0)
		return ;
	ray->delta = (ray->cx - ray->ax) * (ray->cx - ray->ax) + (ray->cy - ray->ay)
		* (ray->cy - ray->ay);
	ray->delta_u = (ray->dx - ray->ax) * (ray->cx - ray->ax) + (ray->dy
			- ray->ay) * (ray->cy - ray->ay);
	if (ray->delta_u > ray->delta || ray->delta_u < 0)
		return ;
	ray->hit = true;
}

void	calc_delta(t_hitray *ray)
{
	ray->hit = false;
	ray->delta = (ray->dx - ray->cx) * (ray->by - ray->ay) - (ray->dy - ray->cy)
		* (ray->bx - ray->ax);
	ray->delta_t = (ray->dx - ray->cx) * (ray->cy - ray->ay) - (ray->dy
			- ray->cy) * (ray->cx - ray->ax);
	ray->delta_u = (ray->bx - ray->ax) * (ray->cy - ray->ay) - (ray->by
			- ray->ay) * (ray->cx - ray->ax);
	if (ray->delta != 0)
	{
		ray->t = ray->delta_t / ray->delta;
		ray->u = ray->delta_u / ray->delta;
		if (ray->t >= 0 && ray->t <= 1 && ray->u >= 0 && ray->u <= 1)
		{
			ray->hit = true;
			ray->hx = ray->cx + ray->u * (ray->dx - ray->cx);
			ray->hy = ray->cy + ray->u * (ray->dy - ray->cy);
		}
	}
}
