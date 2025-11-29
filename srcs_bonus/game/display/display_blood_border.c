#include "cub3d_bonus.h"
#include "time_bonus.h"
#include <math.h>

int	get_right_red(int color, double distance, int max_dist, int life)
{
	int		r;
	int		g;
	int		b;
	double	factor;
	double	intensity;

	b = (color & 0xFF);
	g = (color >> 8 & 0xFF);
	r = (color >> 16 & 0xFF);
	factor = distance / max_dist;
	if (factor > 1.0)
		factor = 1.0;
	if (factor < 0.0)
		factor = 0.0;
	intensity = (50.0 - life) / 50.0;
	factor = pow(factor, 0.5);
	r = (int)((30 + (int)(intensity * 90)) * factor + r * (1.0 - factor));
	g = ((int)((int)(intensity * 5))) * (factor) + g * (1.0 - factor);
	b = (int)(b * (1.0 - factor));
	color = (r << 16) + (g << 8) + b;
	return (color);
}

static double	calc_distance(t_data *data, int x, int y)
{
	double	distance;

	distance = sqrt((x - (data->mlx.width / 2)) * (x - (data->mlx.width / 2))
			+ (y - ((data->mlx.height - MARGIN) / 2)) * (y - ((data->mlx.height
						- MARGIN) / 2)));
	return (distance);
}

static void	draw_border(t_data *data, int radius, int start_x, int max_x)
{
	int		x;
	int		y;
	int		color;
	double	distance;
	double	max_distance;

	max_distance = sqrt((data->mlx.width / 2) * (data->mlx.width / 2)
			+ ((data->mlx.height - MARGIN) / 2) * ((data->mlx.height - MARGIN)
				/ 2));
	y = -1;
	while (++y <= data->mlx.height - 100)
	{
		x = start_x - 1;
		while (++x < max_x)
		{
			distance = calc_distance(data, x, y);
			if (distance > radius)
			{
				color = get_texture_pixel(data->screen, x, y);
				color = get_right_red(color, distance - radius, max_distance
						- radius, data->player.life);
				pixel_put(data, x, y, color);
			}
		}
	}
}

void	display_blood_border(t_data *data, int start_x, int max_x)
{
	int				radius;
	double			life_factor;
	long long int	cur;

	cur = get_mtime();
	if (data->player.life >= 50)
		return ;
	life_factor = data->player.life / 50.0;
	if (data->player.life > 0 && cur > data->sound_frame + (300 + (life_factor * 1000)))
	{
		data->sound = add_end_lst(create_sound(data, 33), data->sound,
				free_sound);
		data->sound_frame = get_mtime();
	}
	radius = (int)(life_factor * (data->mlx.width) / 2.5);
	draw_border(data, radius, start_x, max_x);
}
