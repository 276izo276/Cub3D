#include "cub3d_bonus.h"
#include <math.h>

int	handle_ray_y_top_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y - 1][ray->case_x] != '1')
	{
		ray->case_y--;
		ray->coo_y = 64;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
	}
	else
	{
		ray->coo_y = 0;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
		return (1);
	}
	return (0);
}

int	handle_ray_y_down_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y + 1][ray->case_x] != '1')
	{
		ray->case_y++;
		ray->coo_y = 0;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
	}
	else
	{
		ray->coo_y = 64;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
		return (1);
	}
	return (0);
}

int	handle_ray_x_left_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y][ray->case_x - 1] != '1')
	{
		ray->case_x--;
		ray->coo_x = 64;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
	}
	else
	{
		ray->coo_x = 0;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
		return (1);
	}
	return (0);
}

int	handle_ray_x_right_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y][ray->case_x + 1] != '1')
	{
		ray->case_x++;
		ray->coo_x = 0;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
	}
	else
	{
		ray->coo_x = 64;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
		return (1);
	}
	return (0);
}
