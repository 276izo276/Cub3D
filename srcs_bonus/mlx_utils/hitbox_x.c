/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:52:52 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:52:53 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils_bonus.h"

static int	check_x_value(t_data *data, t_mini *mini, int y, int x)
{
	if ((y == -1 && x == -1 && data->player.coo.coo_y < 8
			&& data->player.coo.coo_x + mini->dx < 8)
		|| (y == 0 && x == -1 && data->player.coo.coo_x + mini->dx < 8)
		|| (y == 1 && x == -1 && data->player.coo.coo_x + mini->dx < 8
			&& data->player.coo.coo_y > 56)
		|| (y == -1 && x == 0 && data->player.coo.coo_y < 8)
		|| (y == 1 && x == 0 && data->player.coo.coo_y > 56)
		|| (y == -1 && x == 1 && data->player.coo.coo_y < 8
			&& data->player.coo.coo_x + mini->dx > 56)
		|| (y == 0 && x == 1 && data->player.coo.coo_x + mini->dx > 56)
		|| (y == 1 && x == 1 && data->player.coo.coo_x + mini->dx > 56
			&& data->player.coo.coo_y > 56))
		return (1);
	return (0);
}

int	hit_box_x_wall(t_data *data, t_map *map, t_mini *mini)
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
				if (check_x_value(data, mini, y, x))
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

void	hit_box_x_floo(t_mini *mini, t_data *data)
{
	if ((mini->cx == 0 && mini->nx >= 22 && mini->nx <= 42)
		|| (mini->cx == 0 && mini->nx > 32 && data->player.coo.coo_x < 32)
		|| (mini->cx == 0 && mini->nx < 32 && data->player.coo.coo_x > 32))
	{
		if (data->map.door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->is_floo_open == false
			&& abs_value(32 - data->player.coo.coo_x) > abs_value(32
				- mini->nx))
			mini->nx = data->player.coo.coo_x;
		else if ((data->player.coo.coo_x < 22 || data->player.coo.coo_x > 42)
			&& (mini->ny < 16 || mini->ny > 48))
			mini->nx = data->player.coo.coo_x;
		else if (data->player.coo.coo_x >= 22 && data->player.coo.coo_x <= 42
			&& (mini->ny < 16 || mini->ny > 48))
			mini->ny = data->player.coo.coo_y;
	}
}

static void	hit_door(t_mini *mini, t_data *data)
{
	if ((mini->cx == 0 && mini->nx >= 22 && mini->nx <= 42)
		|| (mini->cx == 0 && mini->nx > 32 && data->player.coo.coo_x < 32)
		|| (mini->cx == 0 && mini->nx < 32 && data->player.coo.coo_x > 32))
	{
		if (data->map.door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->pos <= 50 && abs_value(32
				- data->player.coo.coo_x) > abs_value(32 - mini->nx))
			mini->nx = data->player.coo.coo_x;
		else if ((data->player.coo.coo_x < 22
				|| data->player.coo.coo_x > 42)
			&& (mini->ny < 16 || mini->ny > 48))
			mini->nx = data->player.coo.coo_x;
		else if (data->player.coo.coo_x >= 22
			&& data->player.coo.coo_x <= 42
			&& (mini->ny < 16 || mini->ny > 48))
			mini->ny = data->player.coo.coo_y;
	}
}

void	movex(t_map *map, t_mini *mini, t_data *data)
{
	if (hit_box_x_wall(data, map, mini))
		mini->nx = data->player.coo.coo_x;
	if (data->map.tabmap[data->player.coo.case_y]
		[data->player.coo.case_x] == 'D'
		&& data->map.door_map[data->player.coo.case_y]
		[data->player.coo.case_x]->is_verti == true)
	{
		hit_door(mini, data);
	}
	if (data->map.tabmap[data->player.coo.case_y]
		[data->player.coo.case_x] == 'F'
		&& data->map.door_map[data->player.coo.case_y]
		[data->player.coo.case_x]->is_verti == true)
		hit_box_x_floo(mini, data);
}
