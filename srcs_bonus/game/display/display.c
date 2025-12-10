/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:47:12 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:47:13 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

static void	get_right_text(t_data *data, int i)
{
	if (data->ray[i].dir == NORTH)
		data->ray[i].img = data->map.north;
	else if (data->ray[i].dir == SOUTH)
		data->ray[i].img = data->map.south;
	else if (data->ray[i].dir == EAST)
		data->ray[i].img = data->map.east;
	else if (data->ray[i].dir == WEST)
		data->ray[i].img = data->map.west;
}

static void	check_dir(t_data *data, int i)
{
	double	posx_display;

	posx_display = 0;
	get_right_text(data, i);
	if (data->ray[i].dir == NORTH || data->ray[i].dir == SOUTH)
	{
		posx_display = data->ray[i].coo_x / 64;
		if (data->ray[i].dir == NORTH)
			posx_display = 1 - posx_display;
	}
	else if (data->ray[i].dir == WEST || data->ray[i].dir == EAST)
	{
		posx_display = data->ray[i].coo_y / 64;
		if (data->ray[i].dir == EAST)
			posx_display = 1 - posx_display;
	}
	posx_display -= floor(posx_display);
	data->ray[i].texture_coo.x = (int)(posx_display * data->ray[i].img->width);
	if (data->ray[i].texture_coo.x < 0)
		data->ray[i].texture_coo.x = 0;
	if (data->ray[i].texture_coo.x >= data->ray[i].img->width)
		data->ray[i].texture_coo.x = data->ray[i].img->width - 1;
}

static void	put_text_pix_img(t_data *data, int i, int dist_heigh, int text_x)
{
	char			*text_pix;
	int				text_y;
	char			*pixel_addr;
	unsigned int	color;

	text_y = (data->ray[i].pix_y - data->ray[i].htop_wall) / dist_heigh
		* data->ray[i].img->height;
	pixel_addr = data->ray[i].img_addr + (data->ray[i].pix_y
			* data->screen->size_line);
	text_pix = data->ray[i].img->data_addr + (text_y
			* data->ray[i].img->size_line + text_x);
	color = *(unsigned int *)text_pix;
	*(unsigned int *)pixel_addr = color;
}

static void	check_msg_wall_pos(t_data *data, int i)
{
	if (data->ray[i].dir == SOUTH && data->map.wall_map[data->ray[i].case_y
			- 1][data->ray[i].case_x]->is_active
		&& data->map.wall_map[data->ray[i].case_y
		- 1][data->ray[i].case_x]->dir == data->ray[i].dir)
		display_msg(data, i, data->ray[i].case_y - 1, data->ray[i].case_x);
	else if (data->ray[i].dir == NORTH && data->map.wall_map[data->ray[i].case_y
			+ 1][data->ray[i].case_x]->is_active
		&& data->map.wall_map[data->ray[i].case_y
		+ 1][data->ray[i].case_x]->dir == data->ray[i].dir)
		display_msg(data, i, data->ray[i].case_y + 1, data->ray[i].case_x);
	else if (data->ray[i].dir == WEST
		&& data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x
		+ 1]->is_active
		&& data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x
		+ 1]->dir == data->ray[i].dir)
		display_msg(data, i, data->ray[i].case_y, data->ray[i].case_x + 1);
	else if (data->ray[i].dir == EAST
		&& data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x
		- 1]->is_active
		&& data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x
		- 1]->dir == data->ray[i].dir)
		display_msg(data, i, data->ray[i].case_y, data->ray[i].case_x - 1);
}

void	display_game_loop(t_data *data, int i)
{
	int	text_x;
	int	dist_heigh;

	check_dir(data, i);
	text_x = data->ray[i].texture_coo.x
		* (data->ray[i].img->bits_per_pixel >> 3);
	data->ray[i].img_addr = data->screen->data_addr + data->ray[i].pix_x
		* data->ray[i].calc_bits;
	data->ray[i].pix_y = data->ray[i].htop_wall;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	dist_heigh = data->ray[i].hbot_wall - data->ray[i].htop_wall;
	while (data->ray[i].pix_y < data->ray[i].hbot_wall
		&& data->ray[i].pix_y < data->mlx.height)
	{
		put_text_pix_img(data, i, dist_heigh, text_x);
		data->ray[i].pix_y++;
	}
	check_msg_wall_pos(data, i);
}
