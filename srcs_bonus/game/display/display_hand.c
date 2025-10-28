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

static void	wich_wand(t_data *data, t_img **img)
{
	if (data->nb_wand == 1)
		*img = &data->img[PLAYER_WAND_2];
	else if (data->nb_wand == 2)
		*img = &data->img[PLAYER_WAND_3];
	else if (data->nb_wand == 3)
		*img = &data->img[PLAYER_WAND_4];
	else if (data->nb_wand == 4)
		*img = &data->img[PLAYER_WAND_5];
	else if (data->nb_wand == 5 && data->easter_egg == true)
		*img = &data->img[PLAYER_WAND_6];
}
static void display_wand(t_data *data, int pos_x, int pos_y)
{
	int				x;
	int				y;
	unsigned int	color;
	t_img			*img;

	y = 0;
	color = 0;
	img = &data->img[PLAYER_WAND];
	wich_wand(data, &img);
	if (data->is_right_handed == false)
		pos_x -= 40;
	else
		pos_x -= 60;
	while (y < img->height && pos_y + y < data->mlx.height)
	{
		x = 0;
		while (x < img->width)
		{
			color = get_texture_pixel(img, x, y);
			if (color != WHITE)
			{
				pixel_put(data, x + pos_x, pos_y + y, color);
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
				pixel_put(data, x + pos_x, pos_y + y + data->display.move_hand, color);
			}
			++x;
		}
		++y;
	}
	if (data->lumos.count_frame > 0)
		spell_lumos(data);
}
