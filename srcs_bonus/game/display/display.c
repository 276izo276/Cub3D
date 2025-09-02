#include "cub3d_bonus.h"
#include "mlx.h"
#include "struct_bonus.h"
#include <math.h>

static void	get_right_text(t_data *data, int i)
{
	if (data->ray[i].dir == NORTH)
	{
		// if (data->map.tabmap[data->ray[i].case_y
			// + 1][data->ray[i].case_x] == 'D')
		// 	data->ray[i].img = data->map.door;
		// else
		data->ray[i].img = data->map.north;
	}
	else if (data->ray[i].dir == SOUTH)
	{
		// if (data->map.tabmap[data->ray[i].case_y
			// - 1][data->ray[i].case_x] == 'D')
		// 	data->ray[i].img = data->map.door;
		// else
		data->ray[i].img = data->map.south;
	}
	else if (data->ray[i].dir == EAST)
	{
		// if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x
			// - 1] == 'D')
		// 	data->ray[i].img = data->map.door;
		// else
		data->ray[i].img = data->map.east;
	}
	else if (data->ray[i].dir == WEST)
	{
		// if (data->map.tabmap[data->ray[i].case_y][data->ray[i].case_x
			// + 1] == 'D')
		// 	data->ray[i].img = data->map.door;
		// else
		data->ray[i].img = data->map.west;
	}
}

static void	check_dir(t_data *data, int i)
{
	double	posx_display;

	posx_display = 0;
	get_right_text(data, i);
	if (data->ray[i].dir == NORTH || data->ray[i].dir == SOUTH)
	{
		posx_display = data->ray[i].coo_x / 64;
		if (data->ray[i].dir == NORTH)
			posx_display = 1 - posx_display;
	}
	else if (data->ray[i].dir == WEST || data->ray[i].dir == EAST)
	{
		posx_display = data->ray[i].coo_y / 64;
		if (data->ray[i].dir == EAST)
			posx_display = 1 - posx_display;
	}
	posx_display -= floor(posx_display);
	data->ray[i].texture_coo.x = (int)(posx_display * data->ray[i].img->width);
	if (data->ray[i].texture_coo.x < 0)
		data->ray[i].texture_coo.x = 0;
	if (data->ray[i].texture_coo.x >= data->ray[i].img->width)
		data->ray[i].texture_coo.x = data->ray[i].img->width - 1;
}

static void	put_text_pix_img(t_data *data, int i, int dist_heigh, int text_x)
{
	char			*text_pix;
	int				text_y;
	char			*pixel_addr;
	unsigned int	color;

	text_y = (data->ray[i].pix_y - data->ray[i].htop_wall)
		* data->ray[i].img->height / dist_heigh;
	pixel_addr = data->ray[i].img_addr + (data->ray[i].pix_y
			* data->screen->size_line);
	text_pix = data->ray[i].img->data_addr + (text_y
			* data->ray[i].img->size_line + text_x);
	color = *(unsigned int *)text_pix;
	*(unsigned int *)pixel_addr = color;
}

static void	display_game_loop(t_data *data, int i)
{
	int	text_x;
	int	dist_heigh;

	check_dir(data, i);
	text_x = data->ray[i].texture_coo.x
		* (data->ray[i].img->bits_per_pixel >> 3);
	data->ray[i].img_addr = data->screen->data_addr + data->ray[i].pix_x
		* data->ray[i].calc_bits;
	data->ray[i].pix_y = data->ray[i].htop_wall;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	dist_heigh = data->ray[i].hbot_wall - data->ray[i].htop_wall;
	while (data->ray[i].pix_y < data->ray[i].hbot_wall
		&& data->ray[i].pix_y < data->mlx.height)
	{
		put_text_pix_img(data, i, dist_heigh, text_x);
		data->ray[i].pix_y++;
	}
}

void	*display_fst_part(void *ptr)
{
	int		i;
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		i = 0;
		sem_wait(data->sem_display);
		while (i < data->mlx.width / 4)
		{
			display_game_loop(data, i);
			display_door(data, i);
			// display_msg(data, i);
			++i;
		}
		pthread_barrier_wait(&data->barrier_display);
	}
	return (NULL);
	// aff_mini_map(data);
	// display_hand(data);
}

void	*display_snd_part(void *ptr)
{
	int		i;
	t_data	*data;
	int		max_pix;

	data = (t_data *)ptr;
	max_pix = 2 * (data->mlx.width / 4);
	while (1)
	{
		i = data->mlx.width / 4;
		sem_wait(data->sem_display);
		while (i < max_pix)
		{
			display_game_loop(data, i);
			display_door(data, i);
			// display_msg(data, i);
			++i;
		}
		pthread_barrier_wait(&data->barrier_display);
	}
	return (NULL);
	// aff_mini_map(data);
	// display_hand(data);
}

void	*display_third_part(void *ptr)
{
	int		i;
	int		max_pix;
	t_data	*data;

	data = (t_data *)ptr;
	max_pix = 3 * (data->mlx.width / 4);
	while (1)
	{
		i = 2 * (data->mlx.width / 4);
		sem_wait(data->sem_display);
		while (i < max_pix)
		{
			display_game_loop(data, i);
			display_door(data, i);
			// display_msg(data, i);
			++i;
		}
		pthread_barrier_wait(&data->barrier_display);
	}
	return (NULL);
	// aff_mini_map(data);
	// display_hand(data);
}

void	*display_last_part(void *ptr)
{
	int		i;
	t_data	*data;

	data = (t_data *)ptr;
	while (1)
	{
		i = 3 * (data->mlx.width / 4);
		sem_wait(data->sem_display);
		while (i < data->mlx.width)
		{
			display_game_loop(data, i);
			display_door(data, i);
			// display_msg(data, i);
			++i;
		}
		pthread_barrier_wait(&data->barrier_display);
	}
	return (NULL);
	// aff_mini_map(data);
	// display_hand(data);
}
