#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
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

static void	draw_texture_menu(t_data *data, t_img *texture, int final_x,
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
			pixel_put(data, final_x + x, final_y + y, color);
			++x;
		}
		++y;
	}
}

static void select_your_coa(t_data *data)
{
	int	start_x;
	int	start_y;

	start_x = 250; //(data->mlx.width - (2 * data->coa[0].img_coa->width)) / 2;
	start_y = data->mlx.height / 2;
	draw_texture_menu(data, data->select, 0, 0);
	draw_texture_menu(data, data->coa[0].img_coa, start_x, start_y);
	draw_texture_menu(data, data->coa[1].img_coa, start_x
		+ data->coa[0].img_coa->width + 200, start_y);
	draw_texture_menu(data, data->coa[2].img_coa, start_x + 2 * data->coa[0].img_coa->width + 400, start_y);
	draw_texture_menu(data, data->coa[3].img_coa, start_x
		+ 3 * data->coa[0].img_coa->width + 600, start_y);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,
		0);
	draw_select_border(data, start_x, start_y);
}

static void draw_y_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < KEYCODE_NB)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, x + j, y + i, data->color);
			pixel_put(data, x + 230 - j, y
				+ i, data->color);
			++j;
		}
		++i;
	}
}
static void draw_x_border(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 230)
	{
		j = 0;
		while (j < 4)
		{
			pixel_put(data, x + i, y + j, data->color);
			pixel_put(data, x + i, y
				+ 100 - j,
				data->color);
			++j;
		}
		++i;
	}
}

static void select_your_hand(t_data *data)
{

	int	x;
	int	y;
	unsigned int color;
	int	start_x;
	int start_y;

	start_y = data->mlx.height - 413;
	color = 0;
	y = 0;

	draw_texture_menu(data, data->select_hand, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0, 0);
	while (y < data->left_select->height)
	{
		x = 0;
		while (x < data->left_select->width)
		{
			if (data->selected == 1)
			{
				color = get_texture_pixel(data->right_select, x, y);
				start_x = data->mlx.width - data->right_select->width - 290;
			}
			else
			{
				color = get_texture_pixel(data->left_select, x, y);
				start_x = 290;
			}
			if (color != WHITE )
			{
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
	y = data->mlx.height - 315;
	x = 530;
	if (data->selected == 1)
		x += 625;
	draw_y_border(data, x, y);
	draw_x_border(data, x, y);
}

void	display_menu(t_data *data)
{
	if (data->color == 0)
		select_your_coa(data);
	else if (data->is_right_handed == 0)
		select_your_hand(data);
}
