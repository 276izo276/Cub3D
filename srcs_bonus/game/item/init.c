#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include "time_bonus.h"
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include <stdio.h>

t_item	*init_spell_item(t_data *data, t_spells info)
{
	t_item	*item;

	item = malloc(sizeof(t_item));
	if (!item)
		return (NULL);
	bzero(item, sizeof(t_item));
	item->center.case_x = data->player.coo.case_x;
	item->center.case_y = data->player.coo.case_y;
	item->center.coo_x = data->player.coo.coo_x;
	item->center.coo_y = data->player.coo.coo_y;
	item->deg = fmod(data->map.mini.deg + 180, 360);
	item->rad = item->deg * (M_PI / 180);
	item->speed = data->spell[info].item.speed;

	item->damage.damage_do = data->spell[info].damage.damage_do;
	item->damage.damage_spider_do = data->spell[info].damage.damage_spider_do;
	item->damage.damage_dementor_do = data->spell[info].damage.damage_dementor_do;
	item->damage.slow_force_do = data->spell[info].damage.slow_force_do;
	item->damage.slow_frame_do = data->spell[info].damage.slow_frame_do;
	item->damage.poison_force_do = data->spell[info].damage.poison_force_do;
	item->damage.poison_frame_do = data->spell[info].damage.poison_frame_do;
	item->damage.fire_force_do = data->spell[info].damage.fire_force_do;
	item->damage.fire_frame_do = data->spell[info].damage.fire_frame_do;
	item->damage.curse_force_do = data->spell[info].damage.curse_force_do;
	item->damage.curse_frame_do = data->spell[info].damage.curse_frame_do;
	item->damage.confundo_force_do = data->spell[info].damage.confundo_force_do;
	item->damage.confundo_frame_do = data->spell[info].damage.confundo_frame_do;

	item->radius = data->spell[info].item.radius;
	item->back_img = data->spell[info].item.back_img;
	item->front_img = data->spell[info].item.front_img;
	make_move_item(item, 15);
	return (item);
}