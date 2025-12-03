#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "texture_bonus.h"

bool	is_center_floo(t_data *data, int pos_x, int pos_y)
{
	int	cursor_x;
	int	cursor_y;

	cursor_x = data->mlx.width / 2;
	cursor_y = (data->mlx.height - MARGIN) / 2;
	if (cursor_x >= pos_x && cursor_x <= pos_x + data->map.zoom
		&& cursor_y >= pos_y && cursor_y <= pos_y + data->map.zoom)
		return (true);
	return (false);
}

void	draw_player(t_data *data, int pos_x, int pos_y)
{
	unsigned int	color;
	double			pixel_x;
	double			pixel_y;

	pixel_y = -1;
	color = 0;
	while (++pixel_y < data->map.zoom / 2)
	{
		pixel_x = -1;
		while (++pixel_x < data->map.zoom / 2)
		{
			calc_value_player_map((pixel_x / (data->map.zoom / 2))
				* data->map.mini.img[MINI_CURS].width, (pixel_y
					/ (data->map.zoom / 2))
				* data->map.mini.img[MINI_CURS].height, data, &color);
			if (color != 0)
			{
				pixel_put(data, pixel_x + pos_x + (data->map.zoom / 4), pixel_y
					+ pos_y + (data->map.zoom / 4), data->player.color);
			}
		}
	}
}

void	draw_cursor(t_data *data)
{
	unsigned int	color;
	int				pixel_x;
	int				pixel_y;
	double			texture_x;
	double			texture_y;

	pixel_y = 0;
	while (pixel_y < data->map.zoom)
	{
		pixel_x = 0;
		while (pixel_x < data->map.zoom)
		{
			texture_x = (pixel_x * 256) / data->map.zoom;
			texture_y = (pixel_y * 256) / data->map.zoom;
			color = get_texture_pixel(&data->map.mini.img[MAP_CURSOR],
					texture_x, texture_y);
			if (color != WHITE)
				pixel_put(data, pixel_x + data->mlx.width / 2 - (data->map.zoom
						/ 2), pixel_y + (data->mlx.height - MARGIN) / 2
					- (data->map.zoom / 2), data->player.color);
			++pixel_x;
		}
		++pixel_y;
	}
}

static unsigned int	get_color(t_data *data, int text_x, int text_y, char c)
{
	unsigned int	color;

	color = 0;
	if (c == '1')
		color = get_texture_pixel(&data->map.mini.img[MAP_WALL], text_x,
				text_y);
	else if (c == 'D')
		color = get_texture_pixel(&data->map.mini.img[MAP_DOOR], text_x,
				text_y);
	else if (c == 'F')
	{
		color = get_texture_pixel(&data->map.mini.img[MAP_FLOO], text_x,
				text_y);
		if (data->status != MAP && data->map.is_center == false)
			color = darken_the_color(color);
	}
	else if (c == '0' || c == 'W' || c == 'S' || c == 'N' || c == 'E')
		color = get_texture_pixel(&data->map.mini.img[MAP_FLOOR], text_x,
				text_y);
	else if (c != '.')
		color = 0x6e583e;
	return (color);
}

void	draw_texture(t_data *data, int pos_x, int pos_y, char c)
{
	unsigned int	color;
	int				pixel_x;
	int				pixel_y;
	double			text_x;
	double			text_y;

	pixel_y = 0;
	while (pixel_y < data->map.zoom)
	{
		pixel_x = 0;
		while (pixel_x < data->map.zoom)
		{
			text_x = (pixel_x * 256) / data->map.zoom;
			text_y = (pixel_y * 256) / data->map.zoom;
			color = get_color(data, text_x, text_y, c);
			if (get_texture_pixel(data->screen, pixel_x + pos_x, pos_y
					+ pixel_y) != data->player.color)
				pixel_put(data, pos_x + pixel_x, pos_y + pixel_y, color);
			++pixel_x;
		}
		++pixel_y;
	}
}
