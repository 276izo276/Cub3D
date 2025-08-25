#include "cub3d_bonus.h"
#include "mlx.h"
#include "player_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"

static void	handle_input_move(t_data *data, long long int cur)
{
	int i;

	i = 0;
	if (data->time_move + 1000 / FPM < cur)
	{
		// printf("fpm >>>%lld     \n",1000 / (cur - data->time_move));
		data->frame_move = 1000 / (cur - data->time_move);
		data->time_move = cur;
		while (i < 100)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			else if (is_move_player(data, i))
				handle_move(&data->map, &data->map.mini, data->keycode[i],
					data);
			else if (data->keycode[i] == KEY_E)
				rotate_right(data);
			else if (data->keycode[i] == KEY_Q)
				rotate_left(data);
			i++;
		}
	}
}

static void select_right_hand(t_data *data)
{
	if (data->color == FIRE_COLOR && data->is_right_handed == true)
		data->player_hand->path = "./texture/player_hand/red_right_hand.xpm";
	else if (data->color == FIRE_COLOR)
		data->player_hand->path = "./texture/player_hand/red_left_hand.xpm";
	else if (data->color == EARTH_COLOR && data->is_right_handed == true)
		data->player_hand->path = "./texture/player_hand/green_right_hand.xpm";
	else if (data->color == EARTH_COLOR)
		data->player_hand->path = "./texture/player_hand/green_left_hand.xpm";
	else if (data->color == WATER_COLOR && data->is_right_handed == true)
		data->player_hand->path = "./texture/player_hand/blue_right_hand.xpm";
	else if (data->color == WATER_COLOR)
		data->player_hand->path = "./texture/player_hand/blue_left_hand.xpm";
	else if (data->color == AIR_COLOR && data->is_right_handed == true)
		data->player_hand->path = "./texture/player_hand/white_right_hand.xpm";
	else if (data->color == AIR_COLOR)
		data->player_hand->path = "./texture/player_hand/white_left_hand.xpm";
}

int	game_loop(t_data *data)
{
	long long int	cur;

	if (data->status == MENU)
	{
		display_menu(data);
		select_right_hand(data);
	}
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
			display_game(data);
			mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
			aff_mini_map(data);
			pthread_barrier_wait(&data->barrier);
		}
	}
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
