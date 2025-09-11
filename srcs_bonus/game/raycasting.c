#include "cub3d_bonus.h"
#include <math.h>

#include <stdio.h>

static int	handle_ray_x(t_data *data, int i)
{
	if (data->ray[i].delta_x < 0)
		data->ray[i].dir = EAST;
	else
		data->ray[i].dir = WEST;
	if (data->ray[i].delta_x < 0)
	{
		if (handle_ray_x_left(data, i) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_x_right(data, i) == 1)
			return (1);
	}
	return (0);
}

static int	handle_ray_y(t_data *data, int i)
{
	if (data->ray[i].delta_y < 0)
		data->ray[i].dir = SOUTH;
	else
		data->ray[i].dir = NORTH;
	if (data->ray[i].delta_y < 0)
	{
		if (handle_ray_y_top(data, i) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_y_down(data, i) == 1)
			return (1);
	}
	return (0);
}

static void	handle_ray(t_data *data, int i)
{
	while (1)
	{
		if (data->ray[i].delta_x > 0)
			data->ray[i].rx = (64 - data->ray[i].coo_x) / data->ray[i].delta_x;
		else
			data->ray[i].rx = -data->ray[i].coo_x / data->ray[i].delta_x;
		if (data->ray[i].delta_y > 0)
			data->ray[i].ry = (64 - data->ray[i].coo_y) / data->ray[i].delta_y;
		else
			data->ray[i].ry = -data->ray[i].coo_y / data->ray[i].delta_y;
		if (data->ray[i].rx < data->ray[i].ry)
		{
			if (handle_ray_x(data, i) == 1)
				break ;
		}
		else
		{
			if (handle_ray_y(data, i) == 1)
				break ;
		}
	}
}

static void	save_data_ray(t_data *data, int i, double x)
{
	data->ray[i].rad = -atan(1 / x);
	data->ray[i].deg = data->ray[i].rad;
	if (data->ray[i].rad >= 0)
		data->ray[i].rad += M_PI;
	data->ray[i].rad += data->map.mini.deg * (M_PI / 180);
	data->ray[i].coo_y = data->map.mini.player_coo.y;
	data->ray[i].coo_x = data->map.mini.player_coo.x;
	data->ray[i].case_y = data->map.player_coo->y;
	data->ray[i].case_x = data->map.player_coo->x;
	data->ray[i].delta_x = -cos(data->ray[i].rad);
	data->ray[i].delta_y = sin(data->ray[i].rad);
}

static void	calc_sqrt_door(t_data *data, int i, int j)
{
	// printf("CASE_Y>>>>%d\n",data->ray[i].doors[j]->case_y);
	// printf("CASE_Y>>>>%d\n",data->ray[i].doors[j]->case_x);
	// printf("CASE_Y>>>>%lf\n",data->ray[i].doors[j]->coo_y);
	// printf("CASE_Y>>>>%lf\n",data->ray[i].doors[j]->coo_x);
	data->ray[i].doors[j]->dist_door = sqrt(((data->ray[i].doors[j]->case_y
		- data->map.player_coo->y) * 64.0 + (data->ray[i].doors[j]->coo_y
		- data->map.mini.player_coo.y)) * ((data->ray[i].doors[j]->case_y
		- data->map.player_coo->y) * 64.0 + (data->ray[i].doors[j]->coo_y
		- data->map.mini.player_coo.y)) + ((data->ray[i].doors[j]->case_x
		- data->map.player_coo->x) * 64.0 + (data->ray[i].doors[j]->coo_x
		- data->map.mini.player_coo.x)) * ((data->ray[i].doors[j]->case_x
		- data->map.player_coo->x) * 64.0 + (data->ray[i].doors[j]->coo_x
		- data->map.mini.player_coo.x)));
}

#include <stdio.h>

static void	calc_door_value(t_data *data, int i, double x)
{
	int	j;

	j = 0;
	// printf("HERE >>%d  %p\n",i,data->ray[i].doors,data->ray[i].doors[j]);
	// printf("TAB>>>%p  %d",j);
	while (j < data->nb_door && data->ray[i].doors[j]->use != false)
	{
		if (data->ray[i].doors[j]->print == false)
		{
			j++;
			continue;
		}
		calc_sqrt_door(data, i, j);
		// printf("dist >>>%lf    i>>%d    j>>%d\n",data->ray[i].doors[j]->dist_door,i,j);
		data->ray[i].doors[j]->dist_door *= cos(atan(x));
		data->ray[i].doors[j]->size_door = data->ray[i].d_proj
			/ (double)(data->ray[i].doors[j]->dist_door / 64.0);
		// printf("size door>>>%lf\n",data->ray[i].doors[j]->size_door);
		data->ray[i].doors[j]->max_size_door = 0;
		data->ray[i].doors[j]->max_size_door = data->ray[i].doors[j]->size_door * 0.5;
		// printf("max size door>>>%lf\n",data->ray[i].doors[j]->max_size_door);
		// printf("MAX SIZE DOOR>>>%lf\n",data->ray[i].doors[j]->max_size_door);
		data->ray[i].doors[j]->htop_door = round(data->ray[i].max_height
				- data->ray[i].doors[j]->max_size_door);
		data->ray[i].doors[j]->hbot_door = round(data->ray[i].max_height
				+ data->ray[i].doors[j]->max_size_door);
		// printf("max height>>>%lf\n",data->ray[i].max_height);
		j++;
		// printf("TAB>>>%p  %d",data->ray[i].doors[j],j);
	}
}

static void	calc_sqrt_enemy(t_data *data, int i, int j)
{
	// printf("CASE_Y>>>>%d\n",data->ray[i].enemys[j]->case_y);
	// printf("CASE_X>>>>%d\n",data->ray[i].enemys[j]->case_x);
	// printf("COO_Y>>>>%lf\n",data->ray[i].enemys[j]->coo_y);
	// printf("COO_X>>>>%lf\n",data->ray[i].enemys[j]->coo_x);
	// printf("CASE_Y>>>>%d\n",data->ray[i].enemys[j]->case_y);
	// printf("CASE_X>>>>%d\n",data->ray[i].enemys[j]->case_x);
	// printf("COO_Y>>>>%lf\n",data->ray[i].enemys[j]->coo_y);
	// printf("COO_X>>>>%lf\n",data->ray[i].enemys[j]->coo_x);
	data->ray[i].enemys[j]->dist_enemy = sqrt(((data->ray[i].enemys[j]->case_y
		- data->map.player_coo->y) * 64.0 + (data->ray[i].enemys[j]->coo_y
		- data->map.mini.player_coo.y)) * ((data->ray[i].enemys[j]->case_y
		- data->map.player_coo->y) * 64.0 + (data->ray[i].enemys[j]->coo_y
		- data->map.mini.player_coo.y)) + ((data->ray[i].enemys[j]->case_x
		- data->map.player_coo->x) * 64.0 + (data->ray[i].enemys[j]->coo_x
		- data->map.mini.player_coo.x)) * ((data->ray[i].enemys[j]->case_x
		- data->map.player_coo->x) * 64.0 + (data->ray[i].enemys[j]->coo_x
		- data->map.mini.player_coo.x)));
	// printf("dist enemy >>%lf\n",data->ray[i].enemys[j]->dist_enemy);
}

static void	calc_enemy_value(t_data *data, int i, double x)
{
	int	j;

	j = 0;
	// printf("HERE >>%d  %p\n",i,data->ray[i].doors,data->ray[i].doors[j]);
	// printf("TAB>>>%p  %d",j);
	while (j < data->nb_enemy && data->ray[i].enemys[j]->use != false)
	{
		calc_sqrt_enemy(data, i, j);
		// printf("dist >>>%lf    i>>%d    j>>%d\n",data->ray[i].enemys[j]->dist_enemy,i,j);
		data->ray[i].enemys[j]->dist_enemy *= cos(atan(x));
		data->ray[i].enemys[j]->size_enemy = data->ray[i].d_proj
			/ (double)(data->ray[i].enemys[j]->dist_enemy / 64.0);
		// printf("size enemy>>>%lf\n",data->ray[i].enemys[j]->size_enemy);
		data->ray[i].enemys[j]->max_size_enemy = 0;
		data->ray[i].enemys[j]->max_size_enemy = data->ray[i].enemys[j]->size_enemy * 0.5;
		// printf("max size enemy>>>%lf\n",data->ray[i].enemys[j]->max_size_enemy);
		// printf("MAX SIZE enemy>>>%lf\n",data->ray[i].enemys[j]->max_size_enemy);
		data->ray[i].enemys[j]->htop_enemy = round(data->ray[i].max_height
				- data->ray[i].enemys[j]->max_size_enemy);
		data->ray[i].enemys[j]->hbot_enemy = round(data->ray[i].max_height
				+ data->ray[i].enemys[j]->max_size_enemy);
		// printf("max height>>>%lf\n",data->ray[i].max_height);
		j++;
		// printf("TAB>>>%p  %d",data->ray[i].enemys[j],j);
	}
}

#include <unistd.h>

void	*ray_launch_first(void *ptr)
{
	int		i;
	double	x;
	t_data *data;

	data = (t_data *)ptr;
	while (1)
	{
		i = 0;
		pthread_barrier_wait(&data->barrier_background);
		while (i < data->mlx.width / 4)
		{
			x = (double)i / (double)data->mlx.width;
			// printf("x >>>%lf\n",x);
			x = (x * (-2) + 1);
			//write(1,"21\n",3);
			save_data_ray(data, i, x);
			try_hit_enemy(data, i);
			handle_ray(data, i);
			calc_door_value(data, i, x);
			calc_enemy_value(data, i, x);
			calc_sqrt(data, i);
			data->ray[i].dist_wall *= cos(atan(x));
			data->ray[i].size_wall = data->ray[i].d_proj
				/ (double)(data->ray[i].dist_wall / 64.0);
			data->ray[i].pix_x = (double)i;
			data->ray[i].max_size_wall = data->ray[i].size_wall * 0.5;
			data->ray[i].calc_bits = (int)(data->screen->bits_per_pixel >> 3);
			data->ray[i].data_addr = data->screen->data_addr;
			data->ray[i].htop_wall = round(data->ray[i].max_height
					- data->ray[i].max_size_wall);
			data->ray[i].hbot_wall = round(data->ray[i].max_height
					+ data->ray[i].max_size_wall);
			i += 1;
		}
		pthread_barrier_wait(&data->barrier_background);
	}
	return (NULL);
}

void	*ray_launch_snd(void *ptr)
{
	int		i;
	double	x;
	t_data *data;

	data = (t_data *)ptr;
	while (1)
	{
		i = data->mlx.width / 4;
		pthread_barrier_wait(&data->barrier_background);
		while (i < 2 * data->mlx.width / 4)
		{
			x = (double)i / (double)data->mlx.width;
			x = (x * (-2) + 1);
			//write(1,"22\n",3);
			save_data_ray(data, i, x);
			try_hit_enemy(data, i);
			handle_ray(data, i);
			calc_door_value(data, i, x);
			calc_enemy_value(data, i, x);
			calc_sqrt(data, i);
			data->ray[i].dist_wall *= cos(atan(x));
			data->ray[i].size_wall = data->ray[i].d_proj
				/ (double)(data->ray[i].dist_wall / 64.0);
			data->ray[i].pix_x = (double)i;
			data->ray[i].max_size_wall = data->ray[i].size_wall * 0.5;
			data->ray[i].calc_bits = (int)(data->screen->bits_per_pixel >> 3);
			data->ray[i].data_addr = data->screen->data_addr;
			data->ray[i].htop_wall = round(data->ray[i].max_height
					- data->ray[i].max_size_wall);
			data->ray[i].hbot_wall = round(data->ray[i].max_height
					+ data->ray[i].max_size_wall);
			i += 1;
		}
		pthread_barrier_wait(&data->barrier_background);
	}
	return (NULL);
}

void	*ray_launch_third(void *ptr)
{
	int		i;
	double	x;
	t_data *data;

	data = (t_data *)ptr;
	while (1)
	{
		i = 2 * data->mlx.width / 4;
		pthread_barrier_wait(&data->barrier_background);
		while (i < 3 * data->mlx.width / 4)
		{
			x = (double)i / (double)data->mlx.width;
			x = (x * (-2) + 1);
			//write(1,"23\n",3);
			save_data_ray(data, i, x);
			try_hit_enemy(data, i);
			handle_ray(data, i);
			calc_door_value(data, i, x);
			calc_enemy_value(data, i, x);
			calc_sqrt(data, i);
			data->ray[i].dist_wall *= cos(atan(x));
			data->ray[i].size_wall = data->ray[i].d_proj
				/ (double)(data->ray[i].dist_wall / 64.0);
			data->ray[i].pix_x = (double)i;
			data->ray[i].max_size_wall = data->ray[i].size_wall * 0.5;
			data->ray[i].calc_bits = (int)(data->screen->bits_per_pixel >> 3);
			data->ray[i].data_addr = data->screen->data_addr;
			data->ray[i].htop_wall = round(data->ray[i].max_height
					- data->ray[i].max_size_wall);
			data->ray[i].hbot_wall = round(data->ray[i].max_height
					+ data->ray[i].max_size_wall);
			i += 1;
		}
		pthread_barrier_wait(&data->barrier_background);
	}
	return (NULL);
}


void	*ray_launch_last(void *ptr)
{
	int		i;
	double	x;
	t_data *data;

	data = (t_data *)ptr;
	while (1)
	{
		i = 3 * data->mlx.width / 4;
		pthread_barrier_wait(&data->barrier_background);
		while (i < data->mlx.width)
		{
			x = (double)i / (double)data->mlx.width;
			x = (x * (-2) + 1);
			//write(1,"24\n",3);
			save_data_ray(data, i, x);
			try_hit_enemy(data, i);
			handle_ray(data, i);
			calc_door_value(data, i, x);
			calc_enemy_value(data, i, x);
			calc_sqrt(data, i);
			data->ray[i].dist_wall *= cos(atan(x));
			data->ray[i].max_dist_wall = data->ray[i].dist_wall;
			data->ray[i].size_wall = data->ray[i].d_proj
				/ (double)(data->ray[i].dist_wall / 64.0);
			data->ray[i].pix_x = (double)i;
			data->ray[i].max_size_wall = data->ray[i].size_wall * 0.5;
			data->ray[i].calc_bits = (int)(data->screen->bits_per_pixel >> 3);
			data->ray[i].data_addr = data->screen->data_addr;
			data->ray[i].htop_wall = round(data->ray[i].max_height
					- data->ray[i].max_size_wall);
			data->ray[i].hbot_wall = round(data->ray[i].max_height
					+ data->ray[i].max_size_wall);
			i += 1;
		}
		pthread_barrier_wait(&data->barrier_background);
	}
	return (NULL);
}
