#include <stdlib.h>
#include "struct_bonus.h"
#include "mlx.h"
#include "cub3d_bonus.h"

void	f_elem(void *elem)
{
	free(elem);
}

void	f_img(t_img *img)
{
	if (!img)
		return ;
	if (img->img)
		mlx_destroy_image(img->mlx, img->img);
	free(img->path);
	free(img);
}

void	f_imgs(t_data *data)
{
	int	i;

	f_img(data->map.north);
	f_img(data->map.south);
	f_img(data->map.west);
	f_img(data->map.east);
	f_img(data->map.floor);
	f_img(data->map.ceiling);
	i = -1;
	while (++i <= 13 && data->map.mini.img[i].img)
		mlx_destroy_image(data->mlx.mlx, data->map.mini.img[i].img);
	i = -1;
	while (++i < NB_TEXTURES)
		mlx_destroy_image(data->mlx.mlx, data->img[i].img);
				data->img[i].img = NULL;
}

void	f_tab_char(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	join_thread(t_data *data)
{
	pthread_join(data->thread_sky_first, NULL);
	pthread_join(data->thread_sky_snd, NULL);
	pthread_join(data->thread_sky_third, NULL);
	pthread_join(data->thread_sky_last, NULL);
	pthread_join(data->thread_floor_first, NULL);
	pthread_join(data->thread_floor_snd, NULL);
	pthread_join(data->thread_floor_third, NULL);
	pthread_join(data->thread_floor_last, NULL);
	pthread_join(data->thread_ray_first, NULL);
	pthread_join(data->thread_ray_snd, NULL);
	pthread_join(data->thread_ray_third, NULL);
	pthread_join(data->thread_ray_last, NULL);
	pthread_join(data->thread_fst_part, NULL);
	pthread_join(data->thread_snd_part, NULL);
	pthread_join(data->thread_third_part, NULL);
	pthread_join(data->thread_last_part, NULL);
}

void	free_door_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.door_map[i])
	{
		free(data->map.door_map[i]);
		++i;
	}
	free(data->map.door_map);
}

void	free_wall_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			free(data->map.wall_map[y][x]);
			++x;
		}
		free(data->map.wall_map[y]);
		++y;
	}
	free(data->map.wall_map);
}

void	f_exit(t_data *data, int code)
{
	pthread_mutex_lock(&data->m_end);
	data->should_end = true;
	pthread_mutex_unlock(&data->m_end);
	pthread_barrier_wait(&data->barrier_background);
	pthread_barrier_wait(&data->barrier_display);
	join_thread(data);
	int	i = 0;
	while (i < data->mlx.width)
	{
		int j = 0;
		while (j <= MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door
			+ data->map.nb_floo)
		{
			free(data->ray[i].items[j]);
			j++;
		}
		free(data->ray[i].items);
		++i;
	}
	f_all_lst(data->sound);
	if (data->mlx.mlx)
		mlx_do_key_autorepeaton(data->mlx.mlx);
	f_imgs(data);
	f_all_lst(data->enemy);

	free_door_map(data);
	free_wall_map(data);

	f_all_lst(data->map.map);
	f_all_lst(data->map.lines);
	f_all_lst(data->door);
	f_all_lst(data->item);
	f_tab_char(data->map.tabmap);
	if (data->u.mmap.img)
		mlx_destroy_image(data->mlx.mlx, data->u.mmap.img);
	if (data->screen)
		mlx_destroy_image(data->mlx.mlx, data->screen->img);
	free(data->screen);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	free(data->ray);
	exit(code);
}

