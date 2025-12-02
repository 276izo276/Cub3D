#include "cub3d_bonus.h"
#include "color_bonus.h"

void	img_protego(t_data *data, double x, double y, t_img *img)
{
	t_aff	aff;

	aff.a = ((unsigned int)((y - (data->mlx.height - 70)) / 30 * img->height))
		* img->size_line;
	aff.b = ((unsigned int)((x - (data->mlx.width - 350 - 40)) / 30
				* img->width)) * (img->bits_per_pixel >> 3);
	aff.color = *(unsigned int *)(img->data_addr + aff.a + aff.b);
	if (aff.color != WHITE)
		*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
				* data->screen->size_line + ((int)(x))
				* (data->screen->bits_per_pixel / 8)) = aff.color;
}

void	aff_protego(t_data *data)
{
	double	x;
	double	y;
	t_img	*img;

	if (data->player.protego > 0)
	{
		img = &data->img[SHIELD_1 + data->player.protego - 1];
		x = data->mlx.width - 350 - 40;
		while (x < data->mlx.width - 350 - 10)
		{
			y = data->mlx.height - 70;
			while (y < data->mlx.height - 40)
			{
				img_protego(data, x, y, img);
				y++;
			}
			x++;
		}
	}
}
