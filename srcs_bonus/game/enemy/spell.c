
#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <stdlib.h>

void	air_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
					EXPECTO_PATRONUM, &enemy->center, deg + 180), data->item,
				f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ARANIA_EXUMAI,
					&enemy->center, deg + 180), data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, VENTUS,
					&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == KUNFANDI)
		data->item = add_end_lst(create_item(data, BH, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == CAMEO)
		data->item = add_end_lst(create_item(data, MARVIN, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == ANAIS)
		data->item = add_end_lst(create_item(data, TAYLOR_SWIFT, &enemy->center,
					deg + 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = AIR;
}

void	water_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
					EXPECTO_PATRONUM, &enemy->center, deg + 180), data->item,
				f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ARANIA_EXUMAI,
					&enemy->center, deg + 180), data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, AGUAMENTI,
					&enemy->center, deg + 180), data->item, f_item);
	else
		data->item = add_end_lst(create_item(data, FOLDER, &enemy->center, deg
					+ 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = WATER;
}

void	fire_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
					EXPECTO_PATRONUM, &enemy->center, deg + 180), data->item,
				f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ARANIA_EXUMAI,
					&enemy->center, deg + 180), data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, INCENDIO,
					&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == STEF)
		data->item = add_end_lst(create_item(data, COMPANY, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == ZIPPY)
		data->item = add_end_lst(create_item(data, PIZZA, &enemy->center, deg
					+ 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = FIRE;
}

void	earth_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
					EXPECTO_PATRONUM, &enemy->center, deg + 180), data->item,
				f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ARANIA_EXUMAI,
					&enemy->center, deg + 180), data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ENDOLORIS,
					&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == MARINA)
		data->item = add_end_lst(create_item(data, LOGO_42, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == PILO)
		data->item = add_end_lst(create_item(data, MAC, &enemy->center, deg
					+ 180), data->item, f_item);
	else if (enemy->type == DIRLO)
		data->item = add_end_lst(create_item(data, TIG, &enemy->center, deg
					+ 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = EARTH;
}