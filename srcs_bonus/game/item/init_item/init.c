#include "cub3d_bonus.h"
#include "struct_bonus.h"
#include "time_bonus.h"
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#include "parsing_bonus.h"

static void	init_damage(t_damage *damage_take, t_damage *damage_do)
{
	damage_take->damage_do = damage_do->damage_do;
	damage_take->damage_spider_do = damage_do->damage_spider_do;
	damage_take->damage_dementor_do = damage_do->damage_dementor_do;
	damage_take->damage_snake_do = damage_do->damage_snake_do;
	damage_take->damage_elem_do = damage_do->damage_elem_do;
	damage_take->slow_force_do = damage_do->slow_force_do;
	damage_take->slow_frame_do = damage_do->slow_frame_do;
	damage_take->poison_force_do = damage_do->poison_force_do;
	damage_take->poison_frame_do = damage_do->poison_frame_do;
	damage_take->fire_force_do = damage_do->fire_force_do;
	damage_take->fire_frame_do = damage_do->fire_frame_do;
	damage_take->curse_force_do = damage_do->curse_force_do;
	damage_take->curse_frame_do = damage_do->curse_frame_do;
	damage_take->confundo_force_do = damage_do->confundo_force_do;
	damage_take->confundo_frame_do = damage_do->confundo_frame_do;
	damage_take->repulso_force_do = damage_do->repulso_force_do;
	damage_take->repulso_frame_do = damage_do->repulso_frame_do;
}

t_item	*init_spell_item(t_data *data, int info)
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
	item->type = data->spell[info].type;
	init_damage(&item->damage, &data->spell[info].damage);
	item->radius = data->spell[info].item.radius;
	item->back_img = data->spell[info].item.back_img;
	item->front_img = data->spell[info].item.front_img;
	item->damage.which_coa_do = data->player.coa;
	data->sound = add_end_lst(create_sound(data, info),
			data->sound, free_sound);
	return (item);
}

t_item	*create_spell_item_sorcerer(t_data *data, int info, t_fcoo *coo,
		double deg)
{
	t_item	*item;

	item = malloc(sizeof(t_item));
	if (!item)
		return (NULL);
	bzero(item, sizeof(t_item));
	item->center.case_x = coo->case_x;
	item->center.case_y = coo->case_y;
	item->center.coo_x = coo->coo_x;
	item->center.coo_y = coo->coo_y;
	item->deg = fmod(deg + 180, 360);
	item->rad = item->deg * (M_PI / 180);
	item->speed = data->spell[info].item.speed;
	item->type = data->spell[info].type;
	init_damage(&item->damage, &data->spell[info].damage);
	item->radius = data->spell[info].item.radius;
	item->back_img = data->spell[info].item.back_img;
	item->front_img = data->spell[info].item.front_img;
	item->damage.which_coa_do = OTHERS;
	make_move_item(item, 42);
	return (item);
}

t_item	*create_item(t_data *data, int info, t_fcoo *coo, double deg)
{
	t_item	*item;

	item = malloc(sizeof(t_item));
	if (!item)
		return (NULL);
	bzero(item, sizeof(t_item));
	item->center.case_x = coo->case_x;
	item->center.case_y = coo->case_y;
	item->center.coo_x = coo->coo_x;
	item->center.coo_y = coo->coo_y;
	item->deg = fmod(deg + 180, 360);
	item->rad = item->deg * (M_PI / 180);
	item->speed = data->items[info].speed;
	item->type = data->items[info].type;
	item->deg_rotate = data->items[info].deg_rotate;
	item->categ = data->items[info].categ;
	init_damage(&item->damage, &data->items[info].damage);
	item->radius = data->items[info].radius;
	item->back_img = data->items[info].back_img;
	item->front_img = data->items[info].front_img;
	item->damage.which_coa_do = OTHERS;
	make_move_item(item, 10);
	return (item);
}

void	init_item(t_data *data)
{
	init_web_spider(data);
	init_fireball_elem(data);
	init_popo_heal(data);
	init_popo_shield(data);
	init_popo_floo(data);
	init_popo_invi(data);
	init_death_anim(data);
	init_portkey(data);
	init_tig(data);
	init_bh(data);
	init_pizza(data);
	init_taylor_swift(data);
	init_marvin(data);
	init_logo_42(data);
	init_company(data);
	init_folder(data);
	init_mac(data);
	init_wolf_wand(data);
	init_spider_wand(data);
	init_dementor_wand(data);
	init_elem_wand(data);
	init_pillar(data);
}
