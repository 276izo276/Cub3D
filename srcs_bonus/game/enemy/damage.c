/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:47:41 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:47:42 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "enemy_bonus.h"

void	damage_poison_fire(t_enemy *enemy)
{
	if (enemy->damage.poison_frame_take > 0 && enemy->type != SPIDER)
	{
		enemy->life -= enemy->damage.poison_force_take;
		enemy->damage.poison_frame_take--;
		if (enemy->damage.poison_frame_take <= 0)
			enemy->damage.poison_force_take = 0;
	}
	if (enemy->damage.fire_frame_take > 0 && enemy->type != ELEM)
	{
		enemy->life -= enemy->damage.fire_force_take;
		enemy->damage.fire_frame_take--;
		if (enemy->damage.fire_frame_take <= 0)
			enemy->damage.fire_force_take = 0;
	}
	if (enemy->type == ELEM)
		enemy->life -= enemy->damage.damage_elem_take;
	if (enemy->type == SPIDER)
		enemy->life -= enemy->damage.damage_spider_take;
	if (enemy->type == SNAKE)
		enemy->life -= enemy->damage.damage_snake_take;
	if (enemy->type == DEMENTOR)
		enemy->life -= enemy->damage.damage_dementor_take;
}

void	take_damage_enemy(t_enemy *enemy)
{
	enemy->life -= enemy->damage.damage_take;
	enemy->damage.damage_take = 0;
	damage_poison_fire(enemy);
	if (enemy->type != DEMENTOR)
	{
		if (enemy->damage.curse_frame_take > 0)
		{
			enemy->life -= enemy->damage.curse_force_take;
			enemy->damage.curse_frame_take--;
			if (enemy->damage.curse_frame_take <= 0)
				enemy->damage.curse_force_take = 0;
		}
	}
	if (enemy->type == SNAKE)
	{
		enemy->life -= enemy->damage.damage_snake_take;
		enemy->damage.damage_snake_take = 0;
	}
}

void	death_sorcerer(t_enemy *enemy, t_data *data)
{
	if (enemy->type == NANCY)
		data->sorcerer[0].is_alive = false;
	else if (enemy->type == PILO)
		data->sorcerer[3].is_alive = false;
	else if (enemy->type == ZIPPY)
		data->sorcerer[1].is_alive = false;
	else if (enemy->type == KUNFANDI)
		data->sorcerer[2].is_alive = false;
	else if (enemy->type == DIRLO)
		data->sorcerer[6].is_alive = false;
	else if (enemy->type == STEF)
		data->sorcerer[7].is_alive = false;
	else if (enemy->type == MARINA)
		data->sorcerer[8].is_alive = false;
	else if (enemy->type == ANAIS)
		data->sorcerer[5].is_alive = false;
	else if (enemy->type == CAMEO)
		data->sorcerer[4].is_alive = false;
}

int	low_life_enemy(t_enemy *enemy, t_data *data, t_lst **lst)
{
	t_lst	*next;

	if (enemy->life <= 0)
	{
		if (enemy->type != SNAKE && enemy->type != BIRD)
		{
			data->item = add_end_lst(create_item(data, ANIM_DEATH,
						&(t_fcoo){.case_x = enemy->center.case_x,
						.case_y = enemy->center.case_y,
						.coo_y = enemy->center.coo_y,
						.coo_x = enemy->center.coo_x}, data->map.mini.deg),
					data->item, f_item);
			if (enemy->damage.which_coa_take == data->player.coa)
				spawn_item(data, enemy);
		}
		add_sound_xp(enemy, data);
		death_sorcerer(enemy, data);
		next = (*lst)->next;
		data->enemy = remove_elem_lst(*lst);
		f_elem_lst(*lst);
		data->nb_enemy--;
		*lst = next;
		return (1);
	}
	return (0);
}
