#include "cub3d_bonus.h"
#include <math.h>

#include <stdio.h>



int	handle_ray_y_top(t_data *data, int i)
{
	// int	x;
	// int	y;

	if (data->map.tabmap[data->ray[i].case_y - 1][data->ray[i].case_x] == 'D')	
	{
		int	j = 0;
		while (j < data->nb_door)
		{
			// printf("in\n");
			if (data->ray[i].doors[j]->use == false)
			{
				// printf("HIT WALL WITH I >>>%d   j>>%d",i,j);
				break;
			}
			j++;
		}

		if (data->ray[i].delta_y < 0)
			data->ray[i].doors[j]->dir = SOUTH;
		else
			data->ray[i].doors[j]->dir = NORTH;
		data->ray[i].doors[j]->use = true;
		data->ray[i].doors[j]->case_x = data->ray[i].case_x;
		data->ray[i].doors[j]->case_y = data->ray[i].case_y - 1;
		data->ray[i].doors[j]->coo_y = 63.999;
		data->ray[i].doors[j]->coo_x = data->ray[i].coo_x + data->ray[i].ry * data->ray[i].delta_x;
		printf("rx>%lf ry>%lf  delta x>>>%lf    delta y>>>%lf    coo y>>>%lf    coo x>>>%lf    ",data->ray[i].rx,data->ray[i].ry,data->ray[i].delta_x,data->ray[i].delta_y,data->ray[i].doors[j]->coo_y,data->ray[i].doors[j]->coo_x);
		// if (data->ray[i].delta_x > 0)
		// 	data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->coo_x) / data->ray[i].delta_x;
		// else
		// 	data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->coo_x / data->ray[i].delta_x;
		// if (data->ray[i].delta_y > 0)
		// 	data->ray[i].doors[j]->ry = (64 - data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
		// else
		// 	data->ray[i].doors[j]->ry = -data->ray[i].doors[j]->coo_y / data->ray[i].delta_y;
		// if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		// {
		// 	if (64 - data->ray[i].doors[j]->rx * data->ray[i].delta_y < 32)
		// 		data->ray[i].doors[j]->print = true;
		// }
		// else
		// 	data->ray[i].doors[j]->print = true;
		if (data->ray[i].delta_x > 0)
			data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->coo_x) / data->ray[i].delta_x;
		else
			data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->coo_x / data->ray[i].delta_x;
		// if (data->ray[i].delta_y > 0)
		// 	data->ray[i].doors[j]->ry = (32 - data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
		// else
		data->ray[i].doors[j]->ry = (-data->ray[i].doors[j]->coo_y + 32) / data->ray[i].delta_y;
		printf("rx>>>%lf       ry>>>%lf  \n",data->ray[i].doors[j]->rx,data->ray[i].doors[j]->ry);
		if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		{
			// if (64 - data->ray[i].doors[j]->rx * data->ray[i].delta_y < 32)
			data->ray[i].doors[j]->print = false;
		}
		else
		{
			data->ray[i].doors[j]->print = true;
			data->ray[i].doors[j]->coo_x += data->ray[i].doors[j]->ry * data->ray[i].delta_x;
			printf("coo_x modif>>>%lf\n",data->ray[i].doors[j]->coo_x);
		}
		data->ray[i].doors[j]->coo_y = 32;
		// printf("j>>>>>%d\n",j);
		// if (data->ray[i].coo_x + data->ray[i].ry * data->ray[i].delta_x > 32)
			// data->ray[i].doors[j]->print = true;
		// set_valid_door();
		// printf("top_y>>>%lf\n",data->ray[i].doors[j]->coo_x);
	}
	if (data->map.tabmap[data->ray[i].case_y - 1][data->ray[i].case_x] != '1'
	)//&& data->map.tabmap[data->ray[i].case_y - 1][data->ray[i].case_x] != 'D')
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

	if (data->map.tabmap[data->ray[i].case_y + 1][data->ray[i].case_x] == 'D')	
	{
		int	j = 0;
		while (j < data->nb_door)
		{
			if (data->ray[i].doors[j]->use == false)
			{
				// printf("HIT i>>%d   j>>%d\n",i,j);
				break;
			}
			j++;
		}

		// printf("OUT i>>%d   j>>%d\n",i,j);
		if (data->ray[i].delta_y < 0)
			data->ray[i].doors[j]->dir = SOUTH;
		else
			data->ray[i].doors[j]->dir = NORTH;
		data->ray[i].doors[j]->use = true;
		data->ray[i].doors[j]->case_x = data->ray[i].case_x;
		data->ray[i].doors[j]->case_y = data->ray[i].case_y + 1;
		data->ray[i].doors[j]->coo_y = 32;
		data->ray[i].doors[j]->coo_x = data->ray[i].coo_x + data->ray[i].ry * data->ray[i].delta_x;
		// data->ray[i].doors[j]->print = false;
		if (data->ray[i].delta_x > 0)
			data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->coo_x) / data->ray[i].delta_x;
		else
			data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->coo_x / data->ray[i].delta_x;
		if (data->ray[i].delta_y > 0)
			data->ray[i].doors[j]->ry = (64 - data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
		else
			data->ray[i].doors[j]->ry = -data->ray[i].doors[j]->coo_y / data->ray[i].delta_y;
		if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		{
			if (data->ray[i].doors[j]->coo_y + data->ray[i].doors[j]->rx * data->ray[i].delta_y > 32)
				data->ray[i].doors[j]->print = true;
		}
		else
			data->ray[i].doors[j]->print = true;
		// printf("top_y>>>%lf\n",data->ray[i].doors[j]->coo_x);
	}
	if (data->map.tabmap[data->ray[i].case_y + 1][data->ray[i].case_x] != '1'
	)//&& data->map.tabmap[data->ray[i].case_y + 1][data->ray[i].case_x] != 'D')
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
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x - 1] == 'D')	
	{
		int	j = 0;
		while (j < data->nb_door)
		{
			if (data->ray[i].doors[j]->use == false)
				break;
			j++;
		}
		if (data->ray[i].delta_x < 0)
			data->ray[i].doors[j]->dir = EAST;
		else
			data->ray[i].doors[j]->dir = WEST;
		data->ray[i].doors[j]->use = true;
		data->ray[i].doors[j]->case_y = data->ray[i].case_y;
		data->ray[i].doors[j]->case_x = data->ray[i].case_x - 1;
		data->ray[i].doors[j]->coo_x = 32;
		data->ray[i].doors[j]->coo_y = data->ray[i].coo_y + data->ray[i].rx * data->ray[i].delta_y;

		if (data->ray[i].delta_x > 0)
			data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->coo_x) / data->ray[i].delta_x;
		else
			data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->coo_x / data->ray[i].delta_x;
		if (data->ray[i].delta_y > 0)
			data->ray[i].doors[j]->ry = (64 - data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
		else
			data->ray[i].doors[j]->ry = -data->ray[i].doors[j]->coo_y / data->ray[i].delta_y;
		if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		{
			if (data->ray[i].doors[j]->coo_x + data->ray[i].doors[j]->ry * data->ray[i].delta_x > 32)
				data->ray[i].doors[j]->print = true;
		}
		else
			data->ray[i].doors[j]->print = true;
		// printf("top_y>>>%lf\n",data->ray[i].doors[j]->coo_y);
	}
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x - 1] != '1'
	)//&& data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x - 1] != 'D')
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
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x + 1] == 'D')
	{
		int	j = 0;
		while (j < data->nb_door)
		{
			if (data->ray[i].doors[j]->use == false)
				break;
			j++;
		}
		if (data->ray[i].delta_x < 0)
			data->ray[i].doors[j]->dir = EAST;
		else
			data->ray[i].doors[j]->dir = WEST;
		data->ray[i].doors[j]->use = true;
		data->ray[i].doors[j]->case_y = data->ray[i].case_y;
		data->ray[i].doors[j]->case_x = data->ray[i].case_x + 1;
		data->ray[i].doors[j]->coo_x = 32;
		data->ray[i].doors[j]->coo_y = data->ray[i].coo_y + data->ray[i].rx * data->ray[i].delta_y;

		if (data->ray[i].delta_x > 0)
			data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->coo_x) / data->ray[i].delta_x;
		else
			data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->coo_x / data->ray[i].delta_x;
		if (data->ray[i].delta_y > 0)
			data->ray[i].doors[j]->ry = (64 - data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
		else
			data->ray[i].doors[j]->ry = -data->ray[i].doors[j]->coo_y / data->ray[i].delta_y;
		if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		{
			if (data->ray[i].doors[j]->coo_x + data->ray[i].doors[j]->ry * data->ray[i].delta_x < 32)
				data->ray[i].doors[j]->print = true;
		}
		else
			data->ray[i].doors[j]->print = true;
			
		// printf("top_y>>>%lf\n",data->ray[i].doors[j]->coo_y);
	}
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
