#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "struct_bonus.h"

unsigned int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->data_addr + (y * texture->size_line + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

static void	display_hand_loop(t_data *data, int pos_x, int pos_y)
{
	unsigned int	alpha_color;
	unsigned int	color;
	int				x;
	int				y;

	y = 0;
	while (y < data->img[PLAYER_HAND].height && pos_y + y < data->mlx.height)
	{
		x = 0;
		while (x < data->img[PLAYER_HAND].width)
		{
			color = get_texture_pixel(&data->img[PLAYER_HAND], x, y);
			if (color != 0xFFFFFF)
			{
				alpha_color = (data->player.invisible << 24)
					| (color & 0x00FFFFFF);
				apply_transparancy(data, x + pos_x, y + pos_y
					+ data->display.move_hand, alpha_color);
			}
			++x;
		}
		++y;
	}
}

static void	set_hand_pos(t_data *data)
{
	if (data->player_moved == true && data->display.move_hand < 50
		&& data->display.is_up_move_hand == false)
	{
		if (data->map.mini.speed == 3)
			data->display.move_hand += 3;
		else
			data->display.move_hand += 1;
	}
	else if (data->player_moved == true)
	{
		if (data->map.mini.speed == 3)
			data->display.move_hand -= 3;
		else
			data->display.move_hand -= 1;
		if (data->display.move_hand > 0)
			data->display.is_up_move_hand = true;
		else
			data->display.is_up_move_hand = false;
	}
}

void	display_hand(t_data *data)
{
	int				pos_x;
	int				pos_y;

	pos_x = data->display.pos_x_hand;
	pos_y = data->display.pos_y_hand;
	set_hand_pos(data);
	if (data->display.player_height == 18)
		pos_y += 80;
	display_wand(data, pos_x, pos_y + data->display.move_hand);
	display_hand_loop(data, pos_x, pos_y);
	spell_lumos(data);
}
