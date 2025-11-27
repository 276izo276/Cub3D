#include "color_bonus.h"
#include "cub3d_bonus.h"

void	display_menu_background(t_data *data, t_img *img, int start_x,
		int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = get_texture_pixel(img, x, y);
			if (color != 0)
				pixel_put(data, x + start_x, y + start_y, color);
			++x;
		}
		++y;
	}
}

int	darken_the_color(int color)
{
	int	r;
	int	g;
	int	b;

	b = (color & 255);
	b = (int)b - b * 0.5;
	if (b > 255)
		b = 255;
	g = (color >> 8 & 255);
	g = (int)g - g * 0.5;
	if (g > 255)
		g = 255;
	r = (color >> 16 & 255);
	r = (int)r - r * 0.5;
	if (r > 255)
		r = 255;
	color = (r << 16) + (g << 8) + b;
	return (color);
}

void	display_resume(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->img[PAUSE_RESUME].height)
	{
		x = 0;
		while (x < data->img[PAUSE_RESUME].width)
		{
			color = get_texture_pixel(&data->img[PAUSE_RESUME], x, y);
			if (color == 0xafaaa6 && data->pause_menu.selected == 0)
				color = data->player.color;
			if (color != WHITE && color != YELLOW)
			{
				color = data->player.color;
				if (data->pause_menu.selected != 0)
					color = darken_the_color(color);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

void	display_exit(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->img[PAUSE_EXIT].height)
	{
		x = 0;
		while (x < data->img[PAUSE_EXIT].width)
		{
			color = get_texture_pixel(&data->img[PAUSE_EXIT], x, y);
			if (color == 0xafaaa6 && data->pause_menu.selected == 1)
				color = data->player.color;
			if (color != WHITE && color != YELLOW)
			{
				color = data->player.color;
				if (data->pause_menu.selected != 1)
					color = darken_the_color(color);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

void	display_selector(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->img[PAUSE_SELECTOR].height)
	{
		x = 0;
		while (x < data->img[PAUSE_SELECTOR].width)
		{
			color = get_texture_pixel(&data->img[PAUSE_SELECTOR], x, y);
			if (color != WHITE)
				pixel_put(data, x + start_x, y + start_y, color);
			++x;
		}
		++y;
	}
	draw_gradient(data, start_x, start_y + 50);
}
