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

	y = 0;
	color = 0;
	if (data->is_right_handed == false)
		pos_x -= 40;
	else
		pos_x -= 60;
	while (y < data->player_wand->height)
	{
		x = 0;
		while (x < data->player_wand->width)
		{
			color = get_texture_pixel(data->player_wand, x, y);
			if (color != WHITE)
			{
				pixel_put(data, x + pos_x, pos_y + y, color);
			}
			++x;
		}
		++y;
	}
	data->spell.x_wand = pos_x;
	data->spell.y_wand = pos_y;
}

void	display_hand(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;
	int				pos_x;
	int				pos_y;

	if (data->is_right_handed == true)
	{
		pos_x = (data->mlx.width / 2) + data->player_hand->width / 4 - 100;
		pos_y = (data->mlx.height - data->player_hand->height - 100);
	}
	else
	{
		pos_x = (data->mlx.width / 2) - data->player_hand->width / 4 - 150;
		pos_y = (data->mlx.height - data->player_hand->height - 100);
	}
	display_wand(data, pos_x, pos_y);
	color = 0;
	y = 0;
	while (y < data->player_hand->height)
	{
		x = 0;
		while (x < data->player_hand->width)
		{
			color = get_texture_pixel(data->player_hand, x, y);
			if (color != 0xFFFFFF)
			{
				pixel_put(data, x + pos_x, pos_y + y, color);
			}
			++x;
		}
		++y;
	}
	if (data->spell.active == true)
		spell_lumos(data);
}
