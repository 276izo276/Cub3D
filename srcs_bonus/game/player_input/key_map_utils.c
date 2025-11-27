#include "cub3d_bonus.h"
#include <math.h>

static void	change_player_deg(t_data *data, int angle_deg)
{
	if (angle_deg >= 315 || angle_deg <= 45)
		data->player.coo.coo_y = 42;
	else if (angle_deg > 135 && angle_deg < 225)
		data->player.coo.coo_y = 22;
	else if (angle_deg >= 45 && angle_deg <= 135)
		data->player.coo.coo_x = 42;
	else if (angle_deg >= 225 && angle_deg <= 315)
		data->player.coo.coo_x = 22;
	data->map.mini.deg += 180;
	data->map.mini.deg = fmod(data->map.mini.deg, 360);
	data->map.mini.rad = data->map.mini.deg * M_PI / 180;
}

void	handle_exit_map(int keycode, t_data *data)
{
	int	angle_deg;

	angle_deg = data->map.mini.deg;
	if (keycode == KEY_ESCAPE || (keycode == KEY_M && data->status == MAP))
	{
		data->status = GAME;
		data->map.zoom = 128;
		data->sound = add_end_lst(create_sound(data, 28), data->sound,
				free_sound);
		if (data->status != FLOO_MAP)
			return ;
		data->sound = add_end_lst(create_sound(data, 26), data->sound,
				free_sound);
		change_player_deg(data, angle_deg);
		data->map.door_map[data->player.coo.case_y]
		[data->player.coo.case_x]->is_floo_open = false;
	}
}

static void	is_floo_open_y(t_data *data, bool *open)
{
	if (data->map.tabmap[data->player.coo.case_y
			- 1][data->player.coo.case_x] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y
				- 1][data->player.coo.case_x]->is_floo_open == false)
			*open = true;
		data->map.door_map[data->player.coo.case_y
			- 1][data->player.coo.case_x]->is_floo_open = true;
	}
	else if (data->map.tabmap[data->player.coo.case_y
			+ 1][data->player.coo.case_x] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y
				+ 1][data->player.coo.case_x]->is_floo_open == false)
			*open = true;
		data->map.door_map[data->player.coo.case_y
			+ 1][data->player.coo.case_x]->is_floo_open = true;
	}
}

static void	is_floo_open_x(t_data *data, bool *open)
{
	if (data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x
		+ 1] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y][data->player.coo.case_x
			+ 1]->is_floo_open == false)
			*open = true;
		data->map.door_map[data->player.coo.case_y][data->player.coo.case_x
			+ 1]->is_floo_open = true;
	}
	if (data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x
		- 1] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y][data->player.coo.case_x
			- 1]->is_floo_open == false)
			*open = true;
		data->map.door_map[data->player.coo.case_y][data->player.coo.case_x
			- 1]->is_floo_open = true;
	}
}

bool	handle_floo_open(t_data *data)
{
	bool	open;

	open = false;
	if (data->map.tabmap[data->player.coo.case_y]
		[data->player.coo.case_x] == 'F')
	{
		if (data->map.door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->is_floo_open == false)
			open = true;
		data->map.door_map[data->player.coo.case_y]
		[data->player.coo.case_x]->is_floo_open = true;
	}
	is_floo_open_y(data, &open);
	is_floo_open_x(data, &open);
	return (open);
}
