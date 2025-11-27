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
		//write(1,"S1\n",3);
		while (i < max_pix)
		{
			display_game_loop(data, i);
			//write(1,"1\n",2);
			display_item(data, i);
			++i;
			//write(1,"1b\n",3);
		}
		display_blood_border(data, 0, data->mlx.width / 4);
		//write(1,"W1\n",3);
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
		//write(1,"S2\n",3);
		while (i < max_pix)
		{
			display_game_loop(data, i);
			//write(1,"2\n",2);
			display_item(data, i);
			++i;
			//write(1,"2b\n",3);
		}
		display_blood_border(data, data->mlx.width / 4, max_pix);
		//write(1,"W2\n",3);
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
		//write(1,"S3\n",3);
		while (i < max_pix)
		{
			display_game_loop(data, i);
			//write(1,"3\n",2);
			display_item(data, i);
			++i;
			//write(1,"3b\n",3);
		}
		display_blood_border(data, 2 * (data->mlx.width / 4), max_pix);
		//write(1,"W3\n",3);
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
		//write(1,"S4\n",3);
		while (i < data->mlx.width)
		{
			display_game_loop(data, i);
			//write(1,"4\n",2);
			display_item(data, i);
			++i;
			//write(1,"4b\n",3);
		}
		display_blood_border(data, 3 * (data->mlx.width / 4), data->mlx.width);
		//write(1,"W4\n",3);
		pthread_barrier_wait(&data->barrier_display);
	}
	return (NULL);
}
