#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include "math.h"


#include <stdio.h>

void	spell_lumos(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;
	int				start_x;
	int				start_y;
	double			R = 0;
	double			G = 0;
	double			B = 0;

	start_x = data->spell.x_wand + (data->player_wand->width / 2) - 2;
	start_y = data->spell.y_wand + 5;
	y = -100;
	color = 0;
	while (y < 100)
	{
		x = -100;
		while (x < 100)
		{
			if (sqrt(y * y + x * x) < 100)
			{
				color = get_texture_pixel(data->screen, x + start_x, y
					+ start_y);
				// printf(" 1 er color >> %x\n", color);
				B = (color & 255) * (double)((100 - (sqrt(y * y + x * x))) / 10 + 1.5);
				if (B > 255)
					B = 255;
				G = (color >> 8 & 255) * (double)((100 - (sqrt(y * y + x * x))) / 10 + 1.5);
				if (G > 255)
					G = 255;
				R = (color >> 16 & 255) * (double)((100 - (sqrt(y * y + x * x))) / 10 + 1.5);
				if (R > 255)
					R = 255;
				// printf("R >> %d G >> %d B >>> %d\n", R, G, B);
				color = ((int)R << 16) + ((int)G << 8) + (int)B;
				// printf("color >> %x\n", color);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

// void	spell_lumos(t_data *data)
// {
// 	int				x;
// 	int				y;
// 	unsigned int	color;

// 	y = 0;
// 	color = 0;
// 	while (y < data->spell.lumos->height)
// 	{
// 		x = 0;
// 		while (x < data->spell.lumos->width)
// 		{
// 			color = get_texture_pixel(data->spell.lumos, x, y);
// 			if (color != WHITE)
// 			{
// 				pixel_put(data, x + data->spell.x_wand + (data->player_wand->width / 2) - (data->spell.lumos->width / 2) - 1, y + data->spell.y_wand - (data->spell.lumos->height / 2), color);
// 			}
// 			++x;
// 		}
// 		++y;
// 	}
// }
