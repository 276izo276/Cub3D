#include "cub3d.h"
#include "mlx.h"
#include "player.h"
#include "time.h"
#include "utils.h"

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
		// printf("IN\n");
		while (i < KEYCODE_NB)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
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

	cur = get_mtime();
	handle_input_move(data, cur);
	if (data->time_fps + 1000 / FPS < cur)
	{
		// printf("fps >>>%lld     \n",1000 / (cur - data->time_fps));
		data->time_fps = cur;
		ray_launch(data);
		display_game(data);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
		aff_mini_map(data);
		// ray_launch_old(data);
	}
	// printf("OUT\n");
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
