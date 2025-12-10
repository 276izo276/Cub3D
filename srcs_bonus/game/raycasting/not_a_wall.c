/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_a_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:50:30 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:50:31 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

void	not_a_wall_y_top(t_data *data, int i)
{
	data->ray[i].case_y--;
	data->ray[i].coo_y = 64;
	data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
	data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
}

void	not_a_wall_y_down(t_data *data, int i)
{
	data->ray[i].case_y++;
	data->ray[i].coo_y = 0;
	data->ray[i].coo_x += data->ray[i].ry * data->ray[i].delta_x;
	data->ray[i].coo_x = round(data->ray[i].coo_x * 64) / 64.0;
}

void	not_a_wall_x_left(t_data *data, int i)
{
	data->ray[i].case_x--;
	data->ray[i].coo_x = 64;
	data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
	data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
}

void	not_a_wall_x_right(t_data *data, int i)
{
	data->ray[i].case_x++;
	data->ray[i].coo_x = 0;
	data->ray[i].coo_y += data->ray[i].rx * data->ray[i].delta_y;
	data->ray[i].coo_y = round(data->ray[i].coo_y * 64) / 64.0;
}
