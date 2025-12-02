#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "utils_bonus.h"
#include <stdlib.h>
#include "time_bonus.h"

int	spawn_sorcerer_utils(t_data *data, char type, int y, int x)
{
	int	attempts;
	int	random_y;
	int	random_x;

	attempts = 0;
	random_y = 0;
	while (++attempts < 1000)
	{
		y = 0;
		while (data->map.tabmap[y])
			++y;
		random_y = rand() % y;
		x = 0;
		while (data->map.tabmap[random_y][x])
			++x;
		random_x = rand() % x;
		if (data->map.tabmap[random_y][random_x] == '0')
			break ;
	}
	if (attempts >= 1000)
		return (1);
	data->enemy = add_end_lst(init_enemy(type, (t_fcoo){.case_x = random_x,
				.case_y = random_y, .coo_y = 32, .coo_x = 32}, data,
				data->map.mini.deg), data->enemy, f_enemy);
	return (0);
}

void	spawn_sorcerer(t_data *data, char type)
{
	int	y;
	int	x;
	int	random;

	y = 0;
	x = 0;
	random = rand() % 100;
	if (random > 1 + data->player.xp * 2)
		return ;
	if (spawn_sorcerer_utils(data, type, y, x))
		return ;
	data->last_spawn = get_mtime();
	if (!data->enemy)
		f_exit(data, 1);
}
