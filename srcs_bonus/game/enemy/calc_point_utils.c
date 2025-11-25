#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>

void	recalc_fcoo(t_fcoo *coo, t_fcoo *center, double dy, double dx)
{
	coo->coo_x = center->coo_x + dx;
	coo->coo_y = center->coo_y + dy;
	coo->case_x = center->case_x;
	coo->case_y = center->case_y;
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

void	calc_left_point(t_enemy *enemy)
{
	double	dx;
	double	dy;
	double	v_normalize;
	double	aff_rad;

	aff_rad = enemy->aff_rad + (90 * (M_PI / 180));
	dx = sin(aff_rad);
	dy = cos(aff_rad);
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
	dy *= enemy->radius;
	dx *= enemy->radius;
	recalc_fcoo(&enemy->left, &enemy->center, dy, dx);
}

void	calc_right_point(t_enemy *enemy)
{
	double	dy;
	double	dx;
	double	v_normalize;
	double	aff_rad;

	aff_rad = enemy->aff_rad - (90 * (M_PI / 180));
	dx = sin(aff_rad);
	dy = cos(aff_rad);
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
	dy *= enemy->radius;
	dx *= enemy->radius;
	recalc_fcoo(&enemy->right, &enemy->center, dy, dx);
}
