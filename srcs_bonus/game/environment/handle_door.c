#include "cub3d_bonus.h"
#include "mlx.h"

static void	open_door_condition(t_data *data, int y, int x)
{
	if (data->map.door_map[y][x]->pos >= 100
		&& data->map.door_map[y][x]->is_open == false)
		data->map.door_map[y][x]->is_open = true;
	else if (data->map.door_map[y][x]->pos <= 50)
		data->map.door_map[y][x]->is_open = false;
	if ((y == data->player.coo.case_y && (x == data->player.coo.case_x + 1
				|| x == data->player.coo.case_x - 1))
		|| (x == data->player.coo.case_x && (y == data->player.coo.case_y + 1
				|| y == data->player.coo.case_y - 1))
		|| (y == data->player.coo.case_y && x == data->player.coo.case_x))
	{
		if (data->lumos.count_frame != 0 && data->map.door_map[y][x]->pos < 120)
			data->map.door_map[y][x]->pos += 0.03 * data->lumos.count_frame;
		else if (data->map.door_map[y][x]->pos >= 3)
			data->map.door_map[y][x]->pos -= 3;
	}
	else if (data->map.door_map[y][x]->pos > 0)
	{
		if (data->map.door_map[y][x]->pos < 3)
			data->map.door_map[y][x]->pos = 0;
		else
			data->map.door_map[y][x]->pos -= 3;
	}
}

void	handle_door(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			if (data->map.tabmap[y][x] == 'F'
				&& data->map.door_map[y][x]->is_floo_open == true)
			{
				++data->frame_floo;
				if (data->frame_floo > 50)
				{
					data->frame_floo = 0;
					data->map.door_map[y][x]->is_floo_open = false;
				}
			}
			if (data->map.tabmap[y][x] == 'D')
				open_door_condition(data, y, x);
			++x;
		}
		++y;
	}
}
