#include "struct.h"
#include "ft_printf.h"
#include "cub3d.h"
#include <math.h>

// void	move_up(t_map *map, t_mini *mini)
// {
// 	if (mini->player_coo.y == 0
// 		&& map->tabmap[map->player_coo->y - 1]
// 		[map->player_coo->x] != '1')
// 	{
// 		mini->player_coo.y = 63;
// 		map->player_coo->y--;
// 	}
// 	else if (mini->player_coo.y != 0)
// 		--mini->player_coo.y;
// }
// void	move_down(t_map *map, t_mini *mini)
// {
// 	if (mini->player_coo.y == 63
// 		&& map->tabmap[map->player_coo->y + 1]
// 		[map->player_coo->x] != '1')
// 	{
// 		mini->player_coo.y = 0;
// 		map->player_coo->y++;
// 	}
// 	else if (mini->player_coo.y != 63)
// 		++mini->player_coo.y;
// }
// void	move_right(t_map *map, t_mini *mini)
// {
// 	if (mini->player_coo.x == 63
// 		&& map->tabmap[map->player_coo->y]
// 		[map->player_coo->x + 1] != '1')
// 	{
// 		mini->player_coo.x = 0;
// 		map->player_coo->x++;
// 	}
// 	else if(mini->player_coo.x != 63)
// 		++mini->player_coo.x;
// }
// void	move_left(t_map *map, t_mini *mini)
// {
// 	if (mini->player_coo.x == 0
// 		&& map->tabmap[map->player_coo->y]
// 		[map->player_coo->x - 1] != '1')
// 	{
// 		mini->player_coo.x = 63;
// 		map->player_coo->x--;
// 	}
// 	else if(mini->player_coo.x != 0)
// 		--mini->player_coo.x;
// }

#include <stdio.h>

void	forward(t_map *map, t_mini *mini, int angle)
{
	double	dx;
	double	dy;

	dx = mini->player_coo.x - sin(mini->rad + angle * (M_PI / 180.0));
	dy = mini->player_coo.y - cos(mini->rad + angle * (M_PI / 180.0));
	dx = round(dx);
	dy = round(dy);
	if (dx < 0)
	{
		--map->player_coo->x;
		mini->player_coo.x = 64 + dx;
	}
	else if (dx >= 64)
	{
		++map->player_coo->x;
		mini->player_coo.x = dx - 64;
	}
	else
		mini->player_coo.x = dx;
	if (dy < 0)
	{
		--map->player_coo->y;
		mini->player_coo.y = 64 + dy;
	}
	else if (dy >= 64)
	{
		++map->player_coo->y;
		mini->player_coo.y = dy - 64;
	}
	else
		mini->player_coo.y = dy;
}

void	move(t_map *map, t_mini *mini, int keycode)
{
	if (keycode == KEY_W)
		forward(map, mini, 0);
	else if (keycode == KEY_S)
		forward(map, mini, 180);
	else if (keycode == KEY_D)
		forward(map, mini, 270);
	else if (keycode == KEY_A)
		forward(map, mini, 90);
}
