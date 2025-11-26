#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "struct_bonus.h"

static int	is_end_path(t_lst *open, t_enemy *enemy)
{
	open = get_first_elem_lst(open);
	if (((t_case *)open->dt)->coo.case_x == enemy->goal.case_x
		&& ((t_case *)open->dt)->coo.case_y == enemy->goal.case_y)
		return (1);
	return (0);
}

static t_lst	*update_node(t_case *cur, const int dir[2], t_lst *lst)
{
	t_case	*cel;
	t_lst	*save;

	save = NULL;
	lst = get_first_elem_lst(lst);
	while (lst)
	{
		cel = lst->dt;
		if (cel->coo.case_x == cur->coo.case_x + dir[1]
			&& cel->coo.case_y == cur->coo.case_y + dir[0])
		{
			if (cur->t_cost + 1 < cel->t_cost)
			{
				if (need_update_node(cel, cur, save, &lst))
					return (lst);
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

static t_lst	*add_node(t_case *cur, const int dir[2], t_lst *lst,
		t_enemy *enemy)
{
	t_case		*cel;
	const int	direc[2] = {cur->coo.case_y + dir[0], cur->coo.case_x + dir[1]};

	cel = init_case(man_dist(cur->coo.case_y + dir[0], cur->coo.case_x + dir[1],
				enemy->goal.case_y, enemy->goal.case_x), cur->r_cost + 1,
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
			if (rand() % 10 == 1)
				return (add_before_lst(cel, lst, f_case));
		if (((t_case *)lst->dt)->t_cost > cel->t_cost)
			return (add_before_lst(cel, lst, f_case));
		if (!lst->next)
			return (add_end_lst(cel, lst, f_case));
		lst = lst->next;
	}
	return (lst);
}

static void	exit_path_finder(t_data *data)
{
	f_exit(data, 1);
}

static t_lst	*add_case_open(t_lst *open, t_lst **closed, t_enemy *enemy,
		t_data *data)
{
	const int	dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
	int			i;
	t_lst		*lst;

	lst = get_first_elem_lst(open);
	open = remove_elem_lst(lst);
	open = get_first_elem_lst(open);
	*closed = move_to_end_lst(lst, *closed);
	i = 0;
	while (i < 4)
	{
		if (!is_a_wall(lst->dt, dir[i], data) && !is_in_lst(lst->dt, dir[i],
				*closed, enemy))
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
