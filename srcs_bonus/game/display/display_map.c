#include "struct_bonus.h"
#include "utils_bonus.h"
#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "texture_bonus.h"
#include <math.h>
#include "mlx.h"


#include <stdio.h>
#include <unistd.h>


void    draw_texture(t_data *data, int pos_x, int pos_y, char c)
{
    unsigned int    color;
    int pixel_x;
    int pixel_y;

    pixel_y = 0;
    while (pixel_y < data->map.zoom)
    {
        pixel_x = 0;
        while (pixel_x < data->map.zoom)
        {
            if (c == '1')
                color = get_texture_pixel(&data->map.mini.img[MINI_WALL], pixel_x, pixel_y);
            else if (c == 'D')
                color = get_texture_pixel(&data->map.mini.img[MINI_DOOR], pixel_x, pixel_y);
            else if (c == 'F')
                color = get_texture_pixel(&data->map.mini.img[MINI_FLOO], pixel_x, pixel_y);
            else if (c == '0')
                color = get_texture_pixel(&data->map.mini.img[MINI_FLOOR], pixel_x, pixel_y);
            else if (c != '.')
                color = 0x6e583e;
            pixel_put(data, pos_x + pixel_x, pos_y + pixel_y, color);
            ++pixel_x;
        }
        ++pixel_y;
    }
}

void    display_floo_map(t_data *data)
{
    int x;
    int y;
    int pos_x;
    int pos_y;

    y = 0;
    while (y < data->mlx.height)
    {
        x = 0;
        while (x < data->mlx.width)
        {
            pixel_put(data, x, y,  0x6e583e);
            ++x;
        }
        ++y;
    }
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0, 0);
    y = 0;
    while (data->map.tabmap[y])
    {
        x = 0;
        while(data->map.tabmap[y][x])
        {
            pos_x = (x - data->map.player_coo->x) * data->map.zoom + data->mlx.width / 2;
            pos_y = (y - data->map.player_coo->y) * data->map.zoom + data->mlx.height / 2;
            if (pos_x + data->map.zoom > 0 && pos_x < data->mlx.width
            && pos_y + data->map.zoom > 0 && pos_y < data->mlx.height)
            {
                draw_texture(data, pos_x, pos_y, data->map.tabmap[y][x]);
            }
            ++x;
        }
        ++y;
    }
    // data->status = GAME;
}
