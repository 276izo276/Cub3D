#include "struct_bonus.h"
#include "cub3d_bonus.h"
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

int	try_hit_items(t_item *elem, t_data *data)
{
	t_enemy		*enemy;
	// t_item		*item;
	t_lst		*lst;
	t_hitray	ray;
	bool		hit;

	hit = false;
	//DBG1printf("a\n");
	ray.ax = elem->left.case_x * 64 + elem->left.coo_x;
	ray.ay = elem->left.case_y * 64 + elem->left.coo_y;
	ray.bx = elem->right.case_x * 64 + elem->right.coo_x;
	ray.by = elem->right.case_y * 64 + elem->right.coo_y;
	ray.cx = elem->left_before.case_x * 64 + elem->left_before.coo_x;
	ray.cy = elem->left_before.case_y * 64 + elem->left_before.coo_y;
	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		ray.dx = enemy->left.case_x * 64 + enemy->left.coo_x;
		ray.dy = enemy->left.case_y * 64 + enemy->left.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			enemy->damage.damage_take += elem->damage.damage_do;
			enemy->damage.slow_take += elem->damage.slow_do;
			enemy->damage.poison_take += elem->damage.poison_do;
			enemy->damage.fire_take += elem->damage.fire_do;
			lst = lst->next;
			hit = true;
			continue;
		}
		ray.dx = enemy->center.case_x * 64 + enemy->center.coo_x;
		ray.dy = enemy->center.case_y * 64 + enemy->center.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			enemy->damage.damage_take += elem->damage.damage_do;
			enemy->damage.slow_take += elem->damage.slow_do;
			enemy->damage.poison_take += elem->damage.poison_do;
			enemy->damage.fire_take += elem->damage.fire_do;
			lst = lst->next;
			hit = true;
			continue;
		}
		ray.dx = enemy->right.case_x * 64 + enemy->right.coo_x;
		ray.dy = enemy->right.case_y * 64 + enemy->right.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			enemy->damage.damage_take += elem->damage.damage_do;
			enemy->damage.slow_take += elem->damage.slow_do;
			enemy->damage.poison_take += elem->damage.poison_do;
			enemy->damage.fire_take += elem->damage.fire_do;
			lst = lst->next;
			hit = true;
			continue;
		}
		lst = lst->next;
	}
	ray.dx = data->player.coo.case_x * 64 + data->player.coo.coo_x;
	ray.dy = data->player.coo.case_y * 64 + data->player.coo.coo_y;
	calc_scal(&ray);
	if (ray.hit == true)
	{
		data->player.damage.damage_take += elem->damage.damage_do;
		data->player.damage.slow_take += elem->damage.slow_do;
		data->player.damage.poison_take += elem->damage.poison_do;
		data->player.damage.fire_take += elem->damage.fire_do;
		hit = true;
	}
	//DBG1printf("b\n");
	// enemy = lst->dt;
	// bzero(ray, sizeof(t_hitray));
	// ray.ax = elem->left.case_x * 64 + elem->left.coo_x;
	// ray.ay = elem->left.case_y * 64 + elem->left.coo_y;
	// ray.bx = elem->right_before.case_x * 64 + elem->right_before.coo_x;
	// ray.by = elem->right_before.case_y * 64 + elem->right_before.coo_y;
	// ray.cx = data->player.left.case_x * 64 + enemy->left.coo_x;
	// ray.cy = enemy->left.case_y * 64 + enemy->left.coo_y;
	// ray.dx = enemy->right.case_x * 64 + enemy->right.coo_x;
	// ray.dy = enemy->right.case_y * 64 + enemy->right.coo_y;
	// calc_delta(&ray);
	// if (ray.hit == true)
	// {
	// 	enemy->damage.damage_take += elem->damage.damage_do;
	// 	enemy->damage.slow_take += elem->damage.slow_do;
	// 	enemy->damage.poison_take += elem->damage.poison_do;
	// 	enemy->damage.fire_take += elem->damage.fire_do;
	// 	lst = lst->next;
	// 	hit = true;
	// 	return (1);
	// }
	// bzero(ray, sizeof(t_hitray));
	// ray.ax = elem->right.case_x * 64 + elem->right.coo_x;
	// ray.ay = elem->right.case_y * 64 + elem->right.coo_y;
	// ray.bx = elem->left_before.case_x * 64 + elem->left_before.coo_x;
	// ray.by = elem->left_before.case_y * 64 + elem->left_before.coo_y;
	// ray.cx = enemy->left.case_x * 64 + enemy->left.coo_x;
	// ray.cy = enemy->left.case_y * 64 + enemy->left.coo_y;
	// ray.dx = enemy->right.case_x * 64 + enemy->right.coo_x;
	// ray.dy = enemy->right.case_y * 64 + enemy->right.coo_y;
	// calc_delta(&ray);
	// if (ray.hit == true)
	// {
	// 	enemy->damage.damage_take += elem->damage.damage_do;
	// 	enemy->damage.slow_take += elem->damage.slow_do;
	// 	enemy->damage.poison_take += elem->damage.poison_do;
	// 	enemy->damage.fire_take += elem->damage.fire_do;
	// 	lst = lst->next;
	// 	hit = true;
	// 	return (1);
	// }
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
	calc_left_point_item(item);
	calc_right_point_item(item);
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
		item->rad = item->deg * (M_PI / 180);
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
		// item->center_before.coo_x = item->center.coo_x;
		// item->center_before.coo_y = item->center.coo_y;
		// item->center_before.case_x = item->center.case_x;
		// item->center_before.case_y = item->center.case_y;
		// printf("before move item after start coo y>%lf, x>%lf\n",item->center.coo_y,item->center.coo_x);
		make_move_item(item, item->speed);
		// printf("after move item after start coo y>%lf, x>%lf\n",item->center.coo_y,item->center.coo_x);
		if (try_hit_items(item, data)
			|| data->map.tabmap[item->center.case_y][item->center.case_x] == '1')
		{
			//DBG1printf("remove elem lst\n");
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
