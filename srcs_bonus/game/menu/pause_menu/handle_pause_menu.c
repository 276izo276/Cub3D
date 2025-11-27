#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include "player_bonus.h"

static void	sensitivity_loop_x(unsigned int color, t_data *data, int x, int y)
{
	int	max_x;

	max_x = 1148 - (data->sensitivity * 1.28125);
	if (data->sensitivity == 20)
		max_x = 1138;
	if (color != WHITE && color != YELLOW)
	{
		if (data->pause_menu.selected != 2)
			color = darken_the_color(color);
		pixel_put(data, x, y, color);
	}
	if (x > 728 && x < max_x && y > 625 && y < 670 && color == YELLOW)
	{
		color = data->player.color;
		if (data->pause_menu.selected != 2)
			color = darken_the_color(color);
		pixel_put(data, x, y, color);
	}
}

static void	display_sensitivity(t_data *data, int start_x, int start_y)
{
	int				y;
	int				x;
	unsigned int	color;

	y = 0;
	while (y < data->img[PAUSE_SENSITIVITY].height)
	{
		x = 0;
		while (x < data->img[PAUSE_SENSITIVITY].width)
		{
			color = get_texture_pixel(&data->img[PAUSE_SENSITIVITY], x, y);
			sensitivity_loop_x(color, data, x + start_x, y + start_y);
			++x;
		}
		++y;
	}
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
	else if (data->pause_menu.selected == 2 && is_key_pressed(data, KEY_LEFT)
		&& data->sensitivity < 320)
		data->sensitivity += 10;
	else if (data->pause_menu.selected == 2 && is_key_pressed(data, KEY_RIGHT)
		&& data->sensitivity > 20)
		data->sensitivity -= 10;
	else if (data->pause_menu.selected == 0 && is_key_pressed(data, KEY_ENTER))
		data->status = GAME;
	else if ((is_key_pressed(data, KEY_ESCAPE) && data->status == PAUSE)
		|| (data->pause_menu.selected == 1 && is_key_pressed(data, KEY_ENTER)))
		f_exit(data, 1);
}

void	handle_pause_menu(t_data *data, long long int cur)
{
	display_menu_background(data, &data->img[PAUSE_BACKGROUND], 448, 5);
	display_resume(data, 650, 320);
	display_exit(data, 600, 420);
	display_sensitivity(data, 580, 570);
	if (data->pause_menu.selected == 0)
		display_selector(data, 905, 375);
	else if (data->pause_menu.selected == 1)
		display_selector(data, 800, 475);
	else if (data->pause_menu.selected == 2)
		display_selector(data, 1150, 590);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,
		0);
	if (data->pause_menu.elapsed + 1000 / 10 < cur)
	{
		handle_pause_menu_keys(data);
		data->pause_menu.elapsed = cur;
	}
}
