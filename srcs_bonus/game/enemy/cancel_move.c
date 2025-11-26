#include "struct_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>

int	cond_cancel_move_x(t_enemy *enemy, t_data *data, int dx, t_mv_enemy coo)
{
	if (((enemy->center.coo_x + dx < 0 || enemy->center.coo_x + dx >= 64)
			&& (enemy->center.case_y < 0 || enemy->center.case_y
				> data->map.tabmap_height || coo.new_x < 0 || coo.new_x
				>= ft_strlen(data->map.tabmap[enemy->center.case_y])
				|| data->map.tabmap[enemy->center.case_y][coo.new_x]
			== '1' || data->map.tabmap[enemy->center.case_y]
			[coo.new_x] == ' '))
		|| ((enemy->right.coo_x + dx < 0 || enemy->right.coo_x + dx >= 64)
		&& (enemy->right.case_y < 0 || enemy->right.case_y >
			data->map.tabmap_height || coo.new_right_x < 0
			|| coo.new_right_x >= ft_strlen(data->map.tabmap[
				enemy->right.case_y]) || data->map.tabmap[enemy->right.case_y][
					coo.new_right_x] == '1' || data->map.tabmap[
						enemy->right.case_y][coo.new_right_x] == ' ' ))
		|| ((enemy->left.coo_x + dx < 0 || enemy->left.coo_x + dx >= 64)
		&& (enemy->left.case_y < 0 || enemy->left.case_y >
			data->map.tabmap_height || coo.new_left_x < 0
			|| coo.new_left_x >= ft_strlen(data->map.tabmap[
				enemy->left.case_y]) || data->map.tabmap[enemy->left.case_y][
					coo.new_left_x] == '1' || data->map.tabmap[
						enemy->left.case_y][coo.new_left_x] == ' ')))
		return (1);
	return (0);
}

int	cond_cancel_move_y(t_enemy *enemy, t_data *data, int dy, t_mv_enemy coo)
{
	if (((enemy->center.coo_y + dy < 0 || enemy->center.coo_y + dy >= 64)
			&& (coo.new_y < 0 || coo.new_y > data->map.tabmap_height
				|| coo.new_x < 0 || coo.new_x >= ft_strlen(
					data->map.tabmap[coo.new_y])
				|| data->map.tabmap[coo.new_y][coo.new_x] == '1'
			|| data->map.tabmap[coo.new_y][coo.new_x] == ' '))
			|| ((enemy->right.coo_y + dy < 0 || enemy->right.coo_y + dy
			>= 64) && (coo.new_right_y < 0 || coo.new_right_y
				> data->map.tabmap_height || coo.new_right_x < 0
				|| coo.new_right_x >= ft_strlen(data->map.tabmap[
					coo.new_right_y]) || data->map.tabmap[coo.new_right_y]
					[coo.new_right_x] == '1' || data->map.tabmap[
						coo.new_right_y][coo.new_right_x] == ' '))
		|| ((enemy->left.coo_y + dy < 0 || enemy->left.coo_y + dy >= 64)
		&& (coo.new_left_y < 0 || coo.new_left_y > data->map.tabmap_height
			|| coo.new_left_x < 0 || coo.new_left_x >= ft_strlen(
				data->map.tabmap[coo.new_left_y]) || data->map.tabmap[
					coo.new_left_y][coo.new_left_x] == '1' || data->map.tabmap[
						coo.new_left_y][coo.new_left_x] == ' ')))
	{
		return (1);
	}
	return (0);
}

void	cancel_move_x(t_enemy *enemy, t_data *data, int dx, t_mv_enemy *coo)
{
	if (cond_cancel_move_x(enemy, data, dx, *coo))
	{
		dx = 0;
		coo->new_x = enemy->center.case_x;
		coo->new_left_x = enemy->left.case_x;
		coo->new_right_x = enemy->right.case_x;
	}
	else if (enemy->center.coo_x + dx >= 64)
		enemy->center.coo_x = fmod(enemy->center.coo_x + dx, 64);
	else if (enemy->center.coo_x + dx < 0)
		enemy->center.coo_x = enemy->center.coo_x + dx + 64;
	else
		enemy->center.coo_x = enemy->center.coo_x + dx;
}

void	cancel_move_y(t_enemy *enemy, t_data *data, int dy, t_mv_enemy *coo)
{
	if (cond_cancel_move_y(enemy, data, dy, *coo))
	{
		dy = 0;
		coo->new_y = enemy->center.case_y;
		coo->new_left_y = enemy->left.case_y;
		coo->new_right_y = enemy->right.case_y;
	}
	else if (enemy->center.coo_y + dy >= 64)
		enemy->center.coo_y = fmod(enemy->center.coo_y + dy, 64);
	else if (enemy->center.coo_y + dy < 0)
		enemy->center.coo_y = enemy->center.coo_y + dy + 64;
	else
		enemy->center.coo_y = enemy->center.coo_y + dy;
}

void	cancel_move(t_data *data, t_enemy *enemy, int dy, int dx)
{
	t_mv_enemy	coo;

	(void)data;
	center_move_calc_case(&coo, enemy->center, dx, dy);
	right_move_calc_case(&coo, enemy->right, dx, dy);
	left_move_calc_case(&coo, enemy->left, dx, dy);
	coo.new_x = enemy->center.case_x + coo.cx;
	coo.new_y = enemy->center.case_y + coo.cy;
	coo.new_right_x = enemy->right.case_x + coo.right_cx;
	coo.new_right_y = enemy->right.case_y + coo.right_cy;
	coo.new_left_x = enemy->left.case_x + coo.left_cx;
	coo.new_left_y = enemy->left.case_y + coo.left_cy;
	cancel_move_x(enemy, data, dx, &coo);
	cancel_move_y(enemy, data, dy, &coo);
	enemy->center.case_x = coo.new_x;
	enemy->center.case_y = coo.new_y;
	if (coo.cy != 0 || coo.cx != 0)
		enemy->calc = true;
}
