#include "cub3d_bonus.h"
#include "color_bonus.h"

void	aff_shield_color(t_data *data, double *x, double *y)
{
	unsigned int	color;
	unsigned int	a;
	unsigned int	b;

	*x = data->mlx.width - 40;
	while (*x < data->mlx.width - 20)
	{
		*y = data->mlx.height - 82 - 1;
		while (++(*y) < data->mlx.height - 62)
		{
			a = ((unsigned int)((*y - (data->mlx.height - 82)) / 20
						* data->img[SHIELD].height))
				* data->img[SHIELD].size_line;
			b = ((unsigned int)((*x - (data->mlx.width - 40)) / 20
						* data->img[SHIELD].width))
				* (data->img[SHIELD].bits_per_pixel >> 3);
			color = *(unsigned int *)(data->img[SHIELD].data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + ((int)(*y - MARGIN))
						* data->screen->size_line + ((int)(*x))
						* (data->screen->bits_per_pixel >> 3)) = color;
		}
		(*x)++;
	}
}

void	aff_shield(t_data *data)
{
	double	x;
	double	y;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + ((double)data->player.shield / 100
			* 300))
	{
		y = data->mlx.height - 80;
		while (y < data->mlx.height - 65)
		{
			*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
					* data->screen->size_line + ((int)(x))
					* (data->screen->bits_per_pixel / 8)) = 0x0000FF;
			y++;
		}
		x++;
	}
	aff_shield_color(data, &x, &y);
}
