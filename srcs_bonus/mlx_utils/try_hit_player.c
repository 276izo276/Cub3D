#include "cub3d_bonus.h"
#include "texture_bonus.h"
#include "utils_bonus.h"
#include <math.h>

static void	calc_ray_value(t_hitray *ray, t_data *data)
{
	(*ray).ax = data->player.left.case_x * 64 + data->player.left.coo_x;
	(*ray).ay = data->player.left.case_y * 64 + data->player.left.coo_y;
	(*ray).bx = data->player.right.case_x * 64 + data->player.right.coo_x;
	(*ray).by = data->player.right.case_y * 64 + data->player.right.coo_y;
	(*ray).cx = data->player.left_before.case_x * 64
		+ data->player.left_before.coo_x;
	(*ray).cy = data->player.left_before.case_y * 64
		+ data->player.left_before.coo_y;
}

static void	calc_player_left_point(t_hitray *ray, t_item *item, t_data *data,
		t_lst **lst)
{
	(*ray).dx = item->left.case_x * 64 + item->left.coo_x;
	(*ray).dy = item->left.case_y * 64 + item->left.coo_y;
	calc_scal(ray);
	if ((*ray).hit == true)
		pick_up_items(data, item, lst);
}

static void	calc_player_center_point(t_hitray *ray, t_item *item, t_data *data,
		t_lst **lst)
{
	(*ray).dx = item->center.case_x * 64 + item->center.coo_x;
	(*ray).dy = item->center.case_y * 64 + item->center.coo_y;
	calc_scal(ray);
	if ((*ray).hit == true)
		pick_up_items(data, item, lst);
}

static void	calc_player_right_point(t_hitray *ray, t_item *item, t_data *data,
		t_lst **lst)
{
	(*ray).dx = item->right.case_x * 64 + item->right.coo_x;
	(*ray).dy = item->right.case_y * 64 + item->right.coo_y;
	calc_scal(ray);
	if ((*ray).hit == true)
		pick_up_items(data, item, lst);
}

void	try_hit_player(t_data *data)
{
	t_hitray	ray;
	t_lst		*lst;
	t_item		*item;

	calc_ray_value(&ray, data);
	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		item = lst->dt;
		if (is_skip_type(item, data) == true)
		{
			lst = lst->next;
			continue ;
		}
		calc_player_left_point(&ray, item, data, &lst);
		if (ray.hit == true)
			continue ;
		calc_player_center_point(&ray, item, data, &lst);
		if (ray.hit == true)
			continue ;
		calc_player_right_point(&ray, item, data, &lst);
		if (ray.hit == true)
			continue ;
		lst = lst->next;
	}
}
