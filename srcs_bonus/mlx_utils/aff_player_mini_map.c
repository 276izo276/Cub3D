#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include "texture_bonus.h"
#include <math.h>
#include <stdlib.h>

void	calc_value_player_mini_map_aff(t_utils_mini *u, t_img *img, double rad)
{
	u->cos_val = cos(rad);
	u->sin_val = sin(rad);
	u->xdest = u->x - 16;
	u->ydest = u->y - 19;
	u->xfloat = (u->xdest) * u->cos_val + (u->ydest) * u->sin_val + 16;
	u->yfloat = -(u->xdest) * u->sin_val + (u->ydest) * u->cos_val + 19;
	u->color = *(unsigned int *)(img->data_addr + ((u->y) * img->size_line
				+ (u->x) * (img->bits_per_pixel / 8)));
}

static void	set_pix_player(t_data *data, t_utils_mini *u, int start_y,
		int start_x)
{
	if (start_x < 0 || start_x >= u->size || start_y < 0 || start_y > u->size)
		return ;
	if (u->color != YELLOW)
	{
		u->pixel_addr = u->mmap.data_addr + (((int)ceil(u->yfloat) + start_y)
				* u->mmap.size_line + ((int)ceil(u->xfloat) + start_x)
				* (u->mmap.bits_per_pixel / 8));
		*(unsigned int *)u->pixel_addr = data->player.color;
		u->pixel_addr = u->mmap.data_addr + (((int)floor(u->yfloat) + start_y)
				* u->mmap.size_line + ((int)floor(u->xfloat) + start_x)
				* (u->mmap.bits_per_pixel / 8));
		*(unsigned int *)u->pixel_addr = data->player.color;
	}
}

void	set_player_in_mini_map(t_data *data, t_utils_mini *u, double rad)
{
	t_img	*img;

	img = &data->map.mini.img[MINI_CURS];
	u->start_y = u->size / 2 - img->height / 2;
	u->start_x = u->size / 2 - img->width / 2;
	u->y = -1;
	while (++u->y < img->height)
	{
		u->x = -1;
		while (++u->x < img->width)
		{
			calc_value_player_mini_map_aff(u, img, rad);
			if (u->color != 0x00000000)
				set_pix_player(data, u, u->start_y, u->start_x);
		}
	}
	set_trail_foot(data, u);
	save_and_move_foot(data, rad);
}

void	calc_value_player_map(double pixel_x, double pixel_y, t_data *data,
		unsigned int *color)
{
	t_utils_mini	u;

	u.cos_val = cos(data->map.mini.rad);
	u.sin_val = sin(data->map.mini.rad);
	u.xdest = pixel_x - 16;
	u.ydest = pixel_y - 19;
	u.xfloat = -(u.xdest) * u.cos_val + (u.ydest) * u.sin_val + 16;
	u.yfloat = (u.xdest) * u.sin_val + (u.ydest) * u.cos_val + 19;
	*color = *(unsigned int *)(data->map.mini.img[MINI_CURS].data_addr
			+ (((int)u.yfloat) * data->map.mini.img[MINI_CURS].size_line
				+ ((int)u.xfloat)
				* (data->map.mini.img[MINI_CURS].bits_per_pixel / 8)));
}
