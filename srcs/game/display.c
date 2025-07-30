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
	// printf("image>>%d\n",data->ray[i].dir);
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
	// printf("posx_display >>> %lf rayx >>> %lf rayy >>> %lf play >>> %lf playx >>> %lf textur_coo_x >>> %d\n", hit, data->ray[i].coo_x, data->ray[i].coo_y, data->map.mini.player_coo.x, data->map.mini.player_coo.y, data->ray[i].texture_coo.x);
	if (data->ray[i].texture_coo.x < 0)
		data->ray[i].texture_coo.x -= 0;
	if (data->ray[i].texture_coo.x >= data->ray[i].img->width)
		data->ray[i].texture_coo.x = data->ray[i].img->width - 1;
	
}

static void	display_game_loop(t_data *data, int i)
{
	check_dir(data, i);
	int	texture_x = data->ray[i].texture_coo.x * (data->ray[i].img->bits_per_pixel >> 3);
	char *test1 = data->ray[i].data_addr + data->ray[i].pix_x * data->ray[i].calc_bits;
	char	*pixel_addr;
	// while (data->ray[i].pix_y > data->ray[i].htop_wall && data->ray[i].pix_y > 0) //mur haut
	// {
	// 	int	texture_y = (data->ray[i].pix_y - data->ray[i].htop_wall) * data->ray[i].img->height / (data->ray[i].hbot_wall - data->ray[i].htop_wall);
	// 	data->ray[i].pixel_addr = data->ray[i].data_addr + (data->ray[i].pix_y
	// 				* data->screen->size_line + data->ray[i].pix_x
	// 				* (data->ray[i].calc_bits));
	// 	char *texture_pixel = data->ray[i].img->data_addr + (texture_y * data->ray[i].img->size_line + texture_x * (data->ray[i].img->bits_per_pixel / 8));
	// 	unsigned int color = *(unsigned int *)texture_pixel;
	// 	*(unsigned int *)data->ray[i].pixel_addr = color;
	// 	// (void)color;
	// 	// *(unsigned int *)data->ray[i].pixel_addr = 0xFF0000;
	// 	data->ray[i].pix_y--;
	// }
	data->ray[i].pix_y = data->ray[i].htop_wall;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	int	test = (data->ray[i].hbot_wall - data->ray[i].htop_wall);
	while (data->ray[i].pix_y < data->ray[i].hbot_wall && data->ray[i].pix_y < data->mlx.height) //mur bas
	{
		int	texture_y = (data->ray[i].pix_y - data->ray[i].htop_wall) * data->ray[i].img->height / test;
		// *(unsigned int *)pixel_addr = 0x00F00FF;
			pixel_addr = test1 + (data->ray[i].pix_y * data->screen->size_line);
		char *texture_pixel = data->ray[i].img->data_addr + (texture_y * data->ray[i].img->size_line + texture_x);
		unsigned int color = *(unsigned int *)texture_pixel;
		*(unsigned int *)pixel_addr = color;
		data->ray[i].pix_y++;
		// if (data->ray[i].dist_wall < 40)
		// 	data->ray[i].pix_y += 1;
	}
	data->ray[i].pix_y = data->ray[i].htop_wall;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	while (data->ray[i].pix_y > 0) // ciel
	{
		pixel_addr = test1 + ((data->ray[i].pix_y)
					* data->screen->size_line);
		*(unsigned int *)pixel_addr = 0xFF002000;
		data->ray[i].pix_y--;
	}
	data->ray[i].pix_y = data->ray[i].hbot_wall;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	// while (data->ray[i].pix_y < data->mlx.height) // sol
	// {
	// 	pixel_addr = test1 + ((data->ray[i].pix_y)
	// 				* data->screen->size_line);
	// 	*(unsigned int *)pixel_addr = 0xFF4F4F4F;
	// 	data->ray[i].pix_y++;
	// }
}

static void	display_floor(t_data *data)
{
	double	dir_x = cos(data->map.mini.rad);
	double	dir_y = sin(data->map.mini.rad);
	double	planex = -sin(data->map.mini.rad);
	double	planey = cos(data->map.mini.rad);
	char	*pixel_addr;
	int	y;

	y = data->screen->height / 2 + 1;
	while (y < data->screen->height)
	{
		double	raydir_leftx = dir_x - planex;
		double	raydir_lefty = dir_y - planey;
		double	raydir_rightx = dir_x + planex;
		double	raydir_righty = dir_y + planey;

		int		dist_center = y - data->screen->height / 2;
		double	eye_heigh = 0.5 * data->screen->height;
		double	world_dist = eye_heigh / dist_center;

		double	stepx = world_dist * (raydir_rightx - raydir_leftx) / data->screen->width;
		double	stepy = world_dist * (raydir_righty - raydir_lefty) / data->screen->width;
		double	floorx = data->map.mini.player_coo.x + world_dist * raydir_leftx;
		double	floory = data->map.mini.player_coo.y + world_dist * raydir_lefty;
		int x = 0;
		while (x < data->screen->width)
		{
			int pos_mapx = (int)(floorx / 64);
			int	pos_mapy = (int)(floory / 64);
			double	pos_cellx = floorx - pos_mapx * 64;
			double	pos_celly = floory - pos_mapy * 64;
			int	text_x = (int)((pos_cellx / 64) * data->map.text_floor->width);
			int	text_y = (int)((pos_celly / 64) * data->map.text_floor->height);
			char *texture_pixel = data->map.text_floor->data_addr + (text_y * data->map.text_floor->size_line + text_x * (data->map.text_floor->bits_per_pixel / 8));
			unsigned int color = *(unsigned int *)texture_pixel;
			pixel_addr = data->screen->data_addr + (y * data->screen->size_line + x * (data->screen->bits_per_pixel / 8));
			*(unsigned int *)pixel_addr = color;
			++x;
			floorx += stepx;
			floory += stepy;
		}
		++y;
	}
}

void    display_game(t_data *data)
{

	int	i;

	i = 0;
	display_floor(data);
	while (i < data->mlx.width)
	{
		display_game_loop(data, i);
		++i;
	}

}
