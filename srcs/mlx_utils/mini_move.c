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

// #include <stdio.h>

void	calc_dy_dx(t_mini *mini, int angle, t_data *data)
{
	double v_normalize;

	mini->dy = cos(mini->rad + angle * (M_PI / 180.0))
		* mini->speed * (double)(FPM / data->frame_move);
	mini->dx = sin(mini->rad + angle * (M_PI / 180.0))
		* mini->speed * (double)(FPM / data->frame_move);
	v_normalize = sqrt(mini->dx * mini->dx + mini->dy * mini->dy);
	mini->dy = mini->dy / v_normalize;
	mini->dx = mini->dx / v_normalize;
	// printf("norm >>%lf    dy>>%lf     dx>>%lf\n",v_normalize,mini->dy / v_normalize,mini->dx / v_normalize);
	// printf("vector >>> %lf\n",sqrt(mini->dx * mini->dx + mini->dy * mini->dy));
}

void	handle_move(t_map *map, t_mini *mini, int keycode, t_data *data)
{
	int	angle;

	angle = 0;
	if (keycode == KEY_W)
		angle = 0;
	else if (keycode == KEY_S)
	{
		mini->speed -= 0.2;
		angle = 180;
	}
	else if (keycode == KEY_D)
		angle = 270;
	else if (keycode == KEY_A)
		angle = 90;
	calc_dy_dx(mini, angle, data);
	move_x(map, mini);
	move_y(map, mini);
	if (keycode == KEY_S)
		mini->speed += 0.2;
}
