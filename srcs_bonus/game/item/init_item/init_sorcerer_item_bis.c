/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sorcerer_item_bis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:49:03 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:49:04 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_tig(t_data *data)
{
	data->items[TIG].categ = ITEM;
	data->items[TIG].type = TIG;
	data->items[TIG].damage.damage_do = 25;
	data->items[TIG].damage.curse_force_do = .1;
	data->items[TIG].damage.curse_frame_do = 120;
	data->items[TIG].damage.slow_force_do = 35;
	data->items[TIG].damage.slow_frame_do = 120;
	data->items[TIG].damage.repulso_force_do = 2;
	data->items[TIG].damage.repulso_frame_do = 5;
	data->items[TIG].speed = 20;
	data->items[TIG].radius = 5;
	data->items[TIG].front_img = &data->img[TIG_IMG];
	data->items[TIG].back_img = &data->img[TIG_IMG];
}

void	init_mac(t_data *data)
{
	data->items[MAC].categ = ITEM;
	data->items[MAC].type = MAC;
	data->items[MAC].damage.damage_do = 25;
	data->items[MAC].damage.curse_force_do = .1;
	data->items[MAC].damage.curse_frame_do = 120;
	data->items[MAC].damage.slow_force_do = 35;
	data->items[MAC].damage.slow_frame_do = 120;
	data->items[MAC].damage.repulso_force_do = 2;
	data->items[MAC].damage.repulso_frame_do = 5;
	data->items[MAC].speed = 20;
	data->items[MAC].radius = 3;
	data->items[MAC].front_img = &data->img[MAC_IMG];
	data->items[MAC].back_img = &data->img[MAC_IMG];
}

void	init_bh(t_data *data)
{
	data->items[BH].categ = ITEM;
	data->items[BH].type = BH;
	data->items[BH].damage.damage_do = .5;
	data->items[BH].damage.curse_force_do = .05;
	data->items[BH].damage.curse_frame_do = 120;
	data->items[BH].damage.repulso_force_do = -6.0;
	data->items[BH].damage.repulso_frame_do = 1;
	data->items[BH].speed = 6;
	data->items[BH].radius = 5;
}

void	init_pizza(t_data *data)
{
	data->items[PIZZA].categ = ITEM;
	data->items[PIZZA].type = PIZZA;
	data->items[PIZZA].damage.damage_do = 25;
	data->items[PIZZA].damage.curse_force_do = .1;
	data->items[PIZZA].damage.curse_frame_do = 120;
	data->items[PIZZA].damage.slow_force_do = 35;
	data->items[PIZZA].damage.slow_frame_do = 120;
	data->items[PIZZA].damage.repulso_force_do = 2;
	data->items[PIZZA].damage.repulso_frame_do = 5;
	data->items[PIZZA].speed = 20;
	data->items[PIZZA].radius = 8;
	data->items[PIZZA].front_img = &data->img[PIZZA_IMG];
	data->items[PIZZA].back_img = &data->img[PIZZA_IMG];
}
