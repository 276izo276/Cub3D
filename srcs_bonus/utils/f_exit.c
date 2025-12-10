/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:58:30 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:58:31 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include <stdlib.h>

void	free_wall_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.tabmap && data->map.tabmap[y] && data->map.wall_map)
	{
		x = 0;
		while (data->map.tabmap[y][x] && data->map.wall_map[y])
		{
			free(data->map.wall_map[y][x]);
			++x;
		}
		free(data->map.wall_map[y]);
		++y;
	}
	free(data->map.wall_map);
}

static void	join_thread(t_data *data)
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

static void	erase_before_exit(t_data *data)
{
	int	i;
	int	j;

	pthread_mutex_lock(&data->m_end);
	data->should_end = true;
	pthread_mutex_unlock(&data->m_end);
	if (data->is_thread_create)
	{
		pthread_barrier_wait(&data->barrier_background);
		pthread_barrier_wait(&data->barrier_display);
	}
	join_thread(data);
	i = 0;
	while (i < data->mlx.width && data->ray && data->ray[i].items)
	{
		j = 0;
		while (j <= MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door
			+ data->map.nb_floo)
		{
			free(data->ray[i].items[j]);
			j++;
		}
		free(data->ray[i].items);
		++i;
	}
}

void	f_exit(t_data *data, int code)
{
	erase_before_exit(data);
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
	if (data->mlx.mlx)
		mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	free(data->ray);
	exit(code);
}
