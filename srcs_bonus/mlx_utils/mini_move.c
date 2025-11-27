#include "cub3d_bonus.h"
#include <math.h>
#include "texture_bonus.h"
#include "player_bonus.h"

void	handle_map_status(t_map *map, t_data *data, t_mini *mini)
{
	if (data->status == FLOO_MAP)
		return ;
	if (map->tabmap[data->player.coo.case_y][data->player.coo.case_x] == 'F'
		&& (map->door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->is_floo_open == true))
	{
		if (map->door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->is_verti == true
			&& mini->cx == 0 && ((data->player.coo.coo_x <= 32.0
					&& mini->nx > 32.0) || (data->player.coo.coo_x >= 32.0
					&& mini->nx < 32.0)))
			data->status = FLOO_MAP;
		else if (map->door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->is_verti == false
			&& mini->cy == 0 && ((data->player.coo.coo_y <= 32.0
					&& mini->ny > 32.0) || (data->player.coo.coo_y >= 32.0
					&& mini->ny < 32.0)))
			data->status = FLOO_MAP;
		save_pos_before_floo(data);
	}
}

static void	handle_move_speed(t_mini *mini, t_data *data, t_map *map)
{
	mini->dx *= SPEED;
	mini->dy *= SPEED;
	mini->sdx *= SPEED;
	mini->sdy *= SPEED;
	if (data->player.damage.slow_frame_take > 0
		|| data->player.damage.slow_force_take > 0)
	{
		if (data->player.damage.slow_force_take > 100)
			data->player.damage.slow_force_take = 100;
		mini->dx *= (100 - data->player.damage.slow_force_take) / 100;
		mini->dy *= (100 - data->player.damage.slow_force_take) / 100;
		if (data->player.damage.slow_frame_take > 0)
			data->player.damage.slow_frame_take--;
		if (data->player.damage.slow_frame_take <= 0)
			data->player.damage.slow_force_take--;
	}
	recalc_x(data, mini, map);
	recalc_y(data, mini, map);
	movex(map, mini, data);
	movey(map, mini, data);
}

static void	save_last_pos(t_data *data, t_mini *mini)
{
	data->player.left_before.coo_x = data->player.left.coo_x;
	data->player.left_before.coo_y = data->player.left.coo_y;
	data->player.left_before.case_x = data->player.left.case_x;
	data->player.left_before.case_y = data->player.left.case_y;
	data->player.right_before.coo_x = data->player.right.coo_x;
	data->player.right_before.coo_y = data->player.right.coo_y;
	data->player.right_before.case_x = data->player.right.case_x;
	data->player.right_before.case_y = data->player.right.case_y;
	if (mini->ny != data->player.coo.coo_y)
	{
		data->player.coo.coo_y = mini->ny;
		data->player.coo.case_y += mini->cy;
		data->player.left_before.coo_y += mini->sdy;
	}
	if (mini->nx != data->player.coo.coo_x)
	{
		data->player.coo.coo_x = mini->nx;
		data->player.coo.case_x += mini->cx;
		data->player.left_before.coo_x += mini->sdx;
	}
	calc_left_point_player(data);
	calc_right_point_player(data);
	try_hit_player(data);
}

static void	calc_player_move(t_mini *mini, t_data *data, t_map *map)
{
	if (round(mini->sdy) == 0.0 && round(mini->sdx) == 0.0)
	{
		mini->sdy = 0;
		mini->sdx = 0;
	}
	else
		v_norm_sd(mini, data);
	if (round(mini->dy) == 0.0 && round(mini->dx) == 0.0)
	{
		mini->dy = 0;
		mini->dx = 0;
	}
	else
		v_norm_d(mini, data);
	handle_move_speed(mini, data, map);
	handle_map_status(map, data, mini);
	if (data->status == FLOO_MAP)
		return ;
	calc_left_point_player(data);
	calc_right_point_player(data);
	save_last_pos(data, mini);
}

void	handle_move(t_map *map, t_mini *mini, t_data *data)
{
	int	i;

	mini->dy = 0;
	mini->dx = 0;
	mini->sdy = 0;
	mini->sdx = 0;
	i = -1;
	if (data->player.life <= 0)
		return ;
	while (++i < KEYCODE_NB)
	{
		if (is_move_player(data, i))
		{
			calc_dx_dy(data, data->keycode[i], mini);
			if (mini->last_foot == MINI_LEFT)
				mini->last_foot = MINI_RIGHT;
			else
				mini->last_foot = MINI_LEFT;
			data->player_moved = true;
		}
	}
	calc_player_move(mini, data, map);
}
