/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:49:18 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:49:19 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "utils_bonus.h"
#include <math.h>

double	calc_dist_attraction(t_item *attract, t_enemy *enemy)
{
	double	dist_y;
	double	dist_x;
	double	distance;

	dist_x = (attract->center.case_x * 64 + attract->center.coo_x)
		- (enemy->center.case_x * 64 + enemy->center.coo_x);
	dist_y = (attract->center.case_y * 64 + attract->center.coo_y)
		- (enemy->center.case_y * 64 + enemy->center.coo_y);
	distance = sqrt(dist_x * dist_x + dist_y * dist_y);
	return (distance);
}

bool	item_destruction(t_item *item, t_data *data)
{
	if ((try_hit_items(item, data) && ((item->type != BH
					&& item->type != ANIM_DEATH && item->categ)
				|| (item->type != VENTUS && item->type != EXPECTO_PATRONUM
					&& !item->categ)))
		|| (item->center.case_y >= data->map.tabmap_height
			|| item->center.case_y < 0
			|| item->center.case_x >= ft_strlen(data->map.tabmap
				[item->center.case_y])
			|| item->center.case_x < 0)
		|| data->map.tabmap[item->center.case_y][item->center.case_x] == ' '
		|| data->map.tabmap[item->center.case_y][item->center.case_x] == '1')
		return (true);
	if ((item->type == VENTUS && !item->categ && item->nb_move >= 400)
		|| (item->type == ANIM_DEATH && item->categ && item->nb_move >= 10)
		|| (item->type == EXPECTO_PATRONUM && !item->categ
			&& item->nb_move >= 300) || (item->type == BH && item->categ
			&& item->nb_move >= 200))
		return (true);
	return (false);
}

void	define_item_radius(t_item *item, t_data *data)
{
	item->deg += item->deg_rotate;
	item->rad = item->deg * (M_PI / 180);
	if (item->type == BH && item->categ)
		item->radius += .1;
	if (item->type == EXPECTO_PATRONUM && !item->categ)
		item->radius += .3;
	else if (item->type == ANIM_DEATH && item->categ)
		item->radius += 1.5;
	if (item->type == VENTUS && !item->categ)
		item->radius += .1;
	else if (item->type == PILLAR && item->categ)
		calc_deg(&data->player.coo, &item->center, &item->rad, &item->deg);
}

void	save_item_last_pos(t_item *item)
{
	item->left_before.coo_x = item->left.coo_x;
	item->left_before.coo_y = item->left.coo_y;
	item->left_before.case_x = item->left.case_x;
	item->left_before.case_y = item->left.case_y;
	item->right_before.coo_x = item->right.coo_x;
	item->right_before.coo_y = item->right.coo_y;
	item->right_before.case_x = item->right.case_x;
	item->right_before.case_y = item->right.case_y;
	item->center_before.coo_x = item->center.coo_x;
	item->center_before.coo_y = item->center.coo_y;
	item->center_before.case_x = item->center.case_x;
	item->center_before.case_y = item->center.case_y;
}
