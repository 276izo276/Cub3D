#include "cub3d_bonus.h"
#include "mlx.h"
#include "struct_bonus.h"
#include <math.h>


int	get_right_red(int color, double distance, int size)
{
	int r;
	int g;
	int b;
    double factor;

	b = (color & 0xFF);
	g = (color >> 8 & 0xFF);
	r = (color >> 16 & 0xFF);
    factor = distance / (double)size;
    if (factor > 1.0)
        factor = 1.0;
    if (factor < 0.0)
        factor = 0.0;
    r = (int)(255 * (1.0 - factor) + r * factor);
    g = 0;
    b = 0;
	color = (r << 16) + (g << 8) + b;
	return (color);
}

#include <stdio.h>
void    draw_left_border(t_data *data, int size)
{
    int x;
    int y;
    int distance;
    int color;

    y = 0;
    while (y <= data->mlx.height)
    {
        x = 0;
        while (x <= size)
        {
            distance = x;
            // if (distance < 40)
            // {
                color = get_texture_pixel(data->screen, x, y);
                color = get_right_red(color, distance, size);
                pixel_put(data, x, y, color);
            // }
            ++x;
        }
        ++y; 
    }
}

void    draw_right_border(t_data *data, int size)
{
    int x;
    int y;
    int distance;
    int color;

    y = 0;
    while (y <= data->mlx.height)
    {
        x = 0;
        while (x <= size)
        {
            distance = x;
            // if (distance < 40)
            // {
                color = get_texture_pixel(data->screen, data->mlx.width - x, y);
                color = get_right_red(color, distance, size);
                pixel_put(data, data->mlx.width - x, y, color);
            // }
            ++x;
        }
        ++y; 
    }
}

void    draw_top_border(t_data *data, int size)
{
    int x;
    int y;
    int distance;
    int color;

    y = 0;
    while (y <= size)
    {
        x = 0;
        while (x <= data->mlx.width)
        {
            distance = y;
            // if (distance < 40)
            // {
                color = get_texture_pixel(data->screen, x, y);
                color = get_right_red(color, distance, size);
                pixel_put(data, x, y, color);
            // }
            ++x;
        }
        ++y; 
    }
}

void    draw_down_border(t_data *data, int size)
{
    int x;
    int y;
    int distance;
    int color;

    y = 0;
    while (y <= size)
    {
        x = 0;
        while (x <= data->mlx.width)
        {
            distance = y;
            // if (distance < 40)
            // {
                color = get_texture_pixel(data->screen, x, data->mlx.height - y - 100);
                color = get_right_red(color, distance, size);
                pixel_put(data, x, data->mlx.height - y - 100, color);
            // }
            ++x;
        }
        ++y; 
    }
}
void    display_blood_border(t_data *data)
{
    int size;

    data->life = 80;
    if (data->life == 100)
        return ;
    size = 100 - data->life;
    draw_left_border(data, size);
    draw_right_border(data, size);
    draw_top_border(data, size);
    draw_down_border(data, size);
}