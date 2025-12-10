/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:50:11 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:50:12 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "time_bonus.h"

bool	is_move_player(t_data *data, int i)
{
	if (data->keycode[i] == KEY_W || data->keycode[i] == KEY_D
		|| data->keycode[i] == KEY_A || data->keycode[i] == KEY_S
		|| data->keycode[i] == KEY_1 || data->keycode[i] == KEY_UP
		|| data->keycode[i] == KEY_DOWN || data->keycode[i] == KEY_LEFT
		|| data->keycode[i] == KEY_RIGHT || data->keycode[i] == KEY_2)
		return (true);
	return (false);
}

static void	is_easter_egg(int keycode, t_data *data)
{
	if (keycode == data->wand.secret_wand[data->wand.count_egg] + 32)
		data->wand.count_egg++;
	if (data->wand.count_egg == 7 && data->wand.wand_status[5] == false)
	{
		data->wand.wand_status[5] = true;
		data->wand.nb_wand = 5;
		data->sound = add_end_lst(create_sound(data, 28), data->sound,
				free_sound);
	}
	else if (keycode == data->wand.secret_sword[data->wand.count_sword] + 32)
		data->wand.count_sword++;
	if (data->wand.count_sword == 5 && data->wand.wand_status[6] == false)
	{
		data->wand.wand_status[6] = true;
		data->wand.nb_wand = 6;
		data->sound = add_end_lst(create_sound(data, 28), data->sound,
				free_sound);
	}
}

void	cheat_code(t_data *data, int keycode)
{
	if (keycode == data->cheat_code_xp[data->index_xp] + 32)
	{
		data->index_xp++;
		if (data->index_xp == 8)
		{
			data->index_xp = 0;
			data->player.xp += 20;
		}
	}
	else if (keycode == data->cheat_code_life[data->index_life] + 32
		|| (keycode == KEY_MINUS && data->index_life == 3))
	{
		data->index_life++;
		if (data->index_life == 8)
		{
			data->index_life = 0;
			if (data->god_mod == false)
				data->god_mod = true;
			else
				data->god_mod = false;
		}
	}
	if (data->wand.wand_status[5] != true || data->wand.wand_status[6] != true)
		is_easter_egg(keycode, data);
}

bool	change_game_status(t_data *data, int keycode)
{
	if (keycode == KEY_TAB)
	{
		if (data->status == GAME)
			data->status = PAUSE;
		else
			data->status = GAME;
		return (true);
	}
	if (keycode == KEY_N && data->status == GAME)
	{
		data->status = MENU_SPELL;
		data->spell_menu.start_time = get_mtime();
		data->selected = 0;
		return (true);
	}
	if (keycode == KEY_M)
	{
		data->status = MAP;
		data->map.last_pos_x = data->player.coo.case_x;
		data->map.last_pos_y = data->player.coo.case_y;
		return (true);
	}
	return (false);
}
