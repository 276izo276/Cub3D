/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_item.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:50:41 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:50:42 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>

static void	set_specific_case_item(t_item *item, t_hitray *ray, int i,
		t_data *data)
{
	if (item->type == EXPECTO_PATRONUM || (item->type == ANIM_DEATH
			&& item->categ) || item->type == BH)
		data->ray[i].items[ray->j]->type = item->type;
	if (item->type == VENTUS && !item->categ)
	{
		data->ray[i].items[ray->j]->type = VENTUS;
		if (item->nb_move <= 102)
			data->ray[i].items[ray->j]->status = item->nb_move / 8;
		else if (item->nb_move > 102 && item->nb_move <= 400 - (10 * 6))
			data->ray[i].items[ray->j]->status = item->nb_move / 8 % 4 + 18;
		else
			data->ray[i].items[ray->j]->status = item->nb_move / 8 - 18;
	}
}

static void	define_value_hit(t_data *data, t_hitray *ray, t_item *item, int i)
{
	ray->j = -1;
	while (++ray->j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door
		+ data->map.nb_floo)
		if (data->ray[i].items[ray->j]->use == false)
			break ;
	data->ray[i].items[ray->j]->type = ITEM;
	data->ray[i].items[ray->j]->categ = item->categ;
	set_specific_case_item(item, ray, i, data);
	data->ray[i].items[ray->j]->use = true;
	data->ray[i].items[ray->j]->item = item;
	data->ray[i].items[ray->j]->case_y = (int)(ray->hy / 64);
	data->ray[i].items[ray->j]->case_x = (int)(ray->hx / 64);
	data->ray[i].items[ray->j]->coo_y = fmod(ray->hy, 64);
	data->ray[i].items[ray->j]->coo_x = fmod(ray->hx, 64);
	data->ray[i].items[ray->j]->posx = ray->t;
	data->ray[i].items[ray->j]->side = FRONT;
	ray->deg = fmod(data->ray[i].deg + 360 - 90, 360);
	if ((ray->deg <= item->deg && ray->deg + 180 >= item->deg)
		|| (ray->deg >= item->deg && !(ray->deg - 180 <= item->deg)))
		data->ray[i].items[ray->j]->side = BACK;
}

static void	calc_pos_point(t_hitray *ray, t_data *data, t_item *item)
{
	ray->delta_x = data->ray[ray->i].delta_x;
	ray->delta_y = data->ray[ray->i].delta_y;
	ray->ax = item->left.coo_x + item->left.case_x * 64;
	ray->ay = item->left.coo_y + item->left.case_y * 64;
	ray->bx = item->right.coo_x + item->right.case_x * 64;
	ray->by = item->right.coo_y + item->right.case_y * 64;
	ray->cx = data->ray[ray->i].coo_x + data->ray[ray->i].case_x * 64;
	ray->cy = data->ray[ray->i].coo_y + data->ray[ray->i].case_y * 64;
	ray->radius = item->radius;
	calc_end_point(ray);
	calc_delta(ray);
}

void	try_hit_item(t_data *data, int i, double x)
{
	t_hitray	ray;
	t_lst		*lst;
	t_item		*item;

	lst = get_first_elem_lst(data->item);
	ft_bzero(&ray, sizeof(t_hitray));
	ray.i = i;
	while (lst)
	{
		item = lst->dt;
		calc_pos_point(&ray, data, item);
		if (ray.hit == true)
		{
			define_value_hit(data, &ray, item, i);
			calc_item_value(data, &ray, x);
		}
		lst = lst->next;
	}
	lst = get_first_elem_lst(data->enemy);
	ft_bzero(&ray, sizeof(t_hitray));
	ray_try_hit_enemy(data, i, x, lst);
	lst = get_first_elem_lst(data->door);
	ft_bzero(&ray, sizeof(t_hitray));
	ray_try_hit_door(data, i, x, lst);
}
