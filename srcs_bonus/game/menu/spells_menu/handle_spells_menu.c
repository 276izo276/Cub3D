/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spells_menu.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:49:48 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:49:49 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include <math.h>

static int	calc_dist_top(t_data *data, double ray, double x, double y)
{
	if (x < data->aff.x_max - (64 - ray))
	{
		data->aff.dist_x = abs_value(data->aff.x_max - (64 - ray) - x);
		data->aff.dist_y = abs_value(data->aff.y_max - (64 - ray) - y);
	}
	else if (x > data->aff.x_max + (64 - ray))
	{
		data->aff.dist_x = abs_value(data->aff.x_max + (64 - ray) - x);
		data->aff.dist_y = abs_value(data->aff.y_max - (64 - ray) - y);
	}
	else
		return (1);
	return (0);
}

static int	calc_dist_bot(t_data *data, double ray, double x, double y)
{
	if (x < data->aff.x_max - (64 - ray))
	{
		data->aff.dist_x = abs_value(data->aff.x_max - (64 - ray) - x);
		data->aff.dist_y = abs_value(data->aff.y_max + (64 - ray) - y);
	}
	else if (x > data->aff.x_max + (64 - ray))
	{
		data->aff.dist_x = abs_value(data->aff.x_max + (64 - ray) - x);
		data->aff.dist_y = abs_value(data->aff.y_max + (64 - ray) - y);
	}
	else
		return (1);
	return (0);
}

int	menu_border_case_spell(t_data *data, double x, double y)
{
	double	ray;

	ray = 10;
	if (y < data->aff.y_max - (64 - ray))
	{
		if (calc_dist_top(data, ray, x, y) == 1)
			return (1);
	}
	else if (y > data->aff.y_max + (64 - ray))
	{
		if (calc_dist_bot(data, ray, x, y) == 1)
			return (1);
	}
	else
		return (1);
	if (sqrt(data->aff.dist_x * data->aff.dist_x + data->aff.dist_y
			* data->aff.dist_y) > ray)
		return (0);
	return (1);
}

void	update_spell_cooldown(t_data *data)
{
	int	i;

	i = 0;
	data->spell_menu.end_time = get_mtime() - data->spell_menu.start_time;
	while (i < 4)
	{
		data->spell[data->spell_take[i]].end_time += data->spell_menu.end_time;
		++i;
	}
}

void	handle_spells_menu(t_data *data)
{
	display_menu_background(data, &data->img[SPELL_BACKGROUND], 384, 57);
	display_spell_take(data);
	display_spell_list(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img, 0,
		0);
}
