#include "cub3d.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "struct.h"
#include "texture.h"
#include "time.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int	handle_ray_y_top(t_data *data, t_ray *ray, t_ray ray_value)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[ray_value.case_y - 1][ray_value.case_x] != '1')
	{
		ray->case_y--;
		ray->coo_y = 63;
		ray->coo_x = ray_value.coo_x + ray_value.ry * ray_value.delta_x;
	}
	else
	{
		ray->coo_y = 0;
		ray->coo_x = ray_value.coo_x + ray_value.ry * ray_value.delta_x;
		// for (int i = -2; i < 2; i++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = i + (5 * 64 / 2) + (ray_value.case_x - data->map.player_coo->x)
		// 			* 64 + (ray_value.coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (ray_value.case_y
		// 				- data->map.player_coo->y) * 64 + (ray_value.coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

int	handle_ray_y_down(t_data *data, t_ray *ray, t_ray ray_value)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[ray_value.case_y + 1][ray_value.case_x] != '1')
	{
		ray->case_y++;
		ray->coo_y = 0;
		ray->coo_x = ray_value.coo_x + ray_value.ry * ray_value.delta_x;
	}
	else
	{
		ray->coo_y = 63;
		ray->coo_x = ray_value.coo_x + ray_value.ry * ray_value.delta_x;
		// for (int i = -2; i < 2; i++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = i + (5 * 64 / 2) + (ray_value.case_x - data->map.player_coo->x)
		// 			* 64 + (ray_value.coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (ray_value.case_y
		// 				- data->map.player_coo->y) * 64 + (ray_value.coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

int	handle_ray_x_left(t_data *data, t_ray *ray, t_ray ray_value)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[ray_value.case_y][ray_value.case_x - 1] != '1')
	{
		ray->case_x--;
		ray->coo_x = 63;
		ray->coo_y = ray_value.coo_y + ray_value.rx * ray_value.delta_y;
	}
	else
	{
		ray->coo_x = 0;
		ray->coo_y = ray_value.coo_y + ray_value.rx * ray_value.delta_y;
		// for (int i = -2; i < 2; i++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = i + (5 * 64 / 2) + (ray_value.case_x - data->map.player_coo->x)
		// 			* 64 + (ray_value.coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (ray_value.case_y
		// 				- data->map.player_coo->y) * 64 + (ray_value.coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

int	handle_ray_x_right(t_data *data, t_ray *ray, t_ray ray_value)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[ray_value.case_y][ray_value.case_x + 1] != '1')
	{
		ray->case_x++;
		ray->coo_x = 0;
		ray->coo_y = ray_value.coo_y + ray_value.rx * ray_value.delta_y;
	}
	else
	{
		ray->coo_x = 63;
		ray->coo_y = ray_value.coo_y + ray_value.rx * ray_value.delta_y;
		// for (int i = -2; i < 2; i++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = i + (5 * 64 / 2) + (ray_value.case_x - data->map.player_coo->x)
		// 			* 64 + (ray_value.coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (ray_value.case_y
		// 				- data->map.player_coo->y) * 64 + (ray_value.coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}
