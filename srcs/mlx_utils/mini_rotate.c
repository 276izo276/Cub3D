#include <math.h>
#include "cub3d.h"

void	rotate_left(t_data *data)
{
	data->map.mini.deg += 1;
	data->map.mini.deg = fmod(data->map.mini.deg, 360.0);
	data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
}

void	rotate_right(t_data *data)
{
	data->map.mini.deg -= 1;
	if (data->map.mini.deg < 0)
		data->map.mini.deg += 360;
	data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
}
