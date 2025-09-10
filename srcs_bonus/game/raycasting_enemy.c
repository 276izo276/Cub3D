#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>

#include <stdio.h>

void	try_hit_enemy(t_data *data, int i)
{
	t_hitray	ray;
	t_lst		*lst;
	t_enemy		*enemy;

	ray.i = i;
	lst = get_first_elem_lst(data->enemy);
	// ray.j = 0;
	// while (++ray.j < data->nb_enemy + MAX_CREATE_ENEMY)
	// 	if (data->ray[i].enemys[ray.j]->use == false)
	// 		break ;
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
		if (ray.delta_x > 0)
			ray.rx = (ray.ax + enemy->radius * 50 - ray.ax ) / ray.delta_x;
		else
			ray.rx = -ray.ax / ray.delta_x;
		if (ray.delta_y > 0)
			ray.ry = (ray.ay + enemy->radius * 50 - ray.ay) / ray.delta_y;
		else
			ray.ry = -ray.ay / ray.delta_y;
		if (ray.rx < ray.ry)
		{
			if (ray.delta_x < 0)
				ray.dx = 0;
			else
				ray.dx = ray.cx + enemy->radius * 50;
			ray.dy = ray.cy + ray.rx * ray.delta_y;
		}
		else
		{
			if (ray.delta_y < 0)
				ray.dy = 0;
			else
				ray.dy = ray.cy + enemy->radius * 50;
			ray.dx = ray.cx + ray.ry * ray.delta_x;
		}
		if (ray.i < data->mlx.width / 4)
			// printf("I>>%d   dely>>%lf     delx>>%lf        cy>>%lf   cx>>%lf        dy>>%lf   dx>>%lf\n",ray.i,ray.delta_y,ray.delta_x,ray.cy,ray.cx,ray.dy,ray.dx);
		calc_delta(&ray);
		if (ray.hit == true)
		{
			ray.j = -1;
			while (++ray.j < data->nb_door)
				if (data->ray[i].enemys[ray.j]->use == false)
					break ;
			data->ray[i].enemys[ray.j]->use = true;
			data->ray[i].enemys[ray.j]->coo_x = ray.hx;
			data->ray[i].enemys[ray.j]->coo_y = ray.hy;
			data->ray[i].enemys[ray.j]->case_y = (int)(data->ray[i].enemys[ray.j]->coo_y / 64);
			data->ray[i].enemys[ray.j]->case_x = (int)(data->ray[i].enemys[ray.j]->coo_x / 64);
			data->ray[i].enemys[ray.j]->coo_y = fmod(data->ray[i].enemys[ray.j]->coo_y, 64);
			data->ray[i].enemys[ray.j]->coo_x = fmod(data->ray[i].enemys[ray.j]->coo_x, 64);
			// printf("HIT ENEMY RAY\n");
			// printf("HIT COO     case_y>%d   case_x>%d     coo_y>%lf    coo_x>%lf\n",
			// data->ray[i].enemys[ray.j]->case_y,
			// data->ray[i].enemys[ray.j]->case_x,
			// data->ray[i].enemys[ray.j]->coo_y,
			// data->ray[i].enemys[ray.j]->coo_x);
		}
		lst = lst->next;
	}
}