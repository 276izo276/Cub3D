#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include "color_bonus.h"

// static void	draw_y_border(t_data *data, int x, int y)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < data->coa[data->selected].img_coa->height)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			pixel_put(data, x + j, y + i, data->coa[data->selected].color);
// 			pixel_put(data, x + data->coa[data->selected].img_coa->width - j, y
// 				+ i, data->coa[data->selected].color);
// 			++j;
// 		}
// 		++i;
// 	}
// }

// static void	draw_x_border(t_data *data, int x, int y)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < data->coa[data->selected].img_coa->width)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			pixel_put(data, x + i, y + j, data->coa[data->selected].color);
// 			pixel_put(data, x + i, y
// 				+ data->coa[data->selected].img_coa->height - j,
// 				data->coa[data->selected].color);
// 			++j;
// 		}
// 		++i;
// 	}
// }

void	draw_select_border(t_data *data, int start_x, int start_y)
{
	if (data->selected == 1)
		start_x += data->coa[data->selected].img_coa->width + 200;
	else if (data->selected == 2)
		start_x += (2 * data->coa[0].img_coa->width + 400);
	else if (data->selected == 3)
	{
		start_x += 3 * data->coa[0].img_coa->width + 600;
	}
	// mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->coa[data->selected].border, start_x,
	// 	start_y);
	// draw_y_border(data, start_x, start_y);
	// draw_x_border(data, start_x, start_y);
	int x;
	int y = 0;
	unsigned int color = 0;
	while (y < data->coa[data->selected].border->height)
	{
		x = 0;
		while (x < data->coa[data->selected].border->width)
		{
			color = get_texture_pixel(data->coa[data->selected].border, x, y);
			if (color != WHITE)
			{
				pixel_put(data, x + start_x -45, y + start_y - 45, color);
			}
			++x;
		}
		++y;
	}
}
