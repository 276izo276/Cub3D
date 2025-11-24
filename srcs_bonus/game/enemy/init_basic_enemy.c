#include "struct_bonus.h"

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
	enemy->drop_wolf_wand = 1;
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
	enemy->drop_elem_wand = 1;
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
	enemy->drop_spider_wand = 1;
}
