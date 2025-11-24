#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "texture_bonus.h"

static void	pick_up_wand(t_data *data, t_item *item)
{
	if (item->type == WOLF_WAND)
	{
		data->wand.wand_status[2] = true;
		data->wand.nb_wand = 2;
	}
	if (item->type == ELEM_WAND)
	{
		data->wand.wand_status[3] = true;
		data->wand.nb_wand = 3;
	}
	if (item->type == DEMENTOR_WAND)
	{
		data->wand.wand_status[4] = true;
		data->wand.nb_wand = 4;
	}
	if (item->type == SPIDER_WAND)
	{
		data->wand.wand_status[1] = true;
		data->wand.nb_wand = 1;
	}
}

void	pick_up_items(t_data *data, t_item *item, t_lst **lst)
{
	t_lst	*next;

	if (item->type == POPO_HEAL)
		data->popo[0].nb ++;
	if (item->type == POPO_SHIELD)
		data->popo[1].nb ++;
	if (item->type == POPO_FLOO)
		data->popo[2].nb ++;
	if (item->type == POPO_INVI)
		data->popo[3].nb++;
	if (item->type == PORTKEY)
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
