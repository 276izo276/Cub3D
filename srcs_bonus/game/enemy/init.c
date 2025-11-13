#include "struct_bonus.h"
#include "utils_bonus.h"
#include "enemy_bonus.h"
#include "cub3d_bonus.h"
#include "color_bonus.h"

#include <stdio.h>

void	fill_bird(t_data *data, t_enemy *enemy)
{
	enemy->back_img = &data->img[BIRD_BACK];
	enemy->front_img = &data->img[BIRD_FRONT];
	enemy->side_img = &data->img[BIRD_SIDE_90];
	enemy->side_front_img = &data->img[BIRD_FRONT_45];
	enemy->side_back_img = &data->img[BIRD_BACK_45];
	enemy->life = 30;
	enemy->dist_stop = 15;
	enemy->dist_damage = 25;
	enemy->dist_visu = 640;
	enemy->speed = 2.5;
	enemy->radius = 2;
	enemy->damage.damage_do = 3;
}

void	fill_snake(t_data *data, t_enemy *enemy)
{
	enemy->back_img = &data->img[SNAKE_BACK];
	enemy->front_img = &data->img[SNAKE_FRONT];
	enemy->side_img = &data->img[SNAKE_SIDE_90];
	enemy->side_front_img = &data->img[SNAKE_FRONT_45];
	enemy->side_back_img = &data->img[SNAKE_BACK_45];
	enemy->life = 30;
	enemy->dist_stop = 15;
	enemy->dist_damage = 25;
	enemy->dist_visu = 640;
	enemy->speed = 2;
	enemy->radius = 2;
	enemy->damage.damage_do = 15;
}

void	fill_wolf(t_data *data, t_enemy *enemy)
{
	enemy->back_img = &data->img[WOLF_BACK];
	enemy->front_img = &data->img[WOLF_FRONT];
	enemy->side_img = &data->img[WOLF_SIDE_90];
	enemy->side_front_img = &data->img[WOLF_FRONT_45];
	enemy->side_back_img = &data->img[WOLF_BACK_45];
	enemy->life = 100;
	enemy->dist_stop = 15;
	enemy->dist_damage = 25;
	enemy->dist_visu = 640;
	enemy->speed = 3.5;
	enemy->drop_heal = 10;
	enemy->drop_shield = 10;
	enemy->drop_floo = 10;
	enemy->drop_cloak = 10;
}

void	fill_elem(t_data *data, t_enemy *enemy)
{
	enemy->back_img = &data->img[ELEM_BACK];
	enemy->front_img = &data->img[ELEM_FRONT];
	enemy->side_img = &data->img[ELEM_SIDE_90];
	enemy->side_front_img = &data->img[ELEM_FRONT_45];
	enemy->side_back_img = &data->img[ELEM_BACK_45];
	enemy->damage.damage_do = 5;
	enemy->damage.fire_force_do = .1;
	enemy->damage.fire_frame_do = 60;
	enemy->life = 40;
	enemy->dist_stop = 20;
	enemy->dist_damage = 50;
	enemy->dist_visu = 640;
	enemy->speed = 2.5;
	enemy->drop_heal = 10;
	enemy->drop_shield = 10;
	enemy->drop_floo = 10;
	enemy->drop_cloak = 10;
}

void	fill_spider(t_data *data, t_enemy *enemy)
{
	enemy->back_img = &data->img[SPIDER_BACK];
	enemy->front_img = &data->img[SPIDER_FRONT];
	enemy->side_img = &data->img[SPIDER_SIDE_90];
	enemy->side_front_img = &data->img[SPIDER_FRONT_45];
	enemy->side_back_img = &data->img[SPIDER_BACK_45];
	enemy->damage.damage_do = 5;
	enemy->damage.poison_force_do = .1;
	enemy->damage.poison_frame_do = 60;
	enemy->life = 35;
	enemy->dist_stop = 64;
	enemy->dist_damage = 32;
	enemy->dist_visu = 640;
	enemy->speed = 1.5;
	enemy->drop_heal = 50;
	enemy->drop_shield = 50;
	enemy->drop_floo = 50;
	enemy->drop_cloak = 50;
}

void	fill_right_img_sorcerer(t_data *data, t_enemy *enemy, char c)
{
	if (c == NANCY)
	{
		enemy->front_img = &data->img[NANCY_FRONT];
		enemy->side_front_img = &data->img[NANCY_FRONT_45];
		data->sorcerer[0].nb_spawn++;
		data->sorcerer[0].is_alive = true;
		enemy->life = 250 + (data->sorcerer[0].nb_spawn * 100);
		enemy->color_coa = WATER_COLOR;
	}
	else if (c == ZIPPY)
	{
		enemy->front_img = &data->img[ZIPPY_FRONT];
		enemy->side_front_img = &data->img[ZIPPY_FRONT_45];
		data->sorcerer[1].nb_spawn++;
		data->sorcerer[1].is_alive = true;
		enemy->life = 200 + (data->sorcerer[1].nb_spawn * 100);
		enemy->color_coa = FIRE_COLOR;
	}
	else if (c == KUNFANDI)
	{
		enemy->front_img = &data->img[KUNFANDI_FRONT];
		enemy->side_front_img = &data->img[KUNFANDI_FRONT_45];
		data->sorcerer[2].nb_spawn++;
		data->sorcerer[2].is_alive = true;
		enemy->life = 150 + (data->sorcerer[2].nb_spawn * 100);
		enemy->color_coa = AIR_COLOR;
	}
	else if (c == PILO)
	{
		enemy->front_img = &data->img[PILO_FRONT];
		enemy->side_front_img = &data->img[PILO_FRONT_45];
		data->sorcerer[3].nb_spawn++;
		data->sorcerer[3].is_alive = true;
		enemy->life = 150 + (data->sorcerer[3].nb_spawn * 100);
		enemy->color_coa = EARTH_COLOR;
	}
	else if (c == CAMEO)
	{
		enemy->front_img = &data->img[CAMEO_FRONT];
		enemy->side_front_img = &data->img[CAMEO_FRONT_45];
		data->sorcerer[4].nb_spawn++;
		data->sorcerer[4].is_alive = true;
		enemy->life = 150 + (data->sorcerer[4].nb_spawn * 100);
		enemy->color_coa = AIR_COLOR;
	}
	else if (c == ANAIS)
	{
		enemy->front_img = &data->img[ANAIS_FRONT];
		enemy->side_front_img = &data->img[ANAIS_FRONT_45];
		data->sorcerer[5].nb_spawn++;
		data->sorcerer[5].is_alive = true;
		enemy->life = 150 + (data->sorcerer[5].nb_spawn * 100);
		enemy->color_coa = AIR_COLOR;
	}
	else if (c == DIRLO)
	{
		enemy->front_img = &data->img[DIRLO_FRONT];
		enemy->side_front_img = &data->img[DIRLO_FRONT_45];
		data->sorcerer[6].nb_spawn++;
		data->sorcerer[6].is_alive = true;
		enemy->life = 150 + (data->sorcerer[6].nb_spawn * 100);
		enemy->color_coa = EARTH_COLOR;
	}
	else if (c == STEF)
	{
		enemy->front_img = &data->img[STEF_FRONT];
		enemy->side_front_img = &data->img[STEF_FRONT_45];
		data->sorcerer[7].nb_spawn++;
		data->sorcerer[7].is_alive = true;
		enemy->life = 200 + (data->sorcerer[7].nb_spawn * 100);
		enemy->color_coa = FIRE_COLOR;
	}
	else if (c == MARINA)
	{
		enemy->front_img = &data->img[MARINA_FRONT];
		enemy->side_front_img = &data->img[MARINA_FRONT_45];
		data->sorcerer[8].nb_spawn++;
		data->sorcerer[8].is_alive = true;
		enemy->life = 150 + (data->sorcerer[8].nb_spawn * 100);
		enemy->color_coa = EARTH_COLOR;
	}
	enemy->back_img = &data->img[SORCERER_BACK];
	enemy->side_img = &data->img[SORCERER_SIDE_90];
	enemy->side_back_img = &data->img[SORCERER_BACK_45];
}
void	fill_sorcerer(t_data *data, t_enemy *enemy, char c)
{
	enemy->dist_stop = 40;
	enemy->dist_damage = 32;
	enemy->dist_visu = 640;
	enemy->speed = 2.5;
	enemy->cooldown_cac = .2;
	enemy->damage.curse_force_do = .2;
	enemy->damage.curse_frame_do = 10;
	enemy->damage.slow_force_do = 25;
	enemy->damage.slow_frame_do = 60;
	fill_right_img_sorcerer(data, enemy, c);
}

void	fill_dementor(t_data *data, t_enemy *enemy)
{
	enemy->back_img = &data->img[DEMENTOR_BACK];
	enemy->front_img = &data->img[DEMENTOR_FRONT];
	enemy->side_img = &data->img[DEMENTOR_SIDE_90];
	enemy->side_front_img = &data->img[DEMENTOR_FRONT_45];
	enemy->side_back_img = &data->img[DEMENTOR_BACK_45];
	enemy->life = 100;
	enemy->dist_stop = 20;
	enemy->dist_damage = 32;
	enemy->dist_visu = 640;
	enemy->speed = 2.5;
	enemy->cooldown_cac = .2;
	enemy->damage.curse_force_do = .2;
	enemy->damage.curse_frame_do = 10;
	enemy->damage.slow_force_do = 25;
	enemy->damage.slow_frame_do = 60;

}

t_enemy	*init_enemy(char c, t_fcoo coo, t_data *data, double deg)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	ft_bzero(enemy, sizeof(t_enemy));
	enemy->type = c;
	enemy->center.case_x = coo.case_x;
	enemy->center.case_y = coo.case_y;
	enemy->center.coo_x = coo.coo_x;
	enemy->center.coo_y = coo.coo_y;
	enemy->radius = 6;
	enemy->dist_target = -1;
	enemy->rad = enemy->deg * (M_PI / 180);
	enemy->calc = true;
	enemy->cooldown_dist = 6;
	enemy->cooldown_cac = 1;
	enemy->deg = deg;
	if (c == DEMENTOR)
		fill_dementor(data, enemy);
	else if (c == SPIDER)
		fill_spider(data, enemy);
	else if (c == ELEM)
		fill_elem(data, enemy);
	else if (c == WOLF)
		fill_wolf(data, enemy);
	else if (c == BIRD)
		fill_bird(data, enemy);
	else if (c == SNAKE)
		fill_snake(data, enemy);
	else
		fill_sorcerer(data, enemy, c);
	calc_left_and_right_point(enemy, data);
	enemy->left_before.coo_x = enemy->left.coo_x;
	enemy->left_before.coo_y = enemy->left.coo_y;
	enemy->left_before.case_x = enemy->left.case_x;
	enemy->left_before.case_y = enemy->left.case_y;
	enemy->right_before.coo_x = enemy->right.coo_x;
	enemy->right_before.coo_y = enemy->right.coo_y;
	enemy->right_before.case_x = enemy->right.case_x;
	enemy->right_before.case_y = enemy->right.case_y;
	enemy->center_before.coo_x = enemy->right.coo_x;
	enemy->center_before.coo_y = enemy->right.coo_y;
	enemy->center_before.case_x = enemy->right.case_x;
	enemy->center_before.case_y = enemy->right.case_y;
	return (enemy);
}

t_case	*init_case(int h_cost, int r_cost, int dir[2], t_case *parent)
{
	t_case	*cel;

	cel = malloc(sizeof(t_case));
	if (!cel)
		return (cel);
	ft_bzero(cel, (sizeof(t_case)));
	cel->parent = parent;
	cel->case_x = dir[1];
	cel->case_y = dir[0];
	cel->h_cost = h_cost;
	cel->r_cost = r_cost;
	cel->t_cost = r_cost + h_cost;
	return (cel);
}
