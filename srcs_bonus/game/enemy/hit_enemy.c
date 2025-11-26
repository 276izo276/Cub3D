#include "struct_bonus.h"
#include "cub3d_bonus.h"

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
