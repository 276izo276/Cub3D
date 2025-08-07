#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <math.h>

bool	is_move_player(t_data *data, int i)
{
	if (data->keycode[i] == KEY_W || data->keycode[i] == KEY_D
		|| data->keycode[i] == KEY_A || data->keycode[i] == KEY_S)
		return (true);
	return (false);
}

int	mouse_move(int x, int y, t_data *data)
{
	(void)data;
	if ((x != data->mlx.width / 2 || y != data->mlx.height / 2)
		&& !is_key_pressed(data, KEY_ALT))
	{
		data->map.mini.deg += (double)-(x - data->mlx.width / 2) / 40;
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
	while (i < 100)
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
	while (i < 100)
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

static void	handle_menu_keys(int keycode, t_data *data)
{
	if (keycode == 65362)
	{
		if (data->selected >= 2)
			data->selected -= 2;
		else
			data->selected += 2;
	}
	else if (keycode == 65364)
	{
		if (data->selected < 2)
			data->selected += 2;
		else
			data->selected -= 2;
	}
	else if (keycode == 65361)
	{
		if (data->selected % 2 == 1)
			data->selected -= 1;
		else
			data->selected += 1;
	}
	else if (keycode == 65363)
	{
		if (data->selected % 2 == 0)
			data->selected += 1;
		else
			data->selected -= 1;
	}
	else if (keycode == 65293)
	{
		data->color = data->menu[data->selected].color;
		data->status = GAME;
	}
	else if (keycode == KEY_ESCAPE)
		f_exit(data, 1);
}

int	key_press(int keycode, t_data *data)
{
	int	i;

	if (data->status == MENU)
	{
		handle_menu_keys(keycode, data);
		return (0);
	}
	// printf("Key pressed: %d\n", keycode);
	i = 0;
	while (data->keycode[i] != 0 && i < 100)
		i++;
	data->keycode[i] = keycode;
	if (keycode == KEY_ALT)
		mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	else if (keycode == KEY_SHIFT)
		data->map.mini.speed = 3;
	return (0);
}
