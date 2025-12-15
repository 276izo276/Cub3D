/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:44:54 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/15 09:17:39 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "player.h"
#include "time.h"
#include "utils.h"

static void	handle_input_move(t_data *data, long long int cur)
{
	int	i;
	int	move;

	i = 0;
	move = 0;
	if (data->time_move + 1000 / FPM < cur)
	{
		data->frame_move = 1000 / (cur - data->time_move);
		data->time_move = cur;
		while (i < KEYCODE_NB)
		{
			if (data->keycode[i] == KEY_ESCAPE)
				f_exit(data, 0);
			else if (is_move_player(data, i))
				move = 1;
			else if (data->keycode[i] == KEY_E || data->keycode[i] == KEY_RIGHT)
				rotate_right(data);
			else if (data->keycode[i] == KEY_Q || data->keycode[i] == KEY_LEFT)
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
		data->time_fps = cur;
		ray_launch(data);
		display_game(data);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img,
			0, 0);
		aff_mini_map(data);
	}
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
