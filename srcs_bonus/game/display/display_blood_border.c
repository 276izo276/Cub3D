#include "cub3d_bonus.h"
#include "mlx.h"
#include "struct_bonus.h"
#include <math.h>


int	get_right_red(int color, double distance, int size, int life)
{
	int r;
	int g;
	int b;
    double factor;
    double intensity;

	b = (color & 0xFF);
	g = (color >> 8 & 0xFF);
	r = (color >> 16 & 0xFF);
    factor = distance / (double)size;
    if (factor > 1.0)
        factor = 1.0;
    if (factor < 0.0)
        factor = 0.0;
    intensity = (50.0 - life) / 50.0;
    r = (int)((20 + (int)(intensity * 80)) * (1.0 - factor) + r * factor);
    g = (int)((int)(intensity * 5)) * factor;
    b = 0; //(b * factor);
	color = (r << 16) + (g << 8) + b;
	return (color);
}


#include <stdio.h>
void    draw_left_border(t_data *data, int size)
{
    int x;
    int y;
    int color;
    double distance;

    y = 0;
    while (y <= data->mlx.height)
    {
        x = 0;
        while (x <= size)
        {
            distance = x;
            if (y < size)
            {
                distance = sqrt(x * x + y * y);
                // printf("dist >> %f\n", distance);
            }
            // else if (y > data->mlx.height - size - 100)
            //     distance = sqrt(x * x + (data->mlx.height - y - 100) * (data->mlx.height - y - 100));
            if (distance <= size)
            {
                color = get_texture_pixel(data->screen, x, y);
                color = get_right_red(color, distance, size, data->life);
                pixel_put(data, x, y, color);
            }
            ++x;
        }
        ++y; 
    }
}

void    draw_top_border(t_data *data, int size)
{
    int x;
    int y;
    int color;
    double distance;

    y = 0;
    while (y <= size)
    {
        x = 0;
        while (x <= data->mlx.width)
        {
            distance = y;
            if (x < size)
                distance = sqrt(x * x + y * y);
            // else if (x > data->mlx.width - size)
            //     distance = sqrt((data->mlx.width - size) * (data->mlx.width - size) + y * y);
            if (distance <= size)
            {
                color = get_texture_pixel(data->screen, x, y);
                color = get_right_red(color, distance, size, data->life);
                pixel_put(data, x, y, color);
            }
            ++x;
        }
        ++y; 
    }
}

void    draw_right_border(t_data *data, int size)
{
    int x;
    int y;
    int color;

    y = 0;
    while (y <= data->mlx.height)
    {
        x = 0;
        while (x <= size)
        {
            color = get_texture_pixel(data->screen, data->mlx.width - x, y);
            color = get_right_red(color, x, size, data->life);
            pixel_put(data, data->mlx.width - x, y, color);
            ++x;
        }
        ++y; 
    }
}


void    draw_down_border(t_data *data, int size)
{
    int x;
    int y;
    int color;

    y = 0;
    while (y <= size)
    {
        x = 0;
        while (x <= data->mlx.width)
        {
            color = get_texture_pixel(data->screen, x, data->mlx.height - y - 100);
            color = get_right_red(color, y, size, data->life);
            pixel_put(data, x, data->mlx.height - y - 100, color);
            ++x;
        }
        ++y; 
    }
}


void    display_blood_border(t_data *data)
{
    int size;

    data->life = 1;
    printf("life >> %d\n", data->life);
    if (data->life >= 50)
        return ;
    size = pow(((50.0 - data->life) / 50.0), 1.5) * 150;
    draw_left_border(data, size);
    // draw_right_border(data, size);
    draw_top_border(data, size);
    // draw_down_border(data, size);
}
