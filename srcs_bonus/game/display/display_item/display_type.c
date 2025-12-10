/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:46:51 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:46:52 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	display_door(t_data *data, int i, int j)
{
	data->ray[i].items[j]->texture = &data->img[DOOR_MOVE];
	define_posx_texture(data, i, j);
	data->ray[i].img_addr = data->screen->data_addr + data->ray[i].pix_x
		* data->ray[i].calc_bits;
	data->ray[i].items[j]->texture_coo.x = data->ray[i].items[j]->texture_coo.x
		* (data->ray[i].items[j]->texture->bits_per_pixel >> 3);
	data->ray[i].pix_y = data->ray[i].items[j]->htop;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	data->ray[i].items[j]->dist_height = data->ray[i].items[j]->hbot
		- data->ray[i].items[j]->htop;
	while (data->ray[i].pix_y < data->ray[i].items[j]->hbot
		&& data->ray[i].pix_y < data->mlx.height)
	{
		if (data->ray[i].pix_y > data->ray[i].items[j]->htop
			+ data->ray[i].items[j]->dist_height * .15)
			put_text_pix_img_item(data, i, j, 0);
		data->ray[i].pix_y++;
	}
}

void	display_others(t_data *data, int i, int j)
{
	set_texture(data, i, j);
	define_posx_texture(data, i, j);
	data->ray[i].img_addr = data->screen->data_addr + data->ray[i].pix_x
		* data->ray[i].calc_bits;
	data->ray[i].items[j]->texture_coo.x = data->ray[i].items[j]->texture_coo.x
		* (data->ray[i].items[j]->texture->bits_per_pixel >> 3);
	data->ray[i].pix_y = data->ray[i].items[j]->htop;
	if (data->ray[i].pix_y < 0)
		data->ray[i].pix_y = 0;
	data->ray[i].items[j]->dist_height = data->ray[i].items[j]->hbot
		- data->ray[i].items[j]->htop;
	while (data->ray[i].pix_y < data->ray[i].items[j]->hbot
		&& data->ray[i].pix_y < data->mlx.height)
	{
		put_text_pix_img_item(data, i, j, 1);
		data->ray[i].pix_y++;
	}
}
