/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:45:44 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:45:45 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "texture.h"
#include "time.h"
#include "utils.h"
#include <math.h>

static void	fill_need_print(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < SIZE_MAP)
	{
		x = 0;
		while (x < SIZE_MAP)
		{
			if (sqrt(pow(y - SIZE_MAP / 2, 2) + pow(x - SIZE_MAP / 2,
						2)) > SIZE_MAP / 2)
				data->map.mini.need_print[y][x] = 0;
			else
				data->map.mini.need_print[y][x] = 1;
			x++;
		}
		y++;
	}
}

static void	init_ray(t_data *data)
{
	double	fov;
	int		i;

	i = 0;
	fov = data->mlx.height / 2 * tan((45 * (M_PI / 180)));
	data->ray = malloc(sizeof(t_ray) * data->mlx.width);
	if (data->ray == NULL)
		f_exit(data, 1);
	ft_bzero(data->ray, sizeof(t_ray) * data->mlx.width);
	if (data->mlx.height < data->mlx.width)
		fov *= (data->mlx.width / data->mlx.height);
	else
		fov /= (data->mlx.height / data->mlx.width) * 0.75;
	while (i < data->mlx.width)
	{
		data->ray[i].d_proj = fov;
		data->ray[i].pix_y = data->mlx.height >> 1;
		data->ray[i].max_height = data->mlx.height >> 1;
		++i;
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->time_fps = get_mtime();
	data->time_move = get_mtime();
	fill_need_print(data);
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		f_exit(data, 1);
	data->mlx.height = 1000;
	data->mlx.width = 1000;
	init_utils_mini(data);
	init_ray(data);
	data->screen = malloc(sizeof(t_img));
	if (!data->screen)
		f_exit(data, 1);
	data->screen->img = mlx_new_image(data->mlx.mlx, data->mlx.width,
			data->mlx.height);
	data->screen->data_addr = mlx_get_data_addr(data->screen->img,
			&data->screen->bits_per_pixel, &data->screen->size_line,
			&data->screen->endian);
	data->screen->width = data->mlx.width;
	data->screen->height = data->mlx.height;
	data->ac = ac;
	data->av = av;
}
