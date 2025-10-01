#include "struct_bonus.h"
#include "utils_bonus.h"
#include "enemy_bonus.h"
#include "cub3d_bonus.h"

#include <stdio.h>

t_enemy	*init_enemy(char c, int y, int x, t_data *data)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	ft_bzero(enemy, sizeof(t_enemy));
	enemy->type = c;
	enemy->center.case_x = x;
	enemy->center.case_y = y;
	enemy->center.coo_x = 32;
	enemy->center.coo_y = 32;
	enemy->speed = 3;
	enemy->radius = 6;
	enemy->deg = 90;
	enemy->damage = 5;
	enemy->damage = 2;
	enemy->rad = enemy->deg * (M_PI / 180);
	enemy->calc = true;
	calc_left_point(enemy);
	calc_right_point(enemy);
	(void)data;
	return (enemy);
}

t_case	*init_case(int h_cost, int r_cost, int dir[2], t_case *parent)
{
	t_case	*cel;

	cel = malloc(sizeof(t_case));
	if (!cel)
		return (cel);
	ft_bzero(cel, (sizeof(t_case)));
	cel->parent = parent;
	cel->case_x = dir[1];
	cel->case_y = dir[0];
	cel->h_cost = h_cost;
	cel->r_cost = r_cost;
	cel->t_cost = r_cost + h_cost;
	return (cel);
}
