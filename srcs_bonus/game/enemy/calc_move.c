#include "struct_bonus.h"

void	center_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy)
{
	if (enemy.coo_x + dx < 0)
		coo->cx = -1;
	else if (enemy.coo_x + dx >= 64)
		coo->cx = 1;
	else
		coo->cx = 0;
	if (enemy.coo_y + dy < 0)
		coo->cy = -1;
	else if (enemy.coo_y + dy >= 64)
		coo->cy = 1;
	else
		coo->cy = 0;
}

void	right_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy)
{
	if (enemy.coo_x + dx < 0)
		coo->right_cx = -1;
	else if (enemy.coo_x + dx >= 64)
		coo->right_cx = 1;
	else
		coo->right_cx = 0;
	if (enemy.coo_y + dy < 0)
		coo->right_cy = -1;
	else if (enemy.coo_y + dy >= 64)
		coo->right_cy = 1;
	else
		coo->right_cy = 0;
}

void	left_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy)
{
	if (enemy.coo_x + dx < 0)
		coo->left_cx = -1;
	else if (enemy.coo_x + dx >= 64)
		coo->left_cx = 1;
	else
		coo->left_cx = 0;
	if (enemy.coo_y + dy < 0)
		coo->left_cy = -1;
	else if (enemy.coo_y + dy >= 64)
		coo->left_cy = 1;
	else
		coo->left_cy = 0;
}