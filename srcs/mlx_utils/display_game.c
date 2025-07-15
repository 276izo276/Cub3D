#include "cub3d.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "struct.h"
#include "texture.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

void init_display(t_data *data, t_display *f_display)
{
    ft_bzero(f_display, sizeof(t_display));
    f_display->img = mlx_new_image(data->mlx.mlx, data->mlx.width, data->mlx.height - MARGIN);
    if (f_display->img == NULL)
        f_exit(data, 1);
    f_display->data_addr = mlx_get_data_addr(f_display->img, &f_display->bits_per_pixel,
        &f_display->size_line, &f_display->endian);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < data->mlx.width && y >= 0 && y < (data->mlx.height - MARGIN))
	{
		dst = data->f_display.data_addr + (y * data->f_display.size_line + x * (data->f_display.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
// void	get_pixel_col(t_data *data, t_display *f_display, double wall_height)
// {
// 	int	text_x;
// 	int	y;
// 	int	start;
// 	int	end;

// 	end = (data->mlx.height / 2) + (wall_height / 2);
// 	start = (data->mlx.height / 2) - (wall_height / 2);
// 	y = 0;
// 	text_x = (int)(wall_height * f_display->texture[NORTH].width);
// 	while (y < data->mlx.height - MARGIN)
// 	{
// 		if (y < start)
// 			put_pixel(data, text_x, y, 0xFF0000);
// 		else if (y >= start && y <= end)
// 		{

// 		}
// 		++y;
// 	}
// 	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, f_display->img, 0, 0);
// }
