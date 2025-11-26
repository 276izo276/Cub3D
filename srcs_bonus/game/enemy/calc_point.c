#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <math.h>

void	calc_deg(t_fcoo *po, t_fcoo *end, double *rad, double *deg)
{
	double	diff_x;
	double	diff_y;

	*deg = 0;
	diff_x = (po->case_x * 64 + po->coo_x) - (end->case_x * 64 + end->coo_x);
	diff_y = (po->case_y * 64 + po->coo_y) - (end->case_y * 64 + end->coo_y);
	if (diff_y != 0)
	{
		*deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
		if (*deg < 0)
			*deg = -(*deg);
	}
	if (diff_y < 0 && diff_x < 0)
		*deg = 180 + *deg;
	else if (diff_y < 0 && diff_x > 0)
		*deg = 180 - *deg;
	else if (diff_y > 0 && diff_x < 0)
		*deg = 360 - *deg;
	else if (diff_y == 0 && diff_x < 0)
		*deg = 270;
	else if (diff_y == 0 && diff_x > 0)
		*deg = 90;
	else if (diff_x == 0 && diff_y < 0)
		*deg = 180;
	*rad = *deg * (M_PI / 180);
}

void	left_y_replace(int *cy, int *new_y, t_data *data, t_enemy *enemy)
{
	double	diff;

	if (*cy != 0 && !(*new_y < 0 || *new_y > data->map.tabmap_height
			|| enemy->left.case_x < 0
			|| enemy->left.case_x >= ft_strlen(data->map.tabmap[*new_y]))
		&& data->map.tabmap[*new_y][enemy->left.case_x] != '1')
	{
		diff = 0;
		if (*cy > 0)
			diff = 64 - enemy->left.coo_y;
		else if (*cy < 0)
			diff = -enemy->left.coo_y - 0.001;
		enemy->right.coo_y += diff;
		enemy->center.coo_y += diff;
		enemy->left.coo_y = fmod(enemy->left.coo_y + diff + 64, 64);
		enemy->left.case_y += *cy;
	}
}

void	left_x_replace(int *cx, int *new_x, t_data *data, t_enemy *enemy)
{
	double	diff;

	if (*cx != 0 && !(enemy->left.case_y < 0
			|| enemy->left.case_y > data->map.tabmap_height || *new_x < 0
			|| *new_x >= ft_strlen(data->map.tabmap[enemy->left.case_y]))
		&& data->map.tabmap[enemy->left.case_y][*new_x] != '1')
	{
		diff = 0;
		if (*cx > 0)
			diff = 64 - enemy->left.coo_x;
		else if (*cx < 0)
			diff = -enemy->left.coo_x - 0.001;
		enemy->right.coo_x += diff;
		enemy->center.coo_x += diff;
		enemy->left.coo_x = fmod(enemy->left.coo_x + diff + 64, 64);
		enemy->left.case_x += *cx;
	}
}

void	left_case_replace(t_enemy *enemy, t_data *data)
{
	int	cy;
	int	cx;
	int	new_x;
	int	new_y;

	if (enemy->left.case_y < 0 || enemy->left.case_y > data->map.tabmap_height
		|| enemy->left.case_x < 0
		|| enemy->left.case_x >= ft_strlen(data->map.tabmap[enemy->left.case_y])
		|| data->map.tabmap[enemy->left.case_y][enemy->left.case_x] == '1')
	{
		cx = enemy->center.case_x - enemy->left.case_x;
		cy = enemy->center.case_y - enemy->left.case_y;
		new_x = enemy->left.case_x + cx;
		new_y = enemy->left.case_y + cy;
		left_y_replace(&cy, &new_y, data, enemy);
		left_x_replace(&cx, &new_x, data, enemy);
	}
}

void	calc_left_and_right_point(t_enemy *enemy, t_data *data)
{
	calc_deg(&data->player.coo, &enemy->center, &enemy->aff_rad,
		&enemy->aff_deg);
	calc_left_point(enemy);
	calc_right_point(enemy);
	left_case_replace(enemy, data);
	right_case_replace(enemy, data);
}
