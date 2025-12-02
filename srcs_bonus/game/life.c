#include "cub3d_bonus.h"
#include "color_bonus.h"

void	aff_heart_color(t_data *data, double x, double y)
{
	t_aff	aff;

	aff.a = ((unsigned int)((y - (data->mlx.height - 57)) / 20
				* data->img[HEART].height)) * data->img[HEART].size_line;
	aff.b = ((unsigned int)((x - (data->mlx.width - 40)) / 20
				* data->img[HEART].width))
		* (data->img[HEART].bits_per_pixel >> 3);
	aff.color = *(unsigned int *)(data->img[HEART].data_addr + aff.a + aff.b);
	if (aff.color != WHITE)
		*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
				* data->screen->size_line + ((int)(x))
				* (data->screen->bits_per_pixel >> 3)) = aff.color;
}

void	aff_life_heart(t_data *data)
{
	double			x;
	double			y;

	x = data->mlx.width - 40;
	while (x < data->mlx.width - 20)
	{
		y = data->mlx.height - 57;
		while (y < data->mlx.height - 37)
		{
			aff_heart_color(data, x, y);
			y++;
		}
		x++;
	}
}

void	aff_life_red(t_data *data, double *x, double *y)
{
	while (*x < data->mlx.width - 50)
	{
		*y = data->mlx.height - 55;
		while (*y < data->mlx.height - 40)
		{
			*(unsigned int *)(data->screen->data_addr + ((int)(*y - MARGIN))
					* data->screen->size_line + ((int)(*x))
					* (data->screen->bits_per_pixel >> 3)) = 0xFF0000;
			(*y)++;
		}
		(*x)++;
	}
}

void	aff_life(t_data *data)
{
	double	x;
	double	y;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + ((double)data->player.life / 100 * 300))
	{
		y = data->mlx.height - 55;
		while (y < data->mlx.height - 40)
		{
			*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
					* data->screen->size_line + ((int)(x))
					* (data->screen->bits_per_pixel >> 3)) = 0x00FF00;
			y++;
		}
		x++;
	}
	aff_life_red(data, &x, &y);
	aff_life_heart(data);
}
