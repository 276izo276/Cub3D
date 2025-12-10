/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_enemy_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:47:52 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:47:53 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include <math.h>

void	set_before_point_enemy(t_enemy *enemy, t_data *data)
{
	calc_left_and_right_point(enemy, data);
	enemy->center_before.coo_x = enemy->center.coo_x;
	enemy->center_before.coo_y = enemy->center.coo_y;
	enemy->center_before.case_x = enemy->center.case_x;
	enemy->center_before.case_y = enemy->center.case_y;
	enemy->left_before.coo_x = enemy->left.coo_x;
	enemy->left_before.coo_y = enemy->left.coo_y;
	enemy->left_before.case_x = enemy->left.case_x;
	enemy->left_before.case_y = enemy->left.case_y;
	enemy->right_before.coo_x = enemy->right.coo_x;
	enemy->right_before.coo_y = enemy->right.coo_y;
	enemy->right_before.case_x = enemy->right.case_x;
	enemy->right_before.case_y = enemy->right.case_y;
}

void	reverse_hit_pos(t_enemy *enemy, t_item *item)
{
	double	deg;
	double	rad;
	double	dx;
	double	dy;
	double	v_normalize;

	calc_deg(&enemy->center_before, &enemy->center, &rad, &deg);
	rad = (deg + 180) * (M_PI / 180);
	dx = sin(rad);
	dy = cos(rad);
	if (round(dy) == 0.0 && round(dx) == 0.0)
	{
		dy = 0;
		dx = 0;
	}
	else
	{
		v_normalize = sqrt(dx * dx + dy * dy);
		dy = dy / v_normalize;
		dx = dx / v_normalize;
	}
	dx *= 2000;
	dy *= 2000;
	item->damage.hit.coo_x += dx;
	item->damage.hit.coo_y += dy;
}

void	move_more_hit_pos(t_enemy *enemy, t_item *item)
{
	double	deg;
	double	rad;
	double	dx;
	double	dy;
	double	v_normalize;

	calc_deg(&enemy->center_before, &enemy->center, &rad, &deg);
	dx = sin(rad);
	dy = cos(rad);
	if (round(dy) == 0.0 && round(dx) == 0.0)
	{
		dy = 0;
		dx = 0;
	}
	else
	{
		v_normalize = sqrt(dx * dx + dy * dy);
		dy = dy / v_normalize;
		dx = dx / v_normalize;
	}
	dx *= 2000;
	dy *= 2000;
	item->damage.hit.coo_x += dx;
	item->damage.hit.coo_y += dy;
}
