

#include "struct_bonus.h"
#include <math.h>

static void	get_world_size(t_data *data, t_display *display, int y)
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
		* (-display->sin_angle) + display->screen_x * display->dist_texture
		* display->cos_angle;
	display->world_y = data->map.mini.player_coo.y - display->dist_texture
		* display->cos_angle - display->screen_x * display->dist_texture
		* display->sin_angle;
	display->pos_cellx = fmod(display->world_x, 64);
	if (display->pos_cellx < 0)
		display->pos_cellx += 64.0;
	display->pos_celly = fmod(display->world_y, 64);
	if (display->pos_celly < 0)
		display->pos_celly += 64.0;
}

static void	get_coo_text(t_data *data, t_display *display)
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

static void	put_text_pix_img(t_data *data, t_display *display, int x, int y)
{
	display->texture_pixel = data->map.floor->data_addr + (display->text_y
			* data->map.floor->size_line + display->text_x
			* display->text_bpp_frac);
	display->color = *(unsigned int *)display->texture_pixel;
	display->pixel_addr = data->screen->data_addr + (y * data->screen->size_line
			+ x * display->screen_bbp_frac);
	*(unsigned int *)display->pixel_addr = display->color;
}

void	*display_floor(void *ptr)
{
	int	x;
	int	y;
	t_data *data;
	t_display display;

	data = (t_data *)ptr;
	display = data->display;
	while (1)
	{
		// sem_wait(data->sem_background);
		pthread_barrier_wait(&data->barrier_background);
		display.cos_angle = cos(data->map.mini.rad);
		display.sin_angle = sin(data->map.mini.rad);
		display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
		display.text_bpp_frac = data->map.floor->bits_per_pixel >> 3;
		y = (data->screen->height / 2) + 1;
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
		pthread_barrier_wait(&data->barrier_background);
		// pthread_barrier_wait(&data->barrier);
	}
}
// #include "struct_bonus.h"
// #include <math.h>

// static void	get_world_size(t_data *data, t_display *display, int y)
// {
// 	display->dist_center = y - data->screen->height * 0.5;
// 	if (display->dist_center == 0)
// 		display->dist_center = 0.0001;
// 	display->screen_y = (double)display->dist_center / data->screen->height;
// 	display->dist_texture = 16.0 / display->screen_y;
// }

// static void	get_coo_world(t_data *data, t_display *display, int x)
// {
// 	display->screen_x = (double)2 * x / data->screen->width - 1;
// 	display->world_x = data->map.mini.player_coo.x + display->dist_texture
// 		* (-display->sin_angle) + display->screen_x * display->dist_texture
// 		* display->cos_angle;
// 	display->world_y = data->map.mini.player_coo.y - display->dist_texture
// 		* display->cos_angle - display->screen_x * display->dist_texture
// 		* display->sin_angle;
// 	display->pos_cellx = fmod(display->world_x, 64);
// 	if (display->pos_cellx < 0)
// 		display->pos_cellx += 64.0;
// 	display->pos_celly = fmod(display->world_y, 64);
// 	if (display->pos_celly < 0)
// 		display->pos_celly += 64.0;
// }

// static void	get_coo_text(t_data *data, t_display *display)
// {
// 	double	zoom_factor;
// 	double	zoomed_x;
// 	double	zoomed_y;

// 	zoom_factor = 2.0 - (data->display.player_height / 16.0);
// 	zoomed_x = display->pos_cellx * zoom_factor;
// 	zoomed_y = display->pos_celly * zoom_factor;
// 	zoomed_x = fmod(zoomed_x, 64.0);
// 	if (zoomed_x < 0)
// 		zoomed_x += 64.0;
// 	zoomed_y = fmod(zoomed_y, 64.0);
// 	if (zoomed_y < 0)
// 		zoomed_y += 64.0;
// 	display->text_x = (int)((zoomed_x / 64.0) * data->map.floor->width);
// 	display->text_y = (int)((zoomed_y / 64.0) * data->map.floor->height);
// 	if (display->text_x < 0)
// 		display->text_x = 0;
// 	if (display->text_x >= data->map.floor->width)
// 		display->text_x = data->map.floor->width - 1;
// 	if (display->text_y < 0)
// 		display->text_y = 0;
// 	if (display->text_y >= data->map.floor->height)
// 		display->text_y = data->map.floor->height - 1;
// }

// static void	put_text_pix_img(t_data *data, t_display *display, int x, int y)
// {
// 	display->texture_pixel = data->map.floor->data_addr + (display->text_y
// 			* data->map.floor->size_line + display->text_x
// 			* display->text_bpp_frac);
// 	display->color = *(unsigned int *)display->texture_pixel;
// 	display->pixel_addr = data->screen->data_addr + (y * data->screen->size_line
// 			+ x * display->screen_bbp_frac);
// 	*(unsigned int *)display->pixel_addr = display->color;
// }

// void	*display_floor(void *ptr)
// {
// 	int			x;
// 	int			y;
// 	t_data		*data;
// 	t_display	display;

// 	data = (t_data *)ptr;
// 	display = data->display;
// 	while (1)
// 	{
// 		sem_wait(data->sem_background);
// 		display.cos_angle = cos(data->map.mini.rad);
// 		display.sin_angle = sin(data->map.mini.rad);
// 		display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
// 		display.text_bpp_frac = data->map.floor->bits_per_pixel >> 3;
// 		y = (data->screen->height / 2) + 1;
// 		while (y < data->screen->height)
// 		{
// 			get_world_size(data, &display, y);
// 			x = 0;
// 			while (x < data->mlx.width)
// 			{
// 				get_coo_world(data, &display, x);
// 				get_coo_text(data, &display);
// 				put_text_pix_img(data, &display, x, y);
// 				++x;
// 			}
// 			++y;
// 		}
// 		pthread_barrier_wait(&data->barrier);
// 		pthread_barrier_wait(&data->barrier);
// 	}
// }
