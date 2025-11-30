#include "enemy_bonus.h"
#include <stdlib.h>
#include "cub3d_bonus.h"

void	set_final_path(t_lst *lst, t_enemy *enemy)
{
	t_case	*cel;

	if (!lst)
		return ;
	cel = lst->dt;
	cel->is_path = 1;
	enemy->goal.case_x = cel->coo.case_x;
	enemy->goal.case_y = cel->coo.case_y;
	while (cel->parent)
	{
		cel->parent->child = cel;
		cel->parent->is_path = 1;
		cel = cel->parent;
	}
	enemy->way = cel;
}

void	end_pathfinder(t_lst *closed, t_lst *open, t_enemy *enemy)
{
	int	nb_elem_lst;
	int	nb_take;

	nb_elem_lst = ft_strlen_lst(closed);
	nb_take = rand() % nb_elem_lst;
	nb_elem_lst = 0;
	closed = get_first_elem_lst(closed);

	f_all_lst(closed);
	f_all_lst(open);
	return ;  // --> les 3 lignes sont bizarre mais sans sa les enemy font n imp
	while (closed->next)
	{
		if (nb_elem_lst == nb_take)
		{
			set_final_path(closed, enemy);
			f_list_final_path(open, closed);
			return ;
		}
		nb_elem_lst++;
		closed = closed->next;
	}
	f_all_lst(closed);
	f_all_lst(open);
}

void	pathfinder(t_data *data, t_enemy *enemy)
{
	t_lst		*open;
	t_lst		*closed;
	const int	dir[2] = {enemy->center.case_y, enemy->center.case_x};

	open = add_end_lst(init_case(man_dist(enemy->center.case_y,
					enemy->center.case_x, enemy->goal.case_y,
					enemy->goal.case_x), 0, (int *)dir, NULL), NULL, f_case);
	closed = NULL;
	if (open && is_end_path(open, enemy))
	{
		set_final_path(get_first_elem_lst(open), enemy);
		f_list_final_path(open, closed);
		return ;
	}
	if (open_loop(enemy, &open, &closed, data))
		return ;
	end_pathfinder(closed, open, enemy);
}
