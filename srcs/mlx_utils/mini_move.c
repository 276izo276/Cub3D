#include "cub3d.h"
#include "ft_printf.h"
#include "struct.h"
#include <math.h>

static void	move_x(t_map *map, t_mini *mini, int angle, t_data *data)
{
	double	dx;

	dx = mini->player_coo.x - sin(mini->rad + angle * (M_PI / 180.0))
		* mini->speed * (double)(FPM / data->frame_move);
	if (dx < 0)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x - 1] == '1')
			return ;
		--map->player_coo->x;
		mini->player_coo.x = 64 + dx;
	}
	else if (dx >= 64)
	{
		if (map->tabmap[map->player_coo->y][map->player_coo->x + 1] == '1')
			return ;
		++map->player_coo->x;
		mini->player_coo.x = dx - 64;
	}
	else if ((map->tabmap[map->player_coo->y][map->player_coo->x + 1] == '1'
		&& dx == 62) || (map->tabmap[map->player_coo->y][map->player_coo->x
			- 1] == '1' && dx == 1))
		return ;
	else
		mini->player_coo.x = dx;
}

static void	move_y(t_map *map, t_mini *mini, int angle, t_data *data)
{
	double	dy;

	dy = mini->player_coo.y - cos(mini->rad + angle * (M_PI / 180.0))
		* mini->speed * (double)(FPM / data->frame_move);
	if (dy < 0)
	{
		if (map->tabmap[map->player_coo->y - 1][map->player_coo->x] == '1')
			return ;
		--map->player_coo->y;
		mini->player_coo.y = 64 + dy;
	}
	else if (dy >= 64)
	{
		if (map->tabmap[map->player_coo->y + 1][map->player_coo->x] == '1')
			return ;
		++map->player_coo->y;
		mini->player_coo.y = dy - 64;
	}
	else if ((map->tabmap[map->player_coo->y + 1][map->player_coo->x] == '1'
		&& dy == 62) || (map->tabmap[map->player_coo->y
			- 1][map->player_coo->x] == '1' && dy == 1))
		return ;
	else
		mini->player_coo.y = dy;
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
	move_x(map, mini, angle, data);
	move_y(map, mini, angle, data);
	if (keycode == KEY_S)
		mini->speed += 0.2;
}
