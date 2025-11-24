#include "struct_bonus.h"
#include "utils_bonus.h"
#include "enemy_bonus.h"
#include "cub3d_bonus.h"
#include "color_bonus.h"

#include <stdio.h>

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
	enemy->drop_dementor_wand = 1;
}

t_enemy	*init_enemy(char c, t_fcoo coo, t_data *data, double deg)
{
	t_enemy	*enemy;

	data->nb_enemy++;
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
	enemy->damage.which_coa_do = OTHERS;
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
	enemy->center_before.coo_x = enemy->center.coo_x;
	enemy->center_before.coo_y = enemy->center.coo_y;
	enemy->center_before.case_x = enemy->center.case_x;
	enemy->center_before.case_y = enemy->center.case_y;
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
