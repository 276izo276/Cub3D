#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "struct_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include <stdio.h>

void	calc_dx_dy_enemy(double *dy, double *dx, double rad)
{
	double	v_normalize;

	*dx = sin(rad);
	*dy = cos(rad);
	if (round(*dy) == 0.0 && round(*dx) == 0.0)
	{
		*dy = 0;
		*dx = 0;
	}
	else
	{
		v_normalize = sqrt(*dx * *dx + *dy * *dy);
		*dy = *dy / v_normalize;
		*dx = *dx / v_normalize;
	}
}

void	set_before_point_enemy(t_enemy *enemy, t_data *data)
{
	calc_left_and_right_point(enemy, data);
	enemy->center_before.coo_x = enemy->center.coo_x;
	enemy->center_before.coo_y = enemy->center.coo_y;
	enemy->center_before.case_x = enemy->center.case_x;
	enemy->center_before.case_y = enemy->center.case_y;
	enemy->left_before.coo_x = enemy->left.coo_x;
	enemy->left_before.coo_y = enemy->left.coo_y;
	enemy->left_before.case_x = enemy->left.case_x;
	enemy->left_before.case_y = enemy->left.case_y;
	enemy->right_before.coo_x = enemy->right.coo_x;
	enemy->right_before.coo_y = enemy->right.coo_y;
	enemy->right_before.case_x = enemy->right.case_x;
	enemy->right_before.case_y = enemy->right.case_y;
}

void	reverse_hit_pos(t_enemy *enemy, t_item *item)
{
	double	deg;
	double	rad;
	double	dx;
	double	dy;
	double	v_normalize;

	calc_deg(&enemy->center_before, &enemy->center, &rad, &deg);
	rad = (deg + 180) * (M_PI / 180);
	dx = sin(rad);
	dy = cos(rad);
	if (round(dy) == 0.0 && round(dx) == 0.0)
	{
		dy = 0;
		dx = 0;
	}
	else
	{
		v_normalize = sqrt(dx * dx + dy * dy);
		dy = dy / v_normalize;
		dx = dx / v_normalize;
	}
	dx *= 2000;
	dy *= 2000;
	item->damage.hit.coo_x += dx;
	item->damage.hit.coo_y += dy;
}

void	move_more_hit_pos(t_enemy *enemy, t_item *item)
{
	double	deg;
	double	rad;
	double	dx;
	double	dy;
	double	v_normalize;

	calc_deg(&enemy->center_before, &enemy->center, &rad, &deg);
	dx = sin(rad);
	dy = cos(rad);
	if (round(dy) == 0.0 && round(dx) == 0.0)
	{
		dy = 0;
		dx = 0;
	}
	else
	{
		v_normalize = sqrt(dx * dx + dy * dy);
		dy = dy / v_normalize;
		dx = dx / v_normalize;
	}
	dx *= 2000;
	dy *= 2000;
	item->damage.hit.coo_x += dx;
	item->damage.hit.coo_y += dy;
}

int	calc_if_hit(t_hitray *ray, t_lst **lst, t_item *item, t_enemy *elem)
{
	t_lst	*next;

	if (ray->hit == true)
	{
		if (item->damage.repulso_force_do > 0 && !ray->type)
		{
			reverse_hit_pos(elem, item);
		}
		else
			move_more_hit_pos(elem, item);
		apply_damage(&elem->damage, &item->damage);
		next = (*lst)->next;
		if (!((!item->categ && (item->type == EXPECTO_PATRONUM
						|| item->type == VENTUS)) || (item->type == BH
					&& item->categ)))
		{
			ray->data->item = remove_elem_lst(*lst);
			f_elem_lst(*lst);
		}
		*lst = next;
		return (1);
	}
	return (0);
}

int	calc_scal_hit_case(t_hitray *ray, t_lst **lst, t_enemy *elem, t_item *item)
{
	ray->ax = elem->left.case_x * 64 + elem->left.coo_x;
	ray->ay = elem->left.case_y * 64 + elem->left.coo_y;
	ray->bx = elem->right.case_x * 64 + elem->right.coo_x;
	ray->by = elem->right.case_y * 64 + elem->right.coo_y;
	ray->cx = elem->left_before.case_x * 64 + elem->left_before.coo_x;
	ray->cy = elem->left_before.case_y * 64 + elem->left_before.coo_y;
	ray->dx = item->left.case_x * 64 + item->left.coo_x;
	ray->dy = item->left.case_y * 64 + item->left.coo_y;
	calc_scal(ray);
	if (calc_if_hit(ray, lst, item, elem))
		return (1);
	ray->dx = item->center.case_x * 64 + item->center.coo_x;
	ray->dy = item->center.case_y * 64 + item->center.coo_y;
	calc_scal(ray);
	if (calc_if_hit(ray, lst, item, elem))
		return (1);
	ray->dx = item->right.case_x * 64 + item->right.coo_x;
	ray->dy = item->right.case_y * 64 + item->right.coo_y;
	calc_scal(ray);
	if (calc_if_hit(ray, lst, item, elem))
		return (1);
	return (0);
}

int	calc_delta_hit_seg(t_hitray *ray, t_lst **lst, t_enemy *elem, t_item *item)
{
	ray->ax = elem->center.case_x * 64 + elem->center.coo_x;
	ray->ay = elem->center.case_y * 64 + elem->center.coo_y;
	ray->bx = elem->center_before.case_x * 64 + elem->center_before.coo_x;
	ray->by = elem->center_before.case_y * 64 + elem->center_before.coo_y;
	ray->cx = item->left.case_x * 64 + item->left.coo_x;
	ray->cy = item->left.case_y * 64 + item->left.coo_y;
	ray->dx = item->center.case_x * 64 + item->center.coo_x;
	ray->dy = item->center.case_y * 64 + item->center.coo_y;
	calc_delta(ray);
	if (calc_if_hit(ray, lst, item, elem))
		return (1);
	ray->cx = item->center.case_x * 64 + item->center.coo_x;
	ray->cy = item->center.case_y * 64 + item->center.coo_y;
	ray->dx = item->right.case_x * 64 + item->right.coo_x;
	ray->dy = item->right.case_y * 64 + item->right.coo_y;
	calc_delta(ray);
	if (calc_if_hit(ray, lst, item, elem))
		return (1);
	return (0);
}

int	need_skip_enenmy_hit(t_item *item, t_enemy *elem)
{
	if (((item->type == POPO_HEAL || item->type == POPO_SHIELD
				|| item->type == POPO_FLOO || item->type == POPO_INVI
				|| item->type == ANIM_DEATH || item->type == WOLF_WAND
				|| item->type == ELEM_WAND || item->type == SPIDER_WAND
				|| item->type == DEMENTOR_WAND || item->type == PILLAR
				|| item->type == PORTKEY) && item->categ)
		|| (elem->type != DEMENTOR && item->type == EXPECTO_PATRONUM
			&& !item->categ))
	{
		return (1);
	}
	return (0);
}

void	try_hit_enemys(t_enemy *elem, t_data *data, int type)
{
	t_item		*item;
	t_lst		*lst;
	t_hitray	ray;

	ray.data = data;
	ray.type = type;
	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		item = lst->dt;
		if (need_skip_enenmy_hit(item, elem))
		{
			lst = lst->next;
			continue ;
		}
		if (calc_scal_hit_case(&ray, &lst, elem, item))
			continue ;
		if (calc_delta_hit_seg(&ray, &lst, elem, item))
			continue ;
		lst = lst->next;
	}
}

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

int	repulso_move_enemy(t_enemy *enemy, t_data *data)
{
	double	dy;
	double	dx;
	double	deg;
	double	rad;

	if (enemy->damage.repulso_force_take > 0)
	{
		calc_deg(&enemy->center, &enemy->damage.hit, &rad, &deg);
		calc_dx_dy_enemy(&dy, &dx, rad);
		f_way(enemy);
		dy *= enemy->damage.repulso_force_take
			* enemy->damage.repulso_frame_take;
		dx *= enemy->damage.repulso_force_take
			* enemy->damage.repulso_frame_take;
		enemy->damage.repulso_frame_take--;
		if (enemy->damage.repulso_frame_take <= 0)
			enemy->damage.repulso_force_take = 0;
		set_before_point_enemy(enemy, data);
		cancel_move(data, enemy, dy, dx);
		calc_left_and_right_point(enemy, data);
		try_hit_enemys(enemy, data, 1);
		return (1);
	}
	return (0);
}

void	confundo_calc_deg(t_enemy *enemy, double *dy, double *dx, double *deg)
{
	enemy->damage.confundo_frame_take--;
	if (enemy->damage.confundo_frame_take <= 0)
		enemy->damage.confundo_force_take = 0;
	if (*dy != 0)
	{
		*deg = atan((*dx / *dy)) / (M_PI / 180);
		if (*deg < 0)
			*deg = -*deg;
	}
	if (*dy < 0 && *dx < 0)
		*deg = 180 + *deg;
	else if (*dy < 0 && *dx > 0)
		*deg = 180 - *deg;
	else if (*dy > 0 && *dx < 0)
		*deg = 360 - *deg;
	else if (*dy == 0 && *dx < 0)
		*deg = 270;
	else if (*dy == 0 && *dx > 0)
		*deg = 90;
	else if (*dx == 0 && *dy < 0)
		*deg = 180;
}

int	confundo_move_enemy(t_enemy *enemy, t_data *data)
{
	double	deg;
	double	dy;
	double	dx;

	if (enemy->damage.confundo_force_take > 0)
	{
		calc_deg(&enemy->center, &data->player.coo, &enemy->rad, &enemy->deg);
		calc_dx_dy_enemy(&dy, &dx, enemy->rad);
		f_way(enemy);
		dy *= enemy->speed;
		dx *= enemy->speed;
		confundo_calc_deg(enemy, &dy, &dx, &deg);
		enemy->deg = deg;
		enemy->rad = enemy->deg * (M_PI / 180);
		set_before_point_enemy(enemy, data);
		cancel_move(data, enemy, dy, dx);
		calc_left_and_right_point(enemy, data);
		try_hit_enemys(enemy, data, 0);
		return (1);
	}
	return (0);
}

int	repulso_neg_deacl(t_enemy *enemy, double *dy, double *dx)
{
	double	diff_x;
	double	diff_y;
	double	decal;

	diff_x = (enemy->damage.hit.case_x * 64 + enemy->damage.hit.coo_x)
		- (enemy->center.case_x * 64 + enemy->center.coo_x);
	diff_y = (enemy->damage.hit.case_y * 64 + enemy->damage.hit.coo_y)
		- (enemy->center.case_y * 64 + enemy->center.coo_y);
	enemy->damage.dist = sqrt(diff_x * diff_x + diff_y * diff_y);
	decal = -(1000 / (enemy->damage.dist + 35)
			+ enemy->damage.repulso_force_take) / 4 - 1;
	if (decal > 0)
		return (1);
	if (enemy->damage.dist >= fabs(decal))
		enemy->damage.repulso_force_take = decal;
	else
	{
		enemy->damage.repulso_force_take = -enemy->damage.dist;
		enemy->damage.repulso_frame_take = enemy->damage.repulso_frame_take;
	}
	*dy *= fabs(enemy->damage.repulso_force_take)
		* enemy->damage.repulso_frame_take;
	*dx *= fabs(enemy->damage.repulso_force_take)
		* enemy->damage.repulso_frame_take;
	return (0);
}

int	repulso_neg_enemy(t_enemy *enemy, t_data *data)
{
	double	rad;
	double	deg;
	double	dy;
	double	dx;

	if (enemy->damage.repulso_force_take < 0)
	{
		calc_deg(&enemy->damage.hit, &enemy->center, &rad, &deg);
		calc_dx_dy_enemy(&dy, &dx, rad);
		f_way(enemy);
		if (repulso_neg_deacl(enemy, &dy, &dx))
			return (1);
		f_way(enemy);
		enemy->damage.repulso_frame_take--;
		if (enemy->damage.repulso_frame_take <= 0)
			enemy->damage.repulso_force_take = 0;
		set_before_point_enemy(enemy, data);
		cancel_move(data, enemy, dy, dx);
		calc_left_and_right_point(enemy, data);
		try_hit_enemys(enemy, data, 1);
		return (1);
	}
	return (0);
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

void	move_center_point(t_data *data, t_enemy *enemy, double *dy, double *dx)
{
	enemy->center.coo_x += *dx;
	enemy->center.coo_y += *dy;
	if (enemy->recalc_path > 0)
		enemy->recalc_path--;
	if (enemy->calc_path > 0)
		enemy->calc_path--;
	if (enemy->center.coo_x <= 0 || enemy->center.coo_x >= 64
		|| enemy->center.coo_y <= 0 || enemy->center.coo_y >= 64)
	{
		if (enemy->center.coo_x <= 0)
			enemy->center.coo_x += 63.999;
		if (enemy->center.coo_x >= 64)
			enemy->center.coo_x -= 63.999;
		if (enemy->center.coo_y <= 0)
			enemy->center.coo_y += 63.999;
		if (enemy->center.coo_y >= 64)
			enemy->center.coo_y -= 63.999;
		remove_child_path(enemy);
	}
	calc_left_and_right_point(enemy, data);
	try_hit_enemys(enemy, data, 0);
}

void	apply_slow_enemy(t_enemy *enemy, double *dx, double *dy)
{
	if (enemy->damage.slow_force_take > 100)
		enemy->damage.slow_force_take = 100;
	*dx *= (100 - enemy->damage.slow_force_take) / 100;
	*dy *= (100 - enemy->damage.slow_force_take) / 100;
	if (enemy->damage.slow_frame_take > 0)
		enemy->damage.slow_frame_take--;
	if (enemy->damage.slow_frame_take <= 0)
		enemy->damage.slow_force_take--;
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
			enemy->calc = true;
		}
		else
			move_center_point(data, enemy, dy, dx);
	}
}

static void	make_move_enemy(t_data *data, t_enemy *enemy)
{
	double	dy;
	double	dx;

	if (repulso_move_enemy(enemy, data))
		return ;
	if (confundo_move_enemy(enemy, data))
		return ;
	if (enemy->calc == true)
	{
		enemy->calc = false;
		calc_deg(&enemy->way->coo, &enemy->center, &enemy->rad, &enemy->deg);
	}
	set_before_point_enemy(enemy, data);
	path_move_enemy(enemy, data, &dx, &dy);
	if (repulso_neg_enemy(enemy, data))
		return ;
}

static int	handle_ray_y_top_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y - 1][ray->case_x] != '1')
	{
		ray->case_y--;
		ray->coo_y = 64;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
	}
	else
	{
		ray->coo_y = 0;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
		return (1);
	}
	return (0);
}

static int	handle_ray_y_down_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y + 1][ray->case_x] != '1')
	{
		ray->case_y++;
		ray->coo_y = 0;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
	}
	else
	{
		ray->coo_y = 64;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
		return (1);
	}
	return (0);
}

static int	handle_ray_x_left_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y][ray->case_x - 1] != '1')
	{
		ray->case_x--;
		ray->coo_x = 64;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
	}
	else
	{
		ray->coo_x = 0;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
		return (1);
	}
	return (0);
}

static int	handle_ray_x_right_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y][ray->case_x + 1] != '1')
	{
		ray->case_x++;
		ray->coo_x = 0;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
	}
	else
	{
		ray->coo_x = 64;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
		return (1);
	}
	return (0);
}

static int	handle_ray_x_gen(t_data *data, t_ray *ray)
{
	if (ray->delta_x < 0)
	{
		if (handle_ray_x_left_gen(data, ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_x_right_gen(data, ray) == 1)
			return (1);
	}
	return (0);
}

static int	handle_ray_y_gen(t_data *data, t_ray *ray)
{
	if (ray->delta_y < 0)
	{
		if (handle_ray_y_top_gen(data, ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_y_down_gen(data, ray) == 1)
			return (1);
	}
	return (0);
}

bool	is_sorcerer(int type)
{
	if (type == MARINA || type == CAMEO || type == DIRLO || type == NANCY
		|| type == PILO || type == ZIPPY || type == ANAIS || type == STEF
		|| type == KUNFANDI)
		return (true);
	return (false);
}

void	air_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
					EXPECTO_PATRONUM, &enemy->center, deg + 180), data->item,
				f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ARANIA_EXUMAI,
					&enemy->center, deg + 180), data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, VENTUS,
					&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == KUNFANDI)
		data->item = add_end_lst(create_item(data, BH, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == CAMEO)
		data->item = add_end_lst(create_item(data, MARVIN, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == ANAIS)
		data->item = add_end_lst(create_item(data, TAYLOR_SWIFT, &enemy->center,
					deg + 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = AIR;
}

void	water_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
					EXPECTO_PATRONUM, &enemy->center, deg + 180), data->item,
				f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ARANIA_EXUMAI,
					&enemy->center, deg + 180), data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, AGUAMENTI,
					&enemy->center, deg + 180), data->item, f_item);
	else
		data->item = add_end_lst(create_item(data, FOLDER, &enemy->center, deg
					+ 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = WATER;
}

void	fire_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	printf("FIRE SPELL\n");
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
					EXPECTO_PATRONUM, &enemy->center, deg + 180), data->item,
				f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ARANIA_EXUMAI,
					&enemy->center, deg + 180), data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, INCENDIO,
					&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == STEF)
		data->item = add_end_lst(create_item(data, COMPANY, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == ZIPPY)
		data->item = add_end_lst(create_item(data, PIZZA, &enemy->center, deg
					+ 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = FIRE;
}

void	earth_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
					EXPECTO_PATRONUM, &enemy->center, deg + 180), data->item,
				f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ARANIA_EXUMAI,
					&enemy->center, deg + 180), data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ENDOLORIS,
					&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == MARINA)
		data->item = add_end_lst(create_item(data, LOGO_42, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == PILO)
		data->item = add_end_lst(create_item(data, MAC, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == DIRLO)
		data->item = add_end_lst(create_item(data, TIG, &enemy->center, deg
					+ 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = EARTH;
}

void	launch_ray_enemy(t_ray *ray, t_data *data)
{
	while (1)
	{
		if (ray->delta_x > 0)
			ray->rx = (64 - ray->coo_x) / ray->delta_x;
		else
			ray->rx = -ray->coo_x / ray->delta_x;
		if (ray->delta_y > 0)
			ray->ry = (64 - ray->coo_y) / ray->delta_y;
		else
			ray->ry = -ray->coo_y / ray->delta_y;
		if (ray->rx < ray->ry)
		{
			if (handle_ray_x_gen(data, ray) == 1)
				break ;
		}
		else
		{
			if (handle_ray_y_gen(data, ray) == 1)
				break ;
		}
	}
}

void	fill_ray_enemy(t_enemy *enemy, t_ray *ray, double deg)
{
	ray->deg = deg;
	ray->start_case_x = enemy->center.case_x;
	ray->start_case_y = enemy->center.case_y;
	ray->start_coo_x = enemy->center.coo_x;
	ray->start_coo_y = enemy->center.coo_y;
	ray->coo_y = enemy->center.coo_y;
	ray->coo_x = enemy->center.coo_x;
	ray->case_y = enemy->center.case_y;
	ray->case_x = enemy->center.case_x;
	ray->deg = fmod(ray->deg, 360);
	ray->rad = ray->deg * (M_PI / 180);
	ray->delta_y = cos(ray->rad);
	ray->delta_x = sin(ray->rad);
}

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

int	vision_case_continue(t_enemy *enemy, t_enemy **elem, t_lst **lst)
{
	*elem = (*lst)->dt;
	*lst = (*lst)->next;
	if (enemy->type == BIRD)
	{
		if ((*elem)->type == BIRD)
			return (1);
	}
	else if (is_sorcerer(enemy->type) == true
		&& (*elem)->color_coa == enemy->color_coa)
		return (1);
	else if (enemy->type == SNAKE && (*elem)->type == SNAKE)
		return (1);
	else if (is_sorcerer(enemy->type) == false
		&& is_sorcerer((*elem)->type) == false && enemy->type != SNAKE)
		return (1);
	return (0);
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

void	case_in_visu(t_enemy_vision *visu, t_enemy *elem, t_enemy *enemy,
		t_data *data)
{
	if ((visu->deg + 360 >= elem->deg - 90 + 360 && visu->deg + 360 <= elem->deg
			+ 90 + 360) || enemy->calc_path > 0)
	{
		fill_ray_enemy(enemy, &visu->ray, visu->deg);
		launch_ray_enemy(&visu->ray, data);
		calc_dist_wall(&visu->ray);
		calc_dist_target(enemy, elem, &visu->ray);
		if (enemy->dist_target < visu->ray.dist_wall || enemy->calc_path > 0)
		{
			if (enemy->dist_target < visu->dist_min || visu->dist_min == -1)
			{
				visu->type = elem->type;
				visu->keep_elem = elem;
				visu->dist_min = enemy->dist_target;
				visu->coo.case_x = elem->center.case_x;
				visu->coo.case_y = elem->center.case_y;
				visu->coo.coo_y = elem->center.coo_y;
				visu->coo.coo_x = elem->center.coo_x;
			}
		}
	}
}

void	case_in_visu_player(t_enemy_vision *visu, t_enemy *enemy, t_data *data)
{
	if ((visu->deg + 360 >= enemy->deg - 90 + 360 && visu->deg
			+ 360 <= enemy->deg + 90 + 360) || enemy->calc_path > 0)
	{
		fill_ray_enemy(enemy, &visu->ray, visu->deg);
		launch_ray_enemy(&visu->ray, data);
		calc_dist_wall(&visu->ray);
		if (visu->dist_min_player < visu->ray.dist_wall || enemy->calc_path > 0)
		{
			if (visu->dist_min_player < visu->dist_min
				|| visu->dist_min_player < 256 || visu->dist_min == -1)
			{
				visu->dist_min = visu->dist_min_player;
				visu->type = -1;
				visu->coo.case_x = data->player.coo.case_x;
				visu->coo.case_y = data->player.coo.case_y;
				visu->coo.coo_y = data->player.coo.coo_y;
				visu->coo.coo_x = data->player.coo.coo_x;
			}
		}
	}
}

void	calc_dist_min_player(t_data *data, t_enemy *enemy, t_enemy_vision *visu)
{
	int	diff_player_x;
	int	diff_player_y;

	diff_player_x = data->player.coo.case_x * 64 + data->player.coo.coo_x
		- enemy->center.case_x * 64 - enemy->center.coo_x;
	diff_player_y = data->player.coo.case_y * 64 + data->player.coo.coo_y
		- enemy->center.case_y * 64 - enemy->center.coo_y;
	visu->dist_min_player = sqrt(diff_player_x * diff_player_x + diff_player_y
			* diff_player_y);
}

int	attack_dist(t_enemy *enemy, t_data *data, t_enemy_vision *visu)
{
	if (is_sorcerer(enemy->type) == true && rand() % 1000 < 50
		&& get_mtime() > enemy->time_attack_dist + enemy->cooldown_dist * 1000)
	{
		enemy->time_attack_dist = get_mtime();
		if (enemy->color_coa == AIR_COLOR)
			air_spell(data, enemy, visu->deg, visu->type);
		else if (enemy->color_coa == EARTH_COLOR)
			earth_spell(data, enemy, visu->deg, visu->type);
		else if (enemy->color_coa == WATER_COLOR)
			water_spell(data, enemy, visu->deg, visu->type);
		else if (enemy->color_coa == FIRE_COLOR)
			fire_spell(data, enemy, visu->deg, visu->type);
		return (1);
	}
	return (0);
}

void	see_target(t_enemy *enemy, t_data *data, t_enemy_vision *visu)
{
	if (attack_dist(enemy, data, visu))
		;
	else if (rand() % 1000 < 50 && get_mtime() > enemy->time_attack_dist
		+ enemy->cooldown_dist * 1000)
	{
		enemy->time_attack_dist = get_mtime();
		if (enemy->type == SPIDER)
		{
			data->item = add_end_lst(create_item(data, WEB_SPIDER,
						&enemy->center, visu->deg + 180), data->item, f_item);
			((t_item *)data->item->dt)->damage.which_coa_do = OTHERS;
		}
		else if (enemy->type == ELEM)
		{
			data->item = add_end_lst(create_item(data, FIREBALL_ELEM,
						&enemy->center, visu->deg + 180), data->item, f_item);
			((t_item *)data->item->dt)->damage.which_coa_do = OTHERS;
		}
	}
	if (enemy->recalc_path <= 50 || !enemy->way)
		enemy->recalc_path = 100;
	if (visu->dist_min_player == visu->dist_min)
		enemy->calc_path = 30;
	else
		enemy->calc_path = 0;
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

void	visu_enemy_valid(t_data *data, t_enemy_vision *visu, t_enemy *enemy)
{
	int	diff_player_x;
	int	diff_player_y;

	calc_deg(&visu->coo, &enemy->center, &visu->rad, &visu->deg);
	diff_player_x = visu->coo.case_x * 64 + visu->coo.coo_x
		- enemy->center.case_x * 64 - enemy->center.coo_x;
	diff_player_y = visu->coo.case_y * 64 + visu->coo.coo_y
		- enemy->center.case_y * 64 - enemy->center.coo_y;
	visu->dist_min_player = sqrt(diff_player_x * diff_player_x + diff_player_y
			* diff_player_y);
	enemy->dist_target = visu->dist_min;
	if (enemy->dist_target < enemy->dist_visu)
		see_target(enemy, data, visu);
	if (enemy->dist_target < enemy->dist_damage
		&& get_mtime() > enemy->time_attack_cac + enemy->cooldown_cac * 1000)
	{
		enemy->time_attack_cac = get_mtime();
		if (visu->dist_min == visu->dist_min_player)
			apply_damage(&data->player.damage, &enemy->damage);
		else if (visu->keep_elem)
			apply_damage(&visu->keep_elem->damage, &enemy->damage);
	}
	recalc_path(enemy, visu, data);
}

int	enemy_vision(t_data *data, t_enemy *enemy)
{
	t_lst			*lst;
	t_enemy			*elem;
	t_enemy_vision	visu;

	visu.dist_min = -1;
	visu.keep_elem = NULL;
	visu.dist_min_player = -1;
	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		if (vision_case_continue(enemy, &elem, &lst))
			continue ;
		calc_deg(&elem->center, &enemy->center, &visu.rad, &visu.deg);
		case_in_visu(&visu, elem, enemy, data);
	}
	if (enemy->type != BIRD && enemy->nb_move >= 10
		&& data->player.invisible == 255)
	{
		calc_deg(&data->player.coo, &enemy->center, &visu.rad, &visu.deg);
		calc_dist_min_player(data, enemy, &visu);
		case_in_visu_player(&visu, enemy, data);
	}
	if (visu.dist_min != -1)
		visu_enemy_valid(data, &visu, enemy);
	return (0);
}

void	damage_poison_fire(t_enemy *enemy)
{
	if (enemy->damage.poison_frame_take > 0)
	{
		enemy->life -= enemy->damage.poison_force_take;
		enemy->damage.poison_frame_take--;
		if (enemy->damage.poison_frame_take <= 0)
			enemy->damage.poison_force_take = 0;
	}
	if (enemy->damage.fire_frame_take > 0)
	{
		enemy->life -= enemy->damage.fire_force_take;
		enemy->damage.fire_frame_take--;
		if (enemy->damage.fire_frame_take <= 0)
			enemy->damage.fire_force_take = 0;
	}
}

void	take_damage_enemy(t_enemy *enemy)
{
	enemy->life -= enemy->damage.damage_take;
	enemy->damage.damage_take = 0;
	damage_poison_fire(enemy);
	if (enemy->type != DEMENTOR)
	{
		if (enemy->damage.curse_frame_take > 0)
		{
			enemy->life -= enemy->damage.curse_force_take;
			enemy->damage.curse_frame_take--;
			if (enemy->damage.curse_frame_take <= 0)
				enemy->damage.curse_force_take = 0;
		}
	}
	if (enemy->type == SNAKE)
	{
		enemy->life -= enemy->damage.damage_snake_take;
		enemy->damage.damage_snake_take = 0;
	}
}

void	set_valid_spawn(double *new_x, double *new_y)
{
	if (*new_x >= 64)
		*new_x = 63.5;
	if (*new_y >= 64)
		*new_y = 63.5;
	if (*new_x < 0)
		*new_x = .5;
	if (*new_y < 0)
		*new_y = .5;
}

void	spawn_heal(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (rand() % 100 <= enemy->drop_heal)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, HEAL_POPO,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y, .coo_x = new_x,
					.coo_y = new_y}, new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
	}
}

void	spawn_floo(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (rand() % 100 <= enemy->drop_floo)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, FLOO_POPO,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
	}
}

void	spawn_shield(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (rand() % 100 <= enemy->drop_shield)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, SHIELD_POPO,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
	}
}

void	spawn_cloak(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (rand() % 100 <= enemy->drop_cloak)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, INVI_POPO,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
	}
}

void	spawn_spider_wand(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (data->wand.is_drop[1] != true && rand()
		% 100 <= enemy->drop_spider_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, SPIDER_WAND,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[1] = true;
	}
}

void	spawn_dementor_wand(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (data->wand.is_drop[4] != true && rand()
		% 100 <= enemy->drop_dementor_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, DEMENTOR_WAND,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[4] = true;
	}
}

void	spawn_elem_wand(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (data->wand.is_drop[3] != true && rand() % 100 <= enemy->drop_elem_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, ELEM_WAND,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[3] = true;
	}
}

void	spawn_wolf_wand(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (data->wand.is_drop[2] != true && rand() % 100 <= enemy->drop_wolf_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, WOLF_WAND,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[2] = true;
		data->wand.is_drop[2] = true;
	}
}

void	spawn_item(t_data *data, t_enemy *enemy)
{
	spawn_heal(enemy, data);
	spawn_floo(enemy, data);
	spawn_shield(enemy, data);
	spawn_cloak(enemy, data);
	spawn_spider_wand(enemy, data);
	spawn_dementor_wand(enemy, data);
	spawn_elem_wand(enemy, data);
	spawn_wolf_wand(enemy, data);
}

void	win_xp(t_data *data, int type, double *xp)
{
	if (type == DEMENTOR)
		*xp += 0.42 / (0.8 + (data->player.xp * 0.1));
	else if (type == SPIDER)
		*xp += 0.23 / (0.8 + (data->player.xp * 0.1));
	else if (type == ELEM)
		*xp += 0.35 / (0.8 + (data->player.xp * 0.1));
	else if (type == WOLF)
		*xp += 0.5 / (0.8 + (data->player.xp * 0.1));
	else
		*xp += 3 / (0.8 + (data->player.xp * 0.1));
}

void	add_sound_xp(t_enemy *enemy, t_data *data)
{
	if (enemy->damage.which_coa_take == data->player.coa)
	{
		data->sound = add_end_lst(create_sound(data, 25), data->sound,
				free_sound);
		win_xp(data, enemy->type, &data->player.xp);
		data->coa[data->player.coa].xp = data->player.xp;
	}
	else if (enemy->damage.which_coa_take == EARTH)
		win_xp(data, enemy->type, &data->coa[EARTH].xp);
	else if (enemy->damage.which_coa_take == AIR)
		win_xp(data, enemy->type, &data->coa[AIR].xp);
	else if (enemy->damage.which_coa_take == WATER)
		win_xp(data, enemy->type, &data->coa[WATER].xp);
	else if (enemy->damage.which_coa_take == FIRE)
		win_xp(data, enemy->type, &data->coa[FIRE].xp);
}

void	death_sorcerer(t_enemy *enemy, t_data *data)
{
	if (enemy->type == NANCY)
		data->sorcerer[0].is_alive = false;
	else if (enemy->type == PILO)
		data->sorcerer[3].is_alive = false;
	else if (enemy->type == ZIPPY)
		data->sorcerer[1].is_alive = false;
	else if (enemy->type == KUNFANDI)
		data->sorcerer[2].is_alive = false;
	else if (enemy->type == DIRLO)
		data->sorcerer[6].is_alive = false;
	else if (enemy->type == STEF)
		data->sorcerer[7].is_alive = false;
	else if (enemy->type == MARINA)
		data->sorcerer[8].is_alive = false;
	else if (enemy->type == ANAIS)
		data->sorcerer[5].is_alive = false;
	else if (enemy->type == CAMEO)
		data->sorcerer[4].is_alive = false;
}

void	low_life_enemy(t_enemy *enemy, t_data *data, t_lst **lst)
{
	if (enemy->life <= 0)
	{
		if (enemy->type != SNAKE && enemy->type != BIRD)
		{
			data->item = add_end_lst(create_item(data, ANIM_DEATH,
						&(t_fcoo){.case_x = enemy->center.case_x,
						.case_y = enemy->center.case_y,
						.coo_y = enemy->center.coo_y,
						.coo_x = enemy->center.coo_x}, data->map.mini.deg),
					data->item, f_item);
			if (enemy->damage.which_coa_take == data->player.coa)
				spawn_item(data, enemy);
		}
		add_sound_xp(enemy, data);
		death_sorcerer(enemy, data);
		data->enemy = remove_elem_lst(*lst);
		f_elem_lst(*lst);
		return ;
	}
}

void	move_enemy(t_data *data)
{
	t_lst	*lst;
	t_enemy	*enemy;
	t_lst	*next;

	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		next = lst->next;
		if ((enemy_vision(data, enemy) && enemy->way) || enemy->way
			|| enemy->damage.confundo_force_take > 0)
			make_move_enemy(data, enemy);
		else
			gen_enemy_way(data, enemy);
		take_damage_enemy(enemy);
		low_life_enemy(enemy, data, &lst);
		enemy->nb_move++;
		lst = next;
	}
}
