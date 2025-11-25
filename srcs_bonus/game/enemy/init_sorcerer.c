#include "struct_bonus.h"
#include "color_bonus.h"

static void	init_sorcerer_p1(t_data *data, t_enemy *enemy, char c)
{
	if (c == KUNFANDI)
	{
		enemy->front_img = &data->img[KUNFANDI_FRONT];
		enemy->side_front_img = &data->img[KUNFANDI_FRONT_45];
		data->sorcerer[2].nb_spawn++;
		data->sorcerer[2].is_alive = true;
		enemy->life = 150 + (data->sorcerer[2].nb_spawn * 100);
		enemy->color_coa = AIR_COLOR;
		enemy->damage.which_coa_do = AIR;
	}
	if (c == CAMEO)
	{
		enemy->front_img = &data->img[CAMEO_FRONT];
		enemy->side_front_img = &data->img[CAMEO_FRONT_45];
		data->sorcerer[4].nb_spawn++;
		data->sorcerer[4].is_alive = true;
		enemy->life = 150 + (data->sorcerer[4].nb_spawn * 100);
		enemy->color_coa = AIR_COLOR;
		enemy->damage.which_coa_do = AIR;
	}
}

static void	init_sorcerer_p2(t_data *data, t_enemy *enemy, char c)
{
	if (c == NANCY)
	{
		enemy->front_img = &data->img[NANCY_FRONT];
		enemy->side_front_img = &data->img[NANCY_FRONT_45];
		data->sorcerer[0].nb_spawn++;
		data->sorcerer[0].is_alive = true;
		enemy->life = 250 + (data->sorcerer[0].nb_spawn * 100);
		enemy->color_coa = WATER_COLOR;
		enemy->damage.which_coa_do = WATER;
	}
	if (c == ANAIS)
	{
		enemy->front_img = &data->img[ANAIS_FRONT];
		enemy->side_front_img = &data->img[ANAIS_FRONT_45];
		data->sorcerer[5].nb_spawn++;
		data->sorcerer[5].is_alive = true;
		enemy->life = 150 + (data->sorcerer[5].nb_spawn * 100);
		enemy->color_coa = AIR_COLOR;
		enemy->damage.which_coa_do = AIR;
	}
}

static void	init_sorcerer_p3(t_data *data, t_enemy *enemy, char c)
{
	if (c == PILO)
	{
		enemy->front_img = &data->img[PILO_FRONT];
		enemy->side_front_img = &data->img[PILO_FRONT_45];
		data->sorcerer[3].nb_spawn++;
		data->sorcerer[3].is_alive = true;
		enemy->life = 150 + (data->sorcerer[3].nb_spawn * 100);
		enemy->color_coa = EARTH_COLOR;
		enemy->damage.which_coa_do = EARTH;
	}
	if (c == DIRLO)
	{
		enemy->front_img = &data->img[DIRLO_FRONT];
		enemy->side_front_img = &data->img[DIRLO_FRONT_45];
		data->sorcerer[6].nb_spawn++;
		data->sorcerer[6].is_alive = true;
		enemy->life = 150 + (data->sorcerer[6].nb_spawn * 100);
		enemy->color_coa = EARTH_COLOR;
		enemy->damage.which_coa_do = EARTH;
	}
}

static void	init_sorcerer_p4(t_data *data, t_enemy *enemy, char c)
{
	if (c == ZIPPY)
	{
		enemy->front_img = &data->img[ZIPPY_FRONT];
		enemy->side_front_img = &data->img[ZIPPY_FRONT_45];
		data->sorcerer[1].nb_spawn++;
		data->sorcerer[1].is_alive = true;
		enemy->life = 200 + (data->sorcerer[1].nb_spawn * 100);
		enemy->color_coa = FIRE_COLOR;
		enemy->damage.which_coa_do = FIRE;
	}
	if (c == STEF)
	{
		enemy->front_img = &data->img[STEF_FRONT];
		enemy->side_front_img = &data->img[STEF_FRONT_45];
		data->sorcerer[7].nb_spawn++;
		data->sorcerer[7].is_alive = true;
		enemy->life = 200 + (data->sorcerer[7].nb_spawn * 100);
		enemy->color_coa = FIRE_COLOR;
		enemy->damage.which_coa_do = FIRE;
	}
}

void	fill_right_img_sorcerer(t_data *data, t_enemy *enemy, char c)
{
	init_sorcerer_p1(data, enemy, c);
	init_sorcerer_p2(data, enemy, c);
	init_sorcerer_p3(data, enemy, c);
	init_sorcerer_p4(data, enemy, c);
	if (c == MARINA)
	{
		enemy->front_img = &data->img[MARINA_FRONT];
		enemy->side_front_img = &data->img[MARINA_FRONT_45];
		data->sorcerer[8].nb_spawn++;
		data->sorcerer[8].is_alive = true;
		enemy->life = 150 + (data->sorcerer[8].nb_spawn * 100);
		enemy->color_coa = EARTH_COLOR;
		enemy->damage.which_coa_do = EARTH;
	}
	if (enemy->color_coa == AIR_COLOR)
		enemy->drop_spider_wand = 100;
	else if (enemy->color_coa == EARTH_COLOR)
		enemy->drop_wolf_wand = 100;
	else if (enemy->color_coa == WATER_COLOR)
		enemy->drop_dementor_wand = 100;
	else if (enemy->color_coa == FIRE_COLOR)
		enemy->drop_elem_wand = 100;
	enemy->back_img = &data->img[SORCERER_BACK];
	enemy->side_img = &data->img[SORCERER_SIDE_90];
	enemy->side_back_img = &data->img[SORCERER_BACK_45];
}
