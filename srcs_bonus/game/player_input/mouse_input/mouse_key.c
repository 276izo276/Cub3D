/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:50:08 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:50:09 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include <math.h>

int	mouse_move(int x, int y, t_data *data)
{
	if ((x != data->mlx.width / 2 || y != data->mlx.height / 2)
		&& !is_key_pressed(data, KEY_ALT) && data->status != FLOO_MAP
		&& data->status != MAP)
	{
		data->map.mini.deg += (double)-(x - data->mlx.width / 2)
			/ data->sensitivity;
		data->map.mini.deg = fmod(data->map.mini.deg, 360.0);
		if (data->map.mini.deg < 0)
			data->map.mini.deg += 360;
		data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
		calc_left_point_player(data);
		calc_right_point_player(data);
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 2,
			data->mlx.height / 2);
	}
	else if (data->status == FLOO_MAP || data->status == MAP)
		mouse_move_map(data, y, x);
	return (0);
}

int	mouse_key(int key, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	mouse_key_ig(data, key);
	mouse_key_map(data, key);
	if (key == 9)
	{
		data->sound = add_end_lst(create_sound(data, 27), data->sound,
				free_sound);
		if (data->status == GAME)
		{
			data->status = MAP;
			data->map.last_pos_x = data->player.coo.case_x;
			data->map.last_pos_y = data->player.coo.case_y;
		}
		else if (data->status == MAP)
			data->status = GAME;
	}
	else if (key == 8)
		mouse_key_spell_menu(data);
	return (0);
}
