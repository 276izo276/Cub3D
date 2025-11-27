#include "cub3d_bonus.h"

void	init_elem_wand(t_data *data)
{
	data->items[ELEM_WAND].categ = ITEM;
	data->items[ELEM_WAND].type = ELEM_WAND;
	data->items[ELEM_WAND].radius = 10;
	data->items[ELEM_WAND].deg_rotate = 6;
	data->items[ELEM_WAND].front_img = &data->img[WAND_ELEM_IMG];
	data->items[ELEM_WAND].back_img = &data->img[WAND_ELEM_IMG];
}

void	init_dementor_wand(t_data *data)
{
	data->items[DEMENTOR_WAND].categ = ITEM;
	data->items[DEMENTOR_WAND].type = DEMENTOR_WAND;
	data->items[DEMENTOR_WAND].radius = 10;
	data->items[DEMENTOR_WAND].deg_rotate = 6;
	data->items[DEMENTOR_WAND].front_img = &data->img[WAND_DEMENTOR_IMG];
	data->items[DEMENTOR_WAND].back_img = &data->img[WAND_DEMENTOR_IMG];
}

void	init_spider_wand(t_data *data)
{
	data->items[SPIDER_WAND].categ = ITEM;
	data->items[SPIDER_WAND].type = SPIDER_WAND;
	data->items[SPIDER_WAND].radius = 10;
	data->items[SPIDER_WAND].deg_rotate = 6;
	data->items[SPIDER_WAND].front_img = &data->img[WAND_SPIDER_IMG];
	data->items[SPIDER_WAND].back_img = &data->img[WAND_SPIDER_IMG];
}

void	init_wolf_wand(t_data *data)
{
	data->items[WOLF_WAND].categ = ITEM;
	data->items[WOLF_WAND].type = WOLF_WAND;
	data->items[WOLF_WAND].radius = 10;
	data->items[WOLF_WAND].deg_rotate = 6;
	data->items[WOLF_WAND].front_img = &data->img[WAND_WOLF_IMG];
	data->items[WOLF_WAND].back_img = &data->img[WAND_WOLF_IMG];
}

void	init_pillar(t_data *data)
{
	data->items[PILLAR].categ = ITEM;
	data->items[PILLAR].type = PILLAR;
	data->items[PILLAR].radius = 10;
	data->items[PILLAR].front_img = &data->img[PILLAR_IMG];
	data->items[PILLAR].back_img = &data->img[PILLAR_IMG];
}
