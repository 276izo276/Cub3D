#include "cub3d.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "struct.h"
#include "texture.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "time.h"

int	game_loop(t_data *data)
{
	int	i;
	long long int cur = get_mtime();

	if (data->time_move + 1000 / FPM  < cur)
	{
		// printf("fpm >>>%lld     \n",1000 / (cur - data->time_move));
		data->frame_move = 1000 / (cur - data->time_move);
		data->time_move = cur;
		// printf("IN\n");
		i = 0;
		while (i < 100)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			else if (is_move_player(data, i))
				handle_move(&data->map, &data->map.mini, data->keycode[i], data);
			else if (data->keycode[i] == KEY_E)
				rotate_right(data);
			else if (data->keycode[i] == KEY_Q)
				rotate_left(data);
			i++;
		}
	}
	if (data->time_fps + 1000 / FPS  < cur)
	{
		// printf("fps >>>%lld     \n",1000 / (cur - data->time_fps));
		data->time_fps = cur;
		ray_launch(data);
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
