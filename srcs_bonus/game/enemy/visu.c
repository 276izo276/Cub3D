#include "cub3d_bonus.h"
#include <math.h>
#include "enemy_bonus.h"

int	vision_case_continue(t_enemy *enemy, t_enemy **elem, t_lst **lst)
{
	*elem = (*lst)->dt;
	*lst = (*lst)->next;
	if (enemy->type == BIRD)
	{
		if ((*elem)->type == BIRD)
			return (1);
	}
	else if (is_sorcerer(enemy->type) == true
		&& (*elem)->color_coa == enemy->color_coa)
		return (1);
	else if (enemy->type == SNAKE && (*elem)->type == SNAKE)
		return (1);
	else if (is_sorcerer(enemy->type) == false
		&& is_sorcerer((*elem)->type) == false && enemy->type != SNAKE)
		return (1);
	return (0);
}

void	case_in_visu(t_enemy_vision *visu, t_enemy *elem, t_enemy *enemy,
		t_data *data)
{
	if ((visu->deg + 360 >= elem->deg - 90 + 360 && visu->deg + 360 <= elem->deg
			+ 90 + 360) || enemy->calc_path > 0)
	{
		fill_ray_enemy(enemy, &visu->ray, visu->deg);
		launch_ray_enemy(&visu->ray, data);
		calc_dist_wall(&visu->ray);
		calc_dist_target(enemy, elem, &visu->ray);
		if (enemy->dist_target < visu->ray.dist_wall || enemy->calc_path > 0)
		{
			if (enemy->dist_target < visu->dist_min || visu->dist_min == -1)
			{
				visu->type = elem->type;
				visu->keep_elem = elem;
				visu->dist_min = enemy->dist_target;
				visu->coo.case_x = elem->center.case_x;
				visu->coo.case_y = elem->center.case_y;
				visu->coo.coo_y = elem->center.coo_y;
				visu->coo.coo_x = elem->center.coo_x;
			}
		}
	}
}

void	calc_dist_min_player(t_data *data, t_enemy *enemy, t_enemy_vision *visu)
{
	int	diff_player_x;
	int	diff_player_y;

	diff_player_x = data->player.coo.case_x * 64 + data->player.coo.coo_x
		- enemy->center.case_x * 64 - enemy->center.coo_x;
	diff_player_y = data->player.coo.case_y * 64 + data->player.coo.coo_y
		- enemy->center.case_y * 64 - enemy->center.coo_y;
	visu->dist_min_player = sqrt(diff_player_x * diff_player_x + diff_player_y
			* diff_player_y);
}

void	case_in_visu_player(t_enemy_vision *visu, t_enemy *enemy, t_data *data)
{
	if ((visu->deg + 360 >= enemy->deg - 90 + 360 && visu->deg
			+ 360 <= enemy->deg + 90 + 360) || enemy->calc_path > 0)
	{
		fill_ray_enemy(enemy, &visu->ray, visu->deg);
		launch_ray_enemy(&visu->ray, data);
		calc_dist_wall(&visu->ray);
		if (visu->dist_min_player < visu->ray.dist_wall || enemy->calc_path > 0)
		{
			if (visu->dist_min_player < visu->dist_min
				|| visu->dist_min_player < 256 || visu->dist_min == -1)
			{
				visu->dist_min = visu->dist_min_player;
				visu->type = -1;
				visu->coo.case_x = data->player.coo.case_x;
				visu->coo.case_y = data->player.coo.case_y;
				visu->coo.coo_y = data->player.coo.coo_y;
				visu->coo.coo_x = data->player.coo.coo_x;
			}
		}
	}
}

int	enemy_vision(t_data *data, t_enemy *enemy)
{
	t_lst			*lst;
	t_enemy			*elem;
	t_enemy_vision	visu;

	visu.dist_min = -1;
	visu.keep_elem = NULL;
	visu.dist_min_player = -1;
	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		if (vision_case_continue(enemy, &elem, &lst))
			continue ;
		calc_deg(&elem->center, &enemy->center, &visu.rad, &visu.deg);
		case_in_visu(&visu, elem, enemy, data);
	}
	if (enemy->type != BIRD && enemy->nb_move >= 10
		&& data->player.invisible == 255)
	{
		calc_deg(&data->player.coo, &enemy->center, &visu.rad, &visu.deg);
		calc_dist_min_player(data, enemy, &visu);
		case_in_visu_player(&visu, enemy, data);
	}
	if (visu.dist_min != -1)
		visu_enemy_valid(data, &visu, enemy);
	return (0);
}
