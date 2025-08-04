#include "cub3d.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "struct.h"
#include "texture.h"
#include "time.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

static void get_world_size(t_data *data, t_display *display, int y)
{
	display->dist_center = y - data->screen->height * 0.5;
		if (display->dist_center == 0)
			display->dist_center = 0.0001;
		display->screen_y = (double)display->dist_center / data->screen->height;
		display->dist_texture = 16.0 / display->screen_y;
}

static void	get_coo_world(t_data *data, t_display *display, int x)
{
	display->screen_x = (double)2 * x / data->screen->width - 1;
	display->world_x = data->map.mini.player_coo.x + display->dist_texture
		* (-display->sin_angle) + display->screen_x * display->dist_texture * display->cos_angle;
	display->world_y = data->map.mini.player_coo.y - display->dist_texture * display->cos_angle
		- display->screen_x * display->dist_texture * display->sin_angle;
	display->pos_cellx = fmod(display->world_x, 64);
	if (display->pos_cellx < 0)
		display->pos_cellx += 64.0;
	display->pos_celly = fmod(display->world_y, 64);
	if (display->pos_celly < 0)
		display->pos_celly += 64.0;
}

static void	get_coo_text(t_data *data, t_display *display)
{
	display->text_x = (int)(((display->pos_cellx) / 64.0) * data->map.text_floor->width);
	display->text_y = (int)(((display->pos_celly) / 64.0) * data->map.text_floor->height);
	if (display->text_x < 0)
		display->text_x = 0;
	if (display->text_x >= data->map.text_floor->width)
		display->text_x = data->map.text_floor->width - 1;
	if (display->text_y < 0)
		display->text_y = 0;
	if (display->text_y >= data->map.text_floor->height)
		display->text_y = data->map.text_floor->height - 1;
}

static void	put_text_pix_img(t_data *data, t_display *display, int x, int y)
{
	display->texture_pixel = data->map.text_floor->data_addr + (display->text_y
			* data->map.text_floor->size_line + display->text_x * display->text_bpp_frac);
	display->color = *(unsigned int *)display->texture_pixel;
	display->pixel_addr = data->screen->data_addr + (y * data->screen->size_line
			+ x * display->screen_bbp_frac);
	*(unsigned int *)display->pixel_addr = display->color;
}

void	display_floor(t_data *data, t_display display)
{
	int	x;
	int	y;

	display.cos_angle = cos(data->map.mini.rad);
	display.sin_angle = sin(data->map.mini.rad);
	display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
	display.text_bpp_frac = data->map.text_floor->bits_per_pixel >> 3;
	y = (data->screen->height >> 2) + 1;
	while (y < data->screen->height)
	{
		get_world_size(data, &display, y);
		x = 0;
		while (x < data->mlx.width)
		{
			get_coo_world(data, &display, x);
			get_coo_text(data, &display);
			put_text_pix_img(data, &display, x, y);
			++x;
		}
		++y;
	}
}
