#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <color_bonus.h>
#include <math.h>

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

int	mouse_move(int x, int y, t_data *data)
{
	(void)data;
	if ((x != data->mlx.width / 2 || y != data->mlx.height / 2)
		&& !is_key_pressed(data, KEY_ALT))
	{
		data->map.mini.deg += (double)-(x - data->mlx.width / 2) / data->sensitivity;
		data->map.mini.deg = fmod(data->map.mini.deg, 360.0);
		if (data->map.mini.deg < 0)
			data->map.mini.deg += 360;
		data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 2,
			data->mlx.height / 2);
	}
	return (0);
}

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

int	key_release(int keycode, t_data *data)
{
	int	i;

	// printf("Key released: %d\n", keycode);
	i = 0;
	while (i < KEYCODE_NB)
	{
		if (data->keycode[i] == keycode)
			data->keycode[i] = 0;
		if (keycode == KEY_ALT)
		{
			mlx_mouse_hide(data->mlx.mlx, data->mlx.win);
			mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width,
				data->mlx.height);
		}
		else if (keycode == KEY_SHIFT)
			data->map.mini.speed = 1.5;
		i++;
	}
	return (0);
	return (0);
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
	{
		data->color = data->coa[data->selected].color;
		data->selected = 0;
	}
	else if (keycode == KEY_ESCAPE)
		f_exit(data, 1);
}

static void key_select_hand(int keycode, t_data *data)
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
		init_img_msg(data);
	}
	else if (keycode == KEY_ESCAPE)
		f_exit(data, 1);
}

static void	handle_menu_keys(int keycode, t_data *data)
{
	if (data->color == 0)
		key_select_coa(keycode, data);
	else if (data->is_right_handed == 0)
		key_select_hand(keycode, data);
}

void	handle_floo_open(t_data *data)
{
	if (data->map.tabmap[data->map.player_coo->y][data->map.player_coo->x] == 'F')
		data->map.door_map[data->map.player_coo->y][data->map.player_coo->x]->is_floo_open = true;
	else if (data->map.tabmap[data->map.player_coo->y - 1][data->map.player_coo->x] == 'F')
		data->map.door_map[data->map.player_coo->y - 1][data->map.player_coo->x]->is_floo_open = true;
	else if (data->map.tabmap[data->map.player_coo->y + 1][data->map.player_coo->x] == 'F')
		data->map.door_map[data->map.player_coo->y + 1][data->map.player_coo->x]->is_floo_open = true;
	else if (data->map.tabmap[data->map.player_coo->y][data->map.player_coo->x + 1] == 'F')
		data->map.door_map[data->map.player_coo->y][data->map.player_coo->x + 1]->is_floo_open = true;
	else if (data->map.tabmap[data->map.player_coo->y][data->map.player_coo->x - 1] == 'F')
		data->map.door_map[data->map.player_coo->y][data->map.player_coo->x - 1]->is_floo_open = true;
}
#include <stdio.h>
int	key_press(int keycode, t_data *data)
{
	int	i;

	if (data->status == MENU)
	{
		handle_menu_keys(keycode, data);
		return (0);
	}
	i = 0;
	while (data->keycode[i] != 0 && i < KEYCODE_NB)
		i++;
	if (keycode == KEY_1)
	{
		if (!data->spell.active)
		{
			data->spell.active = true;
			data->spell.count_frame = 100;
		}
		else
			data->spell.active = false;
	}
	else if (keycode == KEY_2)
		handle_floo_open(data);
	else if (keycode == KEY_CTRL)
	{
		if (data->display.player_height != 16) // a changer on a plus besoins un bool suffit
			data->display.player_height = 16;
		else
			data->display.player_height = 18;
	}
	else if (keycode == KEY_TAB)
	{
		if (data->status == GAME)
			data->status = PAUSE;
		else
			data->status = GAME;
	}
	else
	{
		// printf("oui\n");
		data->keycode[i] = keycode;
	}
	if (keycode == KEY_ALT)
		mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	else if (keycode == KEY_SHIFT)
		data->map.mini.speed = 3;
	return (0);
}
