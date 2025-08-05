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

int	handle_ray_y_top(t_data *data, int i)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[data->ray[i].case_y - 1][data->ray[i].case_x] != '1')
	{
		data->ray[i].case_y--;
		data->ray[i].coo_y = 63.999;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;

	}
	else
	{
		data->ray[i].coo_y = 0;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
		// for (int k = -2; k < 2; k++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = k + (5 * 64 / 2) + (data->ray[i].case_x - data->map.player_coo->x)
		// 			* 64 + (data->ray[i].coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (data->ray[i].case_y
		// 				- data->map.player_coo->y) * 64 + (data->ray[i].coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

int	handle_ray_y_down(t_data *data, int i)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[data->ray[i].case_y + 1][data->ray[i].case_x] != '1')
	{
		data->ray[i].case_y++;
		data->ray[i].coo_y = 0;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
	}
	else
	{
		data->ray[i].coo_y = 63.999;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
		// for (int k = -2; k < 2; k++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = k + (5 * 64 / 2) + (data->ray[i].case_x - data->map.player_coo->x)
		// 			* 64 + (data->ray[i].coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (data->ray[i].case_y
		// 				- data->map.player_coo->y) * 64 + (data->ray[i].coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

int	handle_ray_x_left(t_data *data, int i)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x - 1] != '1')
	{
		data->ray[i].case_x--;
		data->ray[i].coo_x = 63.999;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
	}
	else
	{
		data->ray[i].coo_x = 0;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
		// for (int k = -2; k < 2; k++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = k + (5 * 64 / 2) + (data->ray[i].case_x - data->map.player_coo->x)
		// 			* 64 + (data->ray[i].coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (data->ray[i].case_y
		// 				- data->map.player_coo->y) * 64 + (data->ray[i].coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

int	handle_ray_x_right(t_data *data, int i)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x + 1] != '1')
	{
		data->ray[i].case_x++;
		data->ray[i].coo_x = 0;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
	}
	else
	{
		data->ray[i].coo_x = 63.999;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
		// for (int k = -2; k < 2; k++)
		// {
		// 	for (int j = -2; j < 2; j++)
		// 	{
		// 		x = k + (5 * 64 / 2) + (data->ray[i].case_x - data->map.player_coo->x)
		// 			* 64 + (data->ray[i].coo_x - data->map.mini.player_coo.x);
		// 		y = j + data->mlx.height - MARGIN - (5 * 64 / 2) + (data->ray[i].case_y
		// 				- data->map.player_coo->y) * 64 + (data->ray[i].coo_y
		// 				- data->map.mini.player_coo.y);
		// 		mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, 0xFF0000);
		// 	}
		// }
		return (1);
	}
	return (0);
}

void	calc_sqrt(t_data *data, int i)
{
	data->ray[i].dist_wall = sqrt(((data->ray[i].case_y
		- data->map.player_coo->y) * 64.0 + (data->ray[i].coo_y
		- data->map.mini.player_coo.y)) * ((data->ray[i].case_y
		- data->map.player_coo->y) * 64.0 + (data->ray[i].coo_y
		- data->map.mini.player_coo.y)) + ((data->ray[i].case_x
		- data->map.player_coo->x) * 64.0 + (data->ray[i].coo_x
		- data->map.mini.player_coo.x)) * ((data->ray[i].case_x
		- data->map.player_coo->x) * 64.0 + (data->ray[i].coo_x
		- data->map.mini.player_coo.x)));
}
