#include "struct_bonus.h"
#include "utils_bonus.h"

static void	check_dir_door(t_data *data, int i, int j)
{
	double	posx_display;

	posx_display = 0;
	if (data->ray[i].doors[j]->dir == NORTH || data->ray[i].doors[j]->dir == SOUTH)
	{
		posx_display = data->ray[i].doors[j]->coo_x / 64;
		if (data->ray[i].doors[j]->dir == NORTH)
			posx_display = 1 - posx_display;
	}
	else if (data->ray[i].doors[j]->dir == WEST || data->ray[i].doors[j]->dir == EAST)
	{
		posx_display = data->ray[i].doors[j]->coo_y / 64;
		if (data->ray[i].doors[j]->dir == EAST)
			posx_display = 1 - posx_display;
	}
	posx_display -= floor(posx_display);
	data->ray[i].doors[j]->texture_coo.x = (int)(posx_display * data->map.door->width);
	if (data->ray[i].doors[j]->texture_coo.x < 0)
		data->ray[i].doors[j]->texture_coo.x = 0;
	if (data->ray[i].doors[j]->texture_coo.x >= data->map.door->width)
		data->ray[i].doors[j]->texture_coo.x = data->map.door->width - 1;
}

void	display_item(t_data *data, int i)
{
	double	dist_max_enemy;
	double	dist_max_door;
	int	j;
	int	type;
	
	dist_max_enemy = 1;
	dist_max_door = 1;
	j = 0;
	while (j < data->nb_enemy)
	{
		if (data->ray[i].enemys[j]->dist_enemy < data->ray[i].dist_wall)
			data->ray[i].enemys[j]->print = true;
		else
			ft_bzero(data->ray[i].enemys[j], sizeof(t_hit_enemy));
		j++;
	}
	while (dist_max_enemy != 0 || dist_max_door != 0)
	{
		dist_max_enemy = 0;
		dist_max_door = 0;
		j = 0;
		while (j < data->nb_door)
		{
			if (dist_max_door < data->ray[i].doors[j]->dist_door
				&& data->ray[i].doors[j]->print == true)
			{
				dist_max_door = data->ray[i].doors[j]->dist_door;
			}
			j++;
		}
		j = 0;
		while (j < data->nb_enemy)
		{
			if (dist_max_enemy < data->ray[i].enemys[j]->dist_enemy
				&& data->ray[i].enemys[j]->print == true)
			{
				dist_max_enemy = data->ray[i].enemys[j]->dist_enemy;
			}
			j++;
		}
		if (dist_max_door == 0 && dist_max_enemy == 0)
			continue ;
		if (dist_max_door > dist_max_enemy)
			type = 0;
		else
			type = 1;
		if (type == 0)
		{
			j = -1;
			while (++j < data->nb_door)
				if (data->ray[i].doors[j]->dist_door == dist_max_door)
					break ;
			check_dir_door(data, i, j);
			ft_bzero(data->ray[i].doors[j], sizeof(t_hit_door));
			data->ray[i].doors[j]->print = false;
		}
		else if (type == 1)
		{
			ft_bzero(data->ray[i].doors[j], sizeof(t_hit_enemy));
			data->ray[i].enemys[j]->print = false;
		}
	}
}