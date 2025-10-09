#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>

#include <stdio.h>

void	try_hit_item(t_data *data, int i)
{
	t_hitray	ray;
	t_lst		*lst;
	t_item		*item;
	t_enemy		*enemy;

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
			while (++ray.j < data->nb_door)
				if (data->ray[i].items[ray.j]->use == false)
					break ;
			data->ray[i].items[ray.j]->type = ITEM;
			data->ray[i].items[ray.j]->use = true;
			data->ray[i].items[ray.j]->item = item;
			data->ray[i].items[ray.j]->coo_x = ray.hx;
			data->ray[i].items[ray.j]->coo_y = ray.hy;
			// printf("hy>>%lf       hx>>%lf\n",ray.hy,ray.hx);
			data->ray[i].items[ray.j]->case_y = (int)(data->ray[i].items[ray.j]->coo_y / 64);
			data->ray[i].items[ray.j]->case_x = (int)(data->ray[i].items[ray.j]->coo_x / 64);
			data->ray[i].items[ray.j]->coo_y = fmod(data->ray[i].items[ray.j]->coo_y, 64);
			data->ray[i].items[ray.j]->coo_x = fmod(data->ray[i].items[ray.j]->coo_x, 64);
			data->ray[i].items[ray.j]->posx = ray.t;
			data->ray[i].items[ray.j]->side = FRONT;
			ray.deg = fmod(data->ray[i].deg + 360 - 90, 360);
			if ((ray.deg <= item->deg && ray.deg + 180 >= item->deg)
				|| (ray.deg >= item->deg && ray.deg - 180 <= item->deg))
				data->ray[i].items[ray.j]->side = BACK;
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
		calc_end_point(&ray);
		calc_delta(&ray);
		if (ray.hit == true)
		{
			ray.j = -1;
			while (++ray.j < data->nb_door)
				if (data->ray[i].items[ray.j]->use == false)
					break ;
			data->ray[i].items[ray.j]->type = ENEMY;
			data->ray[i].items[ray.j]->use = true;
			data->ray[i].items[ray.j]->enemy = enemy;
			data->ray[i].items[ray.j]->coo_x = ray.hx;
			data->ray[i].items[ray.j]->coo_y = ray.hy;
			// printf("hy>>%lf       hx>>%lf\n",ray.hy,ray.hx);
			data->ray[i].items[ray.j]->case_y = (int)(data->ray[i].items[ray.j]->coo_y / 64);
			data->ray[i].items[ray.j]->case_x = (int)(data->ray[i].items[ray.j]->coo_x / 64);
			data->ray[i].items[ray.j]->coo_y = fmod(data->ray[i].items[ray.j]->coo_y, 64);
			data->ray[i].items[ray.j]->coo_x = fmod(data->ray[i].items[ray.j]->coo_x, 64);
			data->ray[i].items[ray.j]->posx = ray.t;
			data->ray[i].items[ray.j]->side = FRONT;
			ray.deg = fmod(data->ray[i].deg + 360 - 90, 360);
			if ((ray.deg <= enemy->deg && ray.deg + 180 >= enemy->deg)
				|| (ray.deg >= enemy->deg && ray.deg - 180 <= enemy->deg))
				data->ray[i].items[ray.j]->side = BACK;
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