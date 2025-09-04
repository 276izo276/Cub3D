#include "struct_bonus.h"
#include "utils_bonus.h"
#include "enemy_bonus.h"


#include <stdio.h>

static int	man_dist(int startY, int startX, int endY, int endX)
{
	return (abs_value(startY - endY) + abs_value(startX - endX));
}

static int	is_a_wall(t_case *cur, const int dir[2], t_data *data)
{
	if (data->map.tabmap[cur->case_y + dir[0]][cur->case_x + dir[1]] == '1')
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
			return (1);
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
			if (cur->r_cost + 1 < cel->r_cost)
			{
				cel->parent = cur;
				cel->r_cost = cur->r_cost + 1;
				cel->t_cost = cel->r_cost + cel->h_cost;
				save = lst;
				while (lst->prev && ((t_case *)lst->prev->dt)->t_cost > cel->t_cost)
				{
					lst = lst->prev;
				}
				if (lst != save)
				{
					remove_elem_lst(save);
					move_before_lst(save, lst);
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
	t_case	*cases;
	const int	direc[2] = {enemy->center.case_y, enemy->center.case_y};

	cel = init_case(man_dist(cur->case_y + dir[0],
		cur->case_x + dir[0], enemy->goal.case_y,enemy->goal.case_x),cur->r_cost + 1,
		direc, cur);
	if (!lst)
		return (add_end_lst(cel, lst, f_case));
	lst = get_first_elem_lst(lst);
	while (lst)
	{
		cases = lst->dt;
		if (cases->t_cost > cel->t_cost)
		{
			lst = add_before_lst(cel, lst, f_case);
			return (lst);
		}
		if (lst->next)
			lst = lst->next;
		else
			break ;
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
	open = get_first_elem_lst(remove_elem_lst(lst));
	// lst = open;
	// open = remove_elem_lst(lst);
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

	cel = lst->dt;
	cel->is_path = 1;
	while (cel->parent)
	{
		cel->parent->child = cel;
		cel->parent->is_path = 1;
		cel = cel->parent;
	}
	enemy->way = cel;
}

static void	pathfinder(t_data *data, t_enemy *enemy)
{
	t_lst	*open;
	t_lst	*closed;
	const int	dir[2] = {enemy->center.case_y, enemy->center.case_y};

	open = add_end_lst(init_case(man_dist(enemy->center.case_y,
		enemy->center.case_x,enemy->goal.case_y,enemy->goal.case_x),
		0, dir, NULL), NULL, f_case);
	closed = NULL;
	while (open)
	{
		open = add_case_open(open, &closed, enemy, data);
		if (is_end_path(open, enemy))
		{
			set_final_path(get_first_elem_lst(open), enemy);
			f_list_final_path(open, closed);
			printf("FOUND PATH\n");
			return ;
		}
		printf("PASS HERE\n");
	}
	printf("PATH NOOOOOOOOT FOUND\n");
	f_all_lst(closed);
}

static void	print_path(t_enemy *enemy)
{
	t_case	*cel;

	cel = enemy->way;
	while (cel)
	{
		printf("case_y>>>%d      case_x>>>%d\n",cel->case_y,cel->case_x);
		cel = cel->child;
	}
}

static void	gen_enemy_way(t_data *data, t_enemy *enemy)
{
	int	x;
	int	y;
	int	count;
	int	len_line;
	int	len_tab;

	len_tab = ft_tab_strlen(data->map.tabmap) - 1;
	y = rand() % (len_tab);
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
	printf("Foud Case y>%d   x>%d     value>>%c\n", y, x, data->map.tabmap[y][x]);
	pathfinder(data, enemy);
	print_path(enemy);
}

void	move_enemy(t_data *data)
{
	t_lst	*lst;
	t_enemy	*enemy;

	lst = get_first_elem_lst(data->enemy);
	while (lst)
	{
		enemy = lst->dt;
		if (!enemy->way)
			gen_enemy_way(data, enemy);
		lst = lst->next;
	}
}