#include "color_bonus.h"
#include "cub3d_bonus.h"

void	draw_select_border(t_data *data, int start_x, int start_y)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	if (data->selected == 1)
		start_x += data->img[data->selected + MENU_FIRE].width + 200;
	else if (data->selected == 2)
		start_x += (2 * data->img[MENU_FIRE].width + 400);
	else if (data->selected == 3)
	{
		start_x += 3 * data->img[MENU_FIRE].width + 600;
	}
	while (++y < data->img[data->selected + BORDER_FIRE].height)
	{
		x = -1;
		while (++x < data->img[data->selected + BORDER_FIRE].width)
		{
			color = get_texture_pixel(&data->img[data->selected + BORDER_FIRE],
					x, y);
			if (color != WHITE)
				pixel_put(data, x + start_x - 45, y + start_y - 45, color);
		}
	}
}
