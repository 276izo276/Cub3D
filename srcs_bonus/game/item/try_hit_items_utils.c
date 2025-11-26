#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include <string.h>

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

static void	move_more_hit_pos_item(t_item *item)
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

void	hit_calc_scal_player(bool *hit, t_fcoo *coo, t_item *elem,
		t_hitray *ray)
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

bool	hit_calc_scal_enemy(t_enemy *enemy, t_item *elem, t_hitray *ray,
		t_lst **lst)
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
