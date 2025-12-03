#include "cub3d.h"
#include "mlx.h"
#include "player.h"
#include "struct.h"
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

	i = 0;
	while (i < KEYCODE_NB)
	{
		if (data->keycode[i] == keycode)
			data->keycode[i] = 0;
		i++;
	}
	return (0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	int	i;

	i = 0;
	while (data->keycode[i] != 0 && i < KEYCODE_NB)
		i++;
	data->keycode[i] = keycode;
	if (keycode == KEY_ALT)
		mlx_mouse_show(data->mlx.mlx, data->mlx.win);
	return (0);
}
