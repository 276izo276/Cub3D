#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"

void	spawn_after_dementor(t_data *data, double total_factor, int random)
{
	total_factor += data->wolf_factor;
	if (random <= total_factor)
	{
		data->enemy = add_end_lst(init_enemy('<',
					(t_fcoo){.case_x = data->aff.x, .case_y = data->aff.y,
					.coo_y = 32, .coo_x = 32}, data, data->map.mini.deg),
				data->enemy, f_enemy);
		if (!data->enemy)
			f_exit(data, 1);
		check_enemy_can_escape(data, data->enemy);
		data->last_spawn = get_mtime();
	}
}

void	spawn_after_elem(t_data *data, double total_factor, int random)
{
	total_factor += data->dementor_factor;
	if (random <= total_factor)
	{
		data->enemy = add_end_lst(init_enemy('.',
					(t_fcoo){.case_x = data->aff.x, .case_y = data->aff.y,
					.coo_y = 32, .coo_x = 32}, data, data->map.mini.deg),
				data->enemy, f_enemy);
		if (!data->enemy)
			f_exit(data, 1);
		check_enemy_can_escape(data, data->enemy);
		data->last_spawn = get_mtime();
	}
	else
	{
		spawn_after_dementor(data, total_factor, random);
	}
}

void	spawn_after_spider(t_data *data, double total_factor, int random)
{
	if (random <= total_factor)
	{
		data->enemy = add_end_lst(init_enemy('>',
					(t_fcoo){.case_x = data->aff.x, .case_y = data->aff.y,
					.coo_y = 32, .coo_x = 32}, data, data->map.mini.deg),
				data->enemy, f_enemy);
		if (!data->enemy)
			f_exit(data, 1);
		check_enemy_can_escape(data, data->enemy);
		data->last_spawn = get_mtime();
	}
	else
	{
		spawn_after_elem(data, total_factor, random);
	}
}

void	spawn_enemy_utils(t_data *data, double total_factor, int random)
{
	if (random <= total_factor)
	{
		data->enemy = add_end_lst(init_enemy(',',
					(t_fcoo){.case_x = data->aff.x, .case_y = data->aff.y,
					.coo_y = 32, .coo_x = 32}, data, data->map.mini.deg),
				data->enemy, f_enemy);
		if (!data->enemy)
			f_exit(data, 1);
		check_enemy_can_escape(data, data->enemy);
		data->last_spawn = get_mtime();
	}
	else
	{
		total_factor += data->elem_factor;
		spawn_after_spider(data, total_factor, random);
	}
}

void	spawn_enemy(t_data *data, double total_factor, long long int cur)
{
	int	x;
	int	y;
	int	random;

	y = -1;
	while (data->map.tabmap[++y])
	{
		x = -1;
		while (data->map.tabmap[y][++x])
		{
			if (data->nb_enemy < MAX_CREATE_ENEMY
				&& data->map.tabmap[y][x] == '0')
			{
				random = rand() % 150;
				if (random <= data->player.xp * 2)
				{
					random = rand() % 100;
					total_factor = data->spider_factor;
					data->aff.x = x;
					data->aff.y = y;
					spawn_enemy_utils(data, total_factor, random);
				}
			}
			if (!(cur >= data->spawn_frame + data->last_spawn))
				return ;
		}
	}
}
