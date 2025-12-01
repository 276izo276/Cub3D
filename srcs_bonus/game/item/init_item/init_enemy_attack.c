#include "cub3d_bonus.h"

void	init_web_spider(t_data *data)
{
	data->items[WEB_SPIDER].categ = ITEM;
	data->items[WEB_SPIDER].damage.damage_do = 10;
	data->items[WEB_SPIDER].damage.slow_force_do = 30;
	data->items[WEB_SPIDER].damage.slow_frame_do = 60;
	data->items[WEB_SPIDER].speed = 15;
	data->items[WEB_SPIDER].radius = 3;
	data->items[WEB_SPIDER].front_img = &data->img[WEB_SPIDER_IMG];
	data->items[WEB_SPIDER].back_img = &data->img[WEB_SPIDER_IMG];
}

void	init_fireball_elem(t_data *data)
{
	data->items[FIREBALL_ELEM].categ = ITEM;
	data->items[FIREBALL_ELEM].damage.damage_do = 15;
	data->items[FIREBALL_ELEM].damage.fire_force_do = 0.2;
	data->items[FIREBALL_ELEM].damage.fire_frame_do = 30;
	data->items[FIREBALL_ELEM].speed = 20;
	data->items[FIREBALL_ELEM].radius = 3;
	data->items[FIREBALL_ELEM].front_img = &data->img[INCENDIO_IMG];
	data->items[FIREBALL_ELEM].back_img = &data->img[INCENDIO_IMG];
}

void	init_death_anim(t_data *data)
{
	data->items[ANIM_DEATH].categ = ITEM;
	data->items[ANIM_DEATH].type = ANIM_DEATH;
	data->items[ANIM_DEATH].radius = 20;
}
