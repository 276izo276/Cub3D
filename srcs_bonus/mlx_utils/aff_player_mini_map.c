#include "struct_bonus.h"
#include "color_bonus.h"
#include <math.h>

static void	calc_value_player_mini_map_aff(t_utils_mini *u, t_img *img,
	double rad)
{
	u->cos_val = cos(rad);
	u->sin_val = sin(rad);
	u->xdest = u->x - 9;
	u->ydest = u->y - 15;
	u->xfloat = (u->xdest) * u->cos_val + (u->ydest) * u->sin_val + 9;
	u->yfloat = -(u->xdest) * u->sin_val + (u->ydest) * u->cos_val + 15;
	u->color = *(unsigned int *)(img->data_addr + ((u->y) * img->size_line
				+ (u->x) * (img->bits_per_pixel / 8)));
}

static void	set_pix_player(t_data *data, t_utils_mini *u, int start_y, int start_x)
{
	
	if (u->color != YELLOW)
	{
		u->pixel_addr = u->mmap.data_addr + (((int)ceil(u->yfloat)
				+ start_y) * u->mmap.size_line
			+ ((int)ceil(u->xfloat) + start_x)
			* (u->mmap.bits_per_pixel / 8));
		*(unsigned int *)u->pixel_addr = data->color;
		u->pixel_addr = u->mmap.data_addr + (((int)floor(u->yfloat)
		+ start_y) * u->mmap.size_line
		+ ((int)floor(u->xfloat) + start_x)
		* (u->mmap.bits_per_pixel / 8));
		*(unsigned int *)u->pixel_addr = data->color;
	}
}

void	set_player_in_mini_map(t_data *data, t_utils_mini *u, t_img *img, double rad)
{
	int	start_y;
	int	start_x;

	start_y = u->size / 2 - img->height / 2;
	start_x = u->size / 2 - img->width / 2;
	u->y = -1;
	while (++u->y < img->height)
	{
		u->x = -1;
		while (++u->x < img->width)
		{
			calc_value_player_mini_map_aff(u, img, rad);
			if (u->color != 0x00000000)
			{
				set_pix_player(data, u, start_y, start_x);
			}
		}
	}
}
