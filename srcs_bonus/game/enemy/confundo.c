#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include <math.h>

void	confundo_calc_deg(t_enemy *enemy, double *dy, double *dx, double *deg)
{
	enemy->damage.confundo_frame_take--;
	if (enemy->damage.confundo_frame_take <= 0)
		enemy->damage.confundo_force_take = 0;
	if (*dy != 0)
	{
		*deg = atan((*dx / *dy)) / (M_PI / 180);
		if (*deg < 0)
			*deg = -*deg;
	}
	if (*dy < 0 && *dx < 0)
		*deg = 180 + *deg;
	else if (*dy < 0 && *dx > 0)
		*deg = 180 - *deg;
	else if (*dy > 0 && *dx < 0)
		*deg = 360 - *deg;
	else if (*dy == 0 && *dx < 0)
		*deg = 270;
	else if (*dy == 0 && *dx > 0)
		*deg = 90;
	else if (*dx == 0 && *dy < 0)
		*deg = 180;
}

int	confundo_move_enemy(t_enemy *enemy, t_data *data)
{
	double	deg;
	double	dy;
	double	dx;

	if (enemy->damage.confundo_force_take > 0)
	{
		calc_deg(&enemy->center, &data->player.coo, &enemy->rad, &enemy->deg);
		calc_dx_dy_enemy(&dy, &dx, enemy->rad);
		f_way(enemy);
		dy *= enemy->speed;
		dx *= enemy->speed;
		confundo_calc_deg(enemy, &dy, &dx, &deg);
		enemy->deg = deg;
		enemy->rad = enemy->deg * (M_PI / 180);
		set_before_point_enemy(enemy, data);
		cancel_move(data, enemy, dy, dx);
		calc_left_and_right_point(enemy, data);
		try_hit_enemys(enemy, data, 0);
		return (1);
	}
	return (0);
}
