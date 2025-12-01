#include "enemy_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"

int	man_dist(int startY, int startX, int endY, int endX)
{
	return (abs_value(startY - endY) + abs_value(startX - endX));
}

int	is_a_wall(t_case *cur, const int dir[2], t_data *data)
{
	if (!(cur->coo.case_y + dir[0] >= data->map.tabmap_height
		|| cur->coo.case_y + dir[0] < 0 || cur->coo.case_x + dir[1]
		>= ft_strlen(data->map.tabmap[cur->coo.case_y + dir[0]])
			|| cur->coo.case_x + dir[1] < 0)
			&& (data->map.tabmap[cur->coo.case_y
				+ dir[0]][cur->coo.case_x + dir[1]] == ' '
		|| data->map.tabmap[cur->coo.case_y + dir[0]][cur->coo.case_x
		+ dir[1]] == '1'))
		return (1);
	return (0);
}

int	is_in_lst(t_case *cur, const int dir[2], t_lst *lst, t_enemy *enemy)
{
	t_case	*cel;

	lst = get_first_elem_lst(lst);
	(void)enemy;
	while (lst)
	{
		cel = lst->dt;
		if (cel->coo.case_x == cur->coo.case_x + dir[1]
			&& cel->coo.case_y == cur->coo.case_y + dir[0])
		{
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

t_lst	*need_update_node(t_case *cel, t_case *cur, t_lst *save, t_lst **lst)
{
	cel->parent = cur;
	cel->r_cost = cur->r_cost + 1;
	cel->t_cost = cel->r_cost + cel->h_cost;
	save = *lst;
	*lst = remove_elem_lst(save);
	*lst = get_first_elem_lst(*lst);
	if (!*lst)
	{
		*lst = save;
		return (*lst);
	}
	while (*lst)
	{
		if (((t_case *)(*lst)->dt)->t_cost > cel->t_cost)
		{
			move_before_lst(save, *lst);
			return (*lst);
		}
		if (!(*lst)->next)
		{
			return (move_to_end_lst(save, *lst));
		}
		*lst = (*lst)->next;
	}
	return (NULL);
}

int	open_loop(t_enemy *enemy, t_lst **open, t_lst **closed, t_data *data)
{
	while (*open)
	{
		*open = add_case_open(*open, closed, enemy, data);
		if (*open && is_end_path(*open, enemy))
		{
			set_final_path(get_first_elem_lst(*open), enemy);
			f_list_final_path(*open, *closed);
			return (1);
		}
		*open = get_first_elem_lst(*open);
	}
	return (0);
}
