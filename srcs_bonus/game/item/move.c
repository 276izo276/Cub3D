#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include <string.h>

static void	change_cell(t_item *item)
{
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
	change_cell(item);
	calc_left_point_item(item);
	calc_right_point_item(item);
}

static void	apply_attraction(t_item *attract, t_data *data, t_item *item)
{
	t_lst	*lst;
	t_enemy	*enemy;
	double	distance;

	if (!((item->type == VENTUS && !item->categ) || (item->type == BH
				&& item->categ)))
		return ;
	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		distance = calc_dist_attraction(attract, enemy);
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
	t_lst	*next;

	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		item = lst->dt;
		define_item_radius(item, data);
		apply_attraction(item, data, item);
		calc_left_point_item(item);
		calc_right_point_item(item);
		save_item_last_pos(item);
		make_move_item(item, item->speed);
		if (item_destruction(item, data) == true)
		{
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue ;
		}
		lst = lst->next;
	}
}
