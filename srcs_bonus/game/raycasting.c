#include "cub3d_bonus.h"
#include <math.h>

#include <stdio.h>

static int	handle_ray_x(t_data *data, int i)
{
	if (data->ray[i].delta_x < 0)
		data->ray[i].dir = EAST;
	else
		data->ray[i].dir = WEST;
	if (data->ray[i].delta_x < 0)
	{
		if (handle_ray_x_left(data, i) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_x_right(data, i) == 1)
			return (1);
	}
	return (0);
}

static int	handle_ray_y(t_data *data, int i)
{
	if (data->ray[i].delta_y < 0)
		data->ray[i].dir = SOUTH;
	else
		data->ray[i].dir = NORTH;
	if (data->ray[i].delta_y < 0)
	{
		if (handle_ray_y_top(data, i) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_y_down(data, i) == 1)
			return (1);
	}
	return (0);
}

static void	handle_ray(t_data *data, int i)
{
	while (1)
	{
		if (data->ray[i].delta_x > 0)
			data->ray[i].rx = (64 - data->ray[i].coo_x) / data->ray[i].delta_x;
		else
			data->ray[i].rx = -data->ray[i].coo_x / data->ray[i].delta_x;
		if (data->ray[i].delta_y > 0)
			data->ray[i].ry = (64 - data->ray[i].coo_y) / data->ray[i].delta_y;
		else
			data->ray[i].ry = -data->ray[i].coo_y / data->ray[i].delta_y;
		if (data->ray[i].rx < data->ray[i].ry)
		{
			if (handle_ray_x(data, i) == 1)
				break ;
		}
		else
		{
			if (handle_ray_y(data, i) == 1)
				break ;
		}
	}
}

static void	save_data_ray(t_data *data, int i, double x)
{
	data->ray[i].rad = -atan(1 / x);
	data->ray[i].deg = data->ray[i].rad;
	if (data->ray[i].rad >= 0)
		data->ray[i].rad += M_PI;
	data->ray[i].rad += data->map.mini.deg * (M_PI / 180);
	data->ray[i].coo_y = data->map.mini.player_coo.y;
	data->ray[i].coo_x = data->map.mini.player_coo.x;
	data->ray[i].case_y = data->map.player_coo->y;
	data->ray[i].case_x = data->map.player_coo->x;
	data->ray[i].delta_x = -cos(data->ray[i].rad);
	data->ray[i].delta_y = sin(data->ray[i].rad);
}

static void	calc_sqrt_door(t_data *data, int i, int j)
{
	data->ray[i].doors[j]->dist_door = sqrt(((data->ray[i].doors[j]->case_y
		- data->map.player_coo->y) * 64.0 + (data->ray[i].doors[j]->coo_y
		- data->map.mini.player_coo.y)) * ((data->ray[i].doors[j]->case_y
		- data->map.player_coo->y) * 64.0 + (data->ray[i].doors[j]->coo_y
		- data->map.mini.player_coo.y)) + ((data->ray[i].doors[j]->case_x
		- data->map.player_coo->x) * 64.0 + (data->ray[i].doors[j]->coo_x
		- data->map.mini.player_coo.x)) * ((data->ray[i].doors[j]->case_x
		- data->map.player_coo->x) * 64.0 + (data->ray[i].doors[j]->coo_x
		- data->map.mini.player_coo.x)));
}

#include <stdio.h>

static void	calc_door_value(t_data *data, int i, double x)
{
	int	j;

	j = 0;
	// printf("HERE >>%d  %p\n",i,data->ray[i].doors,data->ray[i].doors[j]);
	// printf("TAB>>>%p  %d",j);
	while (j < data->nb_door && data->ray[i].doors[j]->use != false)
	{
		calc_sqrt_door(data, i, j);
		// printf("dist >>>%lf    i>>%d    j>>%d\n",data->ray[i].doors[j]->dist_door,i,j);
		data->ray[i].doors[j]->dist_door *= cos(atan(x));
		data->ray[i].doors[j]->size_door = data->ray[i].d_proj
			/ (double)(data->ray[i].doors[j]->dist_door / 64.0);
		// printf("size door>>>%lf\n",data->ray[i].doors[j]->size_door);
		data->ray[i].doors[j]->max_size_door = data->ray[i].doors[j]->size_door * 0.5;
		// printf("max size door>>>%lf\n",data->ray[i].doors[j]->max_size_door);
		data->ray[i].doors[j]->htop_door = round(data->ray[i].max_height
				- data->ray[i].doors[j]->max_size_door);
		data->ray[i].doors[j]->hbot_door = round(data->ray[i].max_height
				+ data->ray[i].doors[j]->max_size_door);
		// printf("max height>>>%lf\n",data->ray[i].max_height);
		j++;
		// printf("TAB>>>%p  %d",data->ray[i].doors[j],j);
	}
}

void	ray_launch(t_data *data)
{
	int		i;
	double	x;

	i = 0;
	while (i < data->mlx.width)
	{
		x = (double)i / (double)data->mlx.width;
		x = x * (-2) + 1;
		save_data_ray(data, i, x);
		pthread_mutex_lock(&data->m_data_ray);
		handle_ray(data, i);
		calc_door_value(data, i, x);
		pthread_mutex_unlock(&data->m_data_ray);
		calc_sqrt(data, i);
		data->ray[i].dist_wall *= cos(atan(x));
		data->ray[i].size_wall = data->ray[i].d_proj
			/ (double)(data->ray[i].dist_wall / 64.0);
		data->ray[i].pix_x = (double)i;
		data->ray[i].max_size_wall = data->ray[i].size_wall * 0.5;
		data->ray[i].calc_bits = (int)(data->screen->bits_per_pixel >> 3);
		data->ray[i].data_addr = data->screen->data_addr;
		data->ray[i].htop_wall = round(data->ray[i].max_height
				- data->ray[i].max_size_wall);
		data->ray[i].hbot_wall = round(data->ray[i].max_height
				+ data->ray[i].max_size_wall);
		i += 1;
	}
}
