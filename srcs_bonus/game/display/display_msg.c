#include "cub3d_bonus.h"
#include <math.h>
#include "utils_bonus.h"
#include "color_bonus.h"


static void	put_text_pix_img(t_data *data, int i, int dist_heigh, int text_x)
{
	char			*text_pix;
	int				text_y;
	char			*pixel_addr;
	unsigned int	color;

	text_y = (data->ray[i].pix_y - data->ray[i].htop_wall)
		* data->map.msg_img[data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->msg_nb]->height / dist_heigh;
	pixel_addr = data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->img_addr + (data->ray[i].pix_y
			* data->screen->size_line);
	text_pix = data->map.msg_img[data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->msg_nb]->data_addr + (text_y
			* data->ray[i].img->size_line + text_x);
	color = *(unsigned int *)text_pix;
	*(unsigned int *)pixel_addr = color;
}

static void	check_dir(t_data *data, int i)
{
	double	posx_display;

	posx_display = 0;
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
	data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->texture_coo.x = (int)(posx_display * data->map.msg_img[data->ray[i].case_y][data->ray[i].case_x].width);
	if (data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->texture_coo.x < 0)
		data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->texture_coo.x -= 0;
	if (data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->texture_coo.x >= data->map.msg_img[data->ray[i].case_y][data->ray[i].case_x].width)
		data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->texture_coo.x = data->map.msg_img[data->ray[i].case_y][data->ray[i].case_x].width - 1;
}

void	display_msg(t_data *data, int i)
{
	int	text_x;
	int	dist_heigh;

	check_dir(data, i);
	text_x = data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->texture_coo.x
		* (data->map.msg_img[data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->msg_nb]->bits_per_pixel >> 3);
	data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->img_addr = data->screen->data_addr + data->ray[i].pix_x
		* data->ray[i].calc_bits;
	data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->pix_y = data->ray[i].htop_wall;
	if (data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->pix_y < 0)
		data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->pix_y = 0;
	dist_heigh = data->ray[i].hbot_wall - data->ray[i].htop_wall;
	while (data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->pix_y < data->ray[i].hbot_wall
		&& data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->pix_y < data->mlx.height)
	{
		put_text_pix_img(data, i, dist_heigh, text_x);
		++data->map.wall_map[data->ray[i].case_y][data->ray[i].case_x]->pix_y;
	}
}
