#include "cub3d_bonus.h"
#include <math.h>

void	get_coo_world_floor(t_data *data, t_display *display, int x)
{
	display->screen_x = (double)2 * x / data->screen->width - 1;
	display->world_x = data->player.coo.coo_x + display->dist_texture
		* (-display->sin_angle) + display->screen_x * display->dist_texture
		* display->cos_angle;
	display->world_y = data->player.coo.coo_y - display->dist_texture
		* display->cos_angle - display->screen_x * display->dist_texture
		* display->sin_angle;
	display->pos_cellx = fmod(display->world_x, 64);
	if (display->pos_cellx < 0)
		display->pos_cellx += 64.0;
	display->pos_celly = fmod(display->world_y, 64);
	if (display->pos_celly < 0)
		display->pos_celly += 64.0;
}

void	get_coo_text_floor(t_data *data, t_display *display)
{
	display->text_x = (int)(((display->pos_cellx) / 64.0)
			* data->map.floor->width);
	display->text_y = (int)(((display->pos_celly) / 64.0)
			* data->map.floor->height);
	if (display->text_x < 0)
		display->text_x = 0;
	if (display->text_x >= data->map.floor->width)
		display->text_x = data->map.floor->width - 1;
	if (display->text_y < 0)
		display->text_y = 0;
	if (display->text_y >= data->map.floor->height)
		display->text_y = data->map.floor->height - 1;
}

void	put_text_pix_img_floor(t_data *data, t_display *display, int x, int y)
{
	display->texture_pixel = data->map.floor->data_addr + (display->text_y
			* data->map.floor->size_line + display->text_x
			* display->text_bpp_frac);
	display->color = *(unsigned int *)display->texture_pixel;
	display->pixel_addr = data->screen->data_addr + (y * data->screen->size_line
			+ x * display->screen_bbp_frac);
	*(unsigned int *)display->pixel_addr = display->color;
}

void	display_background_loop_floor(t_data *data, t_display display, int y,
		int max_height)
{
	int	x;

	while (y < max_height)
	{
		get_world_size(data, &display, y);
		x = 0;
		while (x < data->mlx.width)
		{
			get_coo_world_floor(data, &display, x);
			get_coo_text_floor(data, &display);
			put_text_pix_img_floor(data, &display, x, y);
			++x;
		}
		++y;
	}
}
