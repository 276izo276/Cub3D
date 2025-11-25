#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>
#include <string.h>
#include "utils_bonus.h"
#include "enemy_bonus.h"

void	calc_left_point_item(t_item *item)
{
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;

	rad = item->rad + (90 * (M_PI / 180));
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
	dy *= item->radius;
	dx *= item->radius;
	recalc_fcoo(&item->left, &item->center, dy, dx);
}

void	calc_right_point_item(t_item *item)
{
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;

	rad = item->rad - (90 * (M_PI / 180));
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
	dy *= item->radius;
	dx *= item->radius;
	recalc_fcoo(&item->right, &item->center, dy, dx);
}

void	move_more_hit_pos_item(t_item *item)
{
	double	deg;
	double	rad;
	double	dx;
	double	dy;
	double	v_normalize;

	calc_deg(&item->center_before, &item->center, &rad, &deg);
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

void	hit_calc_scal_player(bool *hit, t_fcoo *coo, t_item *elem, t_hitray *ray)
{
	if (*hit == false)
	{
		ray->dx = coo->case_x * 64 + coo->coo_x;
		ray->dy = coo->case_y * 64 + coo->coo_y;
		calc_scal(ray);
		if (ray->hit == true)
		{
			apply_damage(&ray->data->player.damage, &elem->damage);
			*hit = true;
		}
	}
}

void	item_try_hit_player(t_data *data, t_item *elem, t_hitray *ray, bool *hit)
{
	if ((elem->nb_move >= 5 && elem->damage.which_coa_do == data->player.coa)
		|| elem->damage.which_coa_do != data->player.coa)
	{
		ray->ax = elem->left.case_x * 64 + elem->left.coo_x;
		ray->ay = elem->left.case_y * 64 + elem->left.coo_y;
		ray->bx = elem->right.case_x * 64 + elem->right.coo_x;
		ray->by = elem->right.case_y * 64 + elem->right.coo_y;
		ray->cx = elem->left_before.case_x * 64 + elem->left_before.coo_x;
		ray->cy = elem->left_before.case_y * 64 + elem->left_before.coo_y;
		hit_calc_scal_player(hit, &data->player.coo, elem, ray);
		hit_calc_scal_player(hit, &data->player.left, elem, ray);
		hit_calc_scal_player(hit, &data->player.right, elem, ray);
	}
}

bool	hit_calc_scal_enemy(t_enemy *enemy, t_item *elem, t_hitray *ray, t_lst **lst)
{
	if (ray->hit == true)
	{
		move_more_hit_pos_item(elem);
		apply_damage(&enemy->damage, &elem->damage);
		*lst = (*lst)->next;
		return (true);
	}
	return (false);
}

bool 	item_try_hit_enemy(t_hitray *ray, t_item *elem, t_enemy *enemy, t_lst **lst)
{
	ray->ax = elem->left.case_x * 64 + elem->left.coo_x;
	ray->ay = elem->left.case_y * 64 + elem->left.coo_y;
	ray->bx = elem->right.case_x * 64 + elem->right.coo_x;
	ray->by = elem->right.case_y * 64 + elem->right.coo_y;
	ray->cx = elem->left_before.case_x * 64 + elem->left_before.coo_x;
	ray->cy = elem->left_before.case_y * 64 + elem->left_before.coo_y;
	ray->dx = enemy->left.case_x * 64 + enemy->left.coo_x;
	ray->dy = enemy->left.case_y * 64 + enemy->left.coo_y;
	calc_scal(ray);
	if (hit_calc_scal_enemy(enemy, elem, ray, lst) == true)
		return (true);
	ray->dx = enemy->center.case_x * 64 + enemy->center.coo_x;
	ray->dy = enemy->center.case_y * 64 + enemy->center.coo_y;
	calc_scal(ray);
	if (hit_calc_scal_enemy(enemy, elem, ray, lst) == true)
		return (true);
	ray->dx = enemy->right.case_x * 64 + enemy->right.coo_x;
	ray->dy = enemy->right.case_y * 64 + enemy->right.coo_y;
	calc_scal(ray);
	if (hit_calc_scal_enemy(enemy, elem, ray, lst) == true)
		return (true);
	return (false);
}

bool	item_try_hit_enemy_delta(t_hitray *ray, t_item *elem, t_enemy *enemy, t_lst **lst)
{
	ray->ax = elem->center.case_x * 64 + elem->center.coo_x;
	ray->ay = elem->center.case_y * 64 + elem->center.coo_y;
	ray->bx = elem->center_before.case_x * 64 + elem->center_before.coo_x;
	ray->by = elem->center_before.case_y * 64 + elem->center_before.coo_y;
	ray->cx = enemy->left.case_x * 64 + enemy->left.coo_x;
	ray->cy = enemy->left.case_y * 64 + enemy->left.coo_y;
	ray->dx = enemy->center.case_x * 64 + enemy->center.coo_x;
	ray->dy = enemy->center.case_y * 64 + enemy->center.coo_y;
	calc_delta(ray);
	if (hit_calc_scal_enemy(enemy, elem, ray, lst) == true)
		return (true);
	ray->cx = enemy->center.case_x * 64 + enemy->center.coo_x;
	ray->cy = enemy->center.case_y * 64 + enemy->center.coo_y;
	ray->dx = enemy->right.case_x * 64 + enemy->right.coo_x;
	ray->dy = enemy->right.case_y * 64 + enemy->right.coo_y;
	calc_delta(ray);
	if (hit_calc_scal_enemy(enemy, elem, ray, lst) == true)
		return (true);
	return (false);
}

int	try_hit_items(t_item *elem, t_data *data)
{
	t_enemy		*enemy;
	t_lst		*lst;
	t_hitray	ray;
	bool		hit;

	hit = false;
	ray.data = data;
	item_try_hit_player(data, elem, &ray, &hit);
	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		if (enemy->type != DEMENTOR && elem->type == EXPECTO_PATRONUM && !elem->categ)
		{
			lst =lst->next;
			continue;
		}
		hit = item_try_hit_enemy(&ray, elem, enemy, &lst);
		if (hit == true)
			continue ;
		hit = item_try_hit_enemy_delta(&ray, elem, enemy, &lst);
		if (hit == true)
			continue ;
		lst = lst->next;
	}
	elem->nb_move++;
	if (hit == true)
		return (1);
	return (0);
}

void	make_move_item(t_item *item, double speed)
{
	double	dx;
	double	dy;
	double	v_normalize;

	dx = sin(item->rad);
	dy = cos(item->rad);
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
	dy *= speed;
	dx *= speed;
	item->center.coo_x += dx;
	item->center.coo_y += dy;
	if (item->center.coo_x < 0)
	{
		item->center.coo_x += 64;
		item->center.case_x--;
	}
	else if (item->center.coo_x > 64)
	{
		item->center.coo_x -= 64;
		item->center.case_x++;
	}
	if (item->center.coo_y < 0)
	{
		item->center.coo_y += 64;
		item->center.case_y--;
	}
	else if (item->center.coo_y > 64)
	{
		item->center.coo_y -= 64;
		item->center.case_y++;
	}
	item->damage.hit.case_x = item->center_before.case_x;
	item->damage.hit.case_y = item->center_before.case_y;
	item->damage.hit.coo_x = item->center_before.coo_x;
	item->damage.hit.coo_y = item->center_before.coo_y;
	calc_left_point_item(item);
	calc_right_point_item(item);
}

void	apply_attraction(t_item *attract, t_data *data)
{
	t_lst	*lst;
	t_enemy	*enemy;
	double	dist_x;
	double	dist_y;
	double	distance;

	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		dist_x = (attract->center.case_x * 64 + attract->center.coo_x) - (enemy->center.case_x * 64 + enemy->center.coo_x);
		dist_y = (attract->center.case_y * 64 + attract->center.coo_y) - (enemy->center.case_y * 64 + enemy->center.coo_y);
		distance = sqrt(dist_x * dist_x + dist_y * dist_y);
		if (distance < attract->radius * 25)
		{
			enemy->damage.hit.case_x = attract->center.case_x;
			enemy->damage.hit.case_y = attract->center.case_y;
			enemy->damage.hit.coo_x = attract->center.coo_x;
			enemy->damage.hit.coo_y = attract->center.coo_y;
			enemy->damage.repulso_force_take = attract->damage.repulso_force_do;
			enemy->damage.repulso_frame_take = attract->damage.repulso_frame_do;
		}
		lst = lst->next;
	}
	attract->nb_move++;

}

void	move_item(t_data *data)
{
	t_lst	*lst;
	t_item	*item;

	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		item = lst->dt;
		item->deg += item->deg_rotate;
		item->rad = item->deg * (M_PI / 180);
		if (item->type == BH && item->categ)
			item->radius += .1;
		if (item->type == EXPECTO_PATRONUM && !item->categ)
			item->radius += .3;
		else if (item->type == ANIM_DEATH && !item->categ)
			item->radius += 1.5;
		if (item->type == VENTUS && !item->categ)
			item->radius += .1;
		else if (item->type == PILLAR && item->categ)
		{
			double diff_x = (data->player.coo.case_x * 64 + data->player.coo.coo_x) - (item->center.case_x * 64 + item->center.coo_x);
			double diff_y = (data->player.coo.case_y * 64 + data->player.coo.coo_y) - (item->center.case_y * 64 + item->center.coo_y);
			if (diff_y != 0)
			{
				item->deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
				if (item->deg < 0)
					item->deg = -item->deg;
			}
			if (diff_y < 0 && diff_x < 0)
				item->deg = 180 + item->deg;
			else if (diff_y < 0 && diff_x > 0)
				item->deg = 180 - item->deg;
			else if (diff_y > 0 && diff_x < 0)
				item->deg = 360 - item->deg;
			else if (diff_y == 0 && diff_x < 0)
				item->deg = 270;
			else if (diff_y == 0 && diff_x > 0)
				item->deg = 90;
			else if (diff_x == 0 && diff_y < 0)
				item->deg = 180;
		}
		if ((item->type == VENTUS && !item->categ) || (item->type == BH && item->categ))
			apply_attraction(item, data);
		calc_left_point_item(item);
		calc_right_point_item(item);
		item->left_before.coo_x = item->left.coo_x;
		item->left_before.coo_y = item->left.coo_y;
		item->left_before.case_x = item->left.case_x;
		item->left_before.case_y = item->left.case_y;
		item->right_before.coo_x = item->right.coo_x;
		item->right_before.coo_y = item->right.coo_y;
		item->right_before.case_x = item->right.case_x;
		item->right_before.case_y = item->right.case_y;
		item->center_before.coo_x = item->center.coo_x;
		item->center_before.coo_y = item->center.coo_y;
		item->center_before.case_x = item->center.case_x;
		item->center_before.case_y = item->center.case_y;
		make_move_item(item, item->speed);
		if (((try_hit_items(item, data) && (item->type != BH && item->categ) && (item->type != VENTUS && item->type != EXPECTO_PATRONUM && item->type != ANIM_DEATH && !item->categ)) ||
			(item->center.case_y >= data->map.tabmap_height
			|| item->center.case_y < 0
			|| item->center.case_x >= ft_strlen(data->map.tabmap[item->center.case_y])
			|| item->center.case_x < 0)
			|| data->map.tabmap[item->center.case_y][item->center.case_x] == ' '
			|| data->map.tabmap[item->center.case_y][item->center.case_x] == '1')
			)
		{
			t_lst	*next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue;
		}
		if ((item->type == VENTUS && !item->categ && item->nb_move >= 400) || (item->type == ANIM_DEATH && item->categ && item->nb_move >= 10) || (item->type == EXPECTO_PATRONUM && !item->categ && item->nb_move >= 300) || (item->type == BH && item->categ && item->nb_move >= 200))
		{
			t_lst	*next = lst->next;

			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue;
		}
		lst = lst->next;
	}
}
