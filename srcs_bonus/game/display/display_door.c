#include "cub3d_bonus.h"
#include <math.h>
#include "utils_bonus.h"

static void	check_dir(t_data *data, int i, int j)
{
	double	posx_display;

	posx_display = 0;
	if (data->ray[i].doors[j]->dir == NORTH || data->ray[i].doors[j]->dir == SOUTH)
	{
		posx_display = data->ray[i].doors[j]->coo_x / 64;
		if (data->ray[i].doors[j]->dir == NORTH)
			posx_display = 1 - posx_display;
	}
	else if (data->ray[i].doors[j]->dir == WEST || data->ray[i].doors[j]->dir == EAST)
	{
		posx_display = data->ray[i].doors[j]->coo_y / 64;
		if (data->ray[i].doors[j]->dir == EAST)
			posx_display = 1 - posx_display;
	}
	posx_display -= floor(posx_display);
	data->ray[i].doors[j]->texture_coo.x = (int)(posx_display * data->map.door->width);
	if (data->ray[i].doors[j]->texture_coo.x < 0)
		data->ray[i].doors[j]->texture_coo.x -= 0;
	if (data->ray[i].doors[j]->texture_coo.x >= data->map.door->width)
		data->ray[i].doors[j]->texture_coo.x = data->map.door->width - 1;
}

static void	put_text_pix_img(t_data *data, int i, int dist_heigh, int text_x, int j)
{
	char			*text_pix;
	int				text_y;
	char			*pixel_addr;
	unsigned int	color;

	text_y = (data->ray[i].pix_y - data->ray[i].doors[j]->htop_door)
		* data->map.door->height / dist_heigh;
	pixel_addr = data->ray[i].img_addr + (data->ray[i].pix_y
			* data->screen->size_line);
	text_pix = data->map.door->data_addr + (text_y
			* data->map.door->size_line + text_x);
	color = *(unsigned int *)text_pix;
	if (color != 0xFFFFFF)
		*(unsigned int *)pixel_addr = color;
}

#include <stdio.h>

void	display_door(t_data *data, int i)
{
	int	text_x;
	int	dist_heigh;
	int	j;

	j = 0;
	// printf("HERE CHECK IN >>i>>%d      value use>>%d\n",i,data->ray[i].doors[j]->use);
	while (j < data->nb_door && data->ray[i].doors[j]->use != false)
	{
		if (data->ray[i].doors[j]->print == false)
		{
			ft_bzero(data->ray[i].doors[j], sizeof(t_hit_door));
			j++;
			continue;
		}
		check_dir(data, i, j);
		text_x = data->ray[i].doors[j]->texture_coo.x
			* (data->map.door->bits_per_pixel >> 3);
		data->ray[i].img_addr = data->screen->data_addr + data->ray[i].pix_x
			* data->ray[i].calc_bits;
		data->ray[i].pix_y = data->ray[i].doors[j]->htop_door;
		if (data->ray[i].pix_y < 0)
			data->ray[i].pix_y = 0;
		dist_heigh = data->ray[i].doors[j]->hbot_door - data->ray[i].doors[j]->htop_door;
		while (data->ray[i].pix_y < data->ray[i].doors[j]->hbot_door
			&& data->ray[i].pix_y < data->mlx.height)
		{
			put_text_pix_img(data, i, dist_heigh, text_x, j);
			data->ray[i].pix_y++;
		}
		data->ray[i].doors[j]->use = false;
		// printf("RESET USE I>>>%d j>>%d\n",i,j);
		ft_bzero(data->ray[i].doors[j], sizeof(t_hit_door));
		j++;
	}
}
