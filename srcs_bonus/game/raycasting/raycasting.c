#include "cub3d_bonus.h"
#include <math.h>


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

void	raycast_loop(t_data *data, int i, double x)
{
	save_data_ray(data, i, x);
	try_hit_item(data, i, x);
	handle_ray(data, i);
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
}
