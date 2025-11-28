#include "cub3d_bonus.h"

void	*display_fst_part(void *ptr)
{
	int		i;
	t_data	*data;
	int		max_pix;

	data = (t_data *)ptr;
	max_pix = (data->mlx.width / 4);
	while (1)
	{
		i = 0;
		pthread_barrier_wait(&data->barrier_display);
		pthread_mutex_lock(&data->m_end);
		if (data->should_end)
			break ;
		pthread_mutex_unlock(&data->m_end);
		while (i < max_pix)
		{
			display_game_loop(data, i);
			display_item(data, i);
			++i;
		}
		display_blood_border(data, 0, data->mlx.width / 4);
		pthread_barrier_wait(&data->barrier_display);
	}
	return (NULL);
}

void	*display_snd_part(void *ptr)
{
	int		i;
	t_data	*data;
	int		max_pix;

	data = (t_data *)ptr;
	max_pix = 2 * (data->mlx.width / 4);
	while (1)
	{
		i = data->mlx.width / 4;
		pthread_barrier_wait(&data->barrier_display);
		pthread_mutex_lock(&data->m_end);
		if (data->should_end)
			break ;
		pthread_mutex_unlock(&data->m_end);
		while (i < max_pix)
		{
			display_game_loop(data, i);
			display_item(data, i);
			++i;
		}
		display_blood_border(data, data->mlx.width / 4, max_pix);
		pthread_barrier_wait(&data->barrier_display);
	}
	return (NULL);
}

void	*display_third_part(void *ptr)
{
	int		i;
	int		max_pix;
	t_data	*data;

	data = (t_data *)ptr;
	max_pix = 3 * (data->mlx.width / 4);
	while (1)
	{
		i = 2 * (data->mlx.width / 4);
		pthread_barrier_wait(&data->barrier_display);
		pthread_mutex_lock(&data->m_end);
		if (data->should_end)
			break ;
		pthread_mutex_unlock(&data->m_end);
		while (i < max_pix)
		{
			display_game_loop(data, i);
			display_item(data, i);
			++i;
		}
		display_blood_border(data, 2 * (data->mlx.width / 4), max_pix);
		pthread_barrier_wait(&data->barrier_display);
	}
	return (NULL);
}

void	*display_last_part(void *ptr)
{
	int		i;
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		i = 3 * (data->mlx.width / 4);
		pthread_barrier_wait(&data->barrier_display);
		pthread_mutex_lock(&data->m_end);
		if (data->should_end)
			break ;
		pthread_mutex_unlock(&data->m_end);
		while (i < data->mlx.width)
		{
			display_game_loop(data, i);
			display_item(data, i);
			++i;
		}
		display_blood_border(data, 3 * (data->mlx.width / 4), data->mlx.width);
		pthread_barrier_wait(&data->barrier_display);
	}
	return (NULL);
}
