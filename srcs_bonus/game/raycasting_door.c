#include "struct_bonus.h"

// static void	set_value_calc_rxy(t_data *data, t_hitray *ray)
// {
// 	data->ray[ray->i].doors[ray->j]->use = true;
// 	data->ray[ray->i].doors[ray->j]->case_x = data->ray[ray->i].case_x;
// 	data->ray[ray->i].doors[ray->j]->case_y = data->ray[ray->i].case_y;
// 	data->ray[ray->i].doors[ray->j]->start_y = data->ray[ray->i].coo_y;
// 	data->ray[ray->i].doors[ray->j]->start_x = data->ray[ray->i].coo_x;
// 	if (data->ray[ray->i].delta_x > 0)
// 		data->ray[ray->i].doors[ray->j]->rx = (64 - data->ray[ray->i]
// 				.doors[ray->j]->start_x) / data->ray[ray->i].delta_x;
// 	else
// 		data->ray[ray->i].doors[ray->j]->rx = -data->ray[ray->i]
// 			.doors[ray->j]->start_x / data->ray[ray->i].delta_x;
// 	if (data->ray[ray->i].delta_y > 0)
// 		data->ray[ray->i].doors[ray->j]->ry = (64 - data->ray[ray->i]
// 				.doors[ray->j]->start_y) / data->ray[ray->i].delta_y;
// 	else
// 		data->ray[ray->i].doors[ray->j]->ry = -data->ray[ray->i]
// 			.doors[ray->j]->start_y / data->ray[ray->i].delta_y;
// 	ray->cx = data->ray[ray->i].doors[ray->j]->start_x;
// 	ray->cy = data->ray[ray->i].doors[ray->j]->start_y;
// 	// ray->dx = data->ray[ray->i].doors[ray->j]->end_x;
// 	// ray->dy = data->ray[ray->i].doors[ray->j]->end_y;
// }

// static void	set_dir_door(t_data *data, t_hitray *ray)
// {
// 	if (data->map.door_map[data->ray[ray->i].doors[ray->j]->case_y]
// 		[data->ray[ray->i].doors[ray->j]->case_x]->is_verti)
// 	{
// 		if (data->ray[ray->i].delta_x < 0)
// 			data->ray[ray->i].doors[ray->j]->dir = EAST;
// 		else
// 			data->ray[ray->i].doors[ray->j]->dir = WEST;
// 	}
// 	else
// 	{
// 		if (data->ray[ray->i].delta_y < 0)
// 			data->ray[ray->i].doors[ray->j]->dir = SOUTH;
// 		else
// 			data->ray[ray->i].doors[ray->j]->dir = NORTH;
// 	}
// }

// static void	calc_end_ray(t_data *data, t_hitray *ray)
// {
// 	if (data->ray[ray->i].doors[ray->j]->rx < data->ray[ray->i]
// 		.doors[ray->j]->ry)
// 	{
// 		if (data->ray[ray->i].delta_x < 0)
// 			ray->dx = 0;
// 		else
// 			ray->dx = 64;
// 		ray->dy = ray->cy + data->ray[ray->i].doors[ray->j]
// 			->rx * data->ray[ray->i].delta_y;
// 	}
// 	else
// 	{
// 		if (data->ray[ray->i].delta_y < 0)
// 			ray->dy = 0;
// 		else
// 			ray->dy = 64;
// 		ray->dx = ray->cx + data->ray[ray->i].doors[ray->j]
// 			->ry * data->ray[ray->i].delta_x;
// 	}
// }

// #include <stdio.h>

// // void	calc_delta(t_hitray *ray)
// // {
// // 	ray->delta = (ray->dx - ray->cx) * (ray->by - ray->ay)
// // 		- (ray->dy - ray->cy) * (ray->bx - ray->ax);
// // 	ray->delta_t = (ray->dx - ray->cx) * (ray->cy - ray->ay)
// // 		- (ray->dy - ray->cy) * (ray->cx - ray->ax);
// // 	ray->delta_u = (ray->bx - ray->ax) * (ray->cy - ray->ay)
// // 		- (ray->by - ray->ay) * (ray->cx - ray->ax);
// // 	if (ray->delta != 0)
// // 	{
// // 		ray->t = ray->delta_t / ray->delta;
// // 		ray->u = ray->delta_u / ray->delta;
// // 		if (ray->t >= 0 && ray->t <= 1 && ray->u >= 0 && ray->u <= 1)
// // 		{
// // 			ray->hit = true;
// // 			ray->hx = ray->cx + ray->u * (ray->dx - ray->cx);
// // 			ray->hy = ray->cy + ray->u * (ray->dy - ray->cy);
// // 		}
// // 		else
// // 			ray->hit = false;
// // 	}
// // }

// void	calc_door(t_data *data, int i)
// {
// 	t_hitray	ray;

// 	ray.i = i;
// 	if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x] == 'D')
// 	{
// 		ray.j = -1;
// 		while (++ray.j < data->nb_door)
// 			if (data->ray[i].doors[ray.j]->use == false)
// 				break ;
// 		set_value_calc_rxy(data, &ray);
// 		ray.ax = data->map.door_map[data->ray[i].doors[ray.j]->case_y]
// 		[data->ray[i].doors[ray.j]->case_x]->first_p.x;
// 		ray.ay = data->map.door_map[data->ray[i].doors[ray.j]->case_y]
// 		[data->ray[i].doors[ray.j]->case_x]->first_p.y;
// 		ray.bx = data->map.door_map[data->ray[i].doors[ray.j]->case_y]
// 		[data->ray[i].doors[ray.j]->case_x]->second_p.x;
// 		ray.by = data->map.door_map[data->ray[i].doors[ray.j]->case_y]
// 		[data->ray[i].doors[ray.j]->case_x]->second_p.y;
// 		set_dir_door(data, &ray);
// 		calc_end_ray(data, &ray);
// 		calc_delta(&ray);
// 		data->ray[i].doors[ray.j]->coo_x = ray.hx;
// 		data->ray[i].doors[ray.j]->coo_y = ray.hy;
// 		data->ray[i].doors[ray.j]->print = ray.hit;
// 	}
// }
