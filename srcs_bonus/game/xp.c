#include "cub3d_bonus.h"
#include "color_bonus.h"
#include "utils_bonus.h"
#include <math.h>

void	aff_xp_color(t_data *data, double *y, double *x)
{
	unsigned int	color;
	unsigned int	a;
	unsigned int	b;

	*x = data->mlx.width - 40;
	while (*x < data->mlx.width - 10)
	{
		*y = data->mlx.height - 38;
		while (*y < data->mlx.height - 8)
		{
			a = ((unsigned int)((*y - (data->mlx.height - 38)) / 30
						* data->img[XP].height)) * data->img[XP].size_line;
			b = ((unsigned int)((*x - (data->mlx.width - 40)) / 30
						* data->img[XP].width))
				* (data->img[XP].bits_per_pixel >> 3);
			color = *(unsigned int *)(data->img[XP].data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + ((int)(*y - MARGIN))
						* data->screen->size_line + ((int)(*x))
						* (data->screen->bits_per_pixel >> 3)) = color;
			(*y)++;
		}
		(*x)++;
	}
}

void	aff_xp(t_data *data)
{
	double	x;
	double	y;
	char	*str;

	x = data->mlx.width - 350;
	while (x < data->mlx.width - 350 + fmod(data->player.xp * 300, 300))
	{
		y = data->mlx.height - 30;
		while (y < data->mlx.height - 15)
		{
			*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
					* data->screen->size_line + ((int)(x))
					* (data->screen->bits_per_pixel / 8)) = 0xFFFF00;
			y++;
		}
		x++;
	}
	aff_xp_color(data, &y, &x);
	str = ft_itoa((int)data->player.xp);
	aff_text(str, 20, (t_coo){.x = calc_start_text(str, data->mlx.width - 365,
			data, 20), .y = data->mlx.height - 32}, data);
	free(str);
}
