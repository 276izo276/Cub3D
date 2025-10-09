#include "struct_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>
#include "mlx.h"


#include <stdio.h>
#include <unistd.h>


void    display_floo_map(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < data->mlx.height)
    {
        x = 0;
        while (x < data->mlx.width)
        {
            pixel_put(data, x, y, 0);
            ++x;
        }
        ++y;
    }
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0, 0);
    data->status = GAME;
}
