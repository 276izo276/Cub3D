/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_hand_selection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:49:51 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:49:52 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include <color_bonus.h>
#include <math.h>

void	apply_transparancy(t_data *data, int x, int y, unsigned int color)
{
	if (x >= 0 && x < data->mlx.width && y >= 0 && y < data->mlx.height)
	{
		data->aff.tmp_addr = data->screen->data_addr + (y
				* data->screen->size_line + x * (data->screen->bits_per_pixel
					/ 8));
		data->aff.old_color = *(unsigned int *)data->aff.tmp_addr;
		data->aff.r_old = (data->aff.old_color >> 16) & 255;
		data->aff.g_old = (data->aff.old_color >> 8) & 255;
		data->aff.b_old = data->aff.old_color & 255;
		data->aff.a_new = (color >> 24) & 255;
		data->aff.r_new = (color >> 16) & 255;
		data->aff.g_new = (color >> 8) & 255;
		data->aff.b_new = color & 255;
		data->aff.r_new = (int)((1 - (data->aff.a_new / 255.0))
				* data->aff.r_old + (data->aff.a_new / 255.0)
				* data->aff.r_new);
		data->aff.g_new = (int)((1 - (data->aff.a_new / 255.0))
				* data->aff.g_old + (data->aff.a_new / 255.0)
				* data->aff.g_new);
		data->aff.b_new = (int)((1 - (data->aff.a_new / 255.0))
				* data->aff.b_old + (data->aff.a_new / 255.0)
				* data->aff.b_new);
		*(unsigned int *)data->aff.tmp_addr = (data->aff.r_new << 16)
			+ (data->aff.g_new << 8) + data->aff.b_new;
	}
}

void	draw_gradient(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				x;
	int				y;
	double			distance;

	y = -40;
	color = data->player.color;
	while (y < 40)
	{
		x = -40;
		while (x < 40)
		{
			distance = sqrt(y * y + x * x);
			if (distance < 40)
			{
				color = get_right_color(data->player.color, distance);
				apply_transparancy(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

static void	aff_hand_selection(t_data *data, int *start_x, int start_y)
{
	unsigned int	color;
	int				y;
	int				x;

	y = -1;
	while (++y < data->img[LEFT_SELECT].height && y <= data->mlx.height)
	{
		x = -1;
		while (++x < data->img[LEFT_SELECT].width && x <= data->mlx.width)
		{
			if (data->selected == 1)
			{
				color = get_texture_pixel(&data->img[LEFT_SELECT], x, y);
				*start_x = data->mlx.width / 2 - 124;
			}
			else
			{
				color = get_texture_pixel(&data->img[LEFT_SELECT], x, y);
				*start_x = 225;
			}
			if (color != WHITE)
				pixel_put(data, x + *start_x, y + start_y, color);
		}
	}
}

void	select_your_hand(t_data *data)
{
	int				start_x;
	int				start_y;

	start_x = 0;
	start_y = data->mlx.height - 412;
	draw_texture_menu(data, &data->img[SELECT_HAND], 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,
		0);
	aff_hand_selection(data, &start_x, start_y);
	if (data->selected == 1)
	{
		start_x += 355;
		start_y += 150;
	}
	else
	{
		start_x += data->img[LEFT_SELECT].width - 130;
		start_y += 150;
	}
	draw_gradient(data, start_x, start_y);
}
