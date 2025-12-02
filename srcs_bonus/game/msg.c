#include "cub3d_bonus.h"

void	remove_wall_msg(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			if (data->map.tabmap[y][x] == '1')
			{
				if (data->map.wall_map[y][x]->msg_nb < data->current_msg)
					data->map.wall_map[y][x]->is_active = false;
			}
			++x;
		}
		++y;
	}
}

void	handle_msg_utils(t_data *data, long long int cur)
{
	if (data->current_msg == 7 && data->display.elapsed_time == 0)
	{
		data->display.elapsed_time = cur;
		data->display.is_msg_active = false;
	}
	else if (data->current_msg >= 7 && cur
		- data->display.elapsed_time > data->display.time_remove)
	{
		remove_wall_msg(data);
		data->current_msg = 0;
		data->display.elapsed_time = 0;
		data->display.is_msg_active = true;
		data->display.is_first_msg = true;
	}
}

void	handle_wall_msg(t_data *data, long long int cur)
{
	if (data->current_msg == 4 && data->display.elapsed_time == 0
		&& data->display.is_first_msg == true)
	{
		data->display.elapsed_time = cur;
		data->display.is_msg_active = false;
	}
	else if (data->current_msg == 4 && cur
		- data->display.elapsed_time > data->display.time_remove
		&& data->display.is_first_msg == true)
	{
		remove_wall_msg(data);
		data->display.elapsed_time = 0;
		data->display.is_msg_active = true;
		data->display.is_first_msg = false;
	}
}
