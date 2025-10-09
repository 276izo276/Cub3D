#include "cub3d_bonus.h"
#include <math.h>
#include <stdlib.h>




#include <stdio.h>


int	handle_ray_y_top(t_data *data, int i)
{
	// int	x;
	// int	y;
	// calc_door(data, i);
	if (data->map.tabmap[data->ray[i].case_y - 1][data->ray[i].case_x] != '1')
	{
		data->ray[i].case_y--;
		data->ray[i].coo_y = 64;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;

	}
	else
	{
		data->ray[i].coo_y = 0;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
		// printf("map >>>> %c\n", data->map.tabmap[data->ray[i].case_y - 1][data->ray[i].case_x]);
		if (data->map.tabmap[data->ray[i].case_y - 1][data->ray[i].case_x] == '1' && data->map.wall_map[data->ray[i].case_y - 1][data->ray[i].case_x]->is_active == false && data->player_moved == true && data->display.is_msg_active == true)
		{
			// printf("IN \n");
			if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x] == 'D')
				return (1);
		int random = rand() % (150 * data->mlx.width);
			// int random = rand() % (150 * data->mlx.width);
			if (random == data->random_value && data->current_msg < data->nb_msg)
			{
				// printf("rand >> %d\n", random);
				pthread_mutex_lock(&data->m_data_ray);
				data->map.wall_map[data->ray[i].case_y - 1][data->ray[i].case_x]->is_active = true;
				data->map.wall_map[data->ray[i].case_y - 1][data->ray[i].case_x]->coo.x = data->ray[i].case_x;
				data->map.wall_map[data->ray[i].case_y - 1][data->ray[i].case_x]->coo.y = data->ray[i].case_y - 1;
				data->map.wall_map[data->ray[i].case_y - 1][data->ray[i].case_x]->msg_nb = data->current_msg;
				data->map.wall_map[data->ray[i].case_y - 1][data->ray[i].case_x]->dir = data->ray[i].dir;
				++data->current_msg;
				pthread_mutex_unlock(&data->m_data_ray);
			}
		}
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

	// calc_door(data, i);
	if (data->map.tabmap[data->ray[i].case_y + 1][data->ray[i].case_x] != '1'
	)
	{
		data->ray[i].case_y++;
		data->ray[i].coo_y = 0;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
	}
	else
	{
		data->ray[i].coo_y = 64;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
		if (data->map.tabmap[data->ray[i].case_y + 1][data->ray[i].case_x] == '1' && data->map.wall_map[data->ray[i].case_y + 1][data->ray[i].case_x]->is_active == false && data->player_moved == true && data->display.is_msg_active == true)
		{
			if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x] == 'D')
				return (1);
		int random = rand() % (150 * data->mlx.width);
			// int random = rand() % (150 * data->mlx.width);

			if (random == data->random_value && data->current_msg < data->nb_msg)
			{
				pthread_mutex_lock(&data->m_data_ray);
				data->map.wall_map[data->ray[i].case_y + 1][data->ray[i].case_x]->is_active = true;
				data->map.wall_map[data->ray[i].case_y + 1][data->ray[i].case_x]->coo.x = data->ray[i].case_x;
				data->map.wall_map[data->ray[i].case_y + 1][data->ray[i].case_x]->coo.y = data->ray[i].case_y + 1;
				data->map.wall_map[data->ray[i].case_y + 1][data->ray[i].case_x]->msg_nb = data->current_msg;
				data->map.wall_map[data->ray[i].case_y + 1][data->ray[i].case_x]->dir = data->ray[i].dir;
				++data->current_msg;
				pthread_mutex_unlock(&data->m_data_ray);
			}
		}
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

	// calc_door(data, i);
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x - 1] != '1'
	)
	{
		data->ray[i].case_x--;
		data->ray[i].coo_x = 64;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
	}
	else
	{
		data->ray[i].coo_x = 0;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
		if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x - 1] == '1' && data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x - 1]->is_active == false && data->player_moved == true && data->display.is_msg_active == true)
		{
			if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x] == 'D')
				return (1);
		int random = rand() % (150 * data->mlx.width);
			// int random = rand() % (150 * data->mlx.width);

			if (random == data->random_value && data->current_msg < data->nb_msg)
			{
				pthread_mutex_lock(&data->m_data_ray);
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x - 1]->is_active = true;
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x - 1]->coo.x = data->ray[i].case_x - 1;
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x - 1]->coo.y = data->ray[i].case_y;
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x - 1]->msg_nb = data->current_msg;
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x - 1]->dir = data->ray[i].dir;
				++data->current_msg;
				pthread_mutex_unlock(&data->m_data_ray);
			}
		}
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

	// calc_door(data, i);
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x + 1] != '1')
	{
		data->ray[i].case_x++;
		data->ray[i].coo_x = 0;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
	}
	else
	{
		data->ray[i].coo_x = 64;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
		if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x + 1] == '1' && data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x + 1]->is_active == false && data->player_moved == true && data->display.is_msg_active == true)
		{
				if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x] == 'D')
				return (1);
		int random = rand() % (150 * data->mlx.width);
			// int random = rand() % (150 * data->mlx.width);

			if (random == data->random_value && data->current_msg < data->nb_msg)
			{
				pthread_mutex_lock(&data->m_data_ray);
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x + 1]->is_active = true;
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x + 1]->coo.x = data->ray[i].case_x + 1;
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x + 1]->coo.y = data->ray[i].case_y;
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x + 1]->msg_nb = data->current_msg;
				data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x + 1]->dir = data->ray[i].dir;
				++data->current_msg;
				pthread_mutex_unlock(&data->m_data_ray);
			}
		}
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
