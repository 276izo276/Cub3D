#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include "color_bonus.h"

int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->data_addr + (y * texture->size_line + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

static void display_wand(t_data *data, int pos_x, int pos_y)
{
	int				x;
	int				y;
	unsigned int	color;
	unsigned int	alpha_color;

	y = 0;
	alpha_color = 0;
	color = 0;
	if (data->is_right_handed == false)
		pos_x -= 40;
	else
		pos_x -= 60;
	if (data->wand.nb_wand == 6)
	{
		pos_y -= 250;
		pos_x += 10;
	}
	while (y < data->wand.img[data->wand.nb_wand].height && pos_y + y < data->mlx.height)
	{
		x = 0;
		while (x < data->wand.img[data->wand.nb_wand].width)
		{
			color = get_texture_pixel(&data->wand.img[data->wand.nb_wand], x, y);
			if (color != WHITE)
			{
				alpha_color = (data->player.invisible << 24) | (color & 0x00FFFFFF);
				apply_transparancy(data, x + pos_x, y + pos_y, alpha_color);
			}
			++x;
		}
		++y;
	}
	data->lumos.x_wand = pos_x;
	data->lumos.y_wand = pos_y;
}

void	display_hand(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;
	int				pos_x;
	int				pos_y;
	unsigned int	alpha_color;

	alpha_color = 0;
	pos_x = data->display.pos_x_hand;
	pos_y = data->display.pos_y_hand;
	if (data->player_moved == true && data->display.move_hand < 50 && data->display.is_up_move_hand == false)
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
	if (data->display.player_height == 18)
		pos_y += 80;
	display_wand(data, pos_x, pos_y + data->display.move_hand);
	color = 0;
	y = 0;
	while (y < data->img[PLAYER_HAND].height && pos_y + y < data->mlx.height)
	{
		x = 0;
		while (x < data->img[PLAYER_HAND].width)
		{
			color = get_texture_pixel(&data->img[PLAYER_HAND], x, y);
			if (color != 0xFFFFFF)
			{
				alpha_color = (data->player.invisible << 24) | (color & 0x00FFFFFF);
				apply_transparancy(data, x + pos_x, y + pos_y + data->display.move_hand, alpha_color);
			}
			++x;
		}
		++y;
	}
	if (data->lumos.count_frame > 0)
		spell_lumos(data);
}
