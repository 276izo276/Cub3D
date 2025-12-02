#include "cub3d_bonus.h"
#include "mlx.h"

void	mouse_move_map(t_data *data, int y, int x)
{
	double	dx;
	double	dy;
	double	sensitivity;

	dx = x - data->mlx.width / 2;
	dy = y - data->mlx.height / 2;
	mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.width / 2,
		data->mlx.height / 2);
	sensitivity = (50 / data->sensitivity) / data->map.zoom;
	if (dx != 0 || dy != 0)
	{
		data->map.last_pos_x += dx * sensitivity;
		data->map.last_pos_y += dy * sensitivity;
	}
	data->map.last_mouse_x = x;
	data->map.last_mouse_y = y;
}

static void	change_dir_verti(t_data *data)
{
	if (data->map.tabmap[data->map.pos_active_floo.y]
		[data->map.pos_active_floo.x + 1] != '1')
	{
		data->player.coo.coo_x = 42.0;
		data->map.mini.deg = 270;
		data->map.mini.rad = data->map.mini.deg * M_PI / 180;
	}
	else
	{
		data->player.coo.coo_x = 22.0;
		data->map.mini.deg = 90;
		data->map.mini.rad = data->map.mini.deg * M_PI / 180;
	}
}

static void	change_dir_not_verti(t_data *data)
{
	if (data->map.tabmap[data->map.pos_active_floo.y
			+ 1][data->map.pos_active_floo.x] != '1')
	{
		data->player.coo.coo_y = 42.0;
		data->map.mini.deg = 180;
		data->map.mini.rad = data->map.mini.deg * M_PI / 180;
	}
	else
	{
		data->player.coo.coo_y = 22.0;
		data->map.mini.deg = 0;
		data->map.mini.rad = data->map.mini.deg * M_PI / 180;
	}
}

static void	handle_mouse_click(t_data *data)
{
	if (data->map.door_map[data->map.pos_active_floo.y]
		[data->map.pos_active_floo.x]->is_verti == true)
	{
		data->player.coo.coo_y = 32;
		change_dir_verti(data);
	}
	else
	{
		data->player.coo.coo_x = 32.0;
		change_dir_not_verti(data);
	}
}

void	mouse_key_map(t_data *data, int key)
{
	if (key == 1 && data->map.floo_active == true && data->status == FLOO_MAP)
	{
		data->sound = add_end_lst(create_sound(data, 25), data->sound,
				free_sound);
		data->sound = add_end_lst(create_sound(data, 27), data->sound,
				free_sound);
		data->map.door_map[data->player.coo.case_y]
		[data->player.coo.case_x]->is_floo_open = false;
		data->player.coo.case_x = data->map.pos_active_floo.x;
		data->player.coo.case_y = data->map.pos_active_floo.y;
		handle_mouse_click(data);
		data->map.zoom = 128;
		data->status = GAME;
	}
	if (key == 4 && data->map.zoom <= 128 && data->status != GAME)
		data->map.zoom *= 2;
	else if (key == 5 && data->map.zoom >= 32 && data->status != GAME)
		data->map.zoom /= 2;
}
