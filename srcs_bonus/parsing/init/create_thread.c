/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:53:25 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:53:26 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils_bonus.h"

void	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->m_data_ray, NULL) != 0)
		f_exit(data, 1);
	if (pthread_mutex_init(&data->m_end, NULL) != 0)
		f_exit(data, 1);
}

static void	create_sky_thread(t_data *data)
{
	if (pthread_create(&data->thread_sky_first, NULL, display_sky_first,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_sky_snd, NULL, display_sky_snd, data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_sky_third, NULL, display_sky_third,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_sky_last, NULL, display_sky_last,
			data) != 0)
		f_exit(data, 1);
}

static void	create_floor_thread(t_data *data)
{
	if (pthread_create(&data->thread_floor_first, NULL, display_floor_first,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_floor_snd, NULL, display_floor_snd,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_floor_third, NULL, display_floor_third,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_floor_last, NULL, display_floor_last,
			data) != 0)
		f_exit(data, 1);
}

static void	create_ray_thread(t_data *data)
{
	if (pthread_create(&data->thread_ray_first, NULL, ray_launch_first,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_ray_snd, NULL, ray_launch_snd, data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_ray_third, NULL, ray_launch_third,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_ray_last, NULL, ray_launch_last,
			data) != 0)
		f_exit(data, 1);
}

void	create_thread(t_data *data)
{
	if (pthread_barrier_init(&data->barrier_background, NULL, 13) != 0)
		f_exit(data, 1);
	create_sky_thread(data);
	create_floor_thread(data);
	create_ray_thread(data);
	if (pthread_barrier_init(&data->barrier_display, NULL, 5) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_fst_part, NULL, display_fst_part,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_snd_part, NULL, display_snd_part,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_third_part, NULL, display_third_part,
			data) != 0)
		f_exit(data, 1);
	if (pthread_create(&data->thread_last_part, NULL, display_last_part,
			data) != 0)
		f_exit(data, 1);
	data->is_thread_create = true;
}
