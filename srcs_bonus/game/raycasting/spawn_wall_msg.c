#include "cub3d_bonus.h"
#include <stdlib.h>

void	spawn_wall_msg(t_data *data, int i, int y, int x)
{
	int	random;

	random = rand() % (1500 * data->mlx.width);
	if (random == data->random_value && data->current_msg < data->nb_msg)
	{
		// pthread_mutex_lock(&data->m_data_ray);
		data->map.wall_map[y][x]->is_active = true;
		data->map.wall_map[y][x]->coo.x = x;
		data->map.wall_map[y][x]->coo.y = y;
		data->map.wall_map[y][x]->msg_nb = data->current_msg;
		data->map.wall_map[y][x]->dir = data->ray[i].dir;
		++data->current_msg;
		data->sound = add_end_lst(create_sound(data, 35), data->sound,
				free_sound);
		// pthread_mutex_unlock(&data->m_data_ray);
	}
}

bool	is_compatible_wall(t_data *data, int y, int x)
{
	if (data->map.tabmap[y][x] == '1'
		&& data->map.wall_map[y][x]->is_active == false
		&& data->player_moved == true && data->display.is_msg_active == true)
		return (true);
	return (false);
}
