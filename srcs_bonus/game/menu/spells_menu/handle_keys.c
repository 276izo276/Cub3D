/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:49:45 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:49:46 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	handle_lateral_move(t_data *data, int keycode)
{
	if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		if (data->spell_menu.selected % 8 != 7)
			++data->spell_menu.selected;
		else if (data->spell_menu.selected != 21)
			data->spell_menu.selected -= 7;
		if (data->spell_menu.selected == 22)
			data->spell_menu.selected = 16;
	}
	else if (keycode == KEY_LEFT || keycode == KEY_A)
	{
		if (data->spell_menu.selected % 8 != 0)
			--data->spell_menu.selected;
		else if (data->spell_menu.selected != 16)
			data->spell_menu.selected += 7;
		else
			data->spell_menu.selected = 21;
	}
}

static void	handle_up_move(t_data *data, int keycode)
{
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		if (data->spell_menu.selected < 5)
			data->spell_menu.selected += 16;
		else if (data->spell_menu.selected == 6
			|| data->spell_menu.selected == 7)
			data->spell_menu.selected = 21;
		else if (data->spell_menu.selected == 5)
			data->spell_menu.selected = 20;
		else if (data->spell_menu.selected == 21
			|| data->spell_menu.selected == 20)
			data->spell_menu.selected -= 7;
		else
			data->spell_menu.selected -= 8;
	}
}

static void	handle_down_move(t_data *data, int keycode)
{
	if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		if (data->spell_menu.selected == 14 || data->spell_menu.selected == 15)
			data->spell_menu.selected = 21;
		else if (data->spell_menu.selected == 13)
			data->spell_menu.selected = 20;
		else if (data->spell_menu.selected == 21)
			data->spell_menu.selected = 6;
		else if (data->spell_menu.selected == 20)
			data->spell_menu.selected = 5;
		else if (data->spell_menu.selected >= 16)
			data->spell_menu.selected -= 16;
		else
			data->spell_menu.selected += 8;
	}
}

static void	handle_move_spell_take(t_data *data, int keycode)
{
	if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		if (data->selected != 3)
			++data->selected;
		else
			data->selected = 0;
	}
	else if (keycode == KEY_LEFT || keycode == KEY_A)
	{
		if (data->selected != 0)
			--data->selected;
		else
			data->selected = 3;
	}
	else if (keycode == KEY_ENTER
		&& data->spell_menu.start_time > data->spell
		[data->spell_take[data->selected]].end_time
		+ data->spell[data->spell_take[data->selected]].base_cooldown * 1000)
		data->spell_menu.selected = 0;
}

void	handle_menu_spell_keys(int keycode, t_data *data)
{
	if (keycode == KEY_ESCAPE || keycode == KEY_N)
	{
		data->spell_menu.selected = -1;
		update_spell_cooldown(data);
		data->status = GAME;
	}
	if (data->spell_menu.selected == -1)
		handle_move_spell_take(data, keycode);
	else
	{
		handle_lateral_move(data, keycode);
		handle_down_move(data, keycode);
		handle_up_move(data, keycode);
		if (keycode == KEY_ENTER
			&& data->spell
			[data->spell_menu.selected].necessary_lvl <= data->player.xp)
		{
			data->spell_take[data->selected] = data->spell_menu.selected;
			data->spell_menu.selected = -1;
		}
	}
}
