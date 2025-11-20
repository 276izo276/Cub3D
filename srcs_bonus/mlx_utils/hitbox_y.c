
#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "texture_bonus.h"

static int	check_y_value(t_data *data, t_mini *mini, int y, int x)
{
	if ((y == -1 && x == -1 && data->player.coo.coo_y + mini->dy < 8
			&& data->player.coo.coo_x < 8)
		|| (y == 0 && x == -1 && data->player.coo.coo_x < 8)
		|| (y == 1 && x == -1 && data->player.coo.coo_x < 8
			&& data->player.coo.coo_y + mini->dy > 56)
		|| (y == -1 && x == 0 && data->player.coo.coo_y + mini->dy < 8)
		|| (y == 1 && x == 0 && data->player.coo.coo_y + mini->dy > 56)
		|| (y == -1 && x == 1 && data->player.coo.coo_y + mini->dy < 8
			&& data->player.coo.coo_x > 56)
		|| (y == 0 && x == 1 && data->player.coo.coo_x > 56)
		|| (y == 1 && x == 1 && data->player.coo.coo_x > 56
			&& data->player.coo.coo_y + mini->dy > 56))
		return (1);
	return (0);
}

void	hit_box_y_floo(t_mini *mini, t_data *data)
{
	if ((mini->cy == 0 && mini->ny >= 22 && mini->ny <= 42)
		|| (mini->cy == 0 && mini->ny > 32 && data->player.coo.coo_y < 32)
		|| (mini->cy == 0 && mini->ny < 32 && data->player.coo.coo_y > 32))
	{
		if (data->map.door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->is_floo_open == false
			&& abs_value(32 - data->player.coo.coo_y) > abs_value(32
				- mini->ny))
			mini->ny = data->player.coo.coo_y;
		else if ((data->player.coo.coo_y < 22
				|| data->player.coo.coo_y > 42) && (mini->nx < 16
				|| mini->nx > 48))
			mini->ny = data->player.coo.coo_y;
		else if (data->player.coo.coo_y >= 22
			&& data->player.coo.coo_y <= 42 && (mini->nx < 16
				|| mini->nx > 48))
			mini->nx = data->player.coo.coo_x;
	}
}

int	hit_box_y_wall(t_data *data, t_map *map, t_mini *mini)
{
	int	x;
	int	y;

	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			if (map->tabmap[data->player.coo.case_y + y]
				[data->player.coo.case_x + x] == '1')
				if (check_y_value(data, mini, y, x))
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static void	hit_box_door(t_mini *mini, t_data *data)
{
	if ((mini->cy == 0 && mini->ny >= 22 && mini->ny <= 42)
		|| (mini->cy == 0 && mini->ny > 32 && data->player.coo.coo_y < 32)
		|| (mini->cy == 0 && mini->ny < 32 && data->player.coo.coo_y > 32))
	{
		if (data->map.door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->pos <= 50
			&& abs_value(32 - data->player.coo.coo_y) > abs_value(32
				- mini->ny))
			mini->ny = data->player.coo.coo_y;
		else if ((data->player.coo.coo_y < 22
				|| data->player.coo.coo_y > 42)
			&& (mini->nx < 16 || mini->nx > 48))
			mini->ny = data->player.coo.coo_y;
		else if (data->player.coo.coo_y >= 22
			&& data->player.coo.coo_y <= 42
			&& (mini->nx < 16 || mini->nx > 48))
			mini->nx = data->player.coo.coo_x;
	}
}

void	movey(t_map *map, t_mini *mini, t_data *data)
{
	if (hit_box_y_wall(data, map, mini))
		mini->ny = data->player.coo.coo_y;
	if (data->map.tabmap[data->player.coo.case_y]
		[data->player.coo.case_x] == 'D'
		&& data->map.door_map[data->player.coo.case_y]
		[data->player.coo.case_x]->is_verti == false)
	{
		hit_box_door(mini, data);
	}
	if (data->map.tabmap[data->player.coo.case_y]
		[data->player.coo.case_x] == 'F'
		&& data->map.door_map[data->player.coo.case_y]
		[data->player.coo.case_x]->is_verti == false)
		hit_box_y_floo(mini, data);
}
