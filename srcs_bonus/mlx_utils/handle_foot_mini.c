/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_foot_mini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:52:44 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:52:45 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "texture_bonus.h"
#include "cub3d_bonus.h"
#include <stdlib.h>

static bool	check_gap(t_data *data)
{
	int	gap_x;
	int	gap_y;

	gap_x = (data->map.mini.foot_tab[0].coo.case_x - data->player.coo.case_x)
		* 64 + ((int)data->map.mini.foot_tab[0].coo.coo_x
			- (int)data->player.coo.coo_x);
	gap_y = (data->map.mini.foot_tab[0].coo.case_y - data->player.coo.case_y)
		* 64 + ((int)data->map.mini.foot_tab[0].coo.coo_y
			- (int)data->player.coo.coo_y);
	if ((abs(gap_x) < 20 && abs(gap_y) < 20))
		return (false);
	return (true);
}

void	save_and_move_foot(t_data *data, double rad)
{
	int	i;

	i = 0;
	if (check_gap(data) == false)
		return ;
	while (data->map.mini.foot_tab[i].is_save == true && i < 7)
		++i;
	while (i > 0)
	{
		data->map.mini.foot_tab[i] = data->map.mini.foot_tab[i - 1];
		--i;
	}
	data->map.mini.foot_tab[0].coo.case_x = data->player.coo.case_x;
	data->map.mini.foot_tab[0].coo.case_y = data->player.coo.case_y;
	data->map.mini.foot_tab[0].coo.coo_y = data->player.coo.coo_y;
	data->map.mini.foot_tab[0].coo.coo_x = data->player.coo.coo_x;
	data->map.mini.foot_tab[0].rad = rad;
	data->map.mini.foot_tab[0].foot_x = -1;
	data->map.mini.foot_tab[0].foot_y = -1;
	if (data->map.mini.foot_tab[1].is_save == true
		&& data->map.mini.foot_tab[1].is_left == false)
		data->map.mini.foot_tab[0].is_left = true;
	else
		data->map.mini.foot_tab[0].is_left = false;
	data->map.mini.foot_tab[0].is_save = true;
}

void	angle_offset(t_data *data, int *start_x, int *start_y, int i)
{
	int	angle_deg;

	if (data->map.mini.foot_tab[i].foot_x != -1)
	{
		*start_x = data->map.mini.foot_tab[i].foot_x;
		*start_y = data->map.mini.foot_tab[i].foot_y;
		return ;
	}
	angle_deg = data->map.mini.foot_tab[i].rad * 180 / M_PI;
	get_good_offset_x(data, angle_deg, start_x, i);
	get_good_offset_y(data, angle_deg, start_y, i);
	data->map.mini.foot_tab[i].foot_x = *start_x;
	data->map.mini.foot_tab[i].foot_y = *start_y;
}

void	set_foot_in_mini_map(t_data *data, int i, t_utils_mini *u, t_img img)
{
	int		gap_x;
	int		gap_y;
	double	distance;

	distance = 5 + i * 5;
	calc_gap(data, i, &gap_x, &gap_y);
	while (u->y < img.height)
	{
		u->x = 0;
		while (u->x < img.width)
		{
			calc_value_player_mini_map_aff(u, &img,
				data->map.mini.foot_tab[i].rad);
			if (u->color != 0x00000000)
			{
				data->aff.color = get_right_color(data->player.color, distance);
				set_pix_old_player(u, u->start_y + gap_y,
					u->start_x + gap_x, data);
			}
			++u->x;
		}
		++u->y;
	}
}

void	set_trail_foot(t_data *data, t_utils_mini *u)
{
	int		i;
	t_img	img;

	i = 1;
	while (data->map.mini.foot_tab[i].is_save == true && i < 8)
	{
		if (data->map.mini.foot_tab[i].is_left == true)
			img = data->map.mini.img[MINI_LEFT];
		else
			img = data->map.mini.img[MINI_RIGHT];
		u->y = 0;
		angle_offset(data, &u->start_x, &u->start_y, i);
		set_foot_in_mini_map(data, i, u, img);
		++i;
	}
}
