/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_up_items.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:53:13 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:53:14 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	pick_wand(t_data *data, t_item *item)
{
	if (item->type == WOLF_WAND)
	{
		data->wand.wand_status[2] = true;
		data->wand.nb_wand = 2;
		data->sound = add_end_lst(create_sound(data, 28), data->sound,
				free_sound);
	}
	if (item->type == ELEM_WAND)
	{
		data->wand.wand_status[3] = true;
		data->wand.nb_wand = 3;
		data->sound = add_end_lst(create_sound(data, 28), data->sound,
				free_sound);
	}
}

static void	pick_up_wand(t_data *data, t_item *item)
{
	pick_wand(data, item);
	if (item->type == DEMENTOR_WAND)
	{
		data->wand.wand_status[4] = true;
		data->wand.nb_wand = 4;
		data->sound = add_end_lst(create_sound(data, 28), data->sound,
				free_sound);
	}
	if (item->type == SPIDER_WAND)
	{
		data->wand.wand_status[1] = true;
		data->wand.nb_wand = 1;
		data->sound = add_end_lst(create_sound(data, 28), data->sound,
				free_sound);
	}
}

void	pick_up_items(t_data *data, t_item *item, t_lst **lst)
{
	t_lst	*next;

	if (item->type == POPO_HEAL && item->categ)
		data->popo[0].nb++;
	if (item->type == POPO_SHIELD && item->categ)
		data->popo[1].nb++;
	if (item->type == POPO_FLOO && item->categ)
		data->popo[2].nb++;
	if (item->type == POPO_INVI && item->categ)
		data->popo[3].nb++;
	if (item->type == PORTKEY && item->categ)
	{
		data->status = MENU_END;
		get_ranking_xp(data);
	}
	pick_up_wand(data, item);
	apply_damage(&data->player.damage, &item->damage);
	next = (*lst)->next;
	data->item = remove_elem_lst(*lst);
	f_elem_lst(*lst);
	*lst = next;
}

bool	is_skip_type(t_item *item, t_data *data)
{
	if (((item->type == CONFUNDO || item->type == VENTUS
				|| item->type == EXPECTO_PATRONUM || item->type == REPULSO)
			&& !item->categ) || (item->nb_move <= 5
			&& item->damage.which_coa_do == data->player.coa))
		return (true);
	return (false);
}
