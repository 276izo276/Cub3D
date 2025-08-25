#include "cub3d.h"
#include <math.h>

static void	move_x(t_map *map, t_mini *mini)
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
	else if ((map->tabmap[map->player_coo->y][map->player_coo->x + 1] == '1'
		&& mini->dx == 62) || (map->tabmap[map->player_coo->y][map->player_coo->x
			- 1] == '1' && mini->dx == 1))
		return ;
	else
		mini->player_coo.x = mini->dx;
}

static void	move_y(t_map *map, t_mini *mini)
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
	else if ((map->tabmap[map->player_coo->y + 1][map->player_coo->x] == '1'
		&& mini->dy == 62) || (map->tabmap[map->player_coo->y
			- 1][map->player_coo->x] == '1' && mini->dy == 1))
		return ;
	else
		mini->player_coo.y = mini->dy;
}

#include <stdio.h>

void	v_norm(t_mini *mini)
{
	double v_normalize;

	v_normalize = sqrt(mini->dx * mini->dx + mini->dy * mini->dy);
	mini->dy = mini->dy / v_normalize;
	mini->dx = mini->dx / v_normalize;
}

void	calc_dy(t_data *data, t_mini *mini)
{
	int	i;
	int	angle;
	int	speed;

	speed = 1;
	angle = 90;
	i = -1;
	while (++i < 100)
	{
		if (data->keycode[i] == KEY_W)
			angle = 0;
		else if (data->keycode[i] == KEY_S)
		{
			speed -= 0.2;
			angle = 180;
		}
	}
	mini->dy = cos(mini->rad + angle * (M_PI / 180.0))
		* mini->speed * (double)(FPM / data->frame_move);
}

void	calc_dx(t_data *data, t_mini *mini)
{
	int	i;
	int	angle;
	int	speed;

	speed = 1;
	angle = 0;
	i = -1;
	while (++i < 100)
	{
		if (data->keycode[i] == KEY_D)
			angle = 270;
		else if (data->keycode[i] == KEY_A)
			angle = 90;
	}
	mini->dx = sin(mini->rad + angle * (M_PI / 180.0))
		* mini->speed * (double)(FPM / data->frame_move);
}

void	handle_move(t_map *map, t_mini *mini, t_data *data)
{
	calc_dx(data, mini);
	calc_dy(data, mini);
	v_norm(mini);
	move_x(map, mini);
	move_y(map, mini);
}
