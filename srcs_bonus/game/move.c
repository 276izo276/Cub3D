/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:51:59 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:52:00 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "player_bonus.h"
#include "utils_bonus.h"

void	handle_input_cond(t_data *data, int i, int *move)
{
	if (data->keycode[i] >= KEY_1 && data->keycode[i] <= KEY_4)
	{
		if (data->spell[data->spell_take[data->keycode[i]
					- KEY_1]].necessary_lvl <= data->player.xp)
		{
			data->cast_spell = data->spell_take[data->keycode[i] - KEY_1];
			data->keycode[i] = 0;
		}
	}
	else if (is_move_player(data, i))
		*move = 1;
	else if (data->keycode[i] == KEY_E)
		rotate_right(data);
	else if (data->keycode[i] == KEY_Q)
		rotate_left(data);
	else if (data->keycode[i] == KEY_Z)
		data->popo[0].call(data);
	else if (data->keycode[i] == KEY_X)
		data->popo[1].call(data);
	else if (data->keycode[i] == KEY_C)
		data->popo[2].call(data);
	else if (data->keycode[i] == KEY_V)
		data->popo[3].call(data);
}

void	handle_input_move(t_data *data, long long int cur)
{
	int	i;
	int	move;

	i = 0;
	move = 0;
	if (data->time_move + 1000 / FPM < cur)
	{
		player_invisible(data);
		move_item(data);
		move_enemy(data);
		handle_sound(data);
		data->time_move = cur;
		data->player_moved = false;
		while (i < KEYCODE_NB)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			handle_input_cond(data, i, &move);
			i++;
		}
		if (move)
			handle_move(&data->map, &data->map.mini, data);
		take_damage(data);
	}
}
