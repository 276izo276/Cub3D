#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <math.h>

static void	calc_sqrt_item(t_data *data, t_hitray *ray)
{
	data->ray[ray->i].items[ray->j]->dist = sqrt(((data->ray[ray->i].items
				[ray->j]->case_y
					- data->player.coo.case_y) * 64.0
				+ (data->ray[ray->i].items[ray->j]->coo_y
					- data->player.coo.coo_y))
			* ((data->ray[ray->i].items[ray->j]->case_y
					- data->player.coo.case_y) * 64.0
				+ (data->ray[ray->i].items[ray->j]->coo_y
					- data->player.coo.coo_y))
			+ ((data->ray[ray->i].items[ray->j]->case_x
					- data->player.coo.case_x) * 64.0
				+ (data->ray[ray->i].items[ray->j]->coo_x
					- data->player.coo.coo_x))
			* ((data->ray[ray->i].items[ray->j]->case_x
					- data->player.coo.case_x) * 64.0
				+ (data->ray[ray->i].items[ray->j]->coo_x
					- data->player.coo.coo_x)));
}

void	calc_item_value(t_data *data, t_hitray *ray, double x)
{
	calc_sqrt_item(data, ray);
	data->ray[ray->i].items[ray->j]->dist *= cos(atan(x));
	data->ray[ray->i].items[ray->j]->size = data->ray[ray->i].d_proj
		/ (double)(data->ray[ray->i].items[ray->j]->dist / 64.0);
	data->ray[ray->i].items[ray->j]->max_size = data->ray[ray->i].items
	[ray->j]->size * 0.5;
	data->ray[ray->i].items[ray->j]->htop = round(data->ray[ray->i].max_height
			- data->ray[ray->i].items[ray->j]->max_size);
	data->ray[ray->i].items[ray->j]->hbot = round(data->ray[ray->i].max_height
			+ data->ray[ray->i].items[ray->j]->max_size);
}
