#include "cub3d_bonus.h"

void	init_popo_shield(t_data *data)
{
	data->items[SHIELD_POPO].categ = ITEM;
	data->items[SHIELD_POPO].type = POPO_SHIELD;
	data->items[SHIELD_POPO].radius = 3;
	data->items[SHIELD_POPO].deg_rotate = 6;
	data->items[SHIELD_POPO].front_img = &data->img[POPO_SHIELD_IMG];
	data->items[SHIELD_POPO].back_img = &data->img[POPO_SHIELD_IMG];
}

void	init_popo_floo(t_data *data)
{
	data->items[FLOO_POPO].categ = ITEM;
	data->items[FLOO_POPO].type = POPO_FLOO;
	data->items[FLOO_POPO].radius = 3;
	data->items[FLOO_POPO].deg_rotate = 6;
	data->items[FLOO_POPO].front_img = &data->img[POPO_FLOO_IMG];
	data->items[FLOO_POPO].back_img = &data->img[POPO_FLOO_IMG];
}

void	init_portkey(t_data *data)
{
	data->items[PORTKEY].categ = ITEM;
	data->items[PORTKEY].type = PORTKEY;
	data->items[PORTKEY].radius = 3;
	data->items[PORTKEY].deg_rotate = 6;
	data->items[PORTKEY].front_img = &data->img[PORTKEY_IMG];
	data->items[PORTKEY].back_img = &data->img[PORTKEY_IMG];
}

void	init_popo_invi(t_data *data)
{
	data->items[INVI_POPO].categ = ITEM;
	data->items[INVI_POPO].type = POPO_INVI;
	data->items[INVI_POPO].radius = 12;
	data->items[INVI_POPO].deg_rotate = 6;
	data->items[INVI_POPO].front_img = &data->img[POPO_INVI_IMG];
	data->items[INVI_POPO].back_img = &data->img[POPO_INVI_IMG];
}

void	init_popo_heal(t_data *data)
{
	data->items[HEAL_POPO].categ = ITEM;
	data->items[HEAL_POPO].type = POPO_HEAL;
	data->items[HEAL_POPO].radius = 3;
	data->items[HEAL_POPO].deg_rotate = 6;
	data->items[HEAL_POPO].front_img = &data->img[POPO_HEAL_IMG];
	data->items[HEAL_POPO].back_img = &data->img[POPO_HEAL_IMG];
}
