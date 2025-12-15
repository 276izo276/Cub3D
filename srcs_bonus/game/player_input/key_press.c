/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:50:21 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/15 11:57:59 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"

int	is_key_pressed(t_data *data, int keycode)
{
	int	i;

	i = 0;
	while (i < KEYCODE_NB)
	{
		if (data->keycode[i] == keycode)
			return (1);
		i++;
	}
	return (0);
}

static void	reset_popo(t_data *data, int keycode)
{
	if (keycode == KEY_Z)
		data->popo[0].active = 0;
	else if (keycode == KEY_X)
		data->popo[1].active = 0;
	else if (keycode == KEY_C)
		data->popo[2].active = 0;
	else if (keycode == KEY_V)
		data->popo[3].active = 0;
}

int	key_release(int keycode, t_data *data)
{
	int	i;

	i = 0;
	reset_popo(data, keycode);
	while (i < KEYCODE_NB)
	{
		data->popo[3].active = 0;
		if (data->keycode[i] == keycode)
			data->keycode[i] = 0;
		else if (keycode == KEY_SHIFT)
			data->map.mini.speed = 1.5;
		i++;
	}
	return (0);
}

static int	redir_menu_key(t_data *data, int keycode)
{
	if (data->status == MENU)
	{
		handle_menu_keys(keycode, data);
		return (0);
	}
	else if (data->status == FLOO_MAP || data->status == MAP)
	{
		handle_map_keys(keycode, data);
		return (0);
	}
	else if (data->status == MENU_SPELL)
	{
		handle_menu_spell_keys(keycode, data);
		return (0);
	}
	else if (data->status == MENU_DEATH || data->status == MENU_END)
	{
		handle_death_menu_keys(keycode, data);
		return (0);
	}
	return (1);
}

int	key_press(int keycode, t_data *data)
{
	int	i;

	i = 0;
	cheat_code(data, keycode);
	if (redir_menu_key(data, keycode) == 0)
		return (0);
	while (data->keycode[i] != 0 && i < KEYCODE_NB)
		i++;
	if (keycode == KEY_CTRL)
	{
		if (data->display.player_height != 16)
			data->display.player_height = 16;
		else
			data->display.player_height = 18;
	}
	else if (change_game_status(data, keycode) == true)
		data->sound = add_end_lst(create_sound(data, 27),
				data->sound, free_sound);
	else
		data->keycode[i] = keycode;
	if (keycode == KEY_SHIFT)
		data->map.mini.speed = 3;
	return (0);
}
