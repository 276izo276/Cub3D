#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>

#include <stdio.h>

static void	calc_sqrt_item(t_data *data, t_hitray *ray)
{
	// printf("CASE_Y>>>>%d\n",data->ray[i].enemys[j]->case_y);
	// printf("CASE_X>>>>%d\n",data->ray[i].enemys[j]->case_x);
	// printf("COO_Y>>>>%lf\n",data->ray[i].enemys[j]->coo_y);
	// printf("COO_X>>>>%lf\n",data->ray[i].enemys[j]->coo_x);
	// printf("CASE_Y>>>>%d\n",data->ray[i].enemys[j]->case_y);
	// printf("CASE_X>>>>%d\n",data->ray[i].enemys[j]->case_x);
	// printf("COO_Y>>>>%lf\n",data->ray[i].enemys[j]->coo_y);
	// printf("COO_X>>>>%lf\n",data->ray[i].enemys[j]->coo_x);
	data->ray[ray->i].items[ray->j]->dist = sqrt(((data->ray[ray->i].items[ray->j]->case_y
		- data->player.coo.case_y) * 64.0 + (data->ray[ray->i].items[ray->j]->coo_y
		- data->player.coo.coo_y)) * ((data->ray[ray->i].items[ray->j]->case_y
		- data->player.coo.case_y) * 64.0 + (data->ray[ray->i].items[ray->j]->coo_y
		- data->player.coo.coo_y)) + ((data->ray[ray->i].items[ray->j]->case_x
		- data->player.coo.case_x) * 64.0 + (data->ray[ray->i].items[ray->j]->coo_x
		- data->player.coo.coo_x)) * ((data->ray[ray->i].items[ray->j]->case_x
		- data->player.coo.case_x) * 64.0 + (data->ray[ray->i].items[ray->j]->coo_x
		- data->player.coo.coo_x)));
	// printf("dist enemy >>%lf\n",data->ray[i].enemys[j]->dist_enemy);
}

static void	calc_item_value(t_data *data, t_hitray *ray, double x)
{
	calc_sqrt_item(data, ray);
	data->ray[ray->i].items[ray->j]->dist *= cos(atan(x));
	data->ray[ray->i].items[ray->j]->size = data->ray[ray->i].d_proj
		/ (double)(data->ray[ray->i].items[ray->j]->dist / 64.0);
	data->ray[ray->i].items[ray->j]->max_size = data->ray[ray->i].items[ray->j]->size * 0.5;
	data->ray[ray->i].items[ray->j]->htop = round(data->ray[ray->i].max_height
			- data->ray[ray->i].items[ray->j]->max_size);
	data->ray[ray->i].items[ray->j]->hbot = round(data->ray[ray->i].max_height
			+ data->ray[ray->i].items[ray->j]->max_size);
}

void	try_hit_item(t_data *data, int i, double x)
{
	t_hitray	ray;
	t_lst		*lst;
	t_item		*item;
	t_enemy		*enemy;
	t_door		*door;

	lst = get_first_elem_lst(data->item);
	ft_bzero(&ray,sizeof(t_hitray));
	ray.i = i;
	while (lst)
	{
		item = lst->dt;
		ray.delta_x = data->ray[ray.i].delta_x;
		ray.delta_y = data->ray[ray.i].delta_y;
		ray.ax = item->left.coo_x + item->left.case_x * 64;
		ray.ay = item->left.coo_y + item->left.case_y * 64;
		ray.bx = item->right.coo_x + item->right.case_x * 64;
		ray.by = item->right.coo_y + item->right.case_y * 64;
		ray.cx = data->ray[ray.i].coo_x + data->ray[ray.i].case_x * 64;
		ray.cy = data->ray[ray.i].coo_y + data->ray[ray.i].case_y * 64;
		ray.radius = item->radius;
		calc_end_point(&ray);
		calc_delta(&ray);
		if (ray.hit == true)
		{
			ray.j = -1;
			while (++ray.j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door)
				if (data->ray[i].items[ray.j]->use == false)
					break ;
			data->ray[i].items[ray.j]->type = ITEM;
			data->ray[i].items[ray.j]->use = true;
			data->ray[i].items[ray.j]->item = item;
			// printf("hy>>%lf       hx>>%lf\n",ray.hy,ray.hx);
			data->ray[i].items[ray.j]->case_y = (int)(ray.hy / 64);
			data->ray[i].items[ray.j]->case_x = (int)(ray.hx / 64);
			data->ray[i].items[ray.j]->coo_y = fmod(ray.hy, 64);
			data->ray[i].items[ray.j]->coo_x = fmod(ray.hx, 64);
			data->ray[i].items[ray.j]->posx = ray.t;
			data->ray[i].items[ray.j]->side = FRONT;
			ray.deg = fmod(data->ray[i].deg + 360 - 90, 360);
			if ((ray.deg <= item->deg && ray.deg + 180 >= item->deg)
				|| (ray.deg >= item->deg && !(ray.deg - 180 <= item->deg)))
				data->ray[i].items[ray.j]->side = BACK;
			// data->ray[i].items[ray.j]->texture = item->front_img;
			// if (data->ray[i].items[ray.j]->side == BACK)
				// data->ray[i].items[ray.j]->texture = item->back_img;
			calc_item_value(data, &ray, x);
			// printf("HIT item RAY\n");
			// printf("HIT COO     case_y>%d   case_x>%d     coo_y>%lf    coo_x>%lf\n",
			// data->ray[i].items[ray.j]->case_y,
			// data->ray[i].items[ray.j]->case_x,
			// data->ray[i].items[ray.j]->coo_y,
			// data->ray[i].items[ray.j]->coo_x);
		}
		lst = lst->next;
	}

	lst = get_first_elem_lst(data->enemy);
	ft_bzero(&ray,sizeof(t_hitray));
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
			ray.j = -1;
			while (++ray.j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door)
				if (data->ray[i].items[ray.j]->use == false)
					break ;
			data->ray[i].items[ray.j]->type = ENEMY;
			data->ray[i].items[ray.j]->use = true;
			data->ray[i].items[ray.j]->enemy = enemy;
			data->ray[i].items[ray.j]->case_y = (int)(ray.hy / 64);
			data->ray[i].items[ray.j]->case_x = (int)(ray.hx / 64);
			data->ray[i].items[ray.j]->coo_y = fmod(ray.hy, 64);
			data->ray[i].items[ray.j]->coo_x = fmod(ray.hx, 64);
			data->ray[i].items[ray.j]->posx = ray.t;
			data->ray[i].items[ray.j]->side = FRONT;
			ray.deg = fmod(data->ray[i].deg + 360 - 90, 360);
			if ((ray.deg <= enemy->deg && ray.deg + 180 >= enemy->deg)
				|| (ray.deg >= enemy->deg && !(ray.deg - 180 <= enemy->deg)))
				data->ray[i].items[ray.j]->side = BACK;
			// data->ray[i].items[ray.j]->texture = enemy->front_img;
			// if (data->ray[i].items[ray.j]->side == BACK)
				// data->ray[i].items[ray.j]->texture = enemy->back_img;
			calc_item_value(data, &ray, x);
			// printf("HIT item RAY\n");
			// printf("HIT COO     case_y>%d   case_x>%d     coo_y>%lf    coo_x>%lf\n",
			// data->ray[i].items[ray.j]->case_y,
			// data->ray[i].items[ray.j]->case_x,
			// data->ray[i].items[ray.j]->coo_y,
			// data->ray[i].items[ray.j]->coo_x);
		}
		lst = lst->next;
	}

	lst = get_first_elem_lst(data->door);
	ft_bzero(&ray,sizeof(t_hitray));
	ray.i = i;
	while (lst)
	{
		door = lst->dt;
		ray.delta_x = data->ray[ray.i].delta_x;
		ray.delta_y = data->ray[ray.i].delta_y;
		// printf("\ndelta_y>%lf   delta_x>%lf\n",ray.delta_y,ray.delta_x);
		ray.ax = door->first_p.x + door->coo.x * 64;
		ray.ay = door->first_p.y + door->coo.y * 64;
		ray.bx = door->second_p.x + door->coo.x * 64;
		ray.by = door->second_p.y + door->coo.y * 64;
		ray.cx = data->ray[ray.i].coo_x + data->ray[ray.i].case_x * 64;
		ray.cy = data->ray[ray.i].coo_y + data->ray[ray.i].case_y * 64;
		ray.radius = 64;
		calc_end_point(&ray);
		// printf("ray.cy>%lf   ray.cx>%lf       ray.dy>%lf   ray.dx>%lf\n",ray.cy,ray.cx,ray.dy,ray.dx);
		calc_delta(&ray);
		if (ray.hit == true)
		{
			ray.j = -1;
			while (++ray.j < MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door)
				if (data->ray[i].items[ray.j]->use == false)
					break ;
			if (door->is_floo && door->is_floo_open)
				data->ray[i].items[ray.j]->type = FLOO_OPEN;
			else if (door->is_floo && !door->is_floo_open)
				data->ray[i].items[ray.j]->type = FLOO_CLOSE;
			else
				data->ray[i].items[ray.j]->type = DOOR;
			data->ray[i].items[ray.j]->use = true;
			data->ray[i].items[ray.j]->door = door;
			data->ray[i].items[ray.j]->case_y = (int)(ray.hy / 64);
			data->ray[i].items[ray.j]->case_x = (int)(ray.hx / 64);
			data->ray[i].items[ray.j]->coo_y = fmod(ray.hy, 64);
			data->ray[i].items[ray.j]->coo_x = fmod(ray.hx, 64);
			data->ray[i].items[ray.j]->posx = ray.t;
			// data->ray[i].items[ray.j]->texture = &data->img[DOOR_FIXED];
			data->ray[i].items[ray.j]->side = BASIC;
			if ((ray.delta_x < 0 && door->is_verti) || (ray.delta_y > 0 && !door->is_verti))
				data->ray[i].items[ray.j]->side = REVERSED;
			calc_item_value(data, &ray, x);
			// data->ray[i].items[ray.j]->side = FRONT;
			// ray.deg = fmod(data->ray[i].deg + 360 - 90, 360);
			// if ((ray.deg <= enemy->deg && ray.deg + 180 >= enemy->deg)
			// 	|| (ray.deg >= enemy->deg && ray.deg - 180 <= enemy->deg))
			// 	data->ray[i].items[ray.j]->side = BACK;
			// printf("HIT item RAY\n");
			// printf("HIT COO     case_y>%d   case_x>%d     coo_y>%lf    coo_x>%lf\n",
			// data->ray[i].items[ray.j]->case_y,
			// data->ray[i].items[ray.j]->case_x,
			// data->ray[i].items[ray.j]->coo_y,
			// data->ray[i].items[ray.j]->coo_x);
		}
		lst = lst->next;
	}
}