#include "struct_bonus.h"
#include "utils_bonus.h"
#include "enemy_bonus.h"
#include "cub3d_bonus.h"
#include "time_bonus.h"
#include <math.h>
#include "color_bonus.h"

#include <stdio.h>

static int	man_dist(int startY, int startX, int endY, int endX)
{
	return (abs_value(startY - endY) + abs_value(startX - endX));
}

static int	is_a_wall(t_case *cur, const int dir[2], t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
			++x;
		++y;
	}
	if (cur->case_y + dir[0] >= y || cur->case_x + dir[1] >= x
		|| cur->case_y + dir[0] < 0 || cur->case_x + dir[1] < 0)
		return (1);
	if (!(cur->case_y + dir[0] >= data->map.tabmap_height
		|| cur->case_y + dir[0] < 0
		|| cur->case_x + dir[1] >= ft_strlen(data->map.tabmap[cur->case_y
			+ dir[0]]) || cur->case_x + dir[1] < 0
		|| data->map.tabmap[cur->case_y + dir[0]][cur->case_x
			+ dir[1]] == ' ') && data->map.tabmap[cur->case_y
				+ dir[0]][cur->case_x + dir[1]] == '1')
		return (1);
	return (0);
}

static int	is_in_lst(t_case *cur, const int dir[2], t_lst *lst, t_enemy *enemy)
{
	t_case	*cel;

	lst = get_first_elem_lst(lst);
	(void)enemy;
	while (lst)
	{
		cel = lst->dt;
		if (cel->case_x == cur->case_x + dir[1] && cel->case_y == cur->case_y + dir[0])
		{
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static t_lst	*update_node(t_case *cur, const int dir[2], t_lst *lst)
{
	t_case	*cel;
	t_lst	*save;

	lst = get_first_elem_lst(lst);
	while (lst)
	{
		cel = lst->dt;
		if (cel->case_x == cur->case_x + dir[1] && cel->case_y == cur->case_y + dir[0])
		{
			if (cur->t_cost + 1 < cel->t_cost)
			{
				cel->parent = cur;
				cel->r_cost = cur->r_cost + 1;
				cel->t_cost = cel->r_cost + cel->h_cost;
				save = lst;
				lst = remove_elem_lst(save);
				lst = get_first_elem_lst(lst);
				if (!lst)
				{
					return (move_to_end_lst(save,lst));
				}
				while (lst)
				{
					if (((t_case *)lst->dt)->t_cost > cel->t_cost)
					{
						move_before_lst(save, lst);
						return (lst);
					}
					if (!lst->next)
					{
						lst = move_to_end_lst(save, lst);
						return (lst);
					}
					lst = lst->next;
				}
			}
			return (lst);
		}
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	return (lst);
}

static t_lst	*add_node(t_case *cur, const int dir[2], t_lst *lst, t_enemy *enemy)
{
	t_case	*cel;
	const int	direc[2] = {cur->case_y + dir[0], cur->case_x + dir[1]};

	cel = init_case(man_dist(cur->case_y + dir[0],
		cur->case_x + dir[1], enemy->goal.case_y,enemy->goal.case_x),cur->r_cost + 1,
		(int *)direc, cur);
	if (!lst)
	{
		lst = add_end_lst(cel, lst, f_case);
		return (lst);
	}
	lst = get_first_elem_lst(lst);
	while (lst)
	{
		if (((t_case *)lst->dt)->t_cost == cel->t_cost)
		{
			if (rand() % 10 == 1)
			{
				return(add_before_lst(cel, lst, f_case));
			}
		}
		if (((t_case *)lst->dt)->t_cost > cel->t_cost)
		{
			return(add_before_lst(cel, lst, f_case));
		}
		if (!lst->next)
			return(add_end_lst(cel, lst, f_case));
		lst = lst->next;
	}
	return (lst);
}

static void	exit_path_finder(t_data *data)
{
	f_exit(data, 1);
}

static	t_lst	*add_case_open(t_lst *open, t_lst **closed, t_enemy *enemy, t_data *data)
{
	const int	dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
	int		i;
	t_lst	*lst;

	lst = get_first_elem_lst(open);
	open = remove_elem_lst(lst);
	open = get_first_elem_lst(open);
	*closed = move_to_end_lst(lst, *closed);
	i = 0;
	while (i < 4)
	{
		if (!is_a_wall(lst->dt, dir[i], data) && !is_in_lst(lst->dt, dir[i], *closed, enemy))
		{
			if (is_in_lst(lst->dt, dir[i], open, enemy))
				open = update_node(lst->dt, dir[i], open);
			else
				open = add_node(lst->dt, dir[i], open, enemy);
			if (!open)
				exit_path_finder(data);
		}
		i++;
	}
	return (get_first_elem_lst(open));
}

static int	is_end_path(t_lst *open, t_enemy *enemy)
{
	open = get_first_elem_lst(open);
	if (((t_case *)open->dt)->case_x == enemy->goal.case_x
		&& ((t_case *)open->dt)->case_y == enemy->goal.case_y)
		return (1);
	return (0);
}

static void	set_final_path(t_lst *lst, t_enemy *enemy)
{
	t_case	*cel;

	if (!lst)
		return ;
	cel = lst->dt;
	cel->is_path = 1;
	while (cel->parent)
	{
		cel->parent->child = cel;
		cel->parent->is_path = 1;
		cel = cel->parent;
	}
	enemy->way = cel;
	while (cel->child)
	{
		cel = cel->child;
	}
	enemy->goal.case_x = cel->case_x;
	enemy->goal.case_y = cel->case_y;
}

static void	pathfinder(t_data *data, t_enemy *enemy)
{
	t_lst	*open;
	t_lst	*closed;
	const int	dir[2] = {enemy->center.case_y, enemy->center.case_x};

	open = add_end_lst(init_case(man_dist(enemy->center.case_y,
		enemy->center.case_x,enemy->goal.case_y,enemy->goal.case_x),
		0, (int *)dir, NULL), NULL, f_case);
	closed = NULL;
	if (open && is_end_path(open, enemy))
	{
		set_final_path(get_first_elem_lst(open), enemy);
		f_list_final_path(open, closed);
		return ;
	}
	while (open)
	{
		open = add_case_open(open, &closed, enemy, data);
		if (open && is_end_path(open, enemy))
		{
			set_final_path(get_first_elem_lst(open), enemy);
			f_list_final_path(open, closed);
			return ;
		}
		open = get_first_elem_lst(open);
	}
	int	nb_elem_lst = ft_strlen_lst(closed);
	int	nb_take = rand() % nb_elem_lst;
	nb_elem_lst = 0;
	closed = get_first_elem_lst(closed);
	while (closed->next)
	{
		if (nb_elem_lst == nb_take)
		{
			set_final_path(closed, enemy);
			f_list_final_path(open, closed);
			return;
		}
		nb_elem_lst++;
		closed = closed->next;
	}
	f_all_lst(closed);
	f_all_lst(open);
}

static void	print_path(t_enemy *enemy)
{
	t_case	*cel;

	cel = enemy->way;
	while (cel)
		cel = cel->child;
}

static void	calc_in_cell_path(t_data *data, t_enemy *enemy)
{
	t_case	*cel;

	cel = enemy->way;
	while (cel)
	{
		if (cel->child)
		{
			cel->coo_x = 32 + (cel->child->case_x - cel->case_x) * 32;
			cel->coo_y = 32 + (cel->child->case_y - cel->case_y) * 32;
			if (cel->child->child)
			{
				if (cel->coo_x % 64 != 0)
				{
					if (cel->parent)
						if (cel->parent->coo_x % 64 == 0)
							cel->coo_x = 64 - cel->parent->coo_x;
						else
							cel->coo_x = cel->parent->coo_x;
					else
						cel->coo_x = 32;
					cel->coo_x = (cel->coo_x + 32 + (cel->child->child->case_x - cel->child->case_x) * 32) / 2;
				}
				if (cel->coo_y % 64 != 0)
				{
					if (cel->parent)
						if (cel->parent->coo_y % 64 == 0)
							cel->coo_y = 64 - cel->parent->coo_y;
						else
							cel->coo_y = cel->parent->coo_y;
					else
						cel->coo_y = 32;
					cel->coo_y = (cel->coo_y + 32 + (cel->child->child->case_y - cel->child->case_y) * 32) / 2;
				}
			}
			else
			{
				if (cel->coo_x % 64 != 0)
				{
					if (cel->parent)
						if (cel->parent->coo_x % 64 == 0)
							cel->coo_x = 64 - cel->parent->coo_x;
						else
							cel->coo_x = cel->parent->coo_x;
					else
						cel->coo_x = enemy->center.coo_x;
					cel->coo_x = (cel->coo_x + 32 + (cel->child->case_x - cel->case_x) * 32) / 2;
				}
				if (cel->coo_y % 64 != 0)
				{
					if (cel->parent)
						if (cel->parent->coo_y % 64 == 0)
							cel->coo_y = 64 - cel->parent->coo_y;
						else
							cel->coo_y = cel->parent->coo_y;
					else
						cel->coo_y = enemy->center.coo_y;
					cel->coo_y = (cel->coo_y + enemy->goal.coo_y) / 2;
				}
			}
		}
		else
		{
			cel->coo_x = enemy->goal.coo_x;
			cel->coo_y = enemy->goal.coo_y;
		}
		cel = cel->child;
	}
	(void)data;
}

static void	gen_enemy_way(t_data *data, t_enemy *enemy)
{
	int	x;
	int	y;
	int	count;
	int	len_line;
	int	len_tab;

	if (enemy->wait < 10)
	{
		enemy->wait++;
		return ;
	}
	len_tab = ft_tab_strlen(data->map.tabmap) - 1;
	y = rand() % len_tab;
	len_line = ft_strlen(data->map.tabmap[y]);
	x = rand() % len_line;
	count = 0;
	while (data->map.tabmap[y][x] != '0')
	{
		x++;
		x = x % len_line;
		count++;
		if (count >= len_line)
		{
			len_tab = ft_tab_strlen(data->map.tabmap) - 1;
			y = rand() % (len_tab);
			len_line = ft_strlen(data->map.tabmap[y]);
			x = rand() % len_line;
		}
	}
	enemy->goal.case_x = x;
	enemy->goal.case_y = y;
	enemy->goal.coo_y = 32;
	enemy->goal.coo_x = 32;
	pathfinder(data, enemy);
	calc_in_cell_path(data, enemy);
	print_path(enemy);
}

void	calc_left_point(t_enemy *enemy)
{
	double	dx;
	double	dy;
	double	v_normalize;
	double	aff_rad;

	aff_rad = enemy->aff_rad + (90 * (M_PI / 180));
	dx = sin(aff_rad);
	dy = cos(aff_rad);
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
	dy *= enemy->radius;
	dx *= enemy->radius;
	enemy->left.coo_x = enemy->center.coo_x + dx;
	enemy->left.coo_y = enemy->center.coo_y + dy;
	enemy->left.case_x = enemy->center.case_x;
	enemy->left.case_y = enemy->center.case_y;
	if (enemy->left.coo_x < 0)
	{
		enemy->left.case_x--;
		enemy->left.coo_x += 64;
	}
	else if (enemy->left.coo_x > 64)
	{
		enemy->left.case_x++;
		enemy->left.coo_x = fmod(enemy->left.coo_x, 64);
	}
	if (enemy->left.coo_y < 0)
	{
		enemy->left.case_y--;
		enemy->left.coo_y += 64;
	}
	else if (enemy->left.coo_y > 64)
	{
		enemy->left.case_y++;
		enemy->left.coo_y = fmod(enemy->left.coo_y, 64);
	}
}

void	calc_right_point(t_enemy *enemy)
{
	double	dy;
	double	dx;
	double	v_normalize;
	double	aff_rad;

	aff_rad = enemy->aff_rad - (90 * (M_PI / 180));
	dx = sin(aff_rad);
	dy = cos(aff_rad);
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
	dy *= enemy->radius;
	dx *= enemy->radius;
	enemy->right.coo_x = enemy->center.coo_x + dx;
	enemy->right.coo_y = enemy->center.coo_y + dy;
	enemy->right.case_x = enemy->center.case_x;
	enemy->right.case_y = enemy->center.case_y;
	if (enemy->right.coo_x < 0)
	{
		enemy->right.case_x--;
		enemy->right.coo_x += 64;
	}
	else if (enemy->right.coo_x > 64)
	{
		enemy->right.case_x++;
		enemy->right.coo_x = fmod(enemy->right.coo_x, 64);
	}
	if (enemy->right.coo_y < 0)
	{
		enemy->right.case_y--;
		enemy->right.coo_y += 64;
	}
	else if (enemy->right.coo_y > 64)
	{
		enemy->right.case_y++;
		enemy->right.coo_y = fmod(enemy->right.coo_y, 64);
	}
}

void	calc_left_and_right_point(t_enemy *enemy, t_data *data)
{
	double	diff_x;
	double	diff_y;
	int		cy;
	int		cx;
	int		new_x;
	int		new_y;

	enemy->aff_deg = 0;
	enemy->aff_rad = 0;
	diff_x = (data->player.coo.case_x * 64 + data->player.coo.coo_x) - (enemy->center.case_x * 64 + enemy->center.coo_x);
	diff_y = (data->player.coo.case_y * 64 + data->player.coo.coo_y) - (enemy->center.case_y * 64 + enemy->center.coo_y);
	if (diff_y != 0)
	{
		enemy->aff_deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
		if (enemy->aff_deg < 0)
			enemy->aff_deg = -enemy->aff_deg;
	}
	if (diff_y < 0 && diff_x < 0)
		enemy->aff_deg = 180 + enemy->aff_deg;
	else if (diff_y < 0 && diff_x > 0)
		enemy->aff_deg = 180 - enemy->aff_deg;
	else if (diff_y > 0 && diff_x < 0)
		enemy->aff_deg = 360 - enemy->aff_deg;
	else if (diff_y == 0 && diff_x < 0)
		enemy->aff_deg = 270;
	else if (diff_y == 0 && diff_x > 0)
		enemy->aff_deg = 90;
	else if (diff_x == 0 && diff_y < 0)
		enemy->aff_deg = 180;
	enemy->aff_deg = enemy->aff_deg;
	enemy->aff_rad = enemy->aff_deg * (M_PI / 180);
	calc_left_point(enemy);
	calc_right_point(enemy);

	if (enemy->left.case_y < 0 || enemy->left.case_y > data->map.tabmap_height || enemy->left.case_x < 0 || enemy->left.case_x >= ft_strlen(data->map.tabmap[enemy->left.case_y]) || data->map.tabmap[enemy->left.case_y][enemy->left.case_x] == '1')
	{
		cx = enemy->center.case_x - enemy->left.case_x;
		cy = enemy->center.case_y - enemy->left.case_y;
		new_x = enemy->left.case_x + cx;
		new_y = enemy->left.case_y + cy;
		if (cy != 0 && !(new_y < 0 || new_y > data->map.tabmap_height || enemy->left.case_x < 0 || enemy->left.case_x >= ft_strlen(data->map.tabmap[new_y])) && data->map.tabmap[new_y][enemy->left.case_x] != '1')
		{
			double	diff;
			diff = 0;
			if (cy > 0)
				diff = 64 - enemy->left.coo_y;
			else if (cy < 0)
				diff = -enemy->left.coo_y - 0.001;
			enemy->right.coo_y += diff;
			enemy->center.coo_y += diff;
			enemy->left.coo_y = fmod(enemy->left.coo_y + diff + 64, 64);
			enemy->left.case_y += cy;
		}
		else if (cx != 0 && !(enemy->left.case_y < 0 || enemy->left.case_y > data->map.tabmap_height || new_x < 0 || new_x >= ft_strlen(data->map.tabmap[enemy->left.case_y])) && data->map.tabmap[enemy->left.case_y][new_x] != '1')
		{
			double	diff;

			diff = 0;
			if (cx > 0)
				diff = 64 - enemy->left.coo_x;
			else if (cx < 0)
				diff = -enemy->left.coo_x - 0.001;
			enemy->right.coo_x += diff;
			enemy->center.coo_x += diff;
			enemy->left.coo_x = fmod(enemy->left.coo_x + diff + 64, 64);
			enemy->left.case_x += cx;
		}
	}
	if (enemy->right.case_y < 0 || enemy->right.case_y > data->map.tabmap_height || enemy->right.case_x < 0 || enemy->right.case_x >= ft_strlen(data->map.tabmap[enemy->right.case_y]) || data->map.tabmap[enemy->right.case_y][enemy->right.case_x] == '1')
	{
		cx = enemy->center.case_x - enemy->right.case_x;
		cy = enemy->center.case_y - enemy->right.case_y;
		new_x = enemy->right.case_x + cx;
		new_y = enemy->right.case_y + cy;
		if (cy != 0 && !(new_y < 0 || new_y > data->map.tabmap_height || enemy->right.case_x < 0 || enemy->right.case_x >= ft_strlen(data->map.tabmap[new_y])) && data->map.tabmap[new_y][enemy->right.case_x] != '1')
		{
			double	diff;

			diff = 0;
			if (cy > 0)
				diff = 64 - enemy->right.coo_y;
			else if (cy < 0)
				diff = -enemy->right.coo_y - 0.001;
			enemy->left.coo_y += diff;
			enemy->center.coo_y += diff;
			enemy->right.coo_y = fmod(enemy->right.coo_y + diff + 64, 64);
			enemy->right.case_y += cy;
		}
		else if (cx != 0 && !(enemy->right.case_y < 0 || enemy->right.case_y > data->map.tabmap_height || new_x < 0 || new_x >= ft_strlen(data->map.tabmap[enemy->right.case_y])) && data->map.tabmap[enemy->right.case_y][new_x] != '1')
		{
			double	diff;

			diff = 0;
			if (cx > 0)
				diff = 64 - enemy->right.coo_x;
			else if (cx < 0)
				diff = -enemy->right.coo_x - 0.001;
			enemy->left.coo_x += diff;
			enemy->center.coo_x += diff;
			enemy->right.coo_x = fmod(enemy->right.coo_x + diff + 64, 64);
			enemy->right.case_x += cx;
		}
	}
}

void	reverse_hit_pos(t_enemy *enemy, t_item *item)
{
	double	deg;
	double	rad;
	double	dx;
	double	dy;
	double	v_normalize;

	deg = 0;
	rad = 0;
	double	diff_x = (enemy->center_before.case_x * 64 + enemy->center_before.coo_x) - (enemy->center.case_x * 64 + enemy->center.coo_x);
	double	diff_y = (enemy->center_before.case_y * 64 + enemy->center_before.coo_y) - (enemy->center.case_y * 64 + enemy->center.coo_y);
	if (diff_y != 0)
	{
		deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
		if (deg < 0)
			deg = -deg;
	}
	if (diff_y < 0 && diff_x < 0)
		deg = 180 + deg;
	else if (diff_y < 0 && diff_x > 0)
		deg = 180 - deg;
	else if (diff_y > 0 && diff_x < 0)
		deg = 360 - deg;
	else if (diff_y == 0 && diff_x < 0)
		deg = 270;
	else if (diff_y == 0 && diff_x > 0)
		deg = 90;
	else if (diff_x == 0 && diff_y < 0)
		deg = 180;
	deg += 180;
	rad = deg * (M_PI / 180);
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

	deg = 0;
	rad = 0;
	double	diff_x = (enemy->center_before.case_x * 64 + enemy->center_before.coo_x) - (enemy->center.case_x * 64 + enemy->center.coo_x);
	double	diff_y = (enemy->center_before.case_y * 64 + enemy->center_before.coo_y) - (enemy->center.case_y * 64 + enemy->center.coo_y);
	if (diff_y != 0)
	{
		deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
		if (deg < 0)
			deg = -deg;
	}
	if (diff_y < 0 && diff_x < 0)
		deg = 180 + deg;
	else if (diff_y < 0 && diff_x > 0)
		deg = 180 - deg;
	else if (diff_y > 0 && diff_x < 0)
		deg = 360 - deg;
	else if (diff_y == 0 && diff_x < 0)
		deg = 270;
	else if (diff_y == 0 && diff_x > 0)
		deg = 90;
	else if (diff_x == 0 && diff_y < 0)
		deg = 180;
	rad = deg * (M_PI / 180);
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

void	try_hit_enemys(t_enemy *elem, t_data *data, int type)
{
	t_item		*item;
	t_lst		*lst;
	t_hitray	ray;
	t_lst		*next;

	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		
		item = lst->dt;
		if (((item->type == POPO_HEAL || item->type == POPO_SHIELD || item->type == POPO_FLOO || item->type == POPO_INVI || item->type == ANIM_DEATH || item->type == WOLF_WAND || item->type == ELEM_WAND || item->type == SPIDER_WAND || item->type == DEMENTOR_WAND || item->type == PILLAR) && item->categ) || (elem->type != DEMENTOR && item->type == EXPECTO_PATRONUM && !item->categ))
		{
			lst = lst->next;
			continue;
		}
		ray.ax = elem->left.case_x * 64 + elem->left.coo_x;
		ray.ay = elem->left.case_y * 64 + elem->left.coo_y;
		ray.bx = elem->right.case_x * 64 + elem->right.coo_x;
		ray.by = elem->right.case_y * 64 + elem->right.coo_y;
		ray.cx = elem->left_before.case_x * 64 + elem->left_before.coo_x;
		ray.cy = elem->left_before.case_y * 64 + elem->left_before.coo_y;
		ray.dx = item->left.case_x * 64 + item->left.coo_x;
		ray.dy = item->left.case_y * 64 + item->left.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			if (item->damage.repulso_force_do > 0 && !type)
			{
				reverse_hit_pos(elem, item);
			}
			else
				move_more_hit_pos(elem, item);
			apply_damage(&elem->damage, &item->damage);
			next = lst->next;
			if (!((!item->categ && (item->type == EXPECTO_PATRONUM || item->type == VENTUS)) || (item->type == BH && item->categ)))
			{
				data->item = remove_elem_lst(lst);
				f_elem_lst(lst);
			}
			lst = next;
			continue;
		}
		ray.dx = item->center.case_x * 64 + item->center.coo_x;
		ray.dy = item->center.case_y * 64 + item->center.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			if (item->damage.repulso_force_do > 0 && !type)
			{
				reverse_hit_pos(elem, item);
			}
			else
				move_more_hit_pos(elem, item);
			apply_damage(&elem->damage, &item->damage);
			next = lst->next;
			if (!((!item->categ && (item->type == EXPECTO_PATRONUM || item->type == VENTUS)) || (item->type == BH && item->categ)))
			{
				data->item = remove_elem_lst(lst);
				f_elem_lst(lst);
			}
			lst = next;
			continue;
		}
		ray.dx = item->right.case_x * 64 + item->right.coo_x;
		ray.dy = item->right.case_y * 64 + item->right.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			if (item->damage.repulso_force_do > 0 && !type)
			{
				reverse_hit_pos(elem, item);
			}
			else
				move_more_hit_pos(elem, item);
			apply_damage(&elem->damage, &item->damage);
			next = lst->next;
			if (!((!item->categ && (item->type == EXPECTO_PATRONUM || item->type == VENTUS)) || (item->type == BH && item->categ)))
			{
				data->item = remove_elem_lst(lst);
				f_elem_lst(lst);
			}
			lst = next;
			continue;
		}

		ray.ax = elem->center.case_x * 64 + elem->center.coo_x;
		ray.ay = elem->center.case_y * 64 + elem->center.coo_y;
		ray.bx = elem->center_before.case_x * 64 + elem->center_before.coo_x;
		ray.by = elem->center_before.case_y * 64 + elem->center_before.coo_y;

		ray.cx = item->left.case_x * 64 + item->left.coo_x;
		ray.cy = item->left.case_y * 64 + item->left.coo_y;
		ray.dx = item->center.case_x * 64 + item->center.coo_x;
		ray.dy = item->center.case_y * 64 + item->center.coo_y;
		calc_delta(&ray);
		if (ray.hit == true)
		{
			if (item->damage.repulso_force_do > 0 && !type)
			{
				reverse_hit_pos(elem, item);
			}
			else
				move_more_hit_pos(elem, item);
			apply_damage(&elem->damage, &item->damage);
			next = lst->next;
			if (!((!item->categ && (item->type == EXPECTO_PATRONUM || item->type == VENTUS)) || (item->type == BH && item->categ)))
			{
				data->item = remove_elem_lst(lst);
				f_elem_lst(lst);
			}
			lst = next;
			continue;
		}
		ray.cx = item->center.case_x * 64 + item->center.coo_x;
		ray.cy = item->center.case_y * 64 + item->center.coo_y;
		ray.dx = item->right.case_x * 64 + item->right.coo_x;
		ray.dy = item->right.case_y * 64 + item->right.coo_y;
		calc_delta(&ray);
		if (ray.hit == true)
		{
			if (item->damage.repulso_force_do > 0 && !type)
			{
				reverse_hit_pos(elem, item);
			}
			else
				move_more_hit_pos(elem, item);
			apply_damage(&elem->damage, &item->damage);
			next = lst->next;
			if (!((!item->categ && (item->type == EXPECTO_PATRONUM || item->type == VENTUS)) || (item->type == BH && item->categ)))
			{
				data->item = remove_elem_lst(lst);
				f_elem_lst(lst);
			}
			lst = next;
			continue;
		}
		lst = lst->next;
	}
}

static void	make_move_enemy(t_data *data, t_enemy *enemy)
{
	double	deg;
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;
	int		cy;
	int		cx;
	int		right_cy;
	int		right_cx;
	int		left_cy;
	int		left_cx;
	int		new_x;
	int		new_y;
	int		new_left_x;
	int		new_left_y;
	int		new_right_x;
	int		new_right_y;
	if (enemy->damage.repulso_force_take > 0)
	{
		deg = 0;
		rad = 0;
		double	diff_x = (enemy->center.case_x * 64 + enemy->center.coo_x) - (enemy->damage.hit.case_x * 64 + enemy->damage.hit.coo_x);
		double	diff_y = (enemy->center.case_y * 64 + enemy->center.coo_y) - (enemy->damage.hit.case_y * 64 + enemy->damage.hit.coo_y);
		if (diff_y != 0)
		{
			deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
			if (deg < 0)
				deg = -deg;
		}
		if (diff_y < 0 && diff_x < 0)
			deg = 180 + deg;
		else if (diff_y < 0 && diff_x > 0)
			deg = 180 - deg;
		else if (diff_y > 0 && diff_x < 0)
			deg = 360 - deg;
		else if (diff_y == 0 && diff_x < 0)
			deg = 270;
		else if (diff_y == 0 && diff_x > 0)
			deg = 90;
		else if (diff_x == 0 && diff_y < 0)
			deg = 180;
		rad = deg * (M_PI / 180);
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
		dy *= enemy->damage.repulso_force_take * enemy->damage.repulso_frame_take;
		dx *= enemy->damage.repulso_force_take * enemy->damage.repulso_frame_take;
		f_way(enemy);
		enemy->damage.repulso_frame_take--;
		if (enemy->damage.repulso_frame_take <= 0)
			enemy->damage.repulso_force_take = 0;
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

		if (enemy->center.coo_x + dx < 0)
			cx = -1;
		else if (enemy->center.coo_x + dx >= 64)
			cx = 1;
		else
			cx = 0;
		if (enemy->center.coo_y + dy < 0)
			cy = -1;
		else if (enemy->center.coo_y + dy >= 64)
			cy = 1;
		else
			cy = 0;

		if (enemy->right.coo_x + dx < 0)
			right_cx = -1;
		else if (enemy->right.coo_x + dx >= 64)
			right_cx = 1;
		else
			right_cx = 0;
		if (enemy->right.coo_y + dy < 0)
			right_cy = -1;
		else if (enemy->right.coo_y + dy >= 64)
			right_cy = 1;
		else
			right_cy = 0;

		if (enemy->left.coo_x + dx < 0)
			left_cx = -1;
		else if (enemy->left.coo_x + dx >= 64)
			left_cx = 1;
		else
			left_cx = 0;
		if (enemy->left.coo_y + dy < 0)
			left_cy = -1;
		else if (enemy->left.coo_y + dy >= 64)
			left_cy = 1;
		else
			left_cy = 0;
		new_x = enemy->center.case_x + cx;
		new_y = enemy->center.case_y + cy;
		new_right_x = enemy->right.case_x + right_cx;
		new_right_y = enemy->right.case_y + right_cy;
		new_left_x = enemy->left.case_x + left_cx;
		new_left_y = enemy->left.case_y + left_cy;
		if (((enemy->center.coo_x + dx < 0 || enemy->center.coo_x + dx >= 64) && (enemy->center.case_y < 0 || enemy->center.case_y > data->map.tabmap_height || new_x < 0 || new_x >= ft_strlen(data->map.tabmap[enemy->center.case_y]) || data->map.tabmap[enemy->center.case_y][new_x] == '1'))
			|| ((enemy->right.coo_x + dx < 0 || enemy->right.coo_x + dx >= 64) && (enemy->right.case_y < 0 || enemy->right.case_y > data->map.tabmap_height || new_right_x < 0 || new_right_x >= ft_strlen(data->map.tabmap[enemy->right.case_y]) || data->map.tabmap[enemy->right.case_y][new_right_x] == '1'))
			|| ((enemy->left.coo_x + dx < 0 || enemy->left.coo_x + dx >= 64) && (enemy->left.case_y < 0 || enemy->left.case_y > data->map.tabmap_height || new_left_x < 0 || new_left_x >= ft_strlen(data->map.tabmap[enemy->left.case_y]) || data->map.tabmap[enemy->left.case_y][new_left_x] == '1')))
		{
			dx = 0;
			new_x = enemy->center.case_x;
			new_left_x = enemy->left.case_x;
			new_right_x = enemy->right.case_x;
		}
		else if (enemy->center.coo_x + dx >= 64)
			enemy->center.coo_x = fmod(enemy->center.coo_x + dx, 64);
		else if (enemy->center.coo_x + dx < 0)
			enemy->center.coo_x = enemy->center.coo_x + dx + 64;
		else
			enemy->center.coo_x = enemy->center.coo_x + dx;
		if (((enemy->center.coo_y + dy < 0 || enemy->center.coo_y + dy >= 64) && (new_y < 0 || new_y > data->map.tabmap_height || new_x < 0 || new_x >= ft_strlen(data->map.tabmap[new_y]) || data->map.tabmap[new_y][new_x] == '1'))
			|| ((enemy->right.coo_y + dy < 0 || enemy->right.coo_y + dy >= 64) && (new_right_y < 0 || new_right_y > data->map.tabmap_height || new_right_x < 0 || new_right_x >= ft_strlen(data->map.tabmap[new_right_y]) || data->map.tabmap[new_right_y][new_right_x] == '1'))
			|| ((enemy->left.coo_y + dy < 0 || enemy->left.coo_y + dy >= 64) && (new_left_y < 0 || new_left_y > data->map.tabmap_height || new_left_x < 0 || new_left_x >= ft_strlen(data->map.tabmap[new_left_y]) || data->map.tabmap[new_left_y][new_left_x] == '1')))
		{
			dy = 0;
			new_y = enemy->center.case_y;
			new_left_y = enemy->left.case_y;
			new_right_y = enemy->right.case_y;
		}
		else if (enemy->center.coo_y + dy >= 64)
			enemy->center.coo_y = fmod(enemy->center.coo_y + dy, 64);
		else if (enemy->center.coo_y + dy < 0)
			enemy->center.coo_y = enemy->center.coo_y + dy + 64;
		else
			enemy->center.coo_y = enemy->center.coo_y + dy;
		enemy->center.case_x = new_x;
		enemy->center.case_y = new_y;
		if (cy != 0 || cx != 0)
			enemy->calc = true;
		calc_left_and_right_point(enemy, data);
		try_hit_enemys(enemy, data, 1);
		return ;
	}
	if (enemy->damage.confundo_force_take > 0)
	{
		deg = 0;
		enemy->rad = 0;
		double	diff_x = (enemy->center.case_x * 64 + enemy->center.coo_x) - (data->player.coo.case_x * 64 + data->player.coo.coo_x);
		double	diff_y = (enemy->center.case_y * 64 + enemy->center.coo_y) - (data->player.coo.case_y * 64 + data->player.coo.coo_y);
		if (diff_y != 0)
		{
			deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
			if (deg < 0)
				deg = -deg;
		}
		if (diff_y < 0 && diff_x < 0)
			deg = 180 + deg;
		else if (diff_y < 0 && diff_x > 0)
			deg = 180 - deg;
		else if (diff_y > 0 && diff_x < 0)
			deg = 360 - deg;
		else if (diff_y == 0 && diff_x < 0)
			deg = 270;
		else if (diff_y == 0 && diff_x > 0)
			deg = 90;
		else if (diff_x == 0 && diff_y < 0)
			deg = 180;
		enemy->deg = deg;
		enemy->rad = deg * (M_PI / 180);
		dx = sin(enemy->rad);
		dy = cos(enemy->rad);
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
		dy *= enemy->speed;
		dx *= enemy->speed;
		f_way(enemy);
		enemy->damage.confundo_frame_take--;
		if (enemy->damage.confundo_frame_take <= 0)
			enemy->damage.confundo_force_take = 0;
		int	cy;
		int	cx;
		int	right_cy;
		int	right_cx;
		int	left_cy;
		int	left_cx;
		int	new_x;
		int	new_y;
		int	new_left_x;
		int	new_left_y;
		int	new_right_x;
		int	new_right_y;

		if (dy != 0)
		{
			deg = atan(((double)dx / dy)) / (M_PI / 180);
			if (deg < 0)
				deg = -deg;
		}
		if (dy < 0 && dx < 0)
			deg = 180 + deg;
		else if (dy < 0 && dx > 0)
			deg = 180 - deg;
		else if (dy > 0 && dx < 0)
			deg = 360 - deg;
		else if (dy == 0 && dx < 0)
			deg = 270;
		else if (dy == 0 && dx > 0)
			deg = 90;
		else if (dx == 0 && dy < 0)
			deg = 180;
		enemy->deg = deg;
		enemy->rad = enemy->deg * (M_PI / 180);
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
		if (enemy->center.coo_x + dx < 0)
			cx = -1;
		else if (enemy->center.coo_x + dx >= 64)
			cx = 1;
		else
			cx = 0;
		if (enemy->center.coo_y + dy < 0)
			cy = -1;
		else if (enemy->center.coo_y + dy >= 64)
			cy = 1;
		else
			cy = 0;

		if (enemy->right.coo_x + dx < 0)
			right_cx = -1;
		else if (enemy->right.coo_x + dx >= 64)
			right_cx = 1;
		else
			right_cx = 0;
		if (enemy->right.coo_y + dy < 0)
			right_cy = -1;
		else if (enemy->right.coo_y + dy >= 64)
			right_cy = 1;
		else
			right_cy = 0;

		if (enemy->left.coo_x + dx < 0)
			left_cx = -1;
		else if (enemy->left.coo_x + dx >= 64)
			left_cx = 1;
		else
			left_cx = 0;
		if (enemy->left.coo_y + dy < 0)
			left_cy = -1;
		else if (enemy->left.coo_y + dy >= 64)
			left_cy = 1;
		else
			left_cy = 0;
		new_x = enemy->center.case_x + cx;
		new_y = enemy->center.case_y + cy;
		new_right_x = enemy->right.case_x + right_cx;
		new_right_y = enemy->right.case_y + right_cy;
		new_left_x = enemy->left.case_x + left_cx;
		new_left_y = enemy->left.case_y + left_cy;
		if (((enemy->center.coo_x + dx < 0 || enemy->center.coo_x + dx >= 64) && (enemy->center.case_y < 0 || enemy->center.case_y > data->map.tabmap_height || new_x < 0 || new_x >= ft_strlen(data->map.tabmap[enemy->center.case_y]) || data->map.tabmap[enemy->center.case_y][new_x] == '1'))
			|| ((enemy->right.coo_x + dx < 0 || enemy->right.coo_x + dx >= 64) && (enemy->right.case_y < 0 || enemy->right.case_y > data->map.tabmap_height || new_right_x < 0 || new_right_x >= ft_strlen(data->map.tabmap[enemy->right.case_y]) || data->map.tabmap[enemy->right.case_y][new_right_x] == '1'))
			|| ((enemy->left.coo_x + dx < 0 || enemy->left.coo_x + dx >= 64) && (enemy->left.case_y < 0 || enemy->left.case_y > data->map.tabmap_height || new_left_x < 0 || new_left_x >= ft_strlen(data->map.tabmap[enemy->left.case_y]) || data->map.tabmap[enemy->left.case_y][new_left_x] == '1')))
		{
			dx = 0;
			new_x = enemy->center.case_x;
			new_left_x = enemy->left.case_x;
			new_right_x = enemy->right.case_x;
		}
		else if (enemy->center.coo_x + dx >= 64)
			enemy->center.coo_x = fmod(enemy->center.coo_x + dx, 64);
		else if (enemy->center.coo_x + dx < 0)
			enemy->center.coo_x = enemy->center.coo_x + dx + 64;
		else
			enemy->center.coo_x = enemy->center.coo_x + dx;
		if (((enemy->center.coo_y + dy < 0 || enemy->center.coo_y + dy >= 64) && (new_y < 0 || new_y > data->map.tabmap_height || new_x < 0 || new_x >= ft_strlen(data->map.tabmap[new_y]) || data->map.tabmap[new_y][new_x] == '1'))
			|| ((enemy->right.coo_y + dy < 0 || enemy->right.coo_y + dy >= 64) && (new_right_y < 0 || new_right_y > data->map.tabmap_height || new_right_x < 0 || new_right_x >= ft_strlen(data->map.tabmap[new_right_y]) || data->map.tabmap[new_right_y][new_right_x] == '1'))
			|| ((enemy->left.coo_y + dy < 0 || enemy->left.coo_y + dy >= 64) && (new_left_y < 0 || new_left_y > data->map.tabmap_height || new_left_x < 0 || new_left_x >= ft_strlen(data->map.tabmap[new_left_y]) || data->map.tabmap[new_left_y][new_left_x] == '1')))
		{
			dy = 0;
			new_y = enemy->center.case_y;
			new_left_y = enemy->left.case_y;
			new_right_y = enemy->right.case_y;
		}
		else if (enemy->center.coo_y + dy >= 64)
			enemy->center.coo_y = fmod(enemy->center.coo_y + dy, 64);
		else if (enemy->center.coo_y + dy < 0)
			enemy->center.coo_y = enemy->center.coo_y + dy + 64;
		else
			enemy->center.coo_y = enemy->center.coo_y + dy;
		enemy->center.case_x = new_x;
		enemy->center.case_y = new_y;
		if (cy != 0 || cx != 0)
			enemy->calc = true;
		calc_left_and_right_point(enemy, data);
		try_hit_enemys(enemy, data, 0);
		return ;
	}
	
	if (enemy->calc == true)
	{
		enemy->calc = false;
		deg = 0;
		enemy->rad = 0;
		double	diff_x = enemy->way->coo_x - enemy->center.coo_x;
		double	diff_y = enemy->way->coo_y - enemy->center.coo_y;
		if (diff_y != 0)
		{
			deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
			if (deg < 0)
				deg = -deg;
		}
		if (diff_y < 0 && diff_x < 0)
			deg = 180 + deg;
		else if (diff_y < 0 && diff_x > 0)
			deg = 180 - deg;
		else if (diff_y > 0 && diff_x < 0)
			deg = 360 - deg;
		else if (diff_y == 0 && diff_x < 0)
			deg = 270;
		else if (diff_y == 0 && diff_x > 0)
			deg = 90;
		else if (diff_x == 0 && diff_y < 0)
			deg = 180;
		enemy->deg = deg;
		enemy->rad = deg * (M_PI / 180);
	}
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
	if (!(enemy->dist_target < enemy->dist_stop && enemy->way && enemy->dist_target != -1))
	{
		dx = sin(enemy->rad);
		dy = cos(enemy->rad);
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
		dy *= enemy->speed;
		dx *= enemy->speed;
		if (enemy->damage.slow_frame_take > 0 || enemy->damage.slow_force_take > 0)
		{
			if (enemy->damage.slow_force_take > 100)
				enemy->damage.slow_force_take = 100;
			dx *= (100 - enemy->damage.slow_force_take) / 100;
			dy *= (100 - enemy->damage.slow_force_take) / 100;
			if (enemy->damage.slow_frame_take > 0)
				enemy->damage.slow_frame_take--;
			if (enemy->damage.slow_frame_take <= 0)
				enemy->damage.slow_force_take--;
		}
		if (enemy->way 
			&& are_double_close(enemy->center.coo_x, enemy->goal.coo_x)
			&& are_double_close(enemy->center.coo_y, enemy->goal.coo_y)
			&& enemy->center.case_x == enemy->goal.case_x
			&& enemy->center.case_y == enemy->goal.case_y)
		{
			f_case(enemy->way);
			enemy->way = NULL;
			enemy->wait = 0;
			enemy->calc = true;
		}
		else
		{
			enemy->center.coo_x += dx;
			enemy->center.coo_y += dy;
			if (enemy->recalc_path > 0)
				enemy->recalc_path--;
			if (enemy->calc_path > 0)
				enemy->calc_path--;
			if (enemy->center.coo_x <= 0 || enemy->center.coo_x >= 64
				|| enemy->center.coo_y <= 0 || enemy->center.coo_y >= 64)
			{
				if (enemy->center.coo_x <= 0)
					enemy->center.coo_x += 63.999;
				if (enemy->center.coo_x >= 64)
					enemy->center.coo_x -= 63.999;
				if (enemy->center.coo_y <= 0)
					enemy->center.coo_y += 63.999;
				if (enemy->center.coo_y >= 64)
					enemy->center.coo_y -= 63.999;
				if (enemy->way->child)
				{
					enemy->way->child->parent = NULL;
					t_case	*tmp = enemy->way;
					enemy->way = enemy->way->child;
					enemy->center.case_x = enemy->way->case_x;
					enemy->center.case_y = enemy->way->case_y;
					f_case(tmp);
					enemy->calc = true;
				}
				else
				{
					f_case(enemy->way);
					enemy->way = NULL;
					enemy->wait = 0;
					enemy->calc = true;
				}
			}
			calc_left_and_right_point(enemy, data);
			try_hit_enemys(enemy, data, 0);
		}
	}
	if (enemy->damage.repulso_force_take < 0)
	{
		deg = 0;
		rad = 0;
		double	diff_x = (enemy->damage.hit.case_x * 64 + enemy->damage.hit.coo_x) - (enemy->center.case_x * 64 + enemy->center.coo_x);
		double	diff_y = (enemy->damage.hit.case_y * 64 + enemy->damage.hit.coo_y) - (enemy->center.case_y * 64 + enemy->center.coo_y);
		if (diff_y != 0)
		{
			deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
			if (deg < 0)
				deg = -deg;
		}
		if (diff_y < 0 && diff_x < 0)
			deg = 180 + deg;
		else if (diff_y < 0 && diff_x > 0)
			deg = 180 - deg;
		else if (diff_y > 0 && diff_x < 0)
			deg = 360 - deg;
		else if (diff_y == 0 && diff_x < 0)
			deg = 270;
		else if (diff_y == 0 && diff_x > 0)
			deg = 90;
		else if (diff_x == 0 && diff_y < 0)
			deg = 180;
		rad = deg * (M_PI / 180);
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

		diff_x = (enemy->damage.hit.case_x * 64 + enemy->damage.hit.coo_x) - (enemy->center.case_x * 64 + enemy->center.coo_x);
		diff_y = (enemy->damage.hit.case_y * 64 + enemy->damage.hit.coo_y) - (enemy->center.case_y * 64 + enemy->center.coo_y);
		enemy->damage.dist = sqrt(diff_x * diff_x + diff_y * diff_y);
		double	decal = -(1000 / (enemy->damage.dist + 35) + enemy->damage.repulso_force_take) / 4 - 1;
		if (decal > 0)
			return;
		if (enemy->damage.dist >= fabs(decal))
			enemy->damage.repulso_force_take = decal;
		else
		{
			enemy->damage.repulso_force_take = -enemy->damage.dist;
			enemy->damage.repulso_frame_take = enemy->damage.repulso_frame_take;
		}
		dy *= fabs(enemy->damage.repulso_force_take) * enemy->damage.repulso_frame_take;
		dx *= fabs(enemy->damage.repulso_force_take) * enemy->damage.repulso_frame_take;
		f_way(enemy);
		enemy->damage.repulso_frame_take--;
		if (enemy->damage.repulso_frame_take <= 0)
			enemy->damage.repulso_force_take = 0;
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

		if (enemy->center.coo_x + dx < 0)
			cx = -1;
		else if (enemy->center.coo_x + dx >= 64)
			cx = 1;
		else
			cx = 0;
		if (enemy->center.coo_y + dy < 0)
			cy = -1;
		else if (enemy->center.coo_y + dy >= 64)
			cy = 1;
		else
			cy = 0;

		if (enemy->right.coo_x + dx < 0)
			right_cx = -1;
		else if (enemy->right.coo_x + dx >= 64)
			right_cx = 1;
		else
			right_cx = 0;
		if (enemy->right.coo_y + dy < 0)
			right_cy = -1;
		else if (enemy->right.coo_y + dy >= 64)
			right_cy = 1;
		else
			right_cy = 0;

		if (enemy->left.coo_x + dx < 0)
			left_cx = -1;
		else if (enemy->left.coo_x + dx >= 64)
			left_cx = 1;
		else
			left_cx = 0;
		if (enemy->left.coo_y + dy < 0)
			left_cy = -1;
		else if (enemy->left.coo_y + dy >= 64)
			left_cy = 1;
		else
			left_cy = 0;
		new_x = enemy->center.case_x + cx;
		new_y = enemy->center.case_y + cy;
		new_right_x = enemy->right.case_x + right_cx;
		new_right_y = enemy->right.case_y + right_cy;
		new_left_x = enemy->left.case_x + left_cx;
		new_left_y = enemy->left.case_y + left_cy;
		if (((enemy->center.coo_x + dx < 0 || enemy->center.coo_x + dx >= 64) && (enemy->center.case_y < 0 || enemy->center.case_y > data->map.tabmap_height || new_x < 0 || new_x >= ft_strlen(data->map.tabmap[enemy->center.case_y]) || data->map.tabmap[enemy->center.case_y][new_x] == '1'))
			|| ((enemy->right.coo_x + dx < 0 || enemy->right.coo_x + dx >= 64) && (enemy->right.case_y < 0 || enemy->right.case_y > data->map.tabmap_height || new_right_x < 0 || new_right_x >= ft_strlen(data->map.tabmap[enemy->right.case_y]) || data->map.tabmap[enemy->right.case_y][new_right_x] == '1'))
			|| ((enemy->left.coo_x + dx < 0 || enemy->left.coo_x + dx >= 64) && (enemy->left.case_y < 0 || enemy->left.case_y > data->map.tabmap_height || new_left_x < 0 || new_left_x >= ft_strlen(data->map.tabmap[enemy->left.case_y]) || data->map.tabmap[enemy->left.case_y][new_left_x] == '1')))
		{
			dx = 0;
			new_x = enemy->center.case_x;
			new_left_x = enemy->left.case_x;
			new_right_x = enemy->right.case_x;
		}
		else if (enemy->center.coo_x + dx >= 64)
			enemy->center.coo_x = fmod(enemy->center.coo_x + dx, 64);
		else if (enemy->center.coo_x + dx < 0)
			enemy->center.coo_x = enemy->center.coo_x + dx + 64;
		else
			enemy->center.coo_x = enemy->center.coo_x + dx;
		if (((enemy->center.coo_y + dy < 0 || enemy->center.coo_y + dy >= 64) && (new_y < 0 || new_y > data->map.tabmap_height || new_x < 0 || new_x >= ft_strlen(data->map.tabmap[new_y]) || data->map.tabmap[new_y][new_x] == '1'))
			|| ((enemy->right.coo_y + dy < 0 || enemy->right.coo_y + dy >= 64) && (new_right_y < 0 || new_right_y > data->map.tabmap_height || new_right_x < 0 || new_right_x >= ft_strlen(data->map.tabmap[new_right_y]) || data->map.tabmap[new_right_y][new_right_x] == '1'))
			|| ((enemy->left.coo_y + dy < 0 || enemy->left.coo_y + dy >= 64) && (new_left_y < 0 || new_left_y > data->map.tabmap_height || new_left_x < 0 || new_left_x >= ft_strlen(data->map.tabmap[new_left_y]) || data->map.tabmap[new_left_y][new_left_x] == '1')))
		{
			dy = 0;
			new_y = enemy->center.case_y;
			new_left_y = enemy->left.case_y;
			new_right_y = enemy->right.case_y;
		}
		else if (enemy->center.coo_y + dy >= 64)
			enemy->center.coo_y = fmod(enemy->center.coo_y + dy, 64);
		else if (enemy->center.coo_y + dy < 0)
			enemy->center.coo_y = enemy->center.coo_y + dy + 64;
		else
			enemy->center.coo_y = enemy->center.coo_y + dy;
		enemy->center.case_x = new_x;
		enemy->center.case_y = new_y;
		enemy->calc = true;
		calc_left_and_right_point(enemy, data);
		try_hit_enemys(enemy, data, 1);
		return ;
	}
}

static int	handle_ray_y_top_gen(t_data *data, t_ray *ray)
{

	if (data->map.tabmap[ray->case_y - 1][ray->case_x] != '1')
	{
		ray->case_y--;
		ray->coo_y = 64;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
	}
	else
	{
		ray->coo_y = 0;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
		return (1);
	}
	return (0);
}

static int	handle_ray_y_down_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y + 1][ray->case_x] != '1')
	{
		ray->case_y++;
		ray->coo_y = 0;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
	}
	else
	{
		ray->coo_y = 64;
		ray->coo_x += ray->ry * ray->delta_x;
		ray->coo_x = round(ray->coo_x * 64) / 64.0;
		return (1);
	}
	return (0);
}

static int	handle_ray_x_left_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y][ray->case_x - 1] != '1')
	{
		ray->case_x--;
		ray->coo_x = 64;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
	}
	else
	{
		ray->coo_x = 0;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
		return (1);
	}
	return (0);
}

static int	handle_ray_x_right_gen(t_data *data, t_ray *ray)
{
	if (data->map.tabmap[ray->case_y][ray->case_x + 1] != '1')
	{
		ray->case_x++;
		ray->coo_x = 0;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
	}
	else
	{
		ray->coo_x = 64;
		ray->coo_y += ray->rx * ray->delta_y;
		ray->coo_y = round(ray->coo_y * 64) / 64.0;
		return (1);
	}
	return (0);
}

static int	handle_ray_x_gen(t_data *data, t_ray *ray)
{
	if (ray->delta_x < 0)
	{
		if (handle_ray_x_left_gen(data, ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_x_right_gen(data, ray) == 1)
			return (1);
	}
	return (0);
}
static int	handle_ray_y_gen(t_data *data, t_ray *ray)
{
	if (ray->delta_y < 0)
	{
		if (handle_ray_y_top_gen(data, ray) == 1)
			return (1);
	}
	else
	{
		if (handle_ray_y_down_gen(data, ray) == 1)
			return (1);
	}
	return (0);
}

bool	is_sorcerer(int type)
{
	if (type == MARINA || type == CAMEO || type == DIRLO || type == NANCY
		|| type == PILO || type == ZIPPY || type == ANAIS || type == STEF
		|| type == KUNFANDI)
		return (true);
	return (false);
}

void	air_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
			EXPECTO_PATRONUM, &enemy->center, deg + 180),
			data->item, f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
			ARANIA_EXUMAI, &enemy->center, deg + 180),
			data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, VENTUS,
					&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == KUNFANDI)
		data->item = add_end_lst(create_item(data, BH, 
			&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == CAMEO)
		data->item = add_end_lst(create_item(data, MARVIN, 
			&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == ANAIS)
		data->item = add_end_lst(create_item(data, TAYLOR_SWIFT,
			&enemy->center, deg + 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = AIR;
}

void	water_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data, 
			EXPECTO_PATRONUM, &enemy->center, deg + 180),
			data->item, f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
			ARANIA_EXUMAI, &enemy->center, deg + 180),
			data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, AGUAMENTI, 
					&enemy->center, deg + 180), data->item, f_item);
	else
		data->item = add_end_lst(create_item(data, FOLDER, 
			&enemy->center, deg + 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = WATER;
}

void	fire_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	printf("FIRE SPELL\n");
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
			EXPECTO_PATRONUM, &enemy->center, deg + 180),
			data->item, f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
			ARANIA_EXUMAI, &enemy->center, deg + 180),
			data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, INCENDIO, 
					&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == STEF)
		data->item = add_end_lst(create_item(data, COMPANY, 
			&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == ZIPPY)
		data->item = add_end_lst(create_item(data, PIZZA, 
			&enemy->center, deg + 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = FIRE;
}

void	earth_spell(t_data *data, t_enemy *enemy, double deg, int type)
{
	if (type == DEMENTOR)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
			EXPECTO_PATRONUM, &enemy->center, deg + 180),
			data->item, f_item);
	else if (type == SPIDER)
		data->item = add_end_lst(create_spell_item_sorcerer(data,
			ARANIA_EXUMAI, &enemy->center, deg + 180),
			data->item, f_item);
	else if (rand() % 3 == 0)
		data->item = add_end_lst(create_spell_item_sorcerer(data, ENDOLORIS, 
					&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == MARINA)
		data->item = add_end_lst(create_item(data, LOGO_42, 
			&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == PILO)
		data->item = add_end_lst(create_item(data, MAC, 
			&enemy->center, deg + 180), data->item, f_item);
	else if (enemy->type == DIRLO)
		data->item = add_end_lst(create_item(data, TIG, 
			&enemy->center, deg + 180), data->item, f_item);
	((t_item *)data->item->dt)->damage.which_coa_do = EARTH;
}

int	enemy_vision(t_data *data, t_enemy *enemy)
{
	double	deg;
	double	dist_min_player;
	t_lst	*lst;
	t_enemy	*elem;
	t_enemy *keep_elem;
	double	dist_min;
	t_fcoo	coo;
	int		diff_x;
	int		diff_y;
	t_ray	ray;
	int		type;
	
	dist_min = -1;
	keep_elem = NULL;
	dist_min_player = -1;
	deg = 0;
	lst = get_first_elem_lst(data->enemy);
	
	while (lst)
	{
		elem = lst->dt;
		lst = lst->next;
		if (enemy->type == BIRD)
		{
			if (elem->type == BIRD)
				continue;
		}
		else if (is_sorcerer(enemy->type) == true && 
				 elem->color_coa == enemy->color_coa)
			continue;
		else if (enemy->type == SNAKE && elem->type == SNAKE)
			continue ;
		else if (is_sorcerer(enemy->type) == false && is_sorcerer(elem->type) == false && enemy->type != SNAKE)
			continue;
		diff_x = elem->center.case_x * 64 + elem->center.coo_x
			- enemy->center.case_x * 64 - enemy->center.coo_x;
		diff_y = elem->center.case_y * 64 + elem->center.coo_y
			- enemy->center.case_y * 64 - enemy->center.coo_y;
		
		if (diff_x == 0 && diff_y == 0)
			return (0);
			
		if (diff_x != 0 && diff_y != 0)
		{
			deg = atan(((double)diff_x / diff_y)) / (M_PI / 180);
			if (deg < 0)
				deg = -deg;
		}
		if (diff_y < 0 && diff_x < 0)
			deg = 180 + deg;
		else if (diff_y < 0 && diff_x > 0)
			deg = 180 - deg;
		else if (diff_y > 0 && diff_x < 0)
			deg = 360 - deg;
		else if (diff_y == 0 && diff_x < 0)
			deg = 270;
		else if (diff_y == 0 && diff_x > 0)
			deg = 90;
		else if (diff_x == 0 && diff_y < 0)
			deg = 180;
			
		if ((deg + 360 >= elem->deg - 90 + 360
			&& deg + 360 <= elem->deg + 90 + 360)
		|| enemy->calc_path > 0)
		{
			ray.deg = deg;
			ray.start_case_x = enemy->center.case_x;
			ray.start_case_y = enemy->center.case_y;
			ray.start_coo_x = enemy->center.coo_x;
			ray.start_coo_y = enemy->center.coo_y;
			ray.coo_y = enemy->center.coo_y;
			ray.coo_x = enemy->center.coo_x;
			ray.case_y = enemy->center.case_y;
			ray.case_x = enemy->center.case_x;
			ray.deg = fmod(ray.deg, 360);
			ray.rad = ray.deg * (M_PI / 180);
			ray.delta_y = cos(ray.rad);
			ray.delta_x = sin(ray.rad);
			
			while (1)
			{
				if (ray.delta_x > 0)
					ray.rx = (64 - ray.coo_x) / ray.delta_x;
				else
					ray.rx = -ray.coo_x / ray.delta_x;
				if (ray.delta_y > 0)
					ray.ry = (64 - ray.coo_y) / ray.delta_y;
				else
					ray.ry = -ray.coo_y / ray.delta_y;
				if (ray.rx < ray.ry)
				{
					if (handle_ray_x_gen(data, &ray) == 1)
						break;
				}
				else
				{
					if (handle_ray_y_gen(data, &ray) == 1)
						break;
				}
			}
			
			ray.dist_wall = sqrt(((ray.case_y - ray.start_case_y) * 64.0 + 
				(ray.coo_y - ray.start_coo_y)) * ((ray.case_y - ray.start_case_y) * 64.0 + 
				(ray.coo_y - ray.start_coo_y)) + ((ray.case_x - ray.start_case_x) * 64.0 + 
				(ray.coo_x - ray.start_coo_x)) * ((ray.case_x - ray.start_case_x) * 64.0 + 
				(ray.coo_x - ray.start_coo_x)));
				
			enemy->dist_target = sqrt(((elem->center.case_y - ray.start_case_y) * 64.0 + 
				(elem->center.coo_y - ray.start_coo_y)) * ((elem->center.case_y - 
				ray.start_case_y) * 64.0 + (elem->center.coo_y - ray.start_coo_y)) + 
				((elem->center.case_x - ray.start_case_x) * 64.0 + (elem->center.coo_x - 
				ray.start_coo_x)) * ((elem->center.case_x - ray.start_case_x) * 64.0 + 
				(elem->center.coo_x - ray.start_coo_x)));
				
			if (enemy->dist_target < ray.dist_wall || enemy->calc_path > 0)
			{
				if (enemy->dist_target < dist_min || dist_min == -1)
				{
					type = elem->type;
					keep_elem = elem;
					dist_min = enemy->dist_target;
					coo.case_x = elem->center.case_x;
					coo.case_y = elem->center.case_y;
					coo.coo_y = elem->center.coo_y;
					coo.coo_x = elem->center.coo_x;
				}
			}
		}
	}
	if (enemy->type != BIRD && enemy->nb_move >= 10 && data->player.invisible == 255)
	{
		int	diff_player_x = data->player.coo.case_x * 64 + data->player.coo.coo_x
		- enemy->center.case_x * 64 - enemy->center.coo_x;
		int	diff_player_y = data->player.coo.case_y * 64 + data->player.coo.coo_y
		- enemy->center.case_y * 64 - enemy->center.coo_y;
		dist_min_player = sqrt(diff_player_x * diff_player_x + diff_player_y * diff_player_y);
		deg = 0;
		if (diff_player_x != 0 && diff_player_y != 0)
		{
			deg = atan(((double)diff_player_x / diff_player_y)) / (M_PI / 180);
			if (deg < 0)
				deg = -deg;
		}
		if (diff_player_y < 0 && diff_player_x < 0)
			deg = 180 + deg;
		else if (diff_player_y < 0 && diff_player_x > 0)
			deg = 180 - deg;
		else if (diff_player_y > 0 && diff_player_x < 0)
			deg = 360 - deg;
		else if (diff_player_y == 0 && diff_player_x < 0)
			deg = 270;
		else if (diff_player_y == 0 && diff_player_x > 0)
			deg = 90;
		else if (diff_player_x == 0 && diff_player_y < 0)
			deg = 180;
		enemy->deg = fmod(enemy->deg, 360);
		if ((deg + 360 >= enemy->deg - 90 + 360
			&& deg + 360 <= enemy->deg + 90 + 360)
		||
			enemy->calc_path > 0)
		{
			t_ray	ray;
			ray.deg = deg;
			ray.start_case_x = enemy->center.case_x;
			ray.start_case_y = enemy->center.case_y;
			ray.start_coo_x = enemy->center.coo_x;
			ray.start_coo_y = enemy->center.coo_y;
			ray.coo_y = enemy->center.coo_y;
			ray.coo_x = enemy->center.coo_x;
			ray.case_y = enemy->center.case_y;
			ray.case_x = enemy->center.case_x;
			ray.deg = fmod(ray.deg, 360);
			ray.rad = ray.deg * (M_PI / 180);
			ray.delta_y = cos(ray.rad);
			ray.delta_x = sin(ray.rad);
			while (1)
			{
				if (ray.delta_x > 0)
					ray.rx = (64 - ray.coo_x) / ray.delta_x;
				else
					ray.rx = -ray.coo_x / ray.delta_x;
				if (ray.delta_y > 0)
					ray.ry = (64 - ray.coo_y) / ray.delta_y;
				else
					ray.ry = -ray.coo_y / ray.delta_y;
				if (ray.rx < ray.ry)
				{
					if (handle_ray_x_gen(data, &ray) == 1)
						break ;
				}
				else
				{
					if (handle_ray_y_gen(data, &ray) == 1)
						break ;
				}
			}
			ray.dist_wall = sqrt(((ray.case_y
			- ray.start_case_y) * 64.0 + (ray.coo_y
			- ray.start_coo_y)) * ((ray.case_y
			- ray.start_case_y) * 64.0 + (ray.coo_y
			- ray.start_coo_y)) + ((ray.case_x
			- ray.start_case_x) * 64.0 + (ray.coo_x
			- ray.start_coo_x)) * ((ray.case_x
			- ray.start_case_x) * 64.0 + (ray.coo_x
			- ray.start_coo_x)));
			if (dist_min_player < ray.dist_wall || enemy->calc_path > 0)
			{
				if (dist_min_player < dist_min || dist_min_player < 256 || dist_min == -1)
				{
					dist_min = dist_min_player;
					type = -1;
					coo.case_x = data->player.coo.case_x;
					coo.case_y = data->player.coo.case_y;
					coo.coo_y = data->player.coo.coo_y;
					coo.coo_x = data->player.coo.coo_x;
				}
				
			}
		}
	}
	if (dist_min != -1)
	{
		int	diff_player_x = coo.case_x * 64 + coo.coo_x
		- enemy->center.case_x * 64 - enemy->center.coo_x;
		int	diff_player_y = coo.case_y * 64 + coo.coo_y
		- enemy->center.case_y * 64 - enemy->center.coo_y;
		dist_min_player = sqrt(diff_player_x * diff_player_x + diff_player_y * diff_player_y);
		deg = 0;
		if (diff_player_x != 0 && diff_player_y != 0)
		{
			deg = atan(((double)diff_player_x / diff_player_y)) / (M_PI / 180);
			if (deg < 0)
				deg = -deg;
		}
		if (diff_player_y < 0 && diff_player_x < 0)
			deg = 180 + deg;
		else if (diff_player_y < 0 && diff_player_x > 0)
			deg = 180 - deg;
		else if (diff_player_y > 0 && diff_player_x < 0)
			deg = 360 - deg;
		else if (diff_player_y == 0 && diff_player_x < 0)
			deg = 270;
		else if (diff_player_y == 0 && diff_player_x > 0)
			deg = 90;
		else if (diff_player_x == 0 && diff_player_y < 0)
			deg = 180;
		deg = fmod(deg, 360);
		enemy->dist_target = dist_min;
		if (enemy->dist_target < enemy->dist_visu)
		{
			if (is_sorcerer(enemy->type) == true && 
				rand() % 1000 < 50 && 
				get_mtime() > enemy->time_attack_dist + enemy->cooldown_dist * 1000)
			{
				enemy->time_attack_dist = get_mtime();
				if (enemy->color_coa == AIR_COLOR)
					air_spell(data, enemy, deg, type);
				else if (enemy->color_coa == EARTH_COLOR)
					earth_spell(data, enemy, deg, type);
				else if (enemy->color_coa == WATER_COLOR)
					water_spell(data, enemy, deg, type);
				else if (enemy->color_coa == FIRE_COLOR)
					fire_spell(data, enemy, deg, type);
			}
			else if (rand() % 1000 < 50 && 
				get_mtime() > enemy->time_attack_dist + enemy->cooldown_dist * 1000)
			{
				enemy->time_attack_dist = get_mtime();
				if (enemy->type == SPIDER)
				{
					data->item = add_end_lst(create_item(data, WEB_SPIDER, 
						&enemy->center, deg + 180), data->item, f_item);
					((t_item *)data->item->dt)->damage.which_coa_do = OTHERS;
				}
				else if (enemy->type == ELEM)
				{
					data->item = add_end_lst(create_item(data, FIREBALL_ELEM, 
						&enemy->center, deg + 180), data->item, f_item);
						((t_item *)data->item->dt)->damage.which_coa_do = OTHERS;
				}
			}
			
			if (enemy->recalc_path <= 50 || !enemy->way)
				enemy->recalc_path = 100;
			if (dist_min_player == dist_min)
				enemy->calc_path = 30;
			else
				enemy->calc_path = 0;
		}
		if (enemy->dist_target < enemy->dist_damage && 
			get_mtime() > enemy->time_attack_cac + enemy->cooldown_cac * 1000)
		{
			enemy->time_attack_cac = get_mtime();
			if (dist_min == dist_min_player)
				apply_damage(&data->player.damage, &enemy->damage);
			else if (keep_elem)
				apply_damage(&keep_elem->damage, &enemy->damage);
		}
		if (enemy->recalc_path == 100)
		{
			f_way(enemy);
			enemy->goal.case_x = coo.case_x;
			enemy->goal.case_y = coo.case_y;
			enemy->goal.coo_y = coo.coo_y;
			enemy->goal.coo_x = coo.coo_x;
			pathfinder(data, enemy);
			calc_in_cell_path(data, enemy);
			print_path(enemy);
			enemy->calc = true;
		}
	}
	return (0);
}

void	take_damage_enemy(t_enemy *enemy)
{
	enemy->life -= enemy->damage.damage_take;
	enemy->damage.damage_take = 0;
	if (enemy->damage.poison_frame_take > 0)
	{
		enemy->life -= enemy->damage.poison_force_take;
		enemy->damage.poison_frame_take--;
		if (enemy->damage.poison_frame_take <= 0)
			enemy->damage.poison_force_take = 0;
	}
	if (enemy->damage.fire_frame_take > 0)
	{
		enemy->life -= enemy->damage.fire_force_take;
		enemy->damage.fire_frame_take--;
		if (enemy->damage.fire_frame_take <= 0)
			enemy->damage.fire_force_take = 0;
	}
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

void	spawn_item(t_data *data, t_enemy *enemy)
{
	double	new_x;
	double	new_y;
	double	new_deg;

	if (rand() % 100 <= enemy->drop_heal)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		if (new_x >= 64)
			new_x = 63.5;
		if (new_y >= 64)
			new_y = 63.5;
		if (new_x < 0)
			new_x = .5;
		if (new_y < 0)
			new_y = .5;
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, HEAL_POPO, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=new_x,.coo_y=new_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
	}
	if (rand() % 100 <= enemy->drop_floo)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		if (new_x >= 64)
			new_x = 63.5;
		if (new_y >= 64)
			new_y = 63.5;
		if (new_x < 0)
			new_x = .5;
		if (new_y < 0)
			new_y = .5;
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, FLOO_POPO, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
	}
	if (rand() % 100 <= enemy->drop_shield)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		if (new_x >= 64)
			new_x = 63.5;
		if (new_y >= 64)
			new_y = 63.5;
		if (new_x < 0)
			new_x = .5;
		if (new_y < 0)
			new_y = .5;
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, SHIELD_POPO, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
	}
	if (rand() % 100 <= enemy->drop_cloak)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		if (new_x >= 64)
			new_x = 63.5;
		if (new_y >= 64)
			new_y = 63.5;
		if (new_x < 0)
			new_x = .5;
		if (new_y < 0)
			new_y = .5;
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, INVI_POPO, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
	}

	if (data->wand.is_drop[1] != true && rand() % 100 <= enemy->drop_spider_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		if (new_x >= 64)
			new_x = 63.5;
		if (new_y >= 64)
			new_y = 63.5;
		if (new_x < 0)
			new_x = .5;
		if (new_y < 0)
			new_y = .5;
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, SPIDER_WAND, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[1] = true;
	}

	if (data->wand.is_drop[4] != true && rand() % 100 <= enemy->drop_dementor_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		if (new_x >= 64)
			new_x = 63.5;
		if (new_y >= 64)
			new_y = 63.5;
		if (new_x < 0)
			new_x = .5;
		if (new_y < 0)
			new_y = .5;
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, DEMENTOR_WAND, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[4] = true;
	}

	if (data->wand.is_drop[3] != true && rand() % 100 <= enemy->drop_elem_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		if (new_x >= 64)
			new_x = 63.5;
		if (new_y >= 64)
			new_y = 63.5;
		if (new_x < 0)
			new_x = .5;
		if (new_y < 0)
			new_y = .5;
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, ELEM_WAND, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[3] = true;
	}
	if (data->wand.is_drop[2] != true &&  rand() % 100 <= enemy->drop_wolf_wand)
	{
		new_x = enemy->center.coo_x + (10 - rand() % 20);
		new_y = enemy->center.coo_y + (10 - rand() % 20);
		if (new_x >= 64)
			new_x = 63.5;
		if (new_y >= 64)
			new_y = 63.5;
		if (new_x < 0)
			new_x = .5;
		if (new_y < 0)
			new_y = .5;
		new_deg = enemy->aff_deg + (60 - rand() % 120);
		data->item = add_end_lst(create_item(data, WOLF_WAND, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
		data->item = add_end_lst(create_item(data, PILLAR, &(t_fcoo){.case_x=enemy->center.case_x,.case_y=enemy->center.case_y,.coo_x=enemy->center.coo_x,.coo_y=enemy->center.coo_y},new_deg),data->item,f_item);
		make_move_item(data->item->dt, 5);
		data->wand.is_drop[2] = true;
		data->wand.is_drop[2] = true;
	}
}
void	win_xp(t_data *data, int type, double *xp)
{
	if (type == DEMENTOR)
		*xp +=  0.42/ (0.8 + (data->player.xp * 0.1));
	else if (type == SPIDER)
		*xp += 0.23/ (0.8 + (data->player.xp * 0.1));
	else if (type == ELEM)
		*xp += 0.35/ (0.8 + (data->player.xp * 0.1));
	else if (type == WOLF)
		*xp +=  0.5/ (0.8 + (data->player.xp * 0.1));
	else
		*xp +=  3/ (0.8 + (data->player.xp * 0.1));
}
void	move_enemy(t_data *data)
{
	t_lst	*lst;
	t_enemy	*enemy;
	t_lst	*next;

	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		next = lst->next;
		if ((enemy_vision(data, enemy) && enemy->way) || enemy->way || enemy->damage.confundo_force_take > 0)
			make_move_enemy(data, enemy);
		else
			gen_enemy_way(data, enemy);
		take_damage_enemy(enemy);
		if (enemy->life <= 0)
		{
			if (enemy->type != SNAKE && enemy->type != BIRD)
			{
				data->item = add_end_lst(create_item(data, ANIM_DEATH, &(t_fcoo){.case_x=enemy->center.case_x, .case_y=enemy->center.case_y, .coo_y= enemy->center.coo_y, .coo_x= enemy->center.coo_x}, data->map.mini.deg), data->item, f_item);
				if (enemy->damage.which_coa_take == data->player.coa)
					spawn_item(data, enemy);
			}
			if (enemy->damage.which_coa_take == data->player.coa)
			{
				data->sound = add_end_lst(create_sound(data, 25), data->sound, free_sound);
				win_xp(data, enemy->type, &data->player.xp);
				data->coa[data->player.coa].xp = data->player.xp;
			}
			else if (enemy->damage.which_coa_take == EARTH)
				win_xp(data, enemy->type, &data->coa[EARTH].xp);
			else if (enemy->damage.which_coa_take == AIR)
				win_xp(data, enemy->type, &data->coa[AIR].xp);
			else if (enemy->damage.which_coa_take == WATER)
				win_xp(data, enemy->type, &data->coa[WATER].xp);
			else if (enemy->damage.which_coa_take == FIRE)
				win_xp(data, enemy->type, &data->coa[FIRE].xp);
			
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
			data->enemy = remove_elem_lst(lst);
			f_elem_lst(lst);
			return ;
		}
		enemy->nb_move++;
		lst = next;
	}
}

