#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <stdlib.h>

void	spawn_spider_wand(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (data->wand.is_drop[1] != true && rand()
		% 100 <= enemy->drop_spider_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, SPIDER_WAND,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[1] = true;
	}
}

void	spawn_dementor_wand(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (data->wand.is_drop[4] != true && rand()
		% 100 <= enemy->drop_dementor_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, DEMENTOR_WAND,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[4] = true;
	}
}

void	spawn_elem_wand(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (data->wand.is_drop[3] != true && rand() % 100 <= enemy->drop_elem_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, ELEM_WAND,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[3] = true;
	}
}

void	spawn_wolf_wand(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (data->wand.is_drop[2] != true && rand() % 100 <= enemy->drop_wolf_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, WOLF_WAND,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[2] = true;
		data->wand.is_drop[2] = true;
	}
}

