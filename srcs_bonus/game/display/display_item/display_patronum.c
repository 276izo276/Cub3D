#include "cub3d_bonus.h"
#include <math.h>

static void	get_patronum_color(t_data *data, int i, double dist, double factor)
{
	int				r;
	int				g;
	int				b;
	unsigned int	color;

	color = *(unsigned int *)(data->screen->data_addr + (data->ray[i].pix_y
				* data->screen->size_line) + (data->ray[i].pix_x
				* data->ray[i].calc_bits));
	b = (color & 255);
	b = (int)(b + (255 - b) * ((1 - dist * factor)));
	if (b > 255)
		b = 255;
	g = (color >> 8 & 255);
	g = (int)(g + (255 - g) * ((1 - dist * factor)));
	if (g > 255)
		g = 255;
	r = (color >> 16 & 255);
	r = (int)(r + (255 - r) * ((1 - dist * factor)));
	if (r > 255)
		r = 255;
	color = (r << 16) + (g << 8) + b;
	*(unsigned int *)(data->screen->data_addr + (data->ray[i].pix_y
				* data->screen->size_line) + (data->ray[i].pix_x
				* data->ray[i].calc_bits)) = color;
}

static void	calc_patronum_dist(t_data *data, int i, int j, double *dist)
{
	double	rap_y;

	rap_y = (data->ray[i].pix_y - data->mlx.height / 2)
		/ ((data->ray[i].items[j]->hbot - data->ray[i].items[j]->htop) / 2);
	*dist = sqrt((data->ray[i].items[j]->posx - 0.5)
			* (data->ray[i].items[j]->posx - 0.5) + rap_y * rap_y);
}

void	display_patronum(t_data *data, int i, int j)
{
	double	dist;

	data->ray[i].items[j]->htop = data->mlx.height / 2 - (2
			* data->ray[i].items[j]->item->radius) * data->ray[i].d_proj
		/ data->ray[i].items[j]->dist;
	data->ray[i].pix_y = data->ray[i].items[j]->htop;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	if (data->ray[i].pix_y < round(data->ray[i].max_height
			- data->ray[i].items[j]->max_size))
		data->ray[i].pix_y = round(data->ray[i].max_height
				- data->ray[i].items[j]->max_size);
	data->ray[i].items[j]->hbot = data->mlx.height / 2 + (2
			* data->ray[i].items[j]->item->radius) * data->ray[i].d_proj
		/ data->ray[i].items[j]->dist;
	while (data->ray[i].pix_y < data->ray[i].items[j]->hbot
		&& data->ray[i].pix_y < data->mlx.height
		&& data->ray[i].pix_y < round(data->ray[i].max_height
			+ data->ray[i].items[j]->max_size))
	{
		calc_patronum_dist(data, i, j, &dist);
		if (dist < .5)
			get_patronum_color(data, i, dist, 2);
		data->ray[i].pix_y++;
	}
}
