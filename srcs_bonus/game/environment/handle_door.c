#include "cub3d_bonus.h"
#include "mlx.h"






#include <stdio.h>
void	handle_door(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			if (data->map.tabmap[y][x] == 'D')
			{
				if (data->map.door_map[y][x]->pos >= 100 && data->map.door_map[y][x]->is_open == false)
				{
						// data->map.door_map[y][x]->pos = 100;
						data->map.door_map[y][x]->is_open = true;
				}
				else if (data->map.door_map[y][x]->pos <= 50)
					data->map.door_map[y][x]->is_open = false;
				if ((y == data->map.player_coo->y && (x == data->map.player_coo->x + 1
					|| x == data->map.player_coo->x - 1)) || (x == data->map.player_coo->x && (y == data->map.player_coo->y + 1
					|| y == data->map.player_coo->y - 1))
					|| (y == data->map.player_coo->y && x == data->map.player_coo->x))
				{
					if (data->spell.count_frame != 0 && data->map.door_map[y][x]->pos < 120)
						data->map.door_map[y][x]->pos += 0.03 * data->spell.count_frame;
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
			++x;
		}
		++y;
	}
}
