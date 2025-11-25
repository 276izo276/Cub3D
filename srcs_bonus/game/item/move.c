#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>
#include <string.h>
#include "utils_bonus.h"

void	calc_left_point_item(t_item *item)
{
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;

	rad = item->rad + (90 * (M_PI / 180));
	dx = sin(rad);
	dy = cos(rad);
	// printf("dx>>%lf     dy>>%lf\n",dx,dy);
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
	item->left.coo_x = item->center.coo_x + dx;
	item->left.coo_y = item->center.coo_y + dy;
	item->left.case_x = item->center.case_x;
	item->left.case_y = item->center.case_y;
	if (item->left.coo_x < 0)
	{
		item->left.case_x--;
		item->left.coo_x += 64;
	}
	else if (item->left.coo_x > 64)
	{
		item->left.case_x++;
		item->left.coo_x = fmod(item->left.coo_x, 64);
	}
	if (item->left.coo_y < 0)
	{
		item->left.case_y--;
		item->left.coo_y += 64;
	}
	else if (item->left.coo_y > 64)
	{
		item->left.case_y++;
		item->left.coo_y = fmod(item->left.coo_y, 64);
	}
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
	// printf("dx>>%lf     dy>>%lf\n",dx,dy);
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
	item->right.coo_x = item->center.coo_x + dx;
	item->right.coo_y = item->center.coo_y + dy;
	item->right.case_x = item->center.case_x;
	item->right.case_y = item->center.case_y;
	if (item->right.coo_x < 0)
	{
		item->right.case_x--;
		item->right.coo_x += 64;
	}
	else if (item->right.coo_x > 64)
	{
		item->right.case_x++;
		item->right.coo_x = fmod(item->right.coo_x, 64);
	}
	if (item->right.coo_y < 0)
	{
		item->right.case_y--;
		item->right.coo_y += 64;
	}
	else if (item->right.coo_y > 64)
	{
		item->right.case_y++;
		item->right.coo_y = fmod(item->right.coo_y, 64);
	}
}

#include <stdio.h>


void	move_more_hit_pos_item(t_item *item)
{
	double	deg;
	double	rad;
	double	dx;
	double	dy;
	double	v_normalize;

	deg = 0;
	rad = 0;
	double	diff_x = (item->center_before.case_x * 64 + item->center_before.coo_x) - (item->center.case_x * 64 + item->center.coo_x);
	double	diff_y = (item->center_before.case_y * 64 + item->center_before.coo_y) - (item->center.case_y * 64 + item->center.coo_y);
	// printf("way >>> y>%d     x>%d",enemy->way->coo_y,enemy->way->coo_x);
	// printf("x>>>%lf     y>>>%lf\n",diff_x,diff_y);
	if (diff_y != 0)
	{
		deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
		if (deg < 0)
			deg = -deg;
	}
	if (diff_y < 0 && diff_x < 0)
		deg = 180 + deg;
	else if (diff_y < 0 && diff_x > 0)
		deg = 180 - deg;
	else if (diff_y > 0 && diff_x < 0)
		deg = 360 - deg;
	else if (diff_y == 0 && diff_x < 0)
		deg = 270;
	else if (diff_y == 0 && diff_x > 0)
		deg = 90;
	else if (diff_x == 0 && diff_y < 0)
		deg = 180;
	// printf("deg angle >>>%lf\n",deg);
	// printf("deg angle >>>%lf     player>>%lf\n",deg,data->map.mini.deg);
	// if (enemy->damage.confundo_force_take > 0)
	// {
	// 	f_way(enemy);
	// 	deg += 180;
	// }
	// deg += 180;
	rad = deg * (M_PI / 180);
	dx = sin(rad);
	dy = cos(rad);
	// printf("dx>>%lf     dy>>%lf\n",dx,dy);
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
	// double	ay;
	// double	ax;

	// ay = dy;
	// ax = dx;
	// if (ay < 0)
	// 	ay = -ay;
	// if (ax < 0)
	// 	ax = -ax;
	// if (ax < ay)
	// 	dy = -dy;
	// if (ay < ax)
	// 	dx = -dx;
	dx *= 2000;
	dy *= 2000;
	// printf("change hit pos dy>%lf   dx>%lf\n",dy,dx);
	item->damage.hit.coo_x += dx;
	item->damage.hit.coo_y += dy;
}

int	try_hit_items(t_item *elem, t_data *data)
{
	t_enemy		*enemy;
	// t_item		*item;
	t_lst		*lst;
	t_hitray	ray;
	bool		hit;

	hit = false;
	if ((elem->nb_move >= 5 && elem->damage.which_coa_do == data->player.coa) || elem->damage.which_coa_do != data->player.coa)
	{
	//DBG1printf("a\n");
		ray.ax = elem->left.case_x * 64 + elem->left.coo_x;
		ray.ay = elem->left.case_y * 64 + elem->left.coo_y;
		ray.bx = elem->right.case_x * 64 + elem->right.coo_x;
		ray.by = elem->right.case_y * 64 + elem->right.coo_y;
		ray.cx = elem->left_before.case_x * 64 + elem->left_before.coo_x;
		ray.cy = elem->left_before.case_y * 64 + elem->left_before.coo_y;
		if (hit == false)
		{
			ray.dx = data->player.coo.case_x * 64 + data->player.coo.coo_x;
			ray.dy = data->player.coo.case_y * 64 + data->player.coo.coo_y;
			calc_scal(&ray);
			if (ray.hit == true)
			{
				apply_damage(&data->player.damage, &elem->damage);
				hit = true;
			}
		}
		if (hit == false)
		{
			ray.dx = data->player.left.case_x * 64 + data->player.left.coo_x;
			ray.dy = data->player.left.case_y * 64 + data->player.left.coo_y;
			calc_scal(&ray);
			if (ray.hit == true)
			{
				apply_damage(&data->player.damage, &elem->damage);
				hit = true;
			}
		}
		if (hit == false)
		{
			ray.dx = data->player.right.case_x * 64 + data->player.right.coo_x;
			ray.dy = data->player.right.case_y * 64 + data->player.right.coo_y;
			calc_scal(&ray);
			if (ray.hit == true)
			{
				apply_damage(&data->player.damage, &elem->damage);
				hit = true;
			}
		}
	}
	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		if (enemy->type != DEMENTOR && elem->type == EXPECTO_PATRONUM && !elem->categ)
		{
			lst =lst->next;
			continue;
		}
		ray.ax = elem->left.case_x * 64 + elem->left.coo_x;
		ray.ay = elem->left.case_y * 64 + elem->left.coo_y;
		ray.bx = elem->right.case_x * 64 + elem->right.coo_x;
		ray.by = elem->right.case_y * 64 + elem->right.coo_y;
		ray.cx = elem->left_before.case_x * 64 + elem->left_before.coo_x;
		ray.cy = elem->left_before.case_y * 64 + elem->left_before.coo_y;
		// printf("\nax>%lf   ay>%lf\n",ray.ax, ray.ay);
		// printf("bx>%lf   by>%lf\n",ray.bx, ray.by);
		// printf("cx>%lf   cy>%lf\n",ray.cx, ray.cy);
		ray.dx = enemy->left.case_x * 64 + enemy->left.coo_x;
		ray.dy = enemy->left.case_y * 64 + enemy->left.coo_y;
		// printf("dx>%lf   dy>%lf\n",ray.dx, ray.dy);
		calc_scal(&ray);
		if (ray.hit == true)
		{
			// printf("----------------------------------------HIT\n");
			move_more_hit_pos_item(elem);
			apply_damage(&enemy->damage, &elem->damage);
			lst = lst->next;
			hit = true;
			continue;
		}
		ray.dx = enemy->center.case_x * 64 + enemy->center.coo_x;
		ray.dy = enemy->center.case_y * 64 + enemy->center.coo_y;
		// printf("dx>%lf   dy>%lf\n",ray.dx, ray.dy);
		calc_scal(&ray);
		if (ray.hit == true)
		{
			// printf("----------------------------------------HIT\n");
			move_more_hit_pos_item(elem);
			apply_damage(&enemy->damage, &elem->damage);
			lst = lst->next;
			hit = true;
			continue;
		}
		ray.dx = enemy->right.case_x * 64 + enemy->right.coo_x;
		ray.dy = enemy->right.case_y * 64 + enemy->right.coo_y;
		// printf("dx>%lf   dy>%lf\n",ray.dx, ray.dy);
		calc_scal(&ray);
		if (ray.hit == true)
		{
			// printf("----------------------------------------HIT\n");
			move_more_hit_pos_item(elem);
			apply_damage(&enemy->damage, &elem->damage);
			lst = lst->next;
			hit = true;
			continue;
		}

		ray.ax = elem->center.case_x * 64 + elem->center.coo_x;
		ray.ay = elem->center.case_y * 64 + elem->center.coo_y;
		ray.bx = elem->center_before.case_x * 64 + elem->center_before.coo_x;
		ray.by = elem->center_before.case_y * 64 + elem->center_before.coo_y;

		ray.cx = enemy->left.case_x * 64 + enemy->left.coo_x;
		ray.cy = enemy->left.case_y * 64 + enemy->left.coo_y;
		ray.dx = enemy->center.case_x * 64 + enemy->center.coo_x;
		ray.dy = enemy->center.case_y * 64 + enemy->center.coo_y;
		calc_delta(&ray);
		if (ray.hit == true)
		{
			move_more_hit_pos_item(elem);
			apply_damage(&enemy->damage, &elem->damage);
			lst = lst->next;
			hit = true;
			continue;
		}
		ray.cx = enemy->center.case_x * 64 + enemy->center.coo_x;
		ray.cy = enemy->center.case_y * 64 + enemy->center.coo_y;
		ray.dx = enemy->right.case_x * 64 + enemy->right.coo_x;
		ray.dy = enemy->right.case_y * 64 + enemy->right.coo_y;
		calc_delta(&ray);
		if (ray.hit == true)
		{
			move_more_hit_pos_item(elem);
			apply_damage(&enemy->damage, &elem->damage);
			lst = lst->next;
			hit = true;
			continue;
		}
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

		// if (distance < tornado->radius * 20)
		// {
		// 	printf("\n\ndistance>%lf\n",distance);
		// 	if (distance >= fabs(tornado->damage.repulso_force_do / (distance * 0.5)))
		// 	{
		// 		// pritnf("in\n");
		// 		enemy->damage.repulso_force_take = tornado->damage.repulso_force_do / (distance * 0.5);
		// 		enemy->damage.repulso_frame_take = tornado->damage.repulso_frame_do;
		// 		printf("1__repulso force >>> %f  frame >> %f\n", enemy->damage.repulso_force_take, enemy->damage.repulso_frame_take);
		// 	}
		// 	else
		// 	{
		// 		enemy->damage.repulso_force_take = -distance * .5;
		// 		enemy->damage.repulso_frame_take = tornado->damage.repulso_frame_do;
		// 		printf("1__repulso force >>> %f  frame >> %f\n", enemy->damage.repulso_force_take, enemy->damage.repulso_frame_take);
		// 	}
		// 	apply_damage(&enemy->damage, &tornado->damage);
		// 	// enemy->damage.repulso_frame_take = 15;
		// }
		lst = lst->next;
	}
	attract->nb_move++;

}

void	move_item(t_data *data)
{
	t_lst	*lst;
	t_item	*item;
	//DBG1printf("1\n");
	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		//DBG1printf("2\n");
		item = lst->dt;
		//DBG1printf("3\n");
		item->deg += item->deg_rotate;
		item->rad = item->deg * (M_PI / 180);
		if (item->type == BH && item->categ)
			item->radius += .1;
		if (item->type == EXPECTO_PATRONUM && !item->categ)
			item->radius += .3;
		else if (item->type == ANIM_DEATH && !item->categ)
			item->radius += 1.5;
		if (item->type == VENTUS && !item->categ)
		{
			// printf("expecto patronum uo radius\n");
			item->radius += .1;
		}
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
			// printf("rotate >>> %f\n", item->deg);
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
		// printf("before move item after start coo y>%lf, x>%lf\n",item->center.coo_y,item->center.coo_x);
		// if (item->nb_move >= 1)
		make_move_item(item, item->speed);
		// printf("after move item after start coo y>%lf, x>%lf\n",item->center.coo_y,item->center.coo_x);
		if (((try_hit_items(item, data) && (item->type != BH && item->categ) && (item->type != VENTUS && item->type != EXPECTO_PATRONUM && item->type != ANIM_DEATH && !item->categ)) ||
			(item->center.case_y >= data->map.tabmap_height
			|| item->center.case_y < 0
			|| item->center.case_x >= ft_strlen(data->map.tabmap[item->center.case_y])
			|| item->center.case_x < 0)
			|| data->map.tabmap[item->center.case_y][item->center.case_x] == ' '
			|| data->map.tabmap[item->center.case_y][item->center.case_x] == '1')
			)
		{
			//DBG1printf("remove elem lst\n");
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
		//DBG1printf("4\n");
	}
}
