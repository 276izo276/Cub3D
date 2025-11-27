#include "cub3d_bonus.h"
#include <math.h>

void	*display_sky_first(void *ptr)
{
	int			max_height;
	int			y;
	t_data		*data;
	t_display	display;

	data = (t_data *)ptr;
	max_height = data->screen->height / 8;
	y = 0;
	while (1)
	{
		pthread_barrier_wait(&data->barrier_background);
		display = data->display;
		display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
		display.text_bpp_frac = data->map.ceiling->bits_per_pixel >> 3;
		display.cos_angle = cos(data->map.mini.rad);
		display.sin_angle = sin(data->map.mini.rad);
		display_background_loop_sky(data, display, y, max_height);
		pthread_barrier_wait(&data->barrier_background);
	}
	return (NULL);
}

void	*display_sky_snd(void *ptr)
{
	int			max_height;
	int			y;
	t_data		*data;
	t_display	display;

	data = (t_data *)ptr;
	max_height = data->screen->height / 8 * 2;
	y = data->screen->height / 8;
	while (1)
	{
		pthread_barrier_wait(&data->barrier_background);
		display = data->display;
		display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
		display.text_bpp_frac = data->map.ceiling->bits_per_pixel >> 3;
		display.cos_angle = cos(data->map.mini.rad);
		display.sin_angle = sin(data->map.mini.rad);
		display_background_loop_sky(data, display, y, max_height);
		pthread_barrier_wait(&data->barrier_background);
	}
	return (NULL);
}

void	*display_sky_third(void *ptr)
{
	int			max_height;
	int			y;
	t_data		*data;
	t_display	display;

	data = (t_data *)ptr;
	max_height = data->screen->height / 8 * 3;
	y = data->screen->height / 8 * 2;
	while (1)
	{
		pthread_barrier_wait(&data->barrier_background);
		display = data->display;
		display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
		display.text_bpp_frac = data->map.ceiling->bits_per_pixel >> 3;
		display.cos_angle = cos(data->map.mini.rad);
		display.sin_angle = sin(data->map.mini.rad);
		display_background_loop_sky(data, display, y, max_height);
		pthread_barrier_wait(&data->barrier_background);
	}
	return (NULL);
}

void	*display_sky_last(void *ptr)
{
	int			max_height;
	int			y;
	t_data		*data;
	t_display	display;

	data = (t_data *)ptr;
	max_height = data->screen->height / 8 * 4;
	y = data->screen->height / 8 * 3;
	while (1)
	{
		pthread_barrier_wait(&data->barrier_background);
		display = data->display;
		display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
		display.text_bpp_frac = data->map.ceiling->bits_per_pixel >> 3;
		display.cos_angle = cos(data->map.mini.rad);
		display.sin_angle = sin(data->map.mini.rad);
		display_background_loop_sky(data, display, y, max_height);
		pthread_barrier_wait(&data->barrier_background);
	}
	return (NULL);
}
