#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include <color_bonus.h>
#include <math.h>

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

void	apply_transparancy(t_data *data, int x, int y, unsigned int color)
{
	char	*tmp_addr;
	int		a_new;
	int		r_new;
	int		g_new;
	int		b_new;
	int		r_old;
	int		g_old;
	int		b_old;
	unsigned int old_color;

	if (x >= 0 && x < data->mlx.width && y >= 0 && y < data->mlx.height)
	{
		tmp_addr = data->screen->data_addr + (y * data->screen->size_line + x * (data->screen->bits_per_pixel / 8));
		old_color = *(unsigned int *)tmp_addr;
		r_old = (old_color >> 16) & 255;
		g_old = (old_color >> 8) & 255;
		b_old = old_color & 255;

		a_new = (color >> 24) & 255;
		r_new = (color >> 16) & 255;
		g_new = (color >> 8) & 255;
		b_new = color & 255;
		r_new = (int)((1 - (a_new / 255.0)) * r_old + (a_new / 255.0) * r_new);
		g_new = (int)((1 - (a_new / 255.0)) * g_old + (a_new / 255.0) * g_new);
		b_new = (int)((1 - (a_new / 255.0)) * b_old + (a_new / 255.0) * b_new);
		*(unsigned int *)tmp_addr = (r_new << 16) + (g_new << 8) + b_new;
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
			if (color == YELLOW)
			{
				if ((data->selected  == 0 && x < data->mlx.width / 2)
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

static void select_your_coa(t_data *data)
{
	int	start_x;
	int	start_y;

	start_x = 250; //(data->mlx.width - (2 * data->coa[FIRE].img_coa->width)) / 2;
	start_y = data->mlx.height / 2;
	draw_texture_menu(data, &data->img[SELECT], 0, 0);
	draw_texture_menu(data, &data->img[MENU_FIRE], start_x, start_y);
	draw_texture_menu(data, &data->img[MENU_WATER], start_x
		+ data->img[MENU_FIRE].width + 200, start_y);
	draw_texture_menu(data, &data->img[MENU_EARTH], start_x + 2 * data->img[MENU_FIRE].width + 400, start_y);
	draw_texture_menu(data, &data->img[MENU_AIR], start_x
		+ 3 * data->img[MENU_FIRE].width + 600, start_y);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,
		0);
	draw_select_border(data, start_x, start_y);
}

// static void draw_y_border(t_data *data, int x, int y)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < KEYCODE_NB)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			pixel_put(data, x + j, y + i, data->player.color);
// 			pixel_put(data, x + 230 - j, y
// 				+ i, data->player.color);
// 			++j;
// 		}
// 		++i;
// 	}
// }
// static void draw_x_border(t_data *data, int x, int y)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < 230)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			pixel_put(data, x + i, y + j, data->player.color);
// 			pixel_put(data, x + i, y
// 				+ 100 - j,
// 				data->player.color);
// 			++j;
// 		}
// 		++i;
// 	}
// }

int	get_right_color(int color, double distance)
{
	int r;
	int g;
	int b;
	int	a;

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

void	draw_gradient(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				x;
	int				y;
	double			distance;

	y = -40;
	color = data->player.color;
	while (y < 40)
	{
		x = -40;
		while (x < 40)
		{
			distance = sqrt(y * y + x * x);
			if (distance < 40)
			{
				color = get_right_color(data->player.color, distance);
				apply_transparancy(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

static void select_your_hand(t_data *data)
{

	int	x;
	int	y;
	unsigned int color;
	int	start_x;
	int start_y;

	start_y = data->mlx.height - 412;
	color = 0;
	y = 0;

	draw_texture_menu(data, &data->img[SELECT_HAND], 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0, 0);
	while (y < data->img[LEFT_SELECT].height && y <= data->mlx.height)
	{
		x = 0;
		while (x < data->img[LEFT_SELECT].width && x <= data->mlx.width)
		{
			if (data->selected == 1)
			{
				color = get_texture_pixel(&data->img[LEFT_SELECT], x, y);
				start_x = data->mlx.width / 2 - 124 ;
			}
			else
			{
				color = get_texture_pixel(&data->img[LEFT_SELECT], x, y);
				start_x = 225;
			}
			if (color != WHITE)
				pixel_put(data, x + start_x, y + start_y, color);
			++x;
		}
		++y;
	}
	if (data->selected == 1)
	{
		start_x += 355;
		start_y += 150;
	}
	else
	{
		start_x += data->img[LEFT_SELECT].width - 130;
		start_y += 150;
	}
	draw_gradient(data, start_x, start_y);
	y = data->mlx.height - 345;
	x = 530;
	if (data->selected == 1)
		x += 625;
}

void	display_menu(t_data *data)
{
	if (data->player.color == 0)
		select_your_coa(data);
	else if (data->is_right_handed == 0)
		select_your_hand(data);
}
