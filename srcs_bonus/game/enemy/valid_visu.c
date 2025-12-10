/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:48:35 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:48:36 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <stdlib.h>
#include "time_bonus.h"
#include "enemy_bonus.h"
#include <math.h>

void	see_target(t_enemy *enemy, t_data *data, t_enemy_vision *visu)
{
	if (attack_dist(enemy, data, visu))
		;
	else if (rand() % 1000 < 50 && get_mtime() > enemy->time_attack_dist
		+ enemy->cooldown_dist * 1000)
	{
		enemy->time_attack_dist = get_mtime();
		if (enemy->type == SPIDER)
		{
			data->item = add_end_lst(create_item(data, WEB_SPIDER,
						&enemy->center, visu->deg + 180), data->item, f_item);
			((t_item *)data->item->dt)->damage.which_coa_do = OTHERS;
		}
		else if (enemy->type == ELEM)
		{
			data->item = add_end_lst(create_item(data, FIREBALL_ELEM,
						&enemy->center, visu->deg + 180), data->item, f_item);
			((t_item *)data->item->dt)->damage.which_coa_do = OTHERS;
		}
	}
	if (enemy->recalc_path <= 50 || !enemy->way)
		enemy->recalc_path = 100;
	if (visu->dist_min_player == visu->dist_min)
		enemy->calc_path = 30;
	else
		enemy->calc_path = 0;
}

void	visu_enemy_valid(t_data *data, t_enemy_vision *visu, t_enemy *enemy)
{
	int	diff_player_x;
	int	diff_player_y;

	calc_deg(&visu->coo, &enemy->center, &visu->rad, &visu->deg);
	diff_player_x = visu->coo.case_x * 64 + visu->coo.coo_x
		- enemy->center.case_x * 64 - enemy->center.coo_x;
	diff_player_y = visu->coo.case_y * 64 + visu->coo.coo_y
		- enemy->center.case_y * 64 - enemy->center.coo_y;
	visu->dist_min_player = sqrt(diff_player_x * diff_player_x + diff_player_y
			* diff_player_y);
	enemy->dist_target = visu->dist_min;
	if (enemy->dist_target < enemy->dist_visu)
		see_target(enemy, data, visu);
	if (enemy->dist_target < enemy->dist_damage
		&& get_mtime() > enemy->time_attack_cac + enemy->cooldown_cac * 1000)
	{
		enemy->time_attack_cac = get_mtime();
		if (visu->dist_min == visu->dist_min_player)
			apply_damage(&data->player.damage, &enemy->damage);
		else if (visu->keep_elem)
			apply_damage(&visu->keep_elem->damage, &enemy->damage);
	}
	recalc_path(enemy, visu, data);
}
