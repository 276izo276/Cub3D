#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <math.h>

static void	define_value_hit(t_data *data, t_hitray *ray, t_door *door, int i)
{
	(*ray).j = -1;
	while (++(*ray).j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door)
		if (data->ray[i].items[(*ray).j]->use == false)
			break ;
	if (door->is_floo && door->is_floo_open)
		data->ray[i].items[(*ray).j]->type = FLOO_OPEN;
	else if (door->is_floo && !door->is_floo_open)
		data->ray[i].items[(*ray).j]->type = FLOO_CLOSE;
	else
		data->ray[i].items[(*ray).j]->type = DOOR;
	data->ray[i].items[(*ray).j]->use = true;
	data->ray[i].items[(*ray).j]->door = door;
	data->ray[i].items[(*ray).j]->case_y = (int)((*ray).hy / 64);
	data->ray[i].items[(*ray).j]->case_x = (int)((*ray).hx / 64);
	data->ray[i].items[(*ray).j]->coo_y = fmod((*ray).hy, 64);
	data->ray[i].items[(*ray).j]->coo_x = fmod((*ray).hx, 64);
	data->ray[i].items[(*ray).j]->posx = (*ray).t;
	data->ray[i].items[(*ray).j]->side = BASIC;
	if (((*ray).delta_x < 0 && door->is_verti) || ((*ray).delta_y > 0
			&& !door->is_verti))
		data->ray[i].items[(*ray).j]->side = REVERSED;
}

void	ray_try_hit_door(t_data *data, int i, double x, t_lst *lst)
{
	t_hitray	ray;
	t_door		*door;

	ray.i = i;
	while (lst)
	{
		door = lst->dt;
		ray.delta_x = data->ray[ray.i].delta_x;
		ray.delta_y = data->ray[ray.i].delta_y;
		ray.ax = door->first_p.x + door->coo.x * 64;
		ray.ay = door->first_p.y + door->coo.y * 64;
		ray.bx = door->second_p.x + door->coo.x * 64;
		ray.by = door->second_p.y + door->coo.y * 64;
		ray.cx = data->ray[ray.i].coo_x + data->ray[ray.i].case_x * 64;
		ray.cy = data->ray[ray.i].coo_y + data->ray[ray.i].case_y * 64;
		ray.radius = 64;
		calc_end_point(&ray);
		calc_delta(&ray);
		if (ray.hit == true)
		{
			define_value_hit(data, &ray, door, i);
			calc_item_value(data, &ray, x);
		}
		lst = lst->next;
	}
}
