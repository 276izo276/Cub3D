#include <math.h>
#include "cub3d_bonus.h"

void	rotate_left(t_data *data)
{
	data->map.mini.deg += .25 / (data->sensitivity / 1000);
	data->map.mini.deg = fmod(data->map.mini.deg, 360.0);
	data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
	calc_left_point_player(data);
	calc_right_point_player(data);
}

void	rotate_right(t_data *data)
{
	data->map.mini.deg -= .25 / (data->sensitivity / 1000);
	if (data->map.mini.deg < 0)
		data->map.mini.deg += 360;
	data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
	calc_left_point_player(data);
	calc_right_point_player(data);
}
