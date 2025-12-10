/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:58:21 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:58:22 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "struct_bonus.h"

int	calc_start_text(char *str, int x, t_data *data, int height)
{
	int		i;
	t_img	*img;
	int		size;

	i = 0;
	img = NULL;
	size = 0;
	while (str && str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			img = &data->img[str[i] - 'a' + CHAR_A];
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			img = &data->img[str[i] - 'A' + CHAR_A];
		}
		else if (str[i] >= '0' && str[i] <= '9')
			img = &data->img[str[i] - '0' + NB_0];
		else
			img = &data->img[0];
		size += (double)(((double)img->width / (double)img->height) * height);
		i++;
	}
	return (x - size / 2);
}

static void	get_right_text_img(t_data *data, t_img **img, char *str, int i)
{
	if (str[i] >= 'a' && str[i] <= 'z')
		*img = &data->img[str[i] - 'a' + CHAR_A];
	else if (str[i] >= 'A' && str[i] <= 'Z')
		*img = &data->img[str[i] - 'A' + CHAR_A];
	else if (str[i] >= '0' && str[i] <= '9')
		*img = &data->img[str[i] - '0' + NB_0];
	else
		*img = &data->img[0];
}

static void	print_text_pixel(t_data *data, int height, t_img *img, t_coo coo)
{
	while (data->aff.cur.y < data->aff.new.y
		&& data->aff.cur.y < data->mlx.height)
	{
		data->aff.cur.x = coo.x;
		if (data->aff.cur.x < 0)
			data->aff.cur.x = 0;
		while (data->aff.cur.x < data->aff.new.x
			&& data->aff.cur.x < data->mlx.width)
		{
			data->aff.a = (unsigned int)((double)(((double)(data->aff.cur.y
								- coo.y) / (double)height) * img->height));
			data->aff.b = (unsigned int)((double)(((double)(data->aff.cur.x
								- coo.x) / (double)(data->aff.new.x - coo.x))
						* img->width));
			data->aff.color = *(unsigned int *)(img->data_addr + data->aff.a
					* img->size_line + data->aff.b
					* (img->bits_per_pixel >> 3));
			if (data->aff.color != RED)
				*(unsigned int *)(data->screen->data_addr + (data->aff.cur.y
					- MARGIN) * data->screen->size_line + data->aff.cur.x
					* (data->screen->bits_per_pixel >> 3)) = data->aff.color;
			data->aff.cur.x++;
		}
		data->aff.cur.y++;
	}
}

void	aff_text(char *str, int height, t_coo coo, t_data *data)
{
	int		i;
	t_img	*img;

	if (coo.y <= MARGIN)
		coo.y = MARGIN;
	data->aff.new.y = coo.y + height;
	i = 0;
	img = NULL;
	while (str && str[i])
	{
		get_right_text_img(data, &img, str, i);
		data->aff.cur.y = coo.y;
		data->aff.new.x = coo.x + (double)(((double)img->width
					/ (double)img->height) * height);
		print_text_pixel(data, height, img, coo);
		coo.x = coo.x + (double)(((double)img->width / (double)img->height)
				* height);
		i++;
	}
}
