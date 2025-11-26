#include "struct_bonus.h"
#include "utils_bonus.h"
#include <math.h>

void	right_y_replace(int *cy, int *new_y, t_data *data, t_enemy *enemy)
{
	double	diff;

	if (*cy != 0 && !(*new_y < 0 || *new_y > data->map.tabmap_height
			|| enemy->right.case_x < 0
			|| enemy->right.case_x >= ft_strlen(data->map.tabmap[*new_y]))
		&& data->map.tabmap[*new_y][enemy->right.case_x] != '1')
	{
		diff = 0;
		if (*cy > 0)
			diff = 64 - enemy->right.coo_y;
		else if (*cy < 0)
			diff = -enemy->right.coo_y - 0.001;
		enemy->left.coo_y += diff;
		enemy->center.coo_y += diff;
		enemy->right.coo_y = fmod(enemy->right.coo_y + diff + 64, 64);
		enemy->right.case_y += *cy;
	}
}

void	right_x_replace(int *cx, int *new_x, t_data *data, t_enemy *enemy)
{
	double	diff;

	if (*cx != 0 && !(enemy->right.case_y < 0
			|| enemy->right.case_y > data->map.tabmap_height || *new_x < 0
			|| *new_x >= ft_strlen(data->map.tabmap[enemy->right.case_y]))
		&& data->map.tabmap[enemy->right.case_y][*new_x] != '1')
	{
		diff = 0;
		if (*cx > 0)
			diff = 64 - enemy->right.coo_x;
		else if (*cx < 0)
			diff = -enemy->right.coo_x - 0.001;
		enemy->left.coo_x += diff;
		enemy->center.coo_x += diff;
		enemy->right.coo_x = fmod(enemy->right.coo_x + diff + 64, 64);
		enemy->right.case_x += *cx;
	}
}

void	right_case_replace(t_enemy *enemy, t_data *data)
{
	int	cy;
	int	cx;
	int	new_x;
	int	new_y;

	if (enemy->right.case_y < 0 || enemy->right.case_y > data->map.tabmap_height
		|| enemy->right.case_x < 0
		|| enemy->right.case_x >= ft_strlen(data->map.tabmap[
				enemy->right.case_y])
		|| data->map.tabmap[enemy->right.case_y][enemy->right.case_x] == '1')
	{
		cx = enemy->center.case_x - enemy->right.case_x;
		cy = enemy->center.case_y - enemy->right.case_y;
		new_x = enemy->right.case_x + cx;
		new_y = enemy->right.case_y + cy;
		right_y_replace(&cy, &new_y, data, enemy);
		right_x_replace(&cx, &new_x, data, enemy);
	}
}
