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
    double  texture_x;
    double  texture_y;

    pixel_y = 0;
    while (pixel_y < data->map.zoom)
    {
        pixel_x = 0;
        while (pixel_x < data->map.zoom)
        {
            texture_x = (pixel_x * 256) / data->map.zoom;
            texture_y = (pixel_y * 256) / data->map.zoom;
            if (c == '1')
                color = get_texture_pixel(&data->map.mini.img[MAP_WALL], texture_x, texture_y);
            else if (c == 'D')
                color = get_texture_pixel(&data->map.mini.img[MAP_DOOR], texture_x, texture_y);
            else if (c == 'F')
            {
                color = get_texture_pixel(&data->map.mini.img[MAP_FLOO], texture_x, texture_y);
                if (abs((pos_x + (data->map.zoom / 2 ) - data->mlx.width / 2)) > (data->map.zoom / 2)
                && abs((pos_y + (data->map.zoom / 2 ) - (data->mlx.height - MARGIN) / 2)) > (data->map.zoom / 2))
                    color = darken_the_color(color);
            }
            else if (c == '0' || c == 'W' || c == 'S' || c == 'N' || c == 'E')
                color = get_texture_pixel(&data->map.mini.img[MAP_FLOOR], texture_x, texture_y);
            else if (c != '.')
                color = 0x6e583e;
            if (get_texture_pixel(data->screen, pixel_x + pos_x, pos_y + pixel_y) != data->color)
                pixel_put(data, pos_x + pixel_x, pos_y + pixel_y, color);
            ++pixel_x;
        }
        ++pixel_y;
    }
}



void    draw_player(t_data *data, int pos_x, int pos_y)
{
    unsigned int    color;
    double pixel_x;
    double pixel_y;

    pixel_y = 0;
    while (pixel_y < data->map.zoom / 2)
    {
        pixel_x = 0;
        while (pixel_x < data->map.zoom / 2)
        {
            color = get_texture_pixel(&data->map.mini.img[MINI_CURS], (pixel_x / (data->map.zoom / 2)) * data->map.mini.img[MINI_CURS].width, (pixel_y / (data->map.zoom / 2)) * data->map.mini.img[MINI_CURS].height);
            if (color != 0)
                pixel_put(data, pixel_x + pos_x + (data->map.zoom / 4), pixel_y + pos_y + (data->map.zoom / 4), data->color);
            ++pixel_x;
        }
        ++pixel_y;
    }
}

void    draw_cursor(t_data *data)
{
    unsigned int    color;
    int pixel_x;
    int pixel_y;
    double  texture_x;
    double  texture_y;

    pixel_y = 0;
    while (pixel_y < data->map.zoom)
    {
        pixel_x = 0;
        while (pixel_x < data->map.zoom)
        {
            texture_x = (pixel_x * 256) / data->map.zoom;
            texture_y = (pixel_y * 256) / data->map.zoom;
            color = get_texture_pixel(&data->map.mini.img[MAP_CURSOR], texture_x, texture_y);
             if (color != WHITE)
                pixel_put(data, pixel_x + data->mlx.width / 2 - (data->map.zoom / 4), pixel_y + (data->mlx.height - MARGIN) / 2 - (data->map.zoom / 4), data->color);
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
            pos_x = (x - data->map.last_pos_x) * data->map.zoom + data->mlx.width / 2 - data->player.coo.coo_x * ((double)data->map.zoom / 64.0);
            pos_y = (y - data->map.last_pos_y) * data->map.zoom + (data->mlx.height - MARGIN) / 2 - data->player.coo.coo_y * ((double)data->map.zoom / 64.0);
            if (pos_x + data->map.zoom > 0 && pos_x < data->mlx.width
            && pos_y + data->map.zoom > 0 && pos_y < data->mlx.height)
            {
                if (x == data->player.coo.case_x && y == data->player.coo.case_y)
                    draw_player(data, pos_x, pos_y);
                draw_texture(data, pos_x, pos_y, data->map.tabmap[y][x]);
            }
            ++x;
        }
        ++y;
    }
    if (data->map.last_pos_x != data->player.coo.case_x || data->map.last_pos_y != data->player.coo.case_y)
        draw_cursor(data);
    // data->status = GAME;
}
