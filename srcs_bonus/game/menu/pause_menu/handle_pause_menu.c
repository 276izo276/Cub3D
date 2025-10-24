#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <unistd.h>
#include "mlx.h"

void	display_menu_background(t_data *data, t_img *img, int start_x, int start_y)
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
			color = get_texture_pixel(img,x ,y);
			// if (color != 0)
			pixel_put(data, x + start_x, y + start_y, color);
			++x;
		}
		++y;
	}
}

// static void	display_params(t_data *data)
// {
// 	unsigned int	color;
// 	int				y;
// 	int				x;

// 	y = 0;
// 	while (y < data->pause_menu.sensitivity->height)
// 	{
// 		x = 0;
// 		while (x < data->pause_menu.sensitivity->width)
// 		{
// 			color = get_texture_pixel(data->pause_menu.sensitivity,x ,y);
// 			if (color != WHITE && color != YELLOW)
// 				pixel_put(data, x + 600, y + 300, color);
// 			++x;
// 		}
// 		++y;
// 	}
// }

int	darken_the_color(int color)
{
	int r;
	int g;
	int b;

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

static void	display_resume(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->pause_menu.resume->height)
	{
		x = 0;
		while (x < data->pause_menu.resume->width)
		{
			color = get_texture_pixel(data->pause_menu.resume, x, y);
			if (color == 0xafaaa6 && data->pause_menu.selected == 0)
				color = data->color;
			if (color != WHITE && color != YELLOW)
			{
				color = data->color;
				if (data->pause_menu.selected != 0)
					color = darken_the_color(color);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

static void	display_exit(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->pause_menu.exit->height)
	{
		x = 0;
		while (x < data->pause_menu.exit->width)
		{
			color = get_texture_pixel(data->pause_menu.exit, x, y);
			if (color == 0xafaaa6 && data->pause_menu.selected == 1)
				color = data->color;
			if (color != WHITE && color != YELLOW)
			{
				color = data->color;
				if (data->pause_menu.selected != 1)
					color = darken_the_color(color);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

static void	display_sensitivity(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;
	int				max_x;

	max_x = 1148 - (data->sensitivity * 1.28125);
	if (data->sensitivity == 20)
		max_x = 1138;
	y = 0;
	while (y < data->pause_menu.sensitivity->height)
	{
		x = 0;
		while (x < data->pause_menu.sensitivity->width)
		{
			color = get_texture_pixel(data->pause_menu.sensitivity, x, y);
			if (color != WHITE && color != YELLOW)
			{
				if (data->pause_menu.selected != 2)
					color = darken_the_color(color);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			if (x + start_x > 728 && x + start_x < max_x && y + start_y > 625 && start_y + y < 670  && color == YELLOW)
			{
				color = data->color;
				if (data->pause_menu.selected != 2)
					color = darken_the_color(color);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

static void	display_selector(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = 0;
	while (y < data->pause_menu.selector->height)
	{
		x = 0;
		while (x < data->pause_menu.selector->width)
		{
			color = get_texture_pixel(data->pause_menu.selector, x, y);
			if (color != WHITE)
				pixel_put(data, x + start_x, y + start_y, color);
			++x;
		}
		++y;
	}
	draw_gradient(data, start_x, start_y + 50);
}

static void	handle_pause_menu_keys(t_data *data)
{

	if (is_key_pressed(data, KEY_W) || is_key_pressed(data, KEY_UP))
	{
		if (data->pause_menu.selected == 0)
			data->pause_menu.selected = 2;
		else
			--data->pause_menu.selected;
	}
	else if (is_key_pressed(data, KEY_S) || is_key_pressed(data, KEY_DOWN))
	{
		if (data->pause_menu.selected == 2)
			data->pause_menu.selected = 0;
		else
			++data->pause_menu.selected;
	}
	else if (data->pause_menu.selected == 2 && is_key_pressed(data, KEY_LEFT) && data->sensitivity < 320)
		data->sensitivity += 10;
	else if (data->pause_menu.selected == 2 && is_key_pressed(data, KEY_RIGHT) && data->sensitivity > 20)
			data->sensitivity -= 10;
	else if (data->pause_menu.selected == 0 && is_key_pressed(data, KEY_ENTER))
		data->status = GAME;
	else if ((is_key_pressed(data, KEY_ESCAPE) && data->status == PAUSE)
		|| (data->pause_menu.selected == 1 && is_key_pressed(data, KEY_ENTER)))
		f_exit(data, 1);
}

void	handle_pause_menu(t_data *data, long long int cur)
{
	display_menu_background(data, data->pause_menu.background, 448, 5);
	// display_params(data);
	// display_pause_menu(data, data->pause_menu.background, 448, 5);
	display_resume(data, 650, 320);
	display_exit(data, 600, 420);
	display_sensitivity(data, 580, 570);
	if (data->pause_menu.selected == 0)
		display_selector(data, 905, 375);
	else if (data->pause_menu.selected == 1)
		display_selector(data, 800, 475);
	else if (data->pause_menu.selected == 2)
		display_selector(data, 1150, 590);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0, 0);
	if (data->pause_menu.elapsed + 1000 / 10 < cur)
	{
		handle_pause_menu_keys(data);
		data->pause_menu.elapsed = cur;
	}
}
