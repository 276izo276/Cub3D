#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"

static void	handle_input_move(t_data *data, long long int cur)
{
	int i;
	int	move;

	i = 0;
	move = 0;
	if (data->time_move + 1000 / FPM < cur)
	{
		// printf("fpm >>>%lld     \n",1000 / (cur - data->time_move));
		data->frame_move = 1000 / (cur - data->time_move);
		data->time_move = cur;
		while (i < KEYCODE_NB)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			else if (data->keycode[i] == KEY_1)
				data->spell.active = true;
			else if (is_move_player(data, i))
				move = 1;
			else if (data->keycode[i] == KEY_E)
				rotate_right(data);
			else if (data->keycode[i] == KEY_Q)
				rotate_left(data);
			i++;
		}
		if (move)
			handle_move(&data->map, &data->map.mini, data);
	}
}

int	game_loop(t_data *data)
{
	long long int	cur;

	if (data->status == MENU)
		display_menu(data);
	else
	{
		cur = get_mtime();
		handle_input_move(data, cur);
		if (data->time_fps + 1000 / FPS < cur)
		{
			// printf("fps >>>%lld     \n",1000 / (cur - data->time_fps));
			data->time_fps = cur;
			ray_launch(data);
			sem_post(data->sem_background);
			sem_post(data->sem_background);
			pthread_barrier_wait(&data->barrier_background);
			// display_game(data);
			// pthread_mutex_lock(&data->m_data_ray);
			sem_post(data->sem_display);
			sem_post(data->sem_display);
			sem_post(data->sem_display);
			sem_post(data->sem_display);
			pthread_barrier_wait(&data->barrier_display);
			mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
			aff_mini_map(data);
			display_hand(data);
			handle_door(data);
			// pthread_mutex_unlock(&data->m_data_ray);
			// pthread_barrier_wait(&data->barrier);
		}
	}
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
