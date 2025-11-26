#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>
#include "enemy_bonus.h"

void	calc_dist_wall(t_ray *ray)
{
	ray->dist_wall = sqrt(((ray->case_y - ray->start_case_y) * 64.0
				+ (ray->coo_y - ray->start_coo_y)) * ((ray->case_y
					- ray->start_case_y) * 64.0 + (ray->coo_y
					- ray->start_coo_y)) + ((ray->case_x - ray->start_case_x)
				* 64.0 + (ray->coo_x - ray->start_coo_x)) * ((ray->case_x
					- ray->start_case_x) * 64.0 + (ray->coo_x
					- ray->start_coo_x)));
}

void	calc_dist_target(t_enemy *enemy, t_enemy *elem, t_ray *ray)
{
	enemy->dist_target = sqrt(((elem->center.case_y - ray->start_case_y) * 64.0
				+ (elem->center.coo_y - ray->start_coo_y))
			* ((elem->center.case_y - ray->start_case_y) * 64.0
				+ (elem->center.coo_y - ray->start_coo_y))
			+ ((elem->center.case_x - ray->start_case_x) * 64.0
				+ (elem->center.coo_x - ray->start_coo_x))
			* ((elem->center.case_x - ray->start_case_x) * 64.0
				+ (elem->center.coo_x - ray->start_coo_x)));
}

void	recalc_path(t_enemy *enemy, t_enemy_vision *visu, t_data *data)
{
	if (enemy->recalc_path == 100)
	{
		f_way(enemy);
		enemy->goal.case_x = visu->coo.case_x;
		enemy->goal.case_y = visu->coo.case_y;
		enemy->goal.coo_y = visu->coo.coo_y;
		enemy->goal.coo_x = visu->coo.coo_x;
		pathfinder(data, enemy);
		calc_in_cell_path(data, enemy);
		enemy->calc = true;
	}
}

void	path_move_enemy(t_enemy *enemy, t_data *data, double *dx, double *dy)
{
	if (!(enemy->dist_target < enemy->dist_stop && enemy->way
			&& enemy->dist_target != -1))
	{
		calc_dx_dy_enemy(dy, dx, enemy->rad);
		*dy *= enemy->speed;
		*dx *= enemy->speed;
		if (enemy->damage.slow_frame_take > 0
			|| enemy->damage.slow_force_take > 0)
			apply_slow_enemy(enemy, dx, dy);
		if (enemy->way && are_double_close(enemy->center.coo_x,
				enemy->goal.coo_x) && are_double_close(enemy->center.coo_y,
				enemy->goal.coo_y) && enemy->center.case_x == enemy->goal.case_x
			&& enemy->center.case_y == enemy->goal.case_y)
		{
			f_case(enemy->way);
			enemy->way = NULL;
			enemy->wait = 0;
			// enemy->calc = true;
		}
		else
			move_center_point(data, enemy, dy, dx);
	}
}

void	remove_child_path(t_enemy *enemy)
{
	t_case	*tmp;

	if (enemy->way->child)
	{
		enemy->way->child->parent = NULL;
		tmp = enemy->way;
		enemy->way = enemy->way->child;
		enemy->center.case_x = enemy->way->coo.case_x;
		enemy->center.case_y = enemy->way->coo.case_y;
		f_case(tmp);
		enemy->calc = true;
	}
	else
	{
		f_case(enemy->way);
		enemy->way = NULL;
		enemy->wait = 0;
		enemy->calc = true;
	}
}
