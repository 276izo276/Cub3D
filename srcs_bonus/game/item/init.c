#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include "time_bonus.h"
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include <stdio.h>

t_item	*init_spell_item(t_data *data, int info)
{
	printf("CREATE ITEM PLAYER\n");
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

	item->damage.damage_do = data->spell[info].damage.damage_do;
	item->damage.damage_spider_do = data->spell[info].damage.damage_spider_do;
	item->damage.damage_dementor_do = data->spell[info].damage.damage_dementor_do;
	item->damage.damage_snake_do = data->spell[info].damage.damage_snake_do;
	item->damage.damage_elem_do = data->spell[info].damage.damage_elem_do;
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
	item->damage.repulso_force_do = data->spell[info].damage.repulso_force_do;
	item->damage.repulso_frame_do = data->spell[info].damage.repulso_frame_do;

	item->radius = data->spell[info].item.radius;
	item->back_img = data->spell[info].item.back_img;
	item->front_img = data->spell[info].item.front_img;
	item->damage.which_coa_do = data->player.coa;
	data->sound = add_end_lst(create_sound(data, 1), data->sound, free_sound);
	make_move_item(item, 1);
	return (item);
}

t_item	*create_spell_item_sorcerer(t_data *data, int info, t_fcoo *coo, double deg)
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

	item->damage.damage_do = data->spell[info].damage.damage_do;
	item->damage.damage_spider_do = data->spell[info].damage.damage_spider_do;
	item->damage.damage_dementor_do = data->spell[info].damage.damage_dementor_do;
	item->damage.damage_snake_do = data->spell[info].damage.damage_snake_do;
	item->damage.damage_elem_do = data->spell[info].damage.damage_elem_do;
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
	item->damage.repulso_force_do = data->spell[info].damage.repulso_force_do;
	item->damage.repulso_frame_do = data->spell[info].damage.repulso_frame_do;

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

	item->damage.damage_do = data->items[info].damage.damage_do;
	item->damage.damage_spider_do = data->items[info].damage.damage_spider_do;
	item->damage.damage_dementor_do = data->items[info].damage.damage_dementor_do;
	item->damage.slow_force_do = data->items[info].damage.slow_force_do;
	item->damage.slow_frame_do = data->items[info].damage.slow_frame_do;
	item->damage.poison_force_do = data->items[info].damage.poison_force_do;
	item->damage.poison_frame_do = data->items[info].damage.poison_frame_do;
	item->damage.fire_force_do = data->items[info].damage.fire_force_do;
	item->damage.fire_frame_do = data->items[info].damage.fire_frame_do;
	item->damage.curse_force_do = data->items[info].damage.curse_force_do;
	item->damage.curse_frame_do = data->items[info].damage.curse_frame_do;
	item->damage.confundo_force_do = data->items[info].damage.confundo_force_do;
	item->damage.confundo_frame_do = data->items[info].damage.confundo_frame_do;
	item->damage.repulso_force_do = data->items[info].damage.repulso_force_do;
	item->damage.repulso_frame_do = data->items[info].damage.repulso_frame_do;

	item->radius = data->items[info].radius;
	item->back_img = data->items[info].back_img;
	item->front_img = data->items[info].front_img;
	item->damage.which_coa_do = OTHERS;
	make_move_item(item, 10);
	return (item);
}

void	init_poison_spider(t_data *data)
{
	data->items[POISON_SPIDER].categ = ITEM;
	data->items[POISON_SPIDER].damage.poison_force_do = .1;
	data->items[POISON_SPIDER].damage.poison_frame_do = 120;
	data->items[POISON_SPIDER].speed = 1;
	data->items[POISON_SPIDER].radius = 3;
	data->items[POISON_SPIDER].front_img = &data->img[POISON_SPIDER_IMG];
	data->items[POISON_SPIDER].back_img = &data->img[POISON_SPIDER_IMG];
}

void	init_web_spider(t_data *data)
{
	data->items[WEB_SPIDER].categ = ITEM;
	data->items[WEB_SPIDER].damage.damage_do = 10;
	data->items[WEB_SPIDER].damage.slow_force_do = 20;
	data->items[WEB_SPIDER].damage.slow_frame_do = 60;
	data->items[WEB_SPIDER].speed = 20;
	data->items[WEB_SPIDER].radius = 3;
	data->items[WEB_SPIDER].front_img = &data->img[WEB_SPIDER_IMG];
	data->items[WEB_SPIDER].back_img = &data->img[WEB_SPIDER_IMG];
}

void	init_fireball_elem(t_data *data)
{
	data->items[FIREBALL_ELEM].categ = ITEM;
	data->items[FIREBALL_ELEM].damage.damage_do = 10;
	data->items[FIREBALL_ELEM].speed = 5;
	data->items[FIREBALL_ELEM].radius = 3;
	data->items[FIREBALL_ELEM].front_img = &data->img[INCENDIO_IMG];
	data->items[FIREBALL_ELEM].back_img = &data->img[INCENDIO_IMG];
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

void	init_death_anim(t_data *data)
{
	data->items[ANIM_DEATH].categ = ITEM;
	data->items[ANIM_DEATH].type = ANIM_DEATH;
	data->items[ANIM_DEATH].radius = 20;
}

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

static void	init_tig(t_data *data)
{
	data->items[TIG].categ = ITEM;
	data->items[TIG].type = TIG;
	data->items[TIG].damage.damage_do = 25;
	data->items[TIG].damage.curse_force_do = .1;
	data->items[TIG].damage.curse_frame_do = 120;
	data->items[TIG].damage.slow_force_do = 70;
	data->items[TIG].damage.slow_frame_do = 120;
	data->items[TIG].damage.repulso_force_do = 2;
	data->items[TIG].damage.repulso_frame_do = 5;
	data->items[TIG].speed = 0;
	data->items[TIG].radius = 5;
	data->items[TIG].front_img = &data->img[TIG_IMG];
	data->items[TIG].back_img = &data->img[TIG_IMG];
}


static void	init_bh(t_data *data)
{
	data->items[BH].categ = ITEM;
	data->items[BH].type = BH;
	data->items[BH].damage.damage_do = .1;
	data->items[BH].damage.curse_force_do = .05;
	data->items[BH].damage.curse_frame_do = 120;
	data->items[BH].damage.repulso_force_do = -6.0;
	data->items[BH].damage.repulso_frame_do = 1;
	data->items[BH].speed = 3;
	data->items[BH].radius = 5;
}

static void	init_pizza(t_data *data)
{
	data->items[PIZZA].categ = ITEM;
	data->items[PIZZA].type = PIZZA;
	data->items[PIZZA].damage.damage_do = 25;
	data->items[PIZZA].damage.curse_force_do = .1;
	data->items[PIZZA].damage.curse_frame_do = 120;
	data->items[PIZZA].damage.slow_force_do = 70;
	data->items[PIZZA].damage.slow_frame_do = 120;
	data->items[PIZZA].damage.repulso_force_do = 2;
	data->items[PIZZA].damage.repulso_frame_do = 5;
	data->items[PIZZA].speed = 10;
	data->items[PIZZA].radius = 8;
	data->items[PIZZA].front_img = &data->img[PIZZA_IMG];
	data->items[PIZZA].back_img = &data->img[PIZZA_IMG];
}

static void	init_mac(t_data *data)
{
	data->items[MAC].categ = ITEM;
	data->items[MAC].type = MAC;
	data->items[MAC].damage.damage_do = 25;
	data->items[MAC].damage.curse_force_do = .1;
	data->items[MAC].damage.curse_frame_do = 120;
	data->items[MAC].damage.slow_force_do = 70;
	data->items[MAC].damage.slow_frame_do = 120;
	data->items[MAC].damage.repulso_force_do = 2;
	data->items[MAC].damage.repulso_frame_do = 5;
	data->items[MAC].speed = 10;
	data->items[MAC].radius = 3;
	data->items[MAC].front_img = &data->img[MAC_IMG];
	data->items[MAC].back_img = &data->img[MAC_IMG];
}


static void	init_folder(t_data *data)
{
	data->items[FOLDER].categ = ITEM;
	data->items[FOLDER].type = FOLDER;
	data->items[FOLDER].damage.damage_do = 25;
	data->items[FOLDER].damage.curse_force_do = .1;
	data->items[FOLDER].damage.curse_frame_do = 120;
	data->items[FOLDER].damage.slow_force_do = 70;
	data->items[FOLDER].damage.slow_frame_do = 120;
	data->items[FOLDER].damage.repulso_force_do = 2;
	data->items[FOLDER].damage.repulso_frame_do = 5;
	data->items[FOLDER].speed = 0;
	data->items[FOLDER].radius = 3;
	data->items[FOLDER].front_img = &data->img[FOLDER_IMG];
	data->items[FOLDER].back_img = &data->img[FOLDER_IMG];
}


static void	init_marvin(t_data *data)
{
	data->items[MARVIN].categ = ITEM;
	data->items[MARVIN].type = MARVIN;
	data->items[MARVIN].damage.damage_do = 25;
	data->items[MARVIN].damage.curse_force_do = .1;
	data->items[MARVIN].damage.curse_frame_do = 120;
	data->items[MARVIN].damage.slow_force_do = 70;
	data->items[MARVIN].damage.slow_frame_do = 120;
	data->items[MARVIN].damage.repulso_force_do = 2;
	data->items[MARVIN].damage.repulso_frame_do = 5;
	data->items[MARVIN].speed = 10;
	data->items[MARVIN].radius = 3;
	data->items[MARVIN].front_img = &data->img[MARVIN_IMG];
	data->items[MARVIN].back_img = &data->img[MARVIN_IMG];
}

static void	init_taylor_swift(t_data *data)
{
	data->items[TAYLOR_SWIFT].categ = ITEM;
	data->items[TAYLOR_SWIFT].type = TAYLOR_SWIFT;
	data->items[TAYLOR_SWIFT].damage.damage_do = 25;
	data->items[TAYLOR_SWIFT].damage.curse_force_do = .1;
	data->items[TAYLOR_SWIFT].damage.curse_frame_do = 120;
	data->items[TAYLOR_SWIFT].damage.slow_force_do = 70;
	data->items[TAYLOR_SWIFT].damage.slow_frame_do = 120;
	data->items[TAYLOR_SWIFT].damage.repulso_force_do = 2;
	data->items[TAYLOR_SWIFT].damage.repulso_frame_do = 5;
	data->items[TAYLOR_SWIFT].speed = 10;
	data->items[TAYLOR_SWIFT].radius = 5;
	data->items[TAYLOR_SWIFT].front_img = &data->img[TAYLOR_SWIFT_IMG];
	data->items[TAYLOR_SWIFT].back_img = &data->img[TAYLOR_SWIFT_IMG];
}

static void	init_company(t_data *data)
{
	data->items[COMPANY].categ = ITEM;
	data->items[COMPANY].type = COMPANY;
	data->items[COMPANY].damage.damage_do = 25;
	data->items[COMPANY].damage.curse_force_do = .1;
	data->items[COMPANY].damage.curse_frame_do = 120;
	data->items[COMPANY].damage.slow_force_do = 70;
	data->items[COMPANY].damage.slow_frame_do = 120;
	data->items[COMPANY].damage.repulso_force_do = 2;
	data->items[COMPANY].damage.repulso_frame_do = 5;
	data->items[COMPANY].speed = 10;
	data->items[COMPANY].radius = 5;
	data->items[COMPANY].front_img = &data->img[COMPANY_IMG];
	data->items[COMPANY].back_img = &data->img[COMPANY_IMG];
}

static void	init_logo_42(t_data *data)
{
	data->items[LOGO_42].categ = ITEM;
	data->items[LOGO_42].type = LOGO_42;
	data->items[LOGO_42].damage.damage_do = 25;
	data->items[LOGO_42].damage.curse_force_do = .1;
	data->items[LOGO_42].damage.curse_frame_do = 120;
	data->items[LOGO_42].damage.slow_force_do = 70;
	data->items[LOGO_42].damage.slow_frame_do = 120;
	data->items[LOGO_42].damage.repulso_force_do = 2;
	data->items[LOGO_42].damage.repulso_frame_do = 5;
	data->items[LOGO_42].speed = 10;
	data->items[LOGO_42].radius = 5;
	data->items[LOGO_42].front_img = &data->img[LOGO_42_IMG];
	data->items[LOGO_42].back_img = &data->img[LOGO_42_IMG];
}

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

void	init_item(t_data *data)
{
	init_poison_spider(data);
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
