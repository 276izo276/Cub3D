#include "cub3d_bonus.h"
#include "player_bonus.h"

void	handle_map_keys(int keycode, t_data *data)
{
	handle_exit_map(keycode, data);
	if (keycode == KEY_W)
		data->map.last_pos_y -= 1;
	else if (keycode == KEY_S)
		data->map.last_pos_y += 1;
	else if (keycode == KEY_A)
		data->map.last_pos_x -= 1;
	else if (keycode == KEY_D)
		data->map.last_pos_x += 1;
	else if (keycode == KEY_SPACE)
	{
		data->map.last_pos_x = data->player.coo.case_x;
		data->map.last_pos_y = data->player.coo.case_y;
	}
	if (keycode == KEY_1 && data->map.zoom <= 128)
		data->map.zoom *= 2;
	else if (keycode == KEY_2 && data->map.zoom >= 32)
		data->map.zoom /= 2;
}
