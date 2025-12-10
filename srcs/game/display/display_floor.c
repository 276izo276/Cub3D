/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:44:45 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:44:46 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <math.h>

static void	put_text_pix_img(t_data *data, t_display *display, int x, int y)
{
	display->pixel_addr = data->screen->data_addr + (y * data->screen->size_line
			+ x * display->screen_bbp_frac);
	*(unsigned int *)display->pixel_addr = (data->map.floor->r << 16)
		+ (data->map.floor->g << 8) + data->map.floor->b;
}

void	display_floor(t_data *data, t_display display)
{
	int	x;
	int	y;

	display.screen_bbp_frac = data->screen->bits_per_pixel >> 3;
	y = (data->screen->height >> 2) + 1;
	while (y < data->screen->height)
	{
		x = 0;
		while (x < data->mlx.width)
		{
			put_text_pix_img(data, &display, x, y);
			++x;
		}
		++y;
	}
}
