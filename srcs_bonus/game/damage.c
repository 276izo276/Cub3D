/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:51:40 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:51:41 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	apply_slow_frame(t_damage **take, t_damage **apply)
{
	if ((*take)->slow_frame_take < (*apply)->slow_frame_do)
		(*take)->slow_frame_take = (*apply)->slow_frame_do;
	if ((*take)->poison_frame_take < (*apply)->poison_frame_do)
		(*take)->poison_frame_take = (*apply)->poison_frame_do;
	if ((*take)->fire_frame_take < (*apply)->fire_frame_do)
		(*take)->fire_frame_take = (*apply)->fire_frame_do;
	if ((*take)->curse_frame_take < (*apply)->curse_frame_do)
		(*take)->curse_frame_take = (*apply)->curse_frame_do;
	if ((*take)->confundo_frame_take < (*apply)->confundo_frame_do)
		(*take)->confundo_frame_take = (*apply)->confundo_frame_do;
	if ((*take)->repulso_frame_take < (*apply)->repulso_frame_do)
		(*take)->repulso_frame_take = (*apply)->repulso_frame_do;
}

void	apply_damage(t_damage *take, t_damage *apply)
{
	take->which_coa_take = apply->which_coa_do;
	take->damage_take += apply->damage_do;
	take->damage_spider_take += apply->damage_spider_do;
	take->damage_dementor_take += apply->damage_dementor_do;
	take->damage_snake_take += apply->damage_snake_do;
	take->damage_elem_take += apply->damage_elem_do;
	if (take->slow_force_take < apply->slow_force_do)
		take->slow_force_take = apply->slow_force_do;
	if (take->poison_force_take < apply->poison_force_do)
		take->poison_force_take = apply->poison_force_do;
	if (take->fire_force_take < apply->fire_force_do)
		take->fire_force_take = apply->fire_force_do;
	if (take->curse_force_take < apply->curse_force_do)
		take->curse_force_take = apply->curse_force_do;
	if (take->confundo_force_take < apply->confundo_force_do)
		take->confundo_force_take = apply->confundo_force_do;
	if (take->repulso_force_take < apply->repulso_force_do)
	{
		take->repulso_force_take = apply->repulso_force_do;
		take->hit.case_x = apply->hit.case_x;
		take->hit.case_y = apply->hit.case_y;
		take->hit.coo_x = apply->hit.coo_x;
		take->hit.coo_y = apply->hit.coo_y;
	}
	apply_slow_frame(&take, &apply);
}

void	damage_effect(t_data *data)
{
	data->player.damage.damage_take = 0;
	if (data->player.damage.poison_frame_take > 0)
	{
		data->player.life -= data->player.damage.poison_force_take;
		data->player.damage.poison_frame_take--;
		if (data->player.damage.poison_frame_take <= 0)
			data->player.damage.poison_force_take = 0;
	}
	if (data->player.damage.fire_frame_take > 0)
	{
		data->player.life -= data->player.damage.fire_force_take;
		data->player.damage.fire_frame_take--;
		if (data->player.damage.fire_frame_take <= 0)
			data->player.damage.fire_force_take = 0;
	}
	if (data->player.damage.curse_frame_take > 0)
	{
		data->player.life -= data->player.damage.curse_force_take;
		data->player.damage.curse_frame_take--;
		if (data->player.damage.curse_frame_take <= 0)
			data->player.damage.curse_force_take = 0;
	}
	if (data->player.life <= 0)
		data->player.life -= 1;
}

void	take_damage(t_data *data)
{
	double	damage;

	damage = data->player.damage.damage_take;
	while (damage > 0 && data->player.protego > 0)
	{
		damage -= 5;
		data->player.protego--;
	}
	if (damage < 0)
		damage = 0;
	data->player.shield -= damage;
	if (data->player.shield < 0)
	{
		data->player.life += data->player.shield;
		data->player.shield = 0;
	}
	damage_effect(data);
	if (data->player.life <= -115)
	{
		sound_dead(data);
		data->status = MENU_DEATH;
		data->selected = 0;
	}
}
