#include "struct_bonus.h"

#include <stdio.h>

void	apply_damage(t_damage *take, t_damage *apply)
{
	take->damage_take += apply->damage_do;
	take->damage_spider_take += apply->damage_spider_do;
	take->damage_dementor_take += apply->damage_dementor_do;
	if (take->slow_force_take < take->slow_force_do)
	{
		take->slow_force_take = apply->slow_force_do;
		take->slow_frame_take = apply->slow_frame_do;
	}
	if (take->poison_force_take < take->poison_force_do)
	{
		take->poison_force_take = apply->poison_force_do;
		take->poison_frame_take = apply->poison_frame_do;
	}
	if (take->fire_force_take < apply->fire_force_do)
	{
		take->fire_force_take = apply->fire_force_do;
		take->fire_frame_take = apply->fire_frame_do;
	}
	if (take->curse_force_take < take->curse_force_do)
	{
		take->curse_force_take = apply->curse_force_do;
		take->curse_frame_take = apply->curse_frame_do;
	}
	if (apply->confundo_force_take < apply->confundo_force_do)
	{
		take->confundo_force_take = apply->confundo_force_do;
		take->confundo_frame_take = apply->confundo_frame_do;
	}
	if (take->repulso_force_take < apply->repulso_force_do)
	{
		take->repulso_force_take = apply->repulso_force_do;
		take->repulso_frame_take = apply->repulso_frame_do;
	}
	if (take->repulso_force_take > 0)
	{
		take->hit.case_x = apply->hit.case_x;
		take->hit.case_y = apply->hit.case_y;
		take->hit.coo_x = apply->hit.coo_x;
		take->hit.coo_y = apply->hit.coo_y;
	}
}
