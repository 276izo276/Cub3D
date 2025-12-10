/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:52:04 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:52:05 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "color_bonus.h"
#include "utils_bonus.h"

void	popo_back_color(t_data *data)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	while (i < 4)
	{
		x = data->mlx.width - 350 + 64 * i + 13 * (i);
		while (x < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
		{
			set_back_color(data, &y, x, i);
			x++;
		}
		i++;
	}
}

void	popo_img(t_data *data, double *y, double *x, int i)
{
	t_aff	aff;

	while (*y < data->mlx.height - 115 - 64)
	{
		aff.a = ((unsigned int)((*y - (data->mlx.height - 115 - 128)) / 64
					* data->popo[i].img->height))
			* data->popo[i].img->size_line;
		aff.b = ((unsigned int)((*x - (data->mlx.width - 350 + 64 * i + 13
							* (i))) / 64 * data->popo[i].img->width))
			* (data->popo[i].img->bits_per_pixel >> 3);
		aff.color = *(unsigned int *)(data->popo[i].img->data_addr + aff.a
				+ aff.b);
		if (aff.color != WHITE && border_case_spell(*x, *y, 32 + data->mlx.width
				- 350 + 64 * i + 13 * (i), 32 + data->mlx.height - 105 - 128))
		{
			if (i == 3)
				if (cond_back_color(data, *x, *y, i))
					aff.color = darken_the_color(aff.color);
			*(unsigned int *)(data->screen->data_addr + ((int)(*y - MARGIN))
					* data->screen->size_line + ((int)(*x))
					* (data->screen->bits_per_pixel / 8)) = aff.color;
		}
		(*y)++;
	}
	(*x)++;
}

void	aff_popo(t_data *data)
{
	double	x;
	double	y;
	int		i;
	char	*str;

	popo_back_color(data);
	i = 0;
	while (i < 4)
	{
		x = data->mlx.width - 350 + 64 * i + 13 * (i);
		while (x < data->mlx.width - 350 + 64 * (i + 1) + 13 * (i))
		{
			y = data->mlx.height - 115 - 128;
			popo_img(data, &y, &x, i);
		}
		str = ft_itoa(data->popo[i].nb);
		aff_text(str, 25, (t_coo){.y = data->mlx.height - 115 - 80,
			.x = calc_start_text(str, 10 + data->mlx.width - 350 + 64 * i + 13
				* (i), data, 25)}, data);
		aff_text(data->popo[i].key, 25, (t_coo){.y = data->mlx.height - 115
			- 80, .x = calc_start_text(data->popo[i].key, 50 + data->mlx.width
				- 350 + 64 * i + 13 * (i), data, 25)}, data);
		free(str);
		i++;
	}
}
