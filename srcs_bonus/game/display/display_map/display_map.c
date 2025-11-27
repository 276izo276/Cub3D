#include "cub3d_bonus.h"
#include "mlx.h"
#include "texture_bonus.h"
#include <math.h>

static void	calc_dist_center(t_data *data, int x, int y)
{
	double	pos_x;
	double	pos_y;
	double	small_dist;
	double	dist_center;

	small_dist = 0;
	pos_x = (x - data->map.last_pos_x) * data->map.zoom + data->mlx.width / 2
		- data->player.coo.coo_x * ((double)data->map.zoom / 64.0);
	pos_y = (y - data->map.last_pos_y) * data->map.zoom + (data->mlx.height
			- MARGIN) / 2 - data->player.coo.coo_y * ((double)data->map.zoom
			/ 64.0);
	if (is_center_floo(data, pos_x, pos_y) == true)
	{
		dist_center = pow((pos_x + data->map.zoom / 2) - data->map.last_mouse_x,
				2) + pow((pos_y + data->map.zoom / 2) - data->map.last_mouse_y,
				2);
		if (small_dist == 0 || dist_center < small_dist)
		{
			data->map.pos_active_floo->x = x;
			data->map.pos_active_floo->y = y;
			small_dist = dist_center;
		}
	}
}

void	find_closest_floo(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	data->map.pos_active_floo->x = -1;
	data->map.pos_active_floo->y = -1;
	while (data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			if (data->map.tabmap[y][x] == 'F')
				calc_dist_center(data, x, y);
			++x;
		}
		++y;
	}
}

static void	print_map_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->mlx.height)
	{
		x = 0;
		while (x < data->mlx.width)
		{
			pixel_put(data, x, y, 0x6e583e);
			++x;
		}
		++y;
	}
}

static void	print_map_content(t_data *data, int x, int y)
{
	double	pos_x;
	double	pos_y;

	pos_x = (x - data->map.last_pos_x) * data->map.zoom + data->mlx.width / 2
		- data->player.coo.coo_x * ((double)data->map.zoom / 64.0);
	pos_y = (y - data->map.last_pos_y) * data->map.zoom + (data->mlx.height
			- MARGIN) / 2 - data->player.coo.coo_y * ((double)data->map.zoom
			/ 64.0);
	if (pos_x + data->map.zoom > 0 && pos_x < data->mlx.width && pos_y
		+ data->map.zoom > 0 && pos_y < data->mlx.height)
	{
		if (x == data->player.coo.case_x && y == data->player.coo.case_y)
			draw_player(data, pos_x, pos_y);
		if (data->status != MAP && x == data->map.pos_active_floo->x
			&& y == data->map.pos_active_floo->y)
			data->map.is_center = true;
		draw_texture(data, pos_x, pos_y, data->map.tabmap[y][x]);
		if (data->status != MAP && data->map.is_center == true)
		{
			data->map.is_center = false;
			data->map.floo_active = true;
		}
	}
}

void	display_floo_map(t_data *data)
{
	int	x;
	int	y;

	data->map.floo_active = false;
	print_map_background(data);
	if (data->status != MAP)
		find_closest_floo(data);
	y = 0;
	while (data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			print_map_content(data, x, y);
			++x;
		}
		++y;
	}
	if (data->map.last_pos_x != data->player.coo.case_x
		|| data->map.last_pos_y != data->player.coo.case_y)
		draw_cursor(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,
		0);
}
