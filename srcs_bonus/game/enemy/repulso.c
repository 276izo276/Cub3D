#include <math.h>
#include "cub3d_bonus.h"
#include "enemy_bonus.h"

int	repulso_neg_decal(t_enemy *enemy, double *dy, double *dx)
{
	double	diff_x;
	double	diff_y;
	double	decal;

	diff_x = (enemy->damage.hit.case_x * 64 + enemy->damage.hit.coo_x)
		- (enemy->center.case_x * 64 + enemy->center.coo_x);
	diff_y = (enemy->damage.hit.case_y * 64 + enemy->damage.hit.coo_y)
		- (enemy->center.case_y * 64 + enemy->center.coo_y);
	enemy->damage.dist = sqrt(diff_x * diff_x + diff_y * diff_y);
	decal = -(1000 / (enemy->damage.dist + 35)
			+ enemy->damage.repulso_force_take) / 4 - 1;
	if (decal > 0)
		return (1);
	if (enemy->damage.dist >= fabs(decal))
		enemy->damage.repulso_force_take = decal;
	else
	{
		enemy->damage.repulso_force_take = -enemy->damage.dist;
		enemy->damage.repulso_frame_take = enemy->damage.repulso_frame_take;
	}
	*dy *= fabs(enemy->damage.repulso_force_take)
		* enemy->damage.repulso_frame_take;
	*dx *= fabs(enemy->damage.repulso_force_take)
		* enemy->damage.repulso_frame_take;
	return (0);
}

int	repulso_neg_enemy(t_enemy *enemy, t_data *data)
{
	double	rad;
	double	deg;
	double	dy;
	double	dx;

	if (enemy->damage.repulso_force_take < 0)
	{
		calc_deg(&enemy->damage.hit, &enemy->center, &rad, &deg);
		calc_dx_dy_enemy(&dy, &dx, rad);
		f_way(enemy);
		if (repulso_neg_decal(enemy, &dy, &dx))
			return (1);
		f_way(enemy);
		enemy->damage.repulso_frame_take--;
		if (enemy->damage.repulso_frame_take <= 0)
			enemy->damage.repulso_force_take = 0;
		set_before_point_enemy(enemy, data);
		cancel_move(data, enemy, dy, dx);
		calc_left_and_right_point(enemy, data);
		try_hit_enemys(enemy, data, 1);
		return (1);
	}
	return (0);
}

int	repulso_move_enemy(t_enemy *enemy, t_data *data)
{
	double	dy;
	double	dx;
	double	deg;
	double	rad;

	if (enemy->damage.repulso_force_take > 0)
	{
		calc_deg(&enemy->center, &enemy->damage.hit, &rad, &deg);
		calc_dx_dy_enemy(&dy, &dx, rad);
		f_way(enemy);
		dy *= enemy->damage.repulso_force_take
			* enemy->damage.repulso_frame_take;
		dx *= enemy->damage.repulso_force_take
			* enemy->damage.repulso_frame_take;
		enemy->damage.repulso_frame_take--;
		if (enemy->damage.repulso_frame_take <= 0)
			enemy->damage.repulso_force_take = 0;
		set_before_point_enemy(enemy, data);
		cancel_move(data, enemy, dy, dx);
		calc_left_and_right_point(enemy, data);
		try_hit_enemys(enemy, data, 1);
		return (1);
	}
	return (0);
}
