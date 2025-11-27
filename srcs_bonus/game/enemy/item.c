#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <stdlib.h>
#include "enemy_bonus.h"

void	spawn_heal(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (rand() % 100 <= enemy->drop_heal)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, HEAL_POPO,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y, .coo_x = new_x,
					.coo_y = new_y}, new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
	}
}

void	spawn_floo(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (rand() % 100 <= enemy->drop_floo)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, FLOO_POPO,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
	}
}

void	spawn_shield(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (rand() % 100 <= enemy->drop_shield)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, SHIELD_POPO,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
	}
}

void	spawn_cloak(t_enemy *enemy, t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (rand() % 100 <= enemy->drop_cloak)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		set_valid_spawn(&new_x, &new_y);
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, INVI_POPO,
					&(t_fcoo){.case_x = enemy->center.case_x,
					.case_y = enemy->center.case_y,
					.coo_x = enemy->center.coo_x, .coo_y = enemy->center.coo_y},
					new_deg), data->item, f_item);
		make_move_item(data->item->dt, 5);
	}
}

void	spawn_item(t_data *data, t_enemy *enemy)
{
	spawn_heal(enemy, data);
	spawn_floo(enemy, data);
	spawn_shield(enemy, data);
	spawn_cloak(enemy, data);
	spawn_spider_wand(enemy, data);
	spawn_dementor_wand(enemy, data);
	spawn_elem_wand(enemy, data);
	spawn_wolf_wand(enemy, data);
}
