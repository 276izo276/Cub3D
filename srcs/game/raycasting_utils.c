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

int	handle_ray_y_top(t_data *data, t_ray *ray)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[ray->case_y - 1][ray->case_x] != '1')
	{
		ray->case_y--;
		ray->coo_y = 63.999;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;

	}
	else
	{
		ray->coo_y = 0;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
		// for (int i = -2; i < 2; i++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = i + (5 * 64 / 2) + (ray->case_x - data->map.player_coo->x)
		// 			* 64 + (ray->coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (ray->case_y
		// 				- data->map.player_coo->y) * 64 + (ray->coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

int	handle_ray_y_down(t_data *data, t_ray *ray)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[ray->case_y + 1][ray->case_x] != '1')
	{
		ray->case_y++;
		ray->coo_y = 0;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
	}
	else
	{
		ray->coo_y = 63.999;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
		// for (int i = -2; i < 2; i++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = i + (5 * 64 / 2) + (ray->case_x - data->map.player_coo->x)
		// 			* 64 + (ray->coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (ray->case_y
		// 				- data->map.player_coo->y) * 64 + (ray->coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

int	handle_ray_x_left(t_data *data, t_ray *ray)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[ray->case_y][ray->case_x - 1] != '1')
	{
		ray->case_x--;
		ray->coo_x = 63.999;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
	}
	else
	{
		ray->coo_x = 0;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
		// for (int i = -2; i < 2; i++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = i + (5 * 64 / 2) + (ray->case_x - data->map.player_coo->x)
		// 			* 64 + (ray->coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (ray->case_y
		// 				- data->map.player_coo->y) * 64 + (ray->coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

int	handle_ray_x_right(t_data *data, t_ray *ray)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[ray->case_y][ray->case_x + 1] != '1')
	{
		ray->case_x++;
		ray->coo_x = 0;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
	}
	else
	{
		ray->coo_x = 63.999;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
		// for (int i = -2; i < 2; i++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = i + (5 * 64 / 2) + (ray->case_x - data->map.player_coo->x)
		// 			* 64 + (ray->coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (ray->case_y
		// 				- data->map.player_coo->y) * 64 + (ray->coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}



