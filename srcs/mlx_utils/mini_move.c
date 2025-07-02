#include "struct.h"

void	move_up(t_map *map, t_mini *mini)
{
	if (mini->player_coo->y == 0
		&& map->tabmap[map->player_coo->y - 1]
		[map->player_coo->x] != '1')
		mini->player_coo->y = 63;
	else
		--mini->player_coo->y;
}
void	move_down(t_map *map, t_mini *mini)
{
	if (mini->player_coo->y == 63
		&& map->tabmap[map->player_coo->y + 1]
		[map->player_coo->x] != '1')
		mini->player_coo->y = 0;
	else
		++mini->player_coo->y;
}
void	move_right(t_map *map, t_mini *mini)
{
	if (mini->player_coo->x == 63
		&& map->tabmap[map->player_coo->y]
		[map->player_coo->x + 1] != '1')
		mini->player_coo->x = 0;
	else
		++mini->player_coo->x;
}
void	move_left(t_map *map, t_mini *mini)
{
	if (mini->player_coo->x == 0
		&& map->tabmap[map->player_coo->y]
		[map->player_coo->x - 1] != '1')
		mini->player_coo->x = 63;
	else
		--mini->player_coo->x;
}
