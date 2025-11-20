#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "texture_bonus.h"

static void	norm_move(t_data *data, double *dx, double *dy)
{
	double	v_normalize;

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
	*dy *= data->player.radius;
	*dx *= data->player.radius;
}

void	change_case(t_fcoo *coo)
{
	if (coo->coo_x < 0)
	{
		coo->case_x--;
		coo->coo_x += 64;
	}
	else if (coo->coo_x > 64)
	{
		coo->case_x++;
		coo->coo_x = fmod(coo->coo_x, 64);
	}
	if (coo->coo_y < 0)
	{
		coo->case_y--;
		coo->coo_y += 64;
	}
	else if (coo->coo_y > 64)
	{
		coo->case_y++;
		coo->coo_y = fmod(coo->coo_y, 64);
	}
}

void	calc_left_point_player(t_data *data)
{
	double	rad;
	double	dy;
	double	dx;

	rad = data->map.mini.rad + (90 * (M_PI / 180));
	dx = sin(rad);
	dy = cos(rad);
	norm_move(data, &dx, &dy);
	data->player.left.coo_x = data->player.coo.coo_x + dx;
	data->player.left.coo_y = data->player.coo.coo_y + dy;
	data->player.left.case_x = data->player.coo.case_x;
	data->player.left.case_y = data->player.coo.case_y;
	change_case(&data->player.left);
}

void	calc_right_point_player(t_data *data)
{
	double	rad;
	double	dy;
	double	dx;

	rad = data->map.mini.rad - (90 * (M_PI / 180));
	dx = sin(rad);
	dy = cos(rad);
	norm_move(data, &dx, &dy);
	data->player.right.coo_x = data->player.coo.coo_x + dx;
	data->player.right.coo_y = data->player.coo.coo_y + dy;
	data->player.right.case_x = data->player.coo.case_x;
	data->player.right.case_y = data->player.coo.case_y;
	change_case(&data->player.right);
}
