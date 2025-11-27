#include "cub3d_bonus.h"
#include "utils_bonus.h"

static void	coa_valid_key(t_data *data)
{
	int	i;

	data->player.color = data->coa[data->selected].color;
	data->player.coa = data->selected;
	data->coa[data->player.coa].xp = data->player.xp;
	data->selected = 0;
	i = 0;
	while (i < 9)
	{
		if (data->sorcerer[i].color != data->player.color)
			data->sorcerer[i].is_alive = false;
		++i;
	}
}

static void	key_select_coa(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
	{
		if (data->selected == 0)
			data->selected = 3;
		else
			data->selected -= 1;
	}
	else if (keycode == KEY_RIGHT)
	{
		if (data->selected == 3)
			data->selected = 0;
		else
			data->selected += 1;
	}
	else if (keycode == KEY_ENTER)
		coa_valid_key(data);
	else if (keycode == KEY_ESCAPE)
		f_exit(data, 1);
}

static void	key_select_hand(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
	{
		if (data->selected == 1)
			data->selected -= 1;
		else
			data->selected += 1;
	}
	else if (keycode == KEY_RIGHT)
	{
		if (data->selected == 0)
			data->selected += 1;
		else
			data->selected -= 1;
	}
	else if (keycode == KEY_ENTER)
	{
		if (data->selected == 1)
			data->is_right_handed = true;
		else
			data->is_right_handed = false;
		select_right_hand(data);
		data->status = GAME;
	}
	else if (keycode == KEY_ESCAPE)
		f_exit(data, 1);
}

void	handle_death_menu_keys(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT || keycode == KEY_A)
	{
		if (data->selected == 1)
			data->selected -= 1;
		else
			data->selected += 1;
	}
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
	{
		if (data->selected == 0)
			data->selected += 1;
		else
			data->selected -= 1;
	}
	else if (keycode == KEY_ENTER)
	{
		if (data->selected == 1)
			f_exit(data, 0);
		else
			restart(data);
	}
	else if (keycode == KEY_ESCAPE)
		f_exit(data, 0);
}

void	handle_menu_keys(int keycode, t_data *data)
{
	if (data->player.color == 0)
		key_select_coa(keycode, data);
	else if (data->is_right_handed == 0)
		key_select_hand(keycode, data);
}
