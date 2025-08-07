#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"

static void	draw_top_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->menu[data->selected].img_coa->height)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, x + j, y + i, data->menu[data->selected].color);
			pixel_put(data, x + data->menu[data->selected].img_coa->width - j, y
				+ i, data->menu[data->selected].color);
			++j;
		}
		++i;
	}
}

static void	draw_down_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->menu[data->selected].img_coa->width)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, x + i, y + j, data->menu[data->selected].color);
			pixel_put(data, x + i, y
				+ data->menu[data->selected].img_coa->height - j,
				data->menu[data->selected].color);
			++j;
		}
		++i;
	}
}

void	draw_select_border(t_data *data, int start_x, int start_y)
{
	if (data->selected == 1)
		start_x += data->menu[data->selected].img_coa->width + 150;
	else if (data->selected == 2)
		start_y += data->menu[0].img_coa->height + 100;
	else if (data->selected == 3)
	{
		start_x += data->menu[data->selected].img_coa->width + 150;
		start_y += data->menu[0].img_coa->height + 100;
	}
	draw_top_border(data, start_x, start_y);
	draw_down_border(data, start_x, start_y);
}
