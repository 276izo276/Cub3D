#include "cub3d_bonus.h"
#include <math.h>

#include <stdio.h>



int	handle_ray_y_top(t_data *data, int i)
{
	// int	x;
	// int	y;
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x] == 'D')	
	{
		int	j = 0;
		while (j < data->nb_door)
		{
			if (data->ray[i].doors[j]->use == false)
				break;
			j++;
		}

		data->ray[i].doors[j]->use = true;
		data->ray[i].doors[j]->case_x = data->ray[i].case_x;
		data->ray[i].doors[j]->case_y = data->ray[i].case_y;

		data->ray[i].doors[j]->start_y = data->ray[i].coo_y;
		data->ray[i].doors[j]->start_x = data->ray[i].coo_x;
		
		if (data->ray[i].delta_x > 0)
			data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->start_x) / data->ray[i].delta_x;
		else
			data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->start_x / data->ray[i].delta_x;
		if (data->ray[i].delta_y > 0)
			data->ray[i].ry = (64 - data->ray[i].doors[j]->start_y) / data->ray[i].delta_y;
		else
			data->ray[i].doors[j]->ry = -data->ray[i].doors[j]->start_y / data->ray[i].delta_y;
		if (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->is_verti)
		{
			if (data->ray[i].delta_x < 0)
				data->ray[i].doors[j]->dir = EAST;
			else
				data->ray[i].doors[j]->dir = WEST;
		}
		else
		{
			if (data->ray[i].delta_y < 0)
				data->ray[i].doors[j]->dir = SOUTH;
			else
				data->ray[i].doors[j]->dir = NORTH;
		}
		if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		{

			
			if (data->ray[i].delta_x < 0)
				data->ray[i].doors[j]->end_x = 0;
			else
				data->ray[i].doors[j]->end_x = 64;
			
			data->ray[i].doors[j]->end_y = data->ray[i].doors[j]->start_y + data->ray[i].doors[j]->rx * data->ray[i].delta_y;	
		}
		else
		{
			data->ray[i].doors[j]->end_y = 0;
			data->ray[i].doors[j]->end_x = data->ray[i].doors[j]->start_x + data->ray[i].doors[j]->ry * data->ray[i].delta_x;			
		}
		double delta = (data->ray[i].doors[j]->end_x
			- data->ray[i].doors[j]->start_x)
		* (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y
			- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
			- (data->ray[i].doors[j]->end_y
				- data->ray[i].doors[j]->start_y)
			* (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
		if (delta != 0)
		{
			double delta_t = (data->ray[i].doors[j]->end_x
				- data->ray[i].doors[j]->start_x)
			* ( data->ray[i].doors[j]->start_y
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				- (data->ray[i].doors[j]->end_y
					- data->ray[i].doors[j]->start_y)
				* (data->ray[i].doors[j]->start_x
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);

			double delta_u = (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x 
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x)
			* ( data->ray[i].doors[j]->start_y
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				- (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				* (data->ray[i].doors[j]->start_x
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
			
			double t = delta_t / delta;
			double u = delta_u / delta;
			if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
			{
				data->ray[i].doors[j]->print = true;
				data->ray[i].doors[j]->coo_x = data->ray[i].doors[j]->start_x + u * (data->ray[i].doors[j]->end_x - data->ray[i].doors[j]->start_x);
				data->ray[i].doors[j]->coo_y = data->ray[i].doors[j]->start_y + u * (data->ray[i].doors[j]->end_y - data->ray[i].doors[j]->start_y);
			}
		}
		else
		{
			data->ray[i].doors[j]->print = false;
		}
	}

	if (data->map.tabmap[data->ray[i].case_y - 1][data->ray[i].case_x] != '1'
	)
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

	// if (data->map.tabmap[data->ray[i].case_y + 1][data->ray[i].case_x] == 'D')	
	// {
	// 	int	j = 0;
	// 	while (j < data->nb_door)
	// 	{
	// 		if (data->ray[i].doors[j]->use == false)
	// 		{
	// 			// printf("HIT i>>%d   j>>%d\n",i,j);
	// 			break;
	// 		}
	// 		j++;
	// 	}

	// 	// printf("OUT i>>%d   j>>%d\n",i,j);
	// 	if (data->ray[i].delta_y < 0)
	// 		data->ray[i].doors[j]->dir = SOUTH;
	// 	else
	// 		data->ray[i].doors[j]->dir = NORTH;
	// 	data->ray[i].doors[j]->use = true;
	// 	data->ray[i].doors[j]->case_x = data->ray[i].case_x;
	// 	data->ray[i].doors[j]->case_y = data->ray[i].case_y + 1;
	// 	data->ray[i].doors[j]->coo_y = 0;
	// 	data->ray[i].doors[j]->coo_x = data->ray[i].coo_x + data->ray[i].ry * data->ray[i].delta_x;
		
	// 	if (data->ray[i].delta_x > 0)
	// 		data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->coo_x) / data->ray[i].delta_x;
	// 	else
	// 		data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->coo_x / data->ray[i].delta_x;
	// 	// if (data->ray[i].delta_y > 0)
	// 	// 	data->ray[i].doors[j]->ry = (32 - data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
	// 	// else
	// 	data->ray[i].doors[j]->ry = (-data->ray[i].doors[j]->coo_y + 32) / data->ray[i].delta_y;
	// 	if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
	// 	{
	// 		data->ray[i].doors[j]->print = false;
	// 	}
	// 	else
	// 	{
	// 		data->ray[i].doors[j]->print = true;
	// 		// data->ray[i].doors[j]->coo_x += data->ray[i].doors[j]->ry * data->ray[i].delta_x;
	// 	}
	// 	data->ray[i].doors[j]->coo_y = 32;
	// }
	
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x] == 'D')	
	{

		int	j = 0;
		while (j < data->nb_door)
		{
			if (data->ray[i].doors[j]->use == false)
				break;
			j++;
		}

		// if (data->ray[i].delta_y < 0)
		// 	data->ray[i].doors[j]->dir = SOUTH;
		// else
		// 	data->ray[i].doors[j]->dir = NORTH;
		data->ray[i].doors[j]->use = true;
		data->ray[i].doors[j]->case_x = data->ray[i].case_x;
		data->ray[i].doors[j]->case_y = data->ray[i].case_y;

		data->ray[i].doors[j]->start_y = data->ray[i].coo_y;
		data->ray[i].doors[j]->start_x = data->ray[i].coo_x;
		
		if (data->ray[i].delta_x > 0)
			data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->start_x) / data->ray[i].delta_x;
		else
			data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->start_x / data->ray[i].delta_x;
		if (data->ray[i].delta_y > 0)
			data->ray[i].doors[j]->ry = (64 - data->ray[i].doors[j]->start_y) / data->ray[i].delta_y;
		else
			data->ray[i].doors[j]->ry = -data->ray[i].doors[j]->start_y / data->ray[i].delta_y;
		// printf("delta_y>>>%lf   delta_x>>>%lf\n",data->ray[i].delta_y,data->ray[i].delta_x);
		// printf("start coo_y>>>%lf     coo_x>>>%lf\n",data->ray[i].doors[j]->coo_y,data->ray[i].doors[j]->coo_x);
		// printf("rx>>>>%lf     ry>>>>%lf\n",data->ray[i].doors[j]->rx,data->ray[i].doors[j]->ry);
		if (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->is_verti)
		{
			if (data->ray[i].delta_x < 0)
				data->ray[i].doors[j]->dir = EAST;
			else
				data->ray[i].doors[j]->dir = WEST;
		}
		else
		{
			if (data->ray[i].delta_y < 0)
				data->ray[i].doors[j]->dir = SOUTH;
			else
				data->ray[i].doors[j]->dir = NORTH;
		}
		if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		{
			if (data->ray[i].delta_x < 0)
				data->ray[i].doors[j]->end_x = 0;
			else
				data->ray[i].doors[j]->end_x = 64;
			
			data->ray[i].doors[j]->end_y = data->ray[i].doors[j]->start_y + data->ray[i].doors[j]->rx * data->ray[i].delta_y;	
		}
		else
		{
			data->ray[i].doors[j]->end_y = 64;
			data->ray[i].doors[j]->end_x = data->ray[i].doors[j]->start_x + data->ray[i].doors[j]->ry * data->ray[i].delta_x;			
		}
		// if (data->ray[i].delta_x > 0)
		// 	data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->start_x) / data->ray[i].delta_x;
		// else
		// 	data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->start_x / data->ray[i].delta_x;
		// data->ray[i].doors[j]->ry = (-data->ray[i].doors[j]->start_y + 32) / data->ray[i].delta_y;

		// if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		// {
		// 	data->ray[i].doors[j]->print = false;
		// 	printf("MUST DONNNNNNNNNNNT HIT   end y >>>%lf\n",64 + data->ray[i].delta_y * data->ray[i].doors[j]->rx );
		// }
		// else
		// {
		// 	// data->ray[i].doors[j]->print = true;
		// 	printf("OKKKKKKKKKKKK HIT\n");
		// 	// data->ray[i].doors[j]->end_x = data->ray[i].doors[j]->start_x + data->ray[i].doors[j]->ry * data->ray[i].delta_x;
		// 	// data->ray[i].doors[j]->end_y = ;
		// }
		// data->ray[i].doors[j]->coo_y = 32;

		double delta = (data->ray[i].doors[j]->end_x
			- data->ray[i].doors[j]->start_x)
		* (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y
			- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
			- (data->ray[i].doors[j]->end_y
				- data->ray[i].doors[j]->start_y)
			* (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
		if (delta != 0)
		{
			double delta_t = (data->ray[i].doors[j]->end_x
				- data->ray[i].doors[j]->start_x)
			* ( data->ray[i].doors[j]->start_y
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				- (data->ray[i].doors[j]->end_y
					- data->ray[i].doors[j]->start_y)
				* (data->ray[i].doors[j]->start_x
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);

			double delta_u = (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x 
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x)
			* ( data->ray[i].doors[j]->start_y
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				- (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				* (data->ray[i].doors[j]->start_x
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
			
			double t = delta_t / delta;
			double u = delta_u / delta;
			if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
			{
				data->ray[i].doors[j]->print = true;
				// data->ray[i].doors[j]->coo_x += data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x + t * (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x - data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
				// data->ray[i].doors[j]->coo_y = data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y + t * (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y - data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y);
				data->ray[i].doors[j]->coo_x = data->ray[i].doors[j]->start_x + u * (data->ray[i].doors[j]->end_x - data->ray[i].doors[j]->start_x);
				data->ray[i].doors[j]->coo_y = data->ray[i].doors[j]->start_y + u * (data->ray[i].doors[j]->end_y - data->ray[i].doors[j]->start_y);
				// printf("CROSS IN normal'32' y>>>%lf    x>>>%lf\n",data->ray[i].doors[j]->coo_y, data->ray[i].doors[j]->coo_x);
				// printf("ay>>%d  ax>>%d\n",data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y,data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
				// printf("by>>%d  bx>>%d\n",data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y,data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x);
				// printf("cy>>%lf  cx>>%lf\n",data->ray[i].doors[j]->start_y,data->ray[i].doors[j]->start_x);
				// printf("dy>>%lf  dx>>%lf\n",data->ray[i].doors[j]->end_y,data->ray[i].doors[j]->end_x);
				// printf("delta>>%lf     delta_u>>>%lf     delta_t>>>%lf\n",delta, delta_u, delta_t);
				// printf("t>>>%lf     u>>>%lf\n",t,u);
				// printf("end coo_y>>>%lf     coo_x>>>%lf\n",data->ray[i].doors[j]->coo_y,data->ray[i].doors[j]->coo_x);
			}
			// else
			// {
			// 	printf("NOOOOOOOO HIT DOOR\n");
			// }
		}
		else
		{
			data->ray[i].doors[j]->print = false;
		}
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
	// if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x - 1] == 'D')
	// {
	// 	int	j = 0;
	// 	while (j < data->nb_door)
	// 	{
	// 		if (data->ray[i].doors[j]->use == false)
	// 			break;
	// 		j++;
	// 	}
	// 	if (data->ray[i].delta_x < 0)
	// 		data->ray[i].doors[j]->dir = EAST;
	// 	else
	// 		data->ray[i].doors[j]->dir = WEST;
	// 	data->ray[i].doors[j]->use = true;
	// 	data->ray[i].doors[j]->case_y = data->ray[i].case_y;
	// 	data->ray[i].doors[j]->case_x = data->ray[i].case_x - 1;
	// 	data->ray[i].doors[j]->coo_x = 64;
	// 	data->ray[i].doors[j]->coo_y = data->ray[i].coo_y + data->ray[i].rx * data->ray[i].delta_y;

	// 	// if (data->ray[i].delta_x > 0)
	// 	// 	data->ray[i].doors[j]->rx = (32 - data->ray[i].doors[j]->coo_x) / data->ray[i].delta_x;
	// 	// else
	// 	data->ray[i].doors[j]->rx = (-data->ray[i].doors[j]->coo_x + 32) / data->ray[i].delta_x;
	// 	if (data->ray[i].delta_y > 0)
	// 		data->ray[i].doors[j]->ry = (64 - data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
	// 	else
	// 		data->ray[i].doors[j]->ry = (-data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
	// 	if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
	// 	{
	// 		data->ray[i].doors[j]->print = true;
	// 		data->ray[i].doors[j]->coo_y += data->ray[i].doors[j]->rx * data->ray[i].delta_y;
	// 	}
	// 	else
	// 	{
	// 		data->ray[i].doors[j]->print = false;
	// 	}
	// 	data->ray[i].doors[j]->coo_x = 32;
	// }

	
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x] == 'D')	
	{
		// printf("\n\nFOUND CASE DOOR\n");
		int	j = 0;
		while (j < data->nb_door)
		{
			if (data->ray[i].doors[j]->use == false)
				break;
			j++;
		}

		// if (data->ray[i].delta_y < 0)
		// 	data->ray[i].doors[j]->dir = SOUTH;
		// else
		// 	data->ray[i].doors[j]->dir = NORTH;
		data->ray[i].doors[j]->use = true;
		data->ray[i].doors[j]->case_x = data->ray[i].case_x;
		data->ray[i].doors[j]->case_y = data->ray[i].case_y;

		data->ray[i].doors[j]->start_y = data->ray[i].coo_y;
		data->ray[i].doors[j]->start_x = data->ray[i].coo_x;
		
		if (data->ray[i].delta_x > 0)
			data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->start_x) / data->ray[i].delta_x;
		else
			data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->start_x / data->ray[i].delta_x;
		if (data->ray[i].delta_y > 0)
			data->ray[i].doors[j]->ry = (64 - data->ray[i].doors[j]->start_y) / data->ray[i].delta_y;
		else
			data->ray[i].doors[j]->ry = -data->ray[i].doors[j]->start_y / data->ray[i].delta_y;
		// printf("delta_y>>>%lf   delta_x>>>%lf\n",data->ray[i].delta_y,data->ray[i].delta_x);
		// printf("start coo_y>>>%lf     coo_x>>>%lf\n",data->ray[i].doors[j]->coo_y,data->ray[i].doors[j]->coo_x);
		// printf("rx>>>>%lf     ry>>>>%lf\n",data->ray[i].doors[j]->rx,data->ray[i].doors[j]->ry);
		if (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->is_verti)
		{
			if (data->ray[i].delta_x < 0)
				data->ray[i].doors[j]->dir = EAST;
			else
				data->ray[i].doors[j]->dir = WEST;
		}
		else
		{
			if (data->ray[i].delta_y < 0)
				data->ray[i].doors[j]->dir = SOUTH;
			else
				data->ray[i].doors[j]->dir = NORTH;
		}
		if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		{
			data->ray[i].doors[j]->end_x = 0;
			data->ray[i].doors[j]->end_y = data->ray[i].doors[j]->start_y + data->ray[i].doors[j]->rx * data->ray[i].delta_y;	
		}
		else
		{
			
			if (data->ray[i].delta_y < 0)
				data->ray[i].doors[j]->end_y = 0;
			else
				data->ray[i].doors[j]->end_y = 64;
			data->ray[i].doors[j]->end_x = data->ray[i].doors[j]->start_x + data->ray[i].doors[j]->ry * data->ray[i].delta_x;			
		}
		// if (data->ray[i].delta_x > 0)
		// 	data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->start_x) / data->ray[i].delta_x;
		// else
		// 	data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->start_x / data->ray[i].delta_x;
		// data->ray[i].doors[j]->ry = (-data->ray[i].doors[j]->start_y + 32) / data->ray[i].delta_y;

		// if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		// {
		// 	data->ray[i].doors[j]->print = false;
		// 	printf("MUST DONNNNNNNNNNNT HIT   end y >>>%lf\n",64 + data->ray[i].delta_y * data->ray[i].doors[j]->rx );
		// }
		// else
		// {
		// 	// data->ray[i].doors[j]->print = true;
		// 	printf("OKKKKKKKKKKKK HIT\n");
		// 	// data->ray[i].doors[j]->end_x = data->ray[i].doors[j]->start_x + data->ray[i].doors[j]->ry * data->ray[i].delta_x;
		// 	// data->ray[i].doors[j]->end_y = ;
		// }
		// data->ray[i].doors[j]->coo_y = 32;

		double delta = (data->ray[i].doors[j]->end_x
			- data->ray[i].doors[j]->start_x)
		* (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y
			- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
			- (data->ray[i].doors[j]->end_y
				- data->ray[i].doors[j]->start_y)
			* (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
		if (delta != 0)
		{
			double delta_t = (data->ray[i].doors[j]->end_x
				- data->ray[i].doors[j]->start_x)
			* ( data->ray[i].doors[j]->start_y
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				- (data->ray[i].doors[j]->end_y
					- data->ray[i].doors[j]->start_y)
				* (data->ray[i].doors[j]->start_x
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);

			double delta_u = (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x 
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x)
			* ( data->ray[i].doors[j]->start_y
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				- (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				* (data->ray[i].doors[j]->start_x
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
			
			double t = delta_t / delta;
			double u = delta_u / delta;
			if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
			{
				data->ray[i].doors[j]->print = true;
				// data->ray[i].doors[j]->coo_x += data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x + t * (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x - data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
				// data->ray[i].doors[j]->coo_y = data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y + t * (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y - data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y);
				data->ray[i].doors[j]->coo_x = data->ray[i].doors[j]->start_x + u * (data->ray[i].doors[j]->end_x - data->ray[i].doors[j]->start_x);
				data->ray[i].doors[j]->coo_y = data->ray[i].doors[j]->start_y + u * (data->ray[i].doors[j]->end_y - data->ray[i].doors[j]->start_y);
				// printf("CROSS IN normal'32' y>>>%lf    x>>>%lf\n",data->ray[i].doors[j]->coo_y, data->ray[i].doors[j]->coo_x);
				// printf("ay>>%d  ax>>%d\n",data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y,data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
				// printf("by>>%d  bx>>%d\n",data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y,data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x);
				// printf("cy>>%lf  cx>>%lf\n",data->ray[i].doors[j]->start_y,data->ray[i].doors[j]->start_x);
				// printf("dy>>%lf  dx>>%lf\n",data->ray[i].doors[j]->end_y,data->ray[i].doors[j]->end_x);
				// printf("delta>>%lf     delta_u>>>%lf     delta_t>>>%lf\n",delta, delta_u, delta_t);
				// printf("t>>>%lf     u>>>%lf\n",t,u);
				// printf("end coo_y>>>%lf     coo_x>>>%lf\n",data->ray[i].doors[j]->coo_y,data->ray[i].doors[j]->coo_x);
			}
			// else
			// {
			// 	printf("NOOOOOOOO HIT DOOR\n");
			// }
		}
		else
		{
			data->ray[i].doors[j]->print = false;
		}
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
	// if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x + 1] == 'D')
	// {
	// 	int	j = 0;
	// 	while (j < data->nb_door)
	// 	{
	// 		if (data->ray[i].doors[j]->use == false)
	// 			break;
	// 		j++;
	// 	}
	// 	if (data->ray[i].delta_x < 0)
	// 		data->ray[i].doors[j]->dir = EAST;
	// 	else
	// 		data->ray[i].doors[j]->dir = WEST;
	// 	data->ray[i].doors[j]->use = true;
	// 	data->ray[i].doors[j]->case_y = data->ray[i].case_y;
	// 	data->ray[i].doors[j]->case_x = data->ray[i].case_x + 1;
	// 	data->ray[i].doors[j]->coo_x = 0;
	// 	data->ray[i].doors[j]->coo_y = data->ray[i].coo_y + data->ray[i].rx * data->ray[i].delta_y;

	// 	// if (data->ray[i].delta_x > 0)
	// 	data->ray[i].doors[j]->rx = (32 - data->ray[i].doors[j]->coo_x) / data->ray[i].delta_x;
	// 	// else
	// 	// data->ray[i].doors[j]->rx = (-data->ray[i].doors[j]->coo_x + 32) / data->ray[i].delta_x;
	// 	if (data->ray[i].delta_y > 0)
	// 		data->ray[i].doors[j]->ry = (64 - data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
	// 	else
	// 		data->ray[i].doors[j]->ry = (-data->ray[i].doors[j]->coo_y) / data->ray[i].delta_y;
	// 	if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
	// 	{
	// 		data->ray[i].doors[j]->print = true;
	// 		data->ray[i].doors[j]->coo_y += data->ray[i].doors[j]->rx * data->ray[i].delta_y;
	// 	}
	// 	else
	// 	{
	// 		data->ray[i].doors[j]->print = false;
	// 	}
	// 	data->ray[i].doors[j]->coo_x = 32;
			
	// 	// printf("top_y>>>%lf\n",data->ray[i].doors[j]->coo_y);
	// }
	
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x] == 'D')	
	{
		// printf("\n\nFOUND CASE DOOR\n");
		int	j = 0;
		while (j < data->nb_door)
		{
			if (data->ray[i].doors[j]->use == false)
				break;
			j++;
		}

		// if (data->ray[i].delta_y < 0)
		// 	data->ray[i].doors[j]->dir = SOUTH;
		// else
		// 	data->ray[i].doors[j]->dir = NORTH;
		data->ray[i].doors[j]->use = true;
		data->ray[i].doors[j]->case_x = data->ray[i].case_x;
		data->ray[i].doors[j]->case_y = data->ray[i].case_y;

		data->ray[i].doors[j]->start_y = data->ray[i].coo_y;
		data->ray[i].doors[j]->start_x = data->ray[i].coo_x;
		
		if (data->ray[i].delta_x > 0)
			data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->start_x) / data->ray[i].delta_x;
		else
			data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->start_x / data->ray[i].delta_x;
		if (data->ray[i].delta_y > 0)
			data->ray[i].doors[j]->ry = (64 - data->ray[i].doors[j]->start_y) / data->ray[i].delta_y;
		else
			data->ray[i].doors[j]->ry = -data->ray[i].doors[j]->start_y / data->ray[i].delta_y;
		// printf("delta_y>>>%lf   delta_x>>>%lf\n",data->ray[i].delta_y,data->ray[i].delta_x);
		// printf("start coo_y>>>%lf     coo_x>>>%lf\n",data->ray[i].doors[j]->coo_y,data->ray[i].doors[j]->coo_x);
		// printf("rx>>>>%lf     ry>>>>%lf\n",data->ray[i].doors[j]->rx,data->ray[i].doors[j]->ry);
		if (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->is_verti)
		{
			if (data->ray[i].delta_x < 0)
				data->ray[i].doors[j]->dir = EAST;
			else
				data->ray[i].doors[j]->dir = WEST;
		}
		else
		{
			if (data->ray[i].delta_y < 0)
				data->ray[i].doors[j]->dir = SOUTH;
			else
				data->ray[i].doors[j]->dir = NORTH;
		}
		if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		{
			data->ray[i].doors[j]->end_x = 64;
			data->ray[i].doors[j]->end_y = data->ray[i].doors[j]->start_y + data->ray[i].doors[j]->rx * data->ray[i].delta_y;	
		}
		else
		{

			if (data->ray[i].delta_y < 0)
				data->ray[i].doors[j]->end_y = 0;
			else
				data->ray[i].doors[j]->end_y = 64;
			data->ray[i].doors[j]->end_x = data->ray[i].doors[j]->start_x + data->ray[i].doors[j]->ry * data->ray[i].delta_x;			
		}
		// if (data->ray[i].delta_x > 0)
		// 	data->ray[i].doors[j]->rx = (64 - data->ray[i].doors[j]->start_x) / data->ray[i].delta_x;
		// else
		// 	data->ray[i].doors[j]->rx = -data->ray[i].doors[j]->start_x / data->ray[i].delta_x;
		// data->ray[i].doors[j]->ry = (-data->ray[i].doors[j]->start_y + 32) / data->ray[i].delta_y;

		// if (data->ray[i].doors[j]->rx < data->ray[i].doors[j]->ry)
		// {
		// 	data->ray[i].doors[j]->print = false;
		// 	printf("MUST DONNNNNNNNNNNT HIT   end y >>>%lf\n",64 + data->ray[i].delta_y * data->ray[i].doors[j]->rx );
		// }
		// else
		// {
		// 	// data->ray[i].doors[j]->print = true;
		// 	printf("OKKKKKKKKKKKK HIT\n");
		// 	// data->ray[i].doors[j]->end_x = data->ray[i].doors[j]->start_x + data->ray[i].doors[j]->ry * data->ray[i].delta_x;
		// 	// data->ray[i].doors[j]->end_y = ;
		// }
		// data->ray[i].doors[j]->coo_y = 32;

		double delta = (data->ray[i].doors[j]->end_x
			- data->ray[i].doors[j]->start_x)
		* (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y
			- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
			- (data->ray[i].doors[j]->end_y
				- data->ray[i].doors[j]->start_y)
			* (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
		if (delta != 0)
		{
			double delta_t = (data->ray[i].doors[j]->end_x
				- data->ray[i].doors[j]->start_x)
			* ( data->ray[i].doors[j]->start_y
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				- (data->ray[i].doors[j]->end_y
					- data->ray[i].doors[j]->start_y)
				* (data->ray[i].doors[j]->start_x
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);

			double delta_u = (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x 
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x)
			* ( data->ray[i].doors[j]->start_y
				- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				- (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y)
				* (data->ray[i].doors[j]->start_x
					- data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
			
			double t = delta_t / delta;
			double u = delta_u / delta;
			if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
			{
				data->ray[i].doors[j]->print = true;
				// data->ray[i].doors[j]->coo_x += data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x + t * (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x - data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
				// data->ray[i].doors[j]->coo_y = data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y + t * (data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y - data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y);
				data->ray[i].doors[j]->coo_x = data->ray[i].doors[j]->start_x + u * (data->ray[i].doors[j]->end_x - data->ray[i].doors[j]->start_x);
				data->ray[i].doors[j]->coo_y = data->ray[i].doors[j]->start_y + u * (data->ray[i].doors[j]->end_y - data->ray[i].doors[j]->start_y);
				// printf("CROSS IN normal'32' y>>>%lf    x>>>%lf\n",data->ray[i].doors[j]->coo_y, data->ray[i].doors[j]->coo_x);
				// printf("ay>>%d  ax>>%d\n",data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.y,data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->first_p.x);
				// printf("by>>%d  bx>>%d\n",data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.y,data->map.door_map[data->ray[i].doors[j]->case_y][data->ray[i].doors[j]->case_x]->second_p.x);
				// printf("cy>>%lf  cx>>%lf\n",data->ray[i].doors[j]->start_y,data->ray[i].doors[j]->start_x);
				// printf("dy>>%lf  dx>>%lf\n",data->ray[i].doors[j]->end_y,data->ray[i].doors[j]->end_x);
				// printf("delta>>%lf     delta_u>>>%lf     delta_t>>>%lf\n",delta, delta_u, delta_t);
				// printf("t>>>%lf     u>>>%lf\n",t,u);
				// printf("end coo_y>>>%lf     coo_x>>>%lf\n",data->ray[i].doors[j]->coo_y,data->ray[i].doors[j]->coo_x);
			}
			// else
			// {
			// 	printf("NOOOOOOOO HIT DOOR\n");
			// }
		}
		else
		{
			data->ray[i].doors[j]->print = false;
		}
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
