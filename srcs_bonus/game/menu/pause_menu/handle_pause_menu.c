#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "mlx.h"

static void	display_background(t_data *data)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->pause_menu.background->height)
	{
		x = 0;
		while (x < data->pause_menu.background->width)
		{
			color = get_texture_pixel(data->pause_menu.background,x ,y);
			if (color != 0)
				pixel_put(data, x + 448, y + 5, color);
			++x;
		}
		++y;
	}
}

static void	display_params(t_data *data)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->pause_menu.sensitivity->height)
	{
		x = 0;
		while (x < data->pause_menu.sensitivity->width)
		{
			color = get_texture_pixel(data->pause_menu.sensitivity,x ,y);
			if (color != WHITE )
				pixel_put(data, x + 648, y + 300, color);
			++x;
		}
		++y;
	}
}

void	handle_pause_menu(t_data *data)
{
	display_background(data);
	display_params(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0, 0);
}
