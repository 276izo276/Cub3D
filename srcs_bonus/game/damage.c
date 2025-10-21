#include "struct_bonus.h"

void	apply_damage(t_damage *take, t_damage *apply)
{
	take->damage_take += apply->damage_do;
	take->damage_spider_take += apply->damage_spider_do;
	take->damage_dementor_take += apply->damage_dementor_do;
	take->slow_force_take += apply->slow_force_do;
	take->slow_frame_take += apply->slow_frame_do;
	take->poison_force_take += apply->poison_force_do;
	take->poison_frame_take += apply->poison_frame_do;
	take->fire_force_take += apply->fire_force_do;
	take->fire_frame_take += apply->fire_frame_do;
	take->curse_force_take += apply->curse_force_do;
	take->curse_frame_take += apply->curse_frame_do;
}