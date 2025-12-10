/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:44:59 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:45:00 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	handle_ray_y_top(t_data *data, int i)
{
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
		return (1);
	}
	return (0);
}

int	handle_ray_y_down(t_data *data, int i)
{
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
		return (1);
	}
	return (0);
}

int	handle_ray_x_left(t_data *data, int i)
{
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
		return (1);
	}
	return (0);
}

int	handle_ray_x_right(t_data *data, int i)
{
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
