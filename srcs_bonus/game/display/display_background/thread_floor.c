#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include <math.h>

void	*display_floor_first(void *ptr)
{
	int			max_height;
	int			y;
	t_data		*data;
	t_display	display;

	data = (t_data *)ptr;
	max_height = data->screen->height / 8 * 5;
	display = data->display;
	display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
	display.text_bpp_frac = data->map.floor->bits_per_pixel >> 3;
	y = (data->screen->height / 2);
	while (1)
	{
		pthread_barrier_wait(&data->barrier_background);
		display.cos_angle = cos(data->map.mini.rad);
		display.sin_angle = sin(data->map.mini.rad);
		display_background_loop_floor(data, display, y, max_height);
		pthread_barrier_wait(&data->barrier_background);
	}
}

void	*display_floor_snd(void *ptr)
{
	int			max_height;
	int			y;
	t_data		*data;
	t_display	display;

	data = (t_data *)ptr;
	max_height = data->screen->height / 8 * 6;
	display = data->display;
	display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
	display.text_bpp_frac = data->map.floor->bits_per_pixel >> 3;
	y = data->screen->height / 8 * 5;
	while (1)
	{
		pthread_barrier_wait(&data->barrier_background);
		display.cos_angle = cos(data->map.mini.rad);
		display.sin_angle = sin(data->map.mini.rad);
		display_background_loop_floor(data, display, y, max_height);
		pthread_barrier_wait(&data->barrier_background);
	}
}

void	*display_floor_third(void *ptr)
{
	int			max_height;
	int			y;
	t_data		*data;
	t_display	display;

	data = (t_data *)ptr;
	max_height = data->screen->height / 8 * 7;
	display = data->display;
	display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
	display.text_bpp_frac = data->map.floor->bits_per_pixel >> 3;
	y = data->screen->height / 8 * 6;
	while (1)
	{
		pthread_barrier_wait(&data->barrier_background);
		display.cos_angle = cos(data->map.mini.rad);
		display.sin_angle = sin(data->map.mini.rad);
		display_background_loop_floor(data, display, y, max_height);
		pthread_barrier_wait(&data->barrier_background);
	}
}

void	*display_floor_last(void *ptr)
{
	int			max_height;
	int			y;
	t_data		*data;
	t_display	display;

	data = (t_data *)ptr;
	max_height = data->screen->height;
	display = data->display;
	display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
	display.text_bpp_frac = data->map.floor->bits_per_pixel >> 3;
	y = data->screen->height / 8 * 7;
	while (1)
	{
		pthread_barrier_wait(&data->barrier_background);
		display.cos_angle = cos(data->map.mini.rad);
		display.sin_angle = sin(data->map.mini.rad);
		display_background_loop_floor(data, display, y, max_height);
		pthread_barrier_wait(&data->barrier_background);
	}
}
