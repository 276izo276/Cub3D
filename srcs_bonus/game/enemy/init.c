#include "struct_bonus.h"
#include "utils_bonus.h"
#include "enemy_bonus.h"
#include "cub3d_bonus.h"

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
	enemy->speed = 3;
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
	enemy->life = 100;
	enemy->dist_stop = 15;
	enemy->dist_damage = 25;
	enemy->dist_visu = 640;
	enemy->speed = 3;
	enemy->radius = 2;
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
	enemy->cooldown_dist = 10;
	enemy->cooldown_cac = 1;
	enemy->deg = deg;
	if (c == DEMENTOR)
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
	}
	else if (c == SPIDER)
	{
		enemy->back_img = &data->img[SPIDER_BACK];
		enemy->front_img = &data->img[SPIDER_FRONT];
		enemy->side_img = &data->img[SPIDER_SIDE_90];
		enemy->side_front_img = &data->img[SPIDER_FRONT_45];
		enemy->side_back_img = &data->img[SPIDER_BACK_45];
		enemy->damage.damage_do = 5;
		enemy->damage.poison_force_do = .1;
		enemy->damage.poison_frame_do = 60;
		enemy->life = 100;
		enemy->dist_stop = 64;
		enemy->dist_damage = 32;
		enemy->dist_visu = 640;
		enemy->speed = 1;
	}
	else if (c == ELEM)
	{
		enemy->back_img = &data->img[ELEM_BACK];
		enemy->front_img = &data->img[ELEM_FRONT];
		enemy->side_img = &data->img[ELEM_SIDE_90];
		enemy->side_front_img = &data->img[ELEM_FRONT_45];
		enemy->side_back_img = &data->img[ELEM_BACK_45];
		enemy->damage.damage_do = 5;
		enemy->damage.fire_force_do = .1;
		enemy->damage.fire_frame_do = 60;
		enemy->life = 100;
		enemy->dist_stop = 20;
		enemy->dist_damage = 50;
		enemy->dist_visu = 640;
		enemy->speed = 3;
	}
	else if (c == WOLF)
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
		enemy->speed = 3;
	}
	else if (c == BIRD)
	{
		fill_bird(data, enemy);
	}
	else if (c == SNAKE)
		fill_snake(data, enemy);
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
	(void)data;
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
