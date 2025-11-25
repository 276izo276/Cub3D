#include "struct_bonus.h"
#include "enemy_bonus.h"
#include "utils_bonus.h"


int	man_dist(int startY, int startX, int endY, int endX)
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
	if (cur->coo.case_y + dir[0] >= y || cur->coo.case_x + dir[1] >= x
		|| cur->coo.case_y + dir[0] < 0 || cur->coo.case_x + dir[1] < 0)
		return (1);
	if (!(cur->coo.case_y + dir[0] >= data->map.tabmap_height
		|| cur->coo.case_y + dir[0] < 0
		|| cur->coo.case_x + dir[1] >= ft_strlen(data->map.tabmap[cur->coo.case_y
			+ dir[0]]) || cur->coo.case_x + dir[1] < 0
		|| data->map.tabmap[cur->coo.case_y + dir[0]][cur->coo.case_x
			+ dir[1]] == ' ') && data->map.tabmap[cur->coo.case_y
				+ dir[0]][cur->coo.case_x + dir[1]] == '1')
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
		if (cel->coo.case_x == cur->coo.case_x + dir[1] && cel->coo.case_y == cur->coo.case_y + dir[0])
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
		if (cel->coo.case_x == cur->coo.case_x + dir[1] && cel->coo.case_y == cur->coo.case_y + dir[0])
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
	const int	direc[2] = {cur->coo.case_y + dir[0], cur->coo.case_x + dir[1]};

	cel = init_case(man_dist(cur->coo.case_y + dir[0],
		cur->coo.case_x + dir[1], enemy->goal.case_y,enemy->goal.case_x),cur->r_cost + 1,
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
	if (((t_case *)open->dt)->coo.case_x == enemy->goal.case_x
		&& ((t_case *)open->dt)->coo.case_y == enemy->goal.case_y)
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
	enemy->goal.case_x = cel->coo.case_x;
	enemy->goal.case_y = cel->coo.case_y;
}

void	pathfinder(t_data *data, t_enemy *enemy)
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
