/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_spell_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:49:40 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:49:41 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <color_bonus.h>

void	display_name(t_data *data, int i, int pos_x)
{
	unsigned int	color;
	int				x;
	int				y;

	if (i % 8 == 0 && i != 0)
		data->spell_menu.name_pos_y += 110;
	else if (i == 20)
		data->spell_menu.name_pos_y += 35;
	y = -1;
	if (!data->spell[i].icn_name)
		return ;
	while (++y < data->spell[i].icn_name->height)
	{
		x = -1;
		while (++x < data->spell[i].icn_name->width)
		{
			color = get_texture_pixel(data->spell[i].icn_name, x, y);
			if (color != YELLOW)
			{
				color = darken_the_color(color);
				pixel_put(data, x + pos_x, y + data->spell_menu.name_pos_y,
					color);
			}
		}
	}
}

static unsigned int	display_icn(t_data *data, double x, double y, int i)
{
	unsigned int	color;

	data->aff.a = ((unsigned int)((y - data->aff.y_max) / 64
				* data->spell[i].icn->height)) * data->spell[i].icn->size_line;
	data->aff.b = ((unsigned int)((x - data->aff.x_max) / 64
				* data->spell[i].icn->width))
		* (data->spell[i].icn->bits_per_pixel >> 3);
	color = *(unsigned int *)(data->spell[i].icn->data_addr + data->aff.a
			+ data->aff.b);
	return (color);
}

static void	print_spell_lock(t_data *data, int i, double x, double y)
{
	unsigned int	color;

	color = 0;
	if (data->spell[i].necessary_lvl > data->player.xp)
	{
		data->aff.a = ((unsigned int)((y - data->aff.y_max) / 64
					* data->img[SPELL_LOCK].height))
			* data->img[SPELL_LOCK].size_line;
		data->aff.b = ((unsigned int)((x - data->aff.x_max) / 64
					* data->img[SPELL_LOCK].width))
			* (data->img[SPELL_LOCK].bits_per_pixel >> 3);
		color = *(unsigned int *)(data->img[SPELL_LOCK].data_addr + data->aff.a
				+ data->aff.b);
		if (color != YELLOW)
		{
			if (data->spell_menu.selected != i)
				color = darken_the_color(color);
			*(unsigned int *)(data->screen->data_addr + (int)((y - MARGIN)
						* data->screen->size_line) + (int)((x)
						* (data->screen->bits_per_pixel / 8))) = color;
		}
	}
}

static void	aff_spell_loop(t_data *data, double x, int offset, int i)
{
	unsigned int	color;
	double			y;

	while (x < offset + 64 * (i % 8 + 1) + 71 * (i % 8))
	{
		y = data->aff.y_max;
		while (y < data->aff.y_max + 64)
		{
			if (data->spell[i].icn)
				color = display_icn(data, x, y, i);
			if (border_case_spell(x, y, 32 + data->aff.x_max, 32
					+ data->aff.y_max))
			{
				if (data->spell_menu.selected != i)
					color = darken_the_color(color);
				*(unsigned int *)(data->screen->data_addr + (int)((y - MARGIN)
							* data->screen->size_line) + (int)((x)
							* (data->screen->bits_per_pixel / 8))) = color;
			}
			print_spell_lock(data, i, x, y);
			y++;
		}
		x++;
	}
}

void	display_spell_list(t_data *data)
{
	double	x;
	int		i;

	data->spell_menu.name_pos_y = 570;
	data->aff.y_max = 660;
	i = 0;
	while (i < 20)
	{
		x = 440 + 64 * (i % 8) + 71 * (i % 8);
		data->aff.x_max = (440 + 64 * (i % 8) + 71 * (i % 8));
		aff_spell_loop(data, x, 440, i);
		display_name(data, i, 410 + 64 * (i % 8) + 72 * (i % 8));
		i++;
		if (i % 8 == 0)
			data->aff.y_max += 120;
	}
	data->aff.y_max += 30;
	while (i < 22)
	{
		x = 600 + 64 * (i % 8) + 71 * (i % 8);
		data->aff.x_max = 600 + 64 * (i % 8) + 71 * (i % 8);
		aff_spell_loop(data, x, 600, i);
		display_name(data, i, 560 + 64 * (i % 8) + 72 * (i % 8));
		i++;
	}
}
