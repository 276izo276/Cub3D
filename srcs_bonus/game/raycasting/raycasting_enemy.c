#include "cub3d_bonus.h"
#include <math.h>

static void	set_orientation_right(t_enemy *enemy, t_data *data, int i,
		t_hitray *ray)
{
	if ((enemy->deg >= ray->deg && enemy->deg <= ray->deg + 45)
		|| (enemy->deg <= ray->deg && enemy->deg <= ray->deg - 315))
		data->ray[i].items[ray->j]->side = RIGHT;
	ray->deg = fmod(enemy->aff_deg + 22.5, 360);
	if ((enemy->deg >= ray->deg && enemy->deg <= ray->deg + 45)
		|| (enemy->deg <= ray->deg && enemy->deg <= ray->deg - 315))
		data->ray[i].items[ray->j]->side = RIGHT_FRONT;
	ray->deg = fmod(enemy->aff_deg + 112.5, 360);
	if ((enemy->deg >= ray->deg && enemy->deg <= ray->deg + 45)
		|| (enemy->deg <= ray->deg && enemy->deg <= ray->deg - 315))
		data->ray[i].items[ray->j]->side = RIGHT_BACK;
	ray->deg = fmod(enemy->aff_deg + 247.5, 360);
}

static void	set_orientation(t_enemy *enemy, t_data *data, int i, t_hitray *ray)
{
	set_orientation_right(enemy, data, i, ray);
	if ((enemy->deg >= ray->deg && enemy->deg <= ray->deg + 45)
		|| (enemy->deg <= ray->deg && enemy->deg <= ray->deg - 315))
		data->ray[i].items[ray->j]->side = LEFT;
	ray->deg = fmod(enemy->aff_deg + 202.5, 360);
	if ((enemy->deg >= ray->deg && enemy->deg <= ray->deg + 45)
		|| (enemy->deg <= ray->deg && enemy->deg <= ray->deg - 315))
		data->ray[i].items[ray->j]->side = LEFT_BACK;
	ray->deg = fmod(enemy->aff_deg + 292.5, 360);
	if ((enemy->deg >= ray->deg && enemy->deg <= ray->deg + 45)
		|| (enemy->deg <= ray->deg && enemy->deg <= ray->deg - 315))
		data->ray[i].items[ray->j]->side = LEFT_FRONT;
	ray->deg = fmod(enemy->aff_deg + 157.5, 360);
	if ((enemy->deg >= ray->deg && enemy->deg <= ray->deg + 45)
		|| (enemy->deg <= ray->deg && enemy->deg <= ray->deg - 315))
		data->ray[i].items[ray->j]->side = BACK;
}

static void	define_value_hit(t_data *data, t_hitray *ray, t_enemy *enemy, int i)
{
	ray->j = -1;
	while (++ray->j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door + data->map.nb_floo)
		if (data->ray[i].items[ray->j]->use == false)
			break ;
	data->ray[i].items[ray->j]->type = ENEMY;
	data->ray[i].items[ray->j]->use = true;
	data->ray[i].items[ray->j]->enemy = enemy;
	data->ray[i].items[ray->j]->case_y = (int)(ray->hy / 64);
	data->ray[i].items[ray->j]->case_x = (int)(ray->hx / 64);
	data->ray[i].items[ray->j]->coo_y = fmod(ray->hy, 64);
	data->ray[i].items[ray->j]->coo_x = fmod(ray->hx, 64);
	data->ray[i].items[ray->j]->posx = ray->t;
	data->ray[i].items[ray->j]->side = FRONT;
	ray->deg = fmod(enemy->aff_deg + 67.5, 360);
	set_orientation(enemy, data, i, ray);
}

void	ray_try_hit_enemy(t_data *data, int i, double x, t_lst *lst)
{
	t_hitray	ray;
	t_enemy		*enemy;

	ray.i = i;
	while (lst)
	{
		enemy = lst->dt;
		ray.delta_x = data->ray[ray.i].delta_x;
		ray.delta_y = data->ray[ray.i].delta_y;
		ray.ax = enemy->left.coo_x + enemy->left.case_x * 64;
		ray.ay = enemy->left.coo_y + enemy->left.case_y * 64;
		ray.bx = enemy->right.coo_x + enemy->right.case_x * 64;
		ray.by = enemy->right.coo_y + enemy->right.case_y * 64;
		ray.cx = data->ray[ray.i].coo_x + data->ray[ray.i].case_x * 64;
		ray.cy = data->ray[ray.i].coo_y + data->ray[ray.i].case_y * 64;
		ray.radius = enemy->radius;
		calc_end_point(&ray);
		calc_delta(&ray);
		if (ray.hit == true)
		{
			define_value_hit(data, &ray, enemy, i);
			calc_item_value(data, &ray, x);
		}
		lst = lst->next;
	}
}
