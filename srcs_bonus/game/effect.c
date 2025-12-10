/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:51:44 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:51:45 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "color_bonus.h"

void	aff_img_effect_info(t_img *img, int nb_effect, t_data *data)
{
	double			x;
	double			y;
	unsigned int	a;
	unsigned int	b;
	unsigned int	color;

	x = data->mlx.width - 370 - (nb_effect * 20) - 30;
	while (x < data->mlx.width - 370 - (nb_effect * 20) - 10)
	{
		y = data->mlx.height - 35 - 1;
		while (++y < data->mlx.height - 15)
		{
			a = ((unsigned int)((y - (data->mlx.height - 35)) / 20
						* img->height)) * img->size_line;
			b = ((unsigned int)((x - (data->mlx.width - 370 - (nb_effect * 20)
								- 30)) / 20 * img->width))
				* (img->bits_per_pixel >> 3);
			color = *(unsigned int *)(img->data_addr + a + b);
			if (color != WHITE)
				*(unsigned int *)(data->screen->data_addr + ((int)(y - MARGIN))
						* data->screen->size_line + ((int)(x))
						* (data->screen->bits_per_pixel / 8)) = color;
		}
		x++;
	}
}

void	aff_effect_info_utils(t_data *data, int nb_effect)
{
	if (data->player.damage.curse_force_take > 0)
	{
		aff_img_effect_info(&data->img[CURSE], nb_effect, data);
		nb_effect++;
	}
	if (data->player.episkey_heal > 0)
	{
		aff_img_effect_info(&data->img[EPISKEY_ICN], nb_effect, data);
		nb_effect++;
	}
	if (data->player.vul_sanen_heal > 0)
	{
		aff_img_effect_info(&data->img[HEART], nb_effect, data);
		nb_effect++;
	}
}

void	aff_effect_info(t_data *data)
{
	int	nb_effect;

	nb_effect = 0;
	if (data->player.damage.fire_force_take > 0)
	{
		aff_img_effect_info(&data->img[FLAME], nb_effect, data);
		nb_effect++;
	}
	if (data->player.damage.poison_force_take > 0)
	{
		aff_img_effect_info(&data->img[POISON], nb_effect, data);
		nb_effect++;
	}
	if (data->player.damage.slow_force_take > 0)
	{
		aff_img_effect_info(&data->img[SLOW], nb_effect, data);
		nb_effect++;
	}
	aff_effect_info_utils(data, nb_effect);
}
