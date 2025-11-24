#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "texture_bonus.h"

void	handle_map_status(t_map *map, t_data *data, t_mini *mini)
{
	if (data->status == FLOO_MAP)
		return ;
	if (map->tabmap[data->player.coo.case_y][data->player.coo.case_x] == 'F'
		&& (map->door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->is_floo_open == true))
	{
		if (map->door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->is_verti == true
			&& mini->cx == 0 && ((data->player.coo.coo_x <= 32.0
					&& mini->nx > 32.0) || (data->player.coo.coo_x >= 32.0
					&& mini->nx < 32.0)))
			data->status = FLOO_MAP;
		else if (map->door_map[data->player.coo.case_y]
			[data->player.coo.case_x]->is_verti == false
			&& mini->cy == 0 && ((data->player.coo.coo_y <= 32.0
					&& mini->ny > 32.0) || (data->player.coo.coo_y >= 32.0
					&& mini->ny < 32.0)))
			data->status = FLOO_MAP;
		save_pos_before_floo(data);
	}
}

static void	pick_up_wand(t_data *data, t_item *item)
{
	if (item->type == WOLF_WAND)
	{
		data->wand.wand_status[2] = true;
		data->wand.nb_wand = 2;
	}
	if (item->type == ELEM_WAND)
	{
		data->wand.wand_status[3] = true;
		data->wand.nb_wand = 3;	
	}
	if (item->type == DEMENTOR_WAND)
	{
		data->wand.wand_status[4] = true;
		data->wand.nb_wand = 4;	
	}
	if (item->type == SPIDER_WAND)
	{
		data->wand.wand_status[1] = true;
		data->wand.nb_wand = 1;	
	}
}

static void	pick_up_items(t_data *data, t_item *item)
{
	if (item->type == POPO_HEAL)
		data->popo[0].nb ++;
	if (item->type == POPO_SHIELD)
		data->popo[1].nb ++;
	if (item->type == POPO_FLOO)
		data->popo[2].nb ++;
	if (item->type == POPO_INVI)
		data->popo[3].nb++;
	if (item->type == PORTKEY)
	{
		data->status = MENU_END;
		get_ranking_xp(data);
	}
	pick_up_wand(data, item);
	apply_damage(&data->player.damage, &item->damage);
}

void	try_hit_player(t_data *data)
{
	t_hitray	ray;
	t_lst		*lst;
	t_item		*item;
	t_lst		*next;

	ray.ax = data->player.left.case_x * 64 + data->player.left.coo_x;
	ray.ay = data->player.left.case_y * 64 + data->player.left.coo_y;
	ray.bx = data->player.right.case_x * 64 + data->player.right.coo_x;
	ray.by = data->player.right.case_y * 64 + data->player.right.coo_y;
	ray.cx = data->player.left_before.case_x * 64
		+ data->player.left_before.coo_x;
	ray.cy = data->player.left_before.case_y * 64
		+ data->player.left_before.coo_y;
	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		item = lst->dt;
		if (((item->type == CONFUNDO || item->type == VENTUS
					|| item->type == EXPECTO_PATRONUM || item->type == REPULSO)
				&& !item->categ) || (item->nb_move <= 5
				&& item->damage.which_coa_do == data->player.coa))
		{
			lst = lst->next;
			continue ;
		}
		ray.dx = item->left.case_x * 64 + item->left.coo_x;
		ray.dy = item->left.case_y * 64 + item->left.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			pick_up_items(data, item);
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue ;
		}
		ray.dx = item->center.case_x * 64 + item->center.coo_x;
		ray.dy = item->center.case_y * 64 + item->center.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			pick_up_items(data, item);
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue ;
		}
		ray.dx = item->right.case_x * 64 + item->right.coo_x;
		ray.dy = item->right.case_y * 64 + item->right.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			pick_up_items(data, item);
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue ;
		}
		lst = lst->next;
	}
}

void	handle_move(t_map *map, t_mini *mini, t_data *data)
{
	int	i;

	mini->dy = 0;
	mini->dx = 0;
	mini->sdy = 0;
	mini->sdx = 0;
	i = 0;
	if (data->player.life <= 0)
		return ;
	while (i < KEYCODE_NB)
	{
		if (is_move_player(data, i))
		{
			calc_dx_dy(data, data->keycode[i], mini);
			if (mini->last_foot == MINI_LEFT)
				mini->last_foot = MINI_RIGHT;
			else
				mini->last_foot = MINI_LEFT;
			data->player_moved = true;
		}
		i++;
	}
	if (round(mini->sdy) == 0.0 && round(mini->sdx) == 0.0)
	{
		mini->sdy = 0;
		mini->sdx = 0;
	}
	else
		v_norm_sd(mini, data);
	if (round(mini->dy) == 0.0 && round(mini->dx) == 0.0)
	{
		mini->dy = 0;
		mini->dx = 0;
	}
	else
		v_norm_d(mini, data);
	mini->dx *= SPEED;
	mini->dy *= SPEED;
	mini->sdx *= SPEED;
	mini->sdy *= SPEED;
	if (data->player.damage.slow_frame_take > 0
		|| data->player.damage.slow_force_take > 0)
	{
		if (data->player.damage.slow_force_take > 100)
			data->player.damage.slow_force_take = 100;
		mini->dx *= (100 - data->player.damage.slow_force_take) / 100;
		mini->dy *= (100 - data->player.damage.slow_force_take) / 100;
		if (data->player.damage.slow_frame_take > 0)
			data->player.damage.slow_frame_take--;
		if (data->player.damage.slow_frame_take <= 0)
			data->player.damage.slow_force_take--;
	}
	recalc_x(data, mini, map);
	recalc_y(data, mini, map);
	movex(map, mini, data);
	movey(map, mini, data);
	handle_map_status(map, data, mini);
	if (data->status == FLOO_MAP)
		return ;
	calc_left_point_player(data);
	calc_right_point_player(data);
	data->player.left_before.coo_x = data->player.left.coo_x;
	data->player.left_before.coo_y = data->player.left.coo_y;
	data->player.left_before.case_x = data->player.left.case_x;
	data->player.left_before.case_y = data->player.left.case_y;
	data->player.right_before.coo_x = data->player.right.coo_x;
	data->player.right_before.coo_y = data->player.right.coo_y;
	data->player.right_before.case_x = data->player.right.case_x;
	data->player.right_before.case_y = data->player.right.case_y;
	if (mini->ny != data->player.coo.coo_y)
	{
		data->player.coo.coo_y = mini->ny;
		data->player.coo.case_y += mini->cy;
		data->player.left_before.coo_y += mini->sdy;
	}
	if (mini->nx != data->player.coo.coo_x)
	{
		data->player.coo.coo_x = mini->nx;
		data->player.coo.case_x += mini->cx;
		data->player.left_before.coo_x += mini->sdx;
	}
	calc_left_point_player(data);
	calc_right_point_player(data);
	try_hit_player(data);
}
