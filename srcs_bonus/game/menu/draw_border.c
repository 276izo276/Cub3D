#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"

static void	draw_y_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->coa[data->selected].img_coa->height)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, x + j, y + i, data->coa[data->selected].color);
			pixel_put(data, x + data->coa[data->selected].img_coa->width - j, y
				+ i, data->coa[data->selected].color);
			++j;
		}
		++i;
	}
}

static void	draw_x_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->coa[data->selected].img_coa->width)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, x + i, y + j, data->coa[data->selected].color);
			pixel_put(data, x + i, y
				+ data->coa[data->selected].img_coa->height - j,
				data->coa[data->selected].color);
			++j;
		}
		++i;
	}
}

void	draw_select_border(t_data *data, int start_x, int start_y)
{
	if (data->selected == 1)
		start_x += data->coa[data->selected].img_coa->width + 150;
	else if (data->selected == 2)
		start_y += data->coa[0].img_coa->height + 100;
	else if (data->selected == 3)
	{
		start_x += data->coa[data->selected].img_coa->width + 150;
		start_y += data->coa[0].img_coa->height + 100;
	}
	draw_y_border(data, start_x, start_y);
	draw_x_border(data, start_x, start_y);
}
