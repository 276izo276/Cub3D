/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:53:28 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:53:29 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils_bonus.h"

void	init_struct_item(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->mlx.width)
	{
		data->ray[i].items = malloc(sizeof(t_hit_item *) * (1 + MAX_CREATE_ITEM
					+ MAX_CREATE_ENEMY + data->nb_door + data->map.nb_floo));
		if (!data->ray[i].items)
			f_exit(data, 1);
		ft_bzero(data->ray[i].items, sizeof(t_hit_item *) * (1 + MAX_CREATE_ITEM
				+ MAX_CREATE_ENEMY + data->nb_door + data->map.nb_floo));
		j = 0;
		while (j <= MAX_CREATE_ENEMY + MAX_CREATE_ITEM + data->nb_door
			+ data->map.nb_floo)
		{
			data->ray[i].items[j] = malloc(sizeof(t_hit_item));
			if (!data->ray[i].items[j])
				f_exit(data, 1);
			ft_bzero(data->ray[i].items[j], sizeof(t_hit_item));
			j++;
		}
		++i;
	}
}

void	init_foot_tab(t_data *data)
{
	int	i;

	i = 0;
	data->map.mini.foot_tab[0].coo.case_x = data->player.coo.case_x;
	data->map.mini.foot_tab[0].coo.case_y = data->player.coo.case_y;
	data->map.mini.foot_tab[0].coo.coo_y = data->player.coo.coo_y;
	data->map.mini.foot_tab[0].coo.coo_x = data->player.coo.coo_x;
	data->map.mini.foot_tab[0].is_left = true;
	data->map.mini.foot_tab[0].is_save = true;
	data->map.mini.foot_tab[0].rad = 0;
	data->map.mini.foot_tab[0].foot_x = -1;
	data->map.mini.foot_tab[0].foot_y = -1;
	while (++i < 8)
	{
		data->map.mini.foot_tab[i].is_save = false;
		data->map.mini.foot_tab[i].coo.case_x = 0;
		data->map.mini.foot_tab[i].coo.case_y = 0;
		data->map.mini.foot_tab[i].coo.coo_y = 0;
		data->map.mini.foot_tab[i].coo.coo_x = 0;
		data->map.mini.foot_tab[i].rad = 0;
		data->map.mini.foot_tab[i].is_left = true;
		data->map.mini.foot_tab[i].foot_x = -1;
		data->map.mini.foot_tab[i].foot_y = -1;
	}
	data->map.mini.time_foot = 0;
}
