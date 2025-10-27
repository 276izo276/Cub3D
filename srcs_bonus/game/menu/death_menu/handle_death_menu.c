#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include <color_bonus.h>


static void	display_retry_button(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->img[RETRY_BUTTON].height)
	{
		x = 0;
		while (x < data->img[RETRY_BUTTON].width)
		{
			color = get_texture_pixel(&data->img[RETRY_BUTTON], x, y);
			if (color != YELLOW)
			{
				if (data->selected != 0)
					color = darken_the_color(color);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

static void	display_quit_button(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->img[QUIT_BUTTON].height)
	{
		x = 0;
		while (x < data->img[QUIT_BUTTON].width)
		{
			color = get_texture_pixel(&data->img[QUIT_BUTTON], x, y);
			if (color != YELLOW)
			{
				if (data->selected != 1)
					color = darken_the_color(color);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}


void	handle_death_menu(t_data *data)
{
	display_menu_background(data, &data->img[END_MENU], 0, 0);
	display_retry_button(data, 300, 800);
	display_quit_button(data, 1000, 800);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,0);
}
