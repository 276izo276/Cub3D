#include "cub3d_bonus.h"
#include "mlx.h"
#include "time_bonus.h"
#include <math.h>

int	get_right_white(t_data *data, int color, double distance)
{
	int	r;
	int	g;
	int	b;

	if (data->count_frame < 0)
		data->count_frame = 0;
	b = (color & 255);
	b = (int)(b + (255 - b) * ((1 - distance / 350)) * data->count_frame / 100);
	if (b > 255)
		b = 255;
	g = (color >> 8 & 255);
	g = (int)(g + (255 - g) * ((1 - distance / 350)) * data->count_frame / 100);
	if (g > 255)
		g = 255;
	r = (color >> 16 & 255);
	r = (int)(r + (255 - r) * ((1 - distance / 350)) * data->count_frame / 100);
	if (r > 255)
		r = 255;
	color = (r << 16) + (g << 8) + b;
	return (color);
}

void	lumos_loop(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				x;
	int				y;
	double			distance;

	y = -350;
	color = 0;
	while (y < 350)
	{
		x = -350;
		while (x < 350)
		{
			distance = sqrt(y * y + x * x);
			if (distance < 350)
			{
				color = get_texture_pixel(data->screen, x + start_x, y
						+ start_y);
				color = get_right_white(data, color, distance);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

void	spell_lumos(t_data *data)
{
	int	start_x;
	int	start_y;

	if (data->lumos.active && get_mtime() > data->spell[LUMOS].launch_time
		+ data->spell[LUMOS].base_timer * 1000)
	{
		data->spell[LUMOS].end_time = get_mtime();
		data->lumos.active = false;
		data->active_spell = -1;
	}
	start_x = data->lumos.x_wand + (data->img[PLAYER_WAND].width / 2) - 2;
	start_y = data->lumos.y_wand + 5;
	if (data->count_frame > 0)
		data->count_frame -= 2;
	if (data->count_frame < 0)
		data->count_frame = 0;
	if (data->lumos.active)
		data->count_frame = data->lumos.count_frame;
	lumos_loop(data, start_x, start_y);
	if (data->lumos.active == false)
		data->lumos.count_frame -= 3;
	if (data->lumos.count_frame < 0)
		data->lumos.count_frame = 0;
}

void	cast_lumos(t_data *data, int info)
{
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1 && !data->lumos.active
		&& get_mtime() > data->spell[LUMOS].end_time
		+ data->spell[LUMOS].base_cooldown * 1000)
	{
		data->lumos.active = true;
		data->active_spell = LUMOS;
		data->lumos.count_frame = 100;
		data->spell[LUMOS].launch_time = get_mtime();
	}
	else if (data->lumos.active == true)
	{
		data->lumos.active = false;
		data->active_spell = -1;
		data->spell[LUMOS].end_time = get_mtime();
	}
	if (data->lumos.active == true)
		data->sound = add_end_lst(create_sound(data, 0), data->sound,
				free_sound);
}
