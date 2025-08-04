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

static void	check_dir(t_data *data, int i)
{
	double	posx_display;

	posx_display = 0;
	if (data->ray[i].dir == NORTH)
		data->ray[i].img = data->map.north;
	else if (data->ray[i].dir == SOUTH)
		data->ray[i].img = data->map.south;
	else if (data->ray[i].dir == EAST)
		data->ray[i].img = data->map.east;
	else if (data->ray[i].dir == WEST)
		data->ray[i].img = data->map.west;
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
		data->ray[i].texture_coo.x -= 0;
	if (data->ray[i].texture_coo.x >= data->ray[i].img->width)
		data->ray[i].texture_coo.x = data->ray[i].img->width - 1;
}

static void	display_game_loop(t_data *data, int i)
{
	int				texture_x;
	char			*test1;
	char			*pixel_addr;
	int				test;
	int				texture_y;
	char			*texture_pixel;
	unsigned int	color;

	check_dir(data, i);
	texture_x = data->ray[i].texture_coo.x
		* (data->ray[i].img->bits_per_pixel >> 3);
	test1 = data->ray[i].data_addr + data->ray[i].pix_x
		* data->ray[i].calc_bits;
	data->ray[i].pix_y = data->ray[i].htop_wall;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	test = (data->ray[i].hbot_wall - data->ray[i].htop_wall);
	while (data->ray[i].pix_y < data->ray[i].hbot_wall
		&& data->ray[i].pix_y < data->mlx.height)
	{
		texture_y = (data->ray[i].pix_y - data->ray[i].htop_wall)
			* data->ray[i].img->height / test;
		pixel_addr = test1 + (data->ray[i].pix_y * data->screen->size_line);
		texture_pixel = data->ray[i].img->data_addr + (texture_y
				* data->ray[i].img->size_line + texture_x);
		color = *(unsigned int *)texture_pixel;
		*(unsigned int *)pixel_addr = color;
		data->ray[i].pix_y++;
	}
}

void	display_game(t_data *data)
{
	int	i;

	i = 0;
	display_floor(data, data->display);
	display_sky(data, data->display);
	while (i < data->mlx.width)
	{
		display_game_loop(data, i);
		++i;
	}
}
