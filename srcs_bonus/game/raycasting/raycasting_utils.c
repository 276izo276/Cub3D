#include "cub3d_bonus.h"
#include <math.h>

int	handle_ray_y_top(t_data *data, int i)
{
	if (data->map.tabmap[data->ray[i].case_y - 1][data->ray[i].case_x] != '1')
		not_a_wall_y_top(data, i);
	else
	{
		data->ray[i].coo_y = 0;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
		pthread_mutex_lock(&data->m_data_ray);
		if (is_compatible_wall(data, data->ray[i].case_y - 1,
				data->ray[i].case_x))
		{
			if (data->map.tabmap[data->ray[i].case_y]
				[data->ray[i].case_x] == 'D' || data->map.tabmap
				[data->ray[i].case_y][data->ray[i].case_x] == 'F')
			{
				pthread_mutex_unlock(&data->m_data_ray);
				return (1);
			}
			spawn_wall_msg(data, i, data->ray[i].case_y - 1,
				data->ray[i].case_x);
		}
		pthread_mutex_unlock(&data->m_data_ray);
		return (1);
	}
	return (0);
}

int	handle_ray_y_down(t_data *data, int i)
{
	if (data->map.tabmap[data->ray[i].case_y + 1][data->ray[i].case_x] != '1')
		not_a_wall_y_down(data, i);
	else
	{
		data->ray[i].coo_y = 64;
		data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
		data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
		pthread_mutex_lock(&data->m_data_ray);
		if (is_compatible_wall(data, data->ray[i].case_y + 1,
				data->ray[i].case_x))
		{
			if (data->map.tabmap[data->ray[i].case_y]
				[data->ray[i].case_x] == 'D' || data->map.tabmap
				[data->ray[i].case_y][data->ray[i].case_x] == 'F')
			{
				pthread_mutex_unlock(&data->m_data_ray);
				return (1);
			}
			spawn_wall_msg(data, i, data->ray[i].case_y + 1,
				data->ray[i].case_x);
		}
		pthread_mutex_unlock(&data->m_data_ray);
		return (1);
	}
	return (0);
}

int	handle_ray_x_left(t_data *data, int i)
{
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x - 1] != '1')
		not_a_wall_x_left(data, i);
	else
	{
		data->ray[i].coo_x = 0;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
		pthread_mutex_lock(&data->m_data_ray);
		if (is_compatible_wall(data, data->ray[i].case_y,
				data->ray[i].case_x - 1))
		{
			if (data->map.tabmap[data->ray[i].case_y]
				[data->ray[i].case_x] == 'D' || data->map.tabmap
				[data->ray[i].case_y][data->ray[i].case_x] == 'F')
			{
				pthread_mutex_unlock(&data->m_data_ray);
				return (1);
			}
			spawn_wall_msg(data, i, data->ray[i].case_y, data->ray[i].case_x
				- 1);
		}
		pthread_mutex_unlock(&data->m_data_ray);
		return (1);
	}
	return (0);
}

int	handle_ray_x_right(t_data *data, int i)
{
	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x + 1] != '1')
		not_a_wall_x_right(data, i);
	else
	{
		data->ray[i].coo_x = 64;
		data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
		data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
		pthread_mutex_lock(&data->m_data_ray);
		if (is_compatible_wall(data, data->ray[i].case_y,
				data->ray[i].case_x + 1))
		{
			if (data->map.tabmap[data->ray[i].case_y]
				[data->ray[i].case_x] == 'D' || data->map.tabmap
				[data->ray[i].case_y][data->ray[i].case_x] == 'F')
			{
				pthread_mutex_unlock(&data->m_data_ray);
				return (1);
			}
			spawn_wall_msg(data, i, data->ray[i].case_y, data->ray[i].case_x
				+ 1);
		}
		pthread_mutex_unlock(&data->m_data_ray);
		return (1);
	}
	return (0);
}

void	calc_sqrt(t_data *data, int i)
{
	data->ray[i].dist_wall = sqrt(((data->ray[i].case_y
					- data->player.coo.case_y) * 64.0 + (data->ray[i].coo_y
					- data->player.coo.coo_y)) * ((data->ray[i].case_y
					- data->player.coo.case_y) * 64.0 + (data->ray[i].coo_y
					- data->player.coo.coo_y)) + ((data->ray[i].case_x
					- data->player.coo.case_x) * 64.0 + (data->ray[i].coo_x
					- data->player.coo.coo_x)) * ((data->ray[i].case_x
					- data->player.coo.case_x) * 64.0 + (data->ray[i].coo_x
					- data->player.coo.coo_x)));
}
