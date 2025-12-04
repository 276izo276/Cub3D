#include "cub3d_bonus.h"
#include "mlx.h"
#include <color_bonus.h>

void	pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char	*tmp_addr;

	if (x >= 0 && x < data->mlx.width && y >= 0 && y < data->mlx.height)
	{
		tmp_addr = data->screen->data_addr + (y * data->screen->size_line + x
				* (data->screen->bits_per_pixel / 8));
		*(unsigned int *)tmp_addr = color;
	}
}

void	draw_texture_menu(t_data *data, t_img *texture, int final_x,
		int final_y)
{
	int				x;
	int				y;
	unsigned int	color;

	color = 0;
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			color = get_texture_pixel(texture, x, y);
			if (color == YELLOW)
			{
				if ((data->selected == 0 && x < data->mlx.width / 2)
					|| (data->selected == 1 && x > data->mlx.width / 2))
					color = data->player.color;
				else
					color = 0;
			}
			pixel_put(data, final_x + x, final_y + y, color);
			++x;
		}
		++y;
	}
}

static void	select_your_coa(t_data *data)
{
	int	start_x;
	int	start_y;

	start_x = 250;
	start_y = data->mlx.height / 2;
	draw_texture_menu(data, &data->img[SELECT], 0, 0);
	draw_texture_menu(data, &data->img[MENU_FIRE], start_x, start_y);
	draw_texture_menu(data, &data->img[MENU_WATER], start_x
		+ data->img[MENU_FIRE].width + 200, start_y);
	draw_texture_menu(data, &data->img[MENU_EARTH], start_x + 2
		* data->img[MENU_FIRE].width + 400, start_y);
	draw_texture_menu(data, &data->img[MENU_AIR], start_x + 3
		* data->img[MENU_FIRE].width + 600, start_y);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,
		0);
	draw_select_border(data, start_x, start_y);
}

int	get_right_color(int color, double distance)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	b = (color & 255);
	g = (color >> 8 & 255);
	r = (color >> 16 & 255);
	a = (int)(255 * (1 - distance / 40.0));
	if (a > 255)
		a = 255;
	if (a < 0)
		a = 0;
	color = (a << 24) + (r << 16) + (g << 8) + b;
	return (color);
}

void	display_menu(t_data *data)
{
	if (data->player.color == 0)
		select_your_coa(data);
	else if (data->is_right_handed == 0)
		select_your_hand(data);
}
