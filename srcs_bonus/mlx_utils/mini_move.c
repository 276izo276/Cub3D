#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>

static void	move_x(t_data *data, t_map *map, t_mini *mini)
{
	mini->dx = mini->player_coo.x - mini->dx * SPEED;
	if (mini->dx < 0)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x - 1] == '1')
			return ;
		--map->player_coo->x;
		mini->player_coo.x = 64 + mini->dx;
	}
	else if (mini->dx >= 64)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x + 1] == '1')
			return ;
		++map->player_coo->x;
		mini->player_coo.x = mini->dx - 64;
	}
	else
	{
		if (data->map.tabmap[map->player_coo->y][map->player_coo->x] == 'D'
			&& data->map.door_map[map->player_coo->y][map->player_coo->x]->is_verti == true
			&& data->map.door_map[map->player_coo->y][map->player_coo->x]->pos <= 50)
			{
				if ((mini->dx >= 22 && mini->dx <= 42 && abs_value(32 - mini->player_coo.y) > abs_value(32 - mini->dx))
				|| (mini->dx > 32 && mini->player_coo.y < 32) || (mini->dx < 32 && mini->player_coo.y > 32))
					return ;
			}
		mini->player_coo.x = mini->dx;
	}
}

static void	move_y(t_data *data, t_map *map, t_mini *mini)
{
	mini->dy = mini->player_coo.y - mini->dy * SPEED;
	if (mini->dy < 0)
	{
		if (map->tabmap[map->player_coo->y - 1][map->player_coo->x] == '1')
			return ;
		--map->player_coo->y;
		mini->player_coo.y = 64 + mini->dy;
	}
	else if (mini->dy >= 64)
	{
		if (map->tabmap[map->player_coo->y + 1][map->player_coo->x] == '1')
			return ;
		++map->player_coo->y;
		mini->player_coo.y = mini->dy - 64;
	}
	else
	{
		if (data->map.tabmap[map->player_coo->y][map->player_coo->x] == 'D'
			&& data->map.door_map[map->player_coo->y][map->player_coo->x]->is_verti == false
			&& data->map.door_map[map->player_coo->y][map->player_coo->x]->pos <= 50)
			{
				if ((mini->dy >= 22 && mini->dy <= 42 && abs_value(32 - mini->player_coo.y) > abs_value(32 - mini->dy))
				|| (mini->dy > 32 && mini->player_coo.y < 32) || (mini->dy < 32 && mini->player_coo.y > 32))
					return ;
			}
		mini->player_coo.y = mini->dy;
	}
}

void	v_norm(t_mini *mini, t_data *data)
{
	double	v_normalize;
	int		i;

	v_normalize = sqrt(mini->dx * mini->dx + mini->dy * mini->dy);
	mini->dy = mini->dy / v_normalize;
	mini->dx = mini->dx / v_normalize;
	i = -1;
	while (++i < KEYCODE_NB)
	{
		if (data->keycode[i] == KEY_S)
		{
			mini->dy *= .6;
			mini->dx *= .6;
		}
		else if (data->keycode[i] == KEY_A || data->keycode[i] == KEY_D)
		{
			mini->dy *= .9;
			mini->dx *= .9;
		}
		if (data->keycode[i] == KEY_SHIFT)
		{
			mini->dy *= 1.6;
			mini->dx *= 1.6;
		}
	}
}

static void	calc_dx_dy(t_data *data, int keycode, t_mini *mini)
{
	int	angle;

	angle = 0;
	if (keycode == KEY_W)
		angle = 0;
	else if (keycode == KEY_S)
		angle = 180;
	else if (keycode == KEY_D)
		angle = 270;
	else if (keycode == KEY_A)
		angle = 90;
	mini->dx += sin(mini->rad + angle * (M_PI / 180.0))
		* (double)(FPM / data->frame_move);
	mini->dy += cos(mini->rad + angle * (M_PI / 180.0))
		* (double)(FPM / data->frame_move);
}

void	handle_move(t_map *map, t_mini *mini, t_data *data)
{
	int	i;

	mini->dy = 0;
	mini->dx = 0;
	i = 0;
	while (i < KEYCODE_NB)
	{
		if (is_move_player(data, i))
		{
			calc_dx_dy(data, data->keycode[i], mini);
		}
		i++;
	}
	if (round(mini->dy) == 0.0 && round(mini->dx) == 0.0)
	{
		mini->dy = 0;
		mini->dx = 0;
	}
	else
		v_norm(mini, data);
	move_x(data, map, mini);
	move_y(data, map, mini);
}
