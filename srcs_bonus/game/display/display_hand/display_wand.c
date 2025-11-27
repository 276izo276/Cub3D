#include "color_bonus.h"
#include "cub3d_bonus.h"

static void	display_wand_loop(t_data *data, int pos_x, int pos_y)
{
	unsigned int	alpha_color;
	unsigned int	color;
	int				x;
	int				y;

	y = 0;
	while (y < data->img[data->wand.nb_wand + PLAYER_WAND].height && pos_y
		+ y < data->mlx.height)
	{
		x = 0;
		while (x < data->img[data->wand.nb_wand + PLAYER_WAND].width)
		{
			color = get_texture_pixel(&data->img[data->wand.nb_wand
					+ PLAYER_WAND], x, y);
			if (color != WHITE)
			{
				alpha_color = (data->player.invisible << 24)
					| (color & 0x00FFFFFF);
				apply_transparancy(data, x + pos_x, y + pos_y, alpha_color);
			}
			++x;
		}
		++y;
	}
}

void	display_wand(t_data *data, int pos_x, int pos_y)
{
	if (data->is_right_handed == false)
		pos_x -= 40;
	else
		pos_x -= 60;
	if (data->wand.nb_wand == 6)
	{
		pos_y -= 250;
		pos_x += 10;
	}
	display_wand_loop(data, pos_x, pos_y);
	data->lumos.x_wand = pos_x;
	data->lumos.y_wand = pos_y;
}
