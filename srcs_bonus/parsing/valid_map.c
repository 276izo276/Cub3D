#include "cub3d_bonus.h"

void	reset_value_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.tabmap && data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			if (data->map.tabmap[y][x] == '-')
				data->map.tabmap[y][x] = ' ';
			x++;
		}
		y++;
	}
}
