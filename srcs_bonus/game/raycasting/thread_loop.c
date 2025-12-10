/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:50:52 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:50:53 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

void	save_data_ray(t_data *data, int i, double x)
{
	data->ray[i].rad = 90 * (M_PI / 180);
	if (x != 0.0)
		data->ray[i].rad = -atan(1 / x);
	data->ray[i].deg = data->ray[i].rad;
	if (data->ray[i].rad >= 0)
		data->ray[i].rad += M_PI;
	data->ray[i].rad += data->map.mini.deg * (M_PI / 180);
	data->ray[i].deg = fmod(data->ray[i].rad / (M_PI / 180) + 360 + 270, 360);
	data->ray[i].coo_y = data->player.coo.coo_y;
	data->ray[i].coo_x = data->player.coo.coo_x;
	data->ray[i].case_y = data->player.coo.case_y;
	data->ray[i].case_x = data->player.coo.case_x;
	data->ray[i].delta_x = -cos(data->ray[i].rad);
	data->ray[i].delta_y = sin(data->ray[i].rad);
}

void	*ray_launch_first(void *ptr)
{
	int		i;
	double	x;
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		i = 0;
		pthread_barrier_wait(&data->barrier_background);
		pthread_mutex_lock(&data->m_end);
		if (data->should_end)
			break ;
		pthread_mutex_unlock(&data->m_end);
		while (i < data->mlx.width / 4)
		{
			x = (double)i / (double)data->mlx.width;
			x = (x * (-2) + 1);
			raycast_loop(data, i, x);
			i += 1;
		}
		pthread_barrier_wait(&data->barrier_background);
	}
	pthread_mutex_unlock(&data->m_end);
	return (NULL);
}

void	*ray_launch_snd(void *ptr)
{
	int		i;
	double	x;
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		i = data->mlx.width / 4;
		pthread_barrier_wait(&data->barrier_background);
		pthread_mutex_lock(&data->m_end);
		if (data->should_end)
			break ;
		pthread_mutex_unlock(&data->m_end);
		while (i < 2 * data->mlx.width / 4)
		{
			x = (double)i / (double)data->mlx.width;
			x = (x * (-2) + 1);
			raycast_loop(data, i, x);
			i += 1;
		}
		pthread_barrier_wait(&data->barrier_background);
	}
	pthread_mutex_unlock(&data->m_end);
	return (NULL);
}

void	*ray_launch_third(void *ptr)
{
	int		i;
	double	x;
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		i = 2 * data->mlx.width / 4;
		pthread_barrier_wait(&data->barrier_background);
		pthread_mutex_lock(&data->m_end);
		if (data->should_end)
			break ;
		pthread_mutex_unlock(&data->m_end);
		while (i < 3 * data->mlx.width / 4)
		{
			x = (double)i / (double)data->mlx.width;
			x = (x * (-2) + 1);
			save_data_ray(data, i, x);
			raycast_loop(data, i, x);
			i += 1;
		}
		pthread_barrier_wait(&data->barrier_background);
	}
	pthread_mutex_unlock(&data->m_end);
	return (NULL);
}

void	*ray_launch_last(void *ptr)
{
	int		i;
	double	x;
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		i = 3 * data->mlx.width / 4;
		pthread_barrier_wait(&data->barrier_background);
		pthread_mutex_lock(&data->m_end);
		if (data->should_end)
			break ;
		pthread_mutex_unlock(&data->m_end);
		while (i < data->mlx.width)
		{
			x = (double)i / (double)data->mlx.width;
			x = (x * (-2) + 1);
			save_data_ray(data, i, x);
			raycast_loop(data, i, x);
			i += 1;
		}
		pthread_barrier_wait(&data->barrier_background);
	}
	pthread_mutex_unlock(&data->m_end);
	return (NULL);
}
