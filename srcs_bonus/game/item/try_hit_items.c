#include "cub3d_bonus.h"

static void	item_try_hit_player(t_data *data, t_item *elem, t_hitray *ray,
		int *hit)
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

static bool	item_try_hit_enemy(t_hitray *ray, t_item *elem, t_enemy *enemy,
		t_lst **lst)
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

static bool	item_try_hit_enemy_delta(t_hitray *ray, t_item *elem,
		t_enemy *enemy, t_lst **lst)
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

static void	try_hit_items_loop(t_item *elem, t_hitray ray, t_lst *lst, int *hit)
{
	t_enemy	*enemy;

	while (lst)
	{
		enemy = lst->dt;
		if (enemy->type != DEMENTOR && elem->type == EXPECTO_PATRONUM
			&& !elem->categ)
		{
			lst = lst->next;
			continue ;
		}
		*hit += item_try_hit_enemy(&ray, elem, enemy, &lst);
		if (*hit >= 1)
		{
			lst = lst->next;
			continue ;
		}
		*hit += item_try_hit_enemy_delta(&ray, elem, enemy, &lst);
		if (*hit >= 1)
		{
			lst = lst->next;
			continue ;
		}
		lst = lst->next;
	}
}

int	try_hit_items(t_item *elem, t_data *data)
{
	t_lst		*lst;
	t_hitray	ray;
	int			hit;

	hit = false;
	ray.data = data;
	item_try_hit_player(data, elem, &ray, &hit);
	lst = get_first_elem_lst(data->enemy);
	try_hit_items_loop(elem, ray, lst, &hit);
	elem->nb_move++;
	if (hit >= 1)
		return (1);
	return (0);
}
