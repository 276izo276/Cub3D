#include "struct_bonus.h"
#include "utils_bonus.h"
#include "enemy_bonus.h"

static int	man_dist(int startY, int startX, int endY, int endX)
{
	return (abs_value(startY - endY) + abs_value(startX - endX));
}

static int	is_a_wall(t_case *cur, int dir[2], t_data *data)
{
	if (data->map.tabmap[cur->case_y + dir[0]][cur->case_x + dir[1]] == '1')
		return (1);
	return (0);
}

static int	is_in_lst(t_case *cur, int dir[2], t_lst *lst, t_enemy *enemy)
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

static t_lst	*update_node(t_case *cur, int dir[2], t_lst *lst, t_enemy *enemy)
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
		lst = lst->next;
	}
	return (lst);
}

static	t_lst	*add_case_open(t_lst *open, t_lst **closed, t_enemy *enemy, t_data *data)
{
	const	dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
	int		i;

	open = get_first_elem_lst(open);
	while (i < 4)
	{
		if (!is_a_wall(open->dt, dir[i], data) && !is_in_lst(open->dt, dir[i], *closed, enemy))
		{
			if (is_in_lst(open->dt, dir[i], open, enemy))
				open = update_node(open->dt, dir[i], open, enemy);
			else
				add_node();
		}
	}
	return (get_first_elem_lst(open));
}

static	void	pathfinder(t_data *data, t_enemy *enemy)
{
	t_lst	*open;
	t_lst	*closed;

	open = add_end_lst(init_case(man_dist(enemy->center.case_y,
		enemy->center.case_x,enemy->goal.case_y,enemy->goal.case_x),
		enemy->center.case_y, enemy->center.case_y, NULL), NULL, f_case);
	closed = NULL;
	while (open)
	{
		open = add_case_open(open, &closed, enemy, data);
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