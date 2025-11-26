#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "struct_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include <stdio.h>

void	calc_dx_dy_enemy(double *dy, double *dx, double rad)
{
	double	v_normalize;

	*dx = sin(rad);
	*dy = cos(rad);
	if (round(*dy) == 0.0 && round(*dx) == 0.0)
	{
		*dy = 0;
		*dx = 0;
	}
	else
	{
		v_normalize = sqrt(*dx * *dx + *dy * *dy);
		*dy = *dy / v_normalize;
		*dx = *dx / v_normalize;
	}
}

void	move_center_point(t_data *data, t_enemy *enemy, double *dy, double *dx)
{
	enemy->center.coo_x += *dx;
	enemy->center.coo_y += *dy;
	if (enemy->recalc_path > 0)
		enemy->recalc_path--;
	if (enemy->calc_path > 0)
		enemy->calc_path--;
	if (enemy->center.coo_x <= 0 || enemy->center.coo_x >= 64
		|| enemy->center.coo_y <= 0 || enemy->center.coo_y >= 64)
	{
		if (enemy->center.coo_x <= 0)
			enemy->center.coo_x += 63.999;
		if (enemy->center.coo_x >= 64)
			enemy->center.coo_x -= 63.999;
		if (enemy->center.coo_y <= 0)
			enemy->center.coo_y += 63.999;
		if (enemy->center.coo_y >= 64)
			enemy->center.coo_y -= 63.999;
		remove_child_path(enemy);
	}
	calc_left_and_right_point(enemy, data);
	try_hit_enemys(enemy, data, 0);
}

void	apply_slow_enemy(t_enemy *enemy, double *dx, double *dy)
{
	if (enemy->damage.slow_force_take > 100)
		enemy->damage.slow_force_take = 100;
	*dx *= (100 - enemy->damage.slow_force_take) / 100;
	*dy *= (100 - enemy->damage.slow_force_take) / 100;
	if (enemy->damage.slow_frame_take > 0)
		enemy->damage.slow_frame_take--;
	if (enemy->damage.slow_frame_take <= 0)
		enemy->damage.slow_force_take--;
}

static void	make_move_enemy(t_data *data, t_enemy *enemy)
{
	double	dy;
	double	dx;

	if (repulso_move_enemy(enemy, data))
		return ;
	if (confundo_move_enemy(enemy, data))
		return ;
	if (enemy->calc == true)
	{
		enemy->calc = false;
		calc_deg(&enemy->way->coo, &enemy->center, &enemy->rad, &enemy->deg);
	}
	set_before_point_enemy(enemy, data);
	path_move_enemy(enemy, data, &dx, &dy);
	if (repulso_neg_enemy(enemy, data))
		return ;
}

void	move_enemy(t_data *data)
{
	t_lst	*lst;
	t_enemy	*enemy;
	t_lst	*next;

	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		next = lst->next;
		if ((enemy_vision(data, enemy) && enemy->way) || enemy->way
			|| enemy->damage.confundo_force_take > 0)
			make_move_enemy(data, enemy);
		else
			gen_enemy_way(data, enemy);
		take_damage_enemy(enemy);
		low_life_enemy(enemy, data, &lst);
		enemy->nb_move++;
		lst = next;
	}
}
