/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_spell_take.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:49:43 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:49:44 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include <color_bonus.h>

static unsigned int	display_icn_take(t_data *data, double x, double y, int i)
{
	unsigned int	color;

	data->aff.a = ((unsigned int)((y - 460) / 128
				* data->spell[data->spell_take[i]].icn->height))
		* data->spell[data->spell_take[i]].icn->size_line;
	data->aff.b = ((unsigned int)((x - (634 + 128 * i + 40 * (i))) / 128
				* data->spell[data->spell_take[i]].icn->width))
		* (data->spell[data->spell_take[i]].icn->bits_per_pixel >> 3);
	color = *(unsigned int *)(data->spell[data->spell_take[i]].icn->data_addr
			+ data->aff.a + data->aff.b);
	return (color);
}

static void	print_spell_lock_take(t_data *data, int i, double x, double y)
{
	unsigned int	color;

	if (data->spell[data->spell_take[i]].necessary_lvl > data->player.xp)
	{
		data->aff.a = ((unsigned int)((y - 460) / 128
					* data->img[SPELL_LOCK].height))
			* data->img[SPELL_LOCK].size_line;
		data->aff.b = ((unsigned int)((x - (634 + 128 * i + 40 * (i))) / 128
					* data->img[SPELL_LOCK].width))
			* (data->img[SPELL_LOCK].bits_per_pixel >> 3);
		color = *(unsigned int *)(data->img[SPELL_LOCK].data_addr + data->aff.a
				+ data->aff.b);
		if (color != YELLOW)
		{
			if (data->selected != i)
				color = darken_the_color(color);
			*(unsigned int *)(data->screen->data_addr + (int)((y - MARGIN)
						* data->screen->size_line) + (int)((x)
						* (data->screen->bits_per_pixel / 8))) = color;
		}
	}
}

static void	aff_spell_take_loop(t_data *data, double x, int i)
{
	unsigned int	color;
	double			y;

	data->aff.x_max = 64 + 634 + 128 * i + 40 * (i);
	data->aff.y_max = 64 + 460;
	while (x < 634 + 128 * (i + 1) + 40 * (i))
	{
		y = 460;
		while (y < 460 + 128)
		{
			color = display_icn_take(data, x, y, i);
			if (menu_border_case_spell(data, x, y))
			{
				if (data->selected != i)
					color = darken_the_color(color);
				*(unsigned int *)(data->screen->data_addr + (int)((y - MARGIN)
							* data->screen->size_line) + (int)((x)
							* (data->screen->bits_per_pixel / 8))) = color;
			}
			print_spell_lock_take(data, i, x, y);
			y++;
		}
		x++;
	}
}

void	display_spell_take(t_data *data)
{
	double			x;
	int				i;
	long long int	cur_time;
	char			*str;

	i = 0;
	while (i < 4)
	{
		x = 634 + 128 * i + 40 * (i);
		aff_spell_take_loop(data, x, i);
		cur_time = get_mtime();
		if (cur_time < data->spell[data->spell_take[i]].end_time + (cur_time
				- data->spell_menu.start_time)
			+ data->spell[data->spell_take[i]].base_cooldown * 1000)
		{
			str = ft_itoa(((data->spell[data->spell_take[i]].end_time
							+ (cur_time - data->spell_menu.start_time)
							+ data->spell[data->spell_take[i]].base_cooldown
							* 1000) - cur_time) / 1000 + 1);
			aff_text(str, 64, (t_coo){.x = calc_start_text(str, ((634 + 128 * i
							+ 40 * (i)) + 64), data, 64), .y = 460 + 32}, data);
			free(str);
		}
		i++;
	}
}
