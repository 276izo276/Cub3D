#include "struct_bonus.h"
#include "utils_bonus.h"
#include "enemy_bonus.h"
#include "cub3d_bonus.h"
#include <math.h>

#include <stdio.h>

static int	man_dist(int startY, int startX, int endY, int endX)
{
	return (abs_value(startY - endY) + abs_value(startX - endX));
}

static int	is_a_wall(t_case *cur, const int dir[2], t_data *data)
{
	if (data->map.tabmap[cur->case_y + dir[0]][cur->case_x + dir[1]] == '1' || data->map.tabmap[cur->case_y + dir[0]][cur->case_x + dir[1]] == 'D')
		return (1);
	return (0);
}

static int	is_in_lst(t_case *cur, const int dir[2], t_lst *lst, t_enemy *enemy)
{
	t_case	*cel;

	lst = get_first_elem_lst(lst);
	(void)enemy;
	// printf("NEW CASE y>>>%d     x>>>%d\n",cur->case_y + dir[0], cur->case_x + dir[1]);
	while (lst)
	{
		cel = lst->dt;
		// printf("OLD CASE y>>>%d     x>>>%d\n",cel->case_y,cel->case_x);
		if (cel->case_x == cur->case_x + dir[1] && cel->case_y == cur->case_y + dir[0])
		{
			// printf("OK IS INNNNNNNNNN\n");
			return (1);
		}
		lst = lst->next;
	}
	// printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOUT\n");
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
				if (cel->case_x == 27 && cel->case_y == 25)
				{
					// printf("UPDATE CASE UNDER START\n\n");
				}
				cel->parent = cur;
				cel->r_cost = cur->r_cost + 1;
				cel->t_cost = cel->r_cost + cel->h_cost;
				save = lst;
				lst = get_last_elem_lst(lst);
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
	const int	direc[2] = {cur->case_y + dir[0], cur->case_x + dir[1]};

	cel = init_case(man_dist(cur->case_y + dir[0],
		cur->case_x + dir[1], enemy->goal.case_y,enemy->goal.case_x),cur->r_cost + 1,
		(int *)direc, cur);
	if (!lst)
	{
		return (add_end_lst(cel, lst, f_case));
	}
	lst = get_last_elem_lst(lst);
	while (lst)
	{
		cases = lst->dt;
		if (cases->t_cost < cel->t_cost || !lst->prev)
		{
			if (!lst->prev)
				return (add_before_lst(cel, lst, f_case));
			lst = add_after_lst(cel, lst, f_case);
			return (lst);
		}
		if (lst->prev)
			lst = lst->prev;
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

	// printf("\n\nOPEN VALUE RM LST >>%p\n",open);
	lst = get_first_elem_lst(open);
	// printf("RM CASE y>>>%d    x>>>%d\n",((t_case*)lst->dt)->case_y,((t_case*)lst->dt)->case_x);
	// printf("NEXT ADR %p\n",lst->next);
	open = remove_elem_lst(lst);
	open = get_first_elem_lst(open);
	printf("OPEN VALUE RM LST >>%p\n",open);
	// lst = open;
	// open = remove_elem_lst(lst);
	*closed = move_to_end_lst(lst, *closed);
	i = 0;
	// printf("START BASE CASE y>>>%d    x>>>%d\n",((t_case*)lst->dt)->case_y,((t_case*)lst->dt)->case_x);
	while (i < 4)
	{
		// printf("CLOSED\n");
		if (!is_a_wall(lst->dt, dir[i], data) && !is_in_lst(lst->dt, dir[i], *closed, enemy))
		{
			printf("ADD CASE  i>>%d   %c\n",i,data->map.tabmap[((t_case *)lst->dt)->case_y + dir[i][0]][((t_case *)lst->dt)->case_x + dir[i][1]] );
			if (is_in_lst(lst->dt, dir[i], open, enemy))
			{
				open = update_node(lst->dt, dir[i], open);
				// printf("UPDATE NODE\n");
			}
			else
			{
				open = add_node(lst->dt, dir[i], open, enemy);
				// printf("FIRST CASE OPEN AFTER ADD next case y>>%d   x>>%d\n",((t_case *)open->dt)->case_y,((t_case *)open->dt)->case_x);
				// printf("NEW NODE\n");
			}
			if (!open)
				exit_path_finder(data);
		}
		i++;
	}
	// printf("FIRST CASE OPEN next case y>>%d   x>>%d\n",((t_case *)open->dt)->case_y,((t_case *)open->dt)->case_x);
	// printf("FIRST CASE CLOSED next case y>>%d   x>>%d\n",((t_case *)(*closed)->dt)->case_y,((t_case *)(*closed)->dt)->case_x);
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
	{
		// printf("HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		return ;
	}
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
	const int	dir[2] = {enemy->center.case_y, enemy->center.case_x};

	open = add_end_lst(init_case(man_dist(enemy->center.case_y,
		enemy->center.case_x,enemy->goal.case_y,enemy->goal.case_x),
		0, (int *)dir, NULL), NULL, f_case);
	printf("PASS HERE next case y>>%d   x>>%d\n",((t_case *)open->dt)->case_y,((t_case *)open->dt)->case_x);
	closed = NULL;
	// exit(1);
	while (open)
	{
		open = add_case_open(open, &closed, enemy, data);
		// exit(1);
		if (open && is_end_path(open, enemy))
		{
			set_final_path(get_first_elem_lst(open), enemy);
			f_list_final_path(open, closed);
			// printf("FOUND PATH\n");
			return ;
		}
		open = get_first_elem_lst(open);
		// printf("PASS HERE next case y>>%d   x>>%d\n",((t_case *)open->dt)->case_y,((t_case *)open->dt)->case_x);
	}
	printf("PATH NOOOOOOOOT FOUND\n");
	f_all_lst(closed);
	f_all_lst(open);
	// f_exit(data, 1);
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
		}
		else
		{
			cel->coo_x = 32;
			cel->coo_y = 32;
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

	if (enemy->wait < 100)
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
	printf("Foud Case y>%d   x>%d     value>>%c     center   y>%d   x>%d\n", y, x, data->map.tabmap[y][x],enemy->center.case_y,enemy->center.case_x);
	pathfinder(data, enemy);
	calc_in_cell_path(data, enemy);
	print_path(enemy);
}

void	calc_left_point(t_enemy *enemy)
{
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;

	rad = enemy->rad + (90 * (M_PI / 180));
	dx = sin(rad);
	dy = cos(rad);
	// printf("dx>>%lf     dy>>%lf\n",dx,dy);
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
	double	rad;
	double	dy;
	double	dx;
	double	v_normalize;

	rad = enemy->rad - (90 * (M_PI / 180));
	dx = sin(rad);
	dy = cos(rad);
	// printf("dx>>%lf     dy>>%lf\n",dx,dy);
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

static void	make_move_enemy(t_data *data, t_enemy *enemy)
{
	(void)data;
	(void)enemy;
	// printf("Coo in case x>>%d    y>>%d\n",enemy->way->coo_x,enemy->way->coo_y);
	if (enemy->calc == true)
	{
		enemy->calc = false;
		double	deg;
		deg = 0;
		enemy->rad = 0;
		int	diff_x = enemy->way->coo_x - enemy->center.coo_x;
		int	diff_y = enemy->way->coo_y - enemy->center.coo_y;
		if (diff_x == 0 && diff_y == 0)
		{
			enemy->calc = true;
			f_case(enemy->way);
			enemy->way = NULL;
			enemy->wait = 0;
			return ;
		}
		// printf("x>>>%d     y>>>%d\n",diff_x,diff_y);
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
		// printf("deg angle >>>%lf\n",deg);
		enemy->rad = deg * (M_PI / 180);
	}
	double	dy;
	double	dx;
	double	v_normalize;
	dx = sin(enemy->rad);
	dy = cos(enemy->rad);
	// printf("dx>>%lf     dy>>%lf\n",dx,dy);
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
	enemy->center.coo_x += dx;
	enemy->center.coo_y += dy;
	calc_left_point(enemy);
	calc_right_point(enemy);
	// enemy->center.coo_x = round(enemy->center.coo_x);
	// enemy->center.coo_y = round(enemy->center.coo_y);
	// printf("\ny>>>%lf      x>>>%lf\n",enemy->center.coo_y,enemy->center.coo_x);
	// printf("CURRENT   y>>>%d    x>>%d\n",enemy->center.case_x,enemy->center.case_y);
	// printf("GOAL   y>>>%d    x>>%d\n",enemy->goal.case_x,enemy->goal.case_y);
	if (are_double_close(enemy->center.coo_x, enemy->goal.coo_x)
		&& are_double_close(enemy->center.coo_y, enemy->goal.coo_y)
		&& enemy->center.case_x == enemy->goal.case_x
		&& enemy->center.case_y == enemy->goal.case_y)
	{
		f_case(enemy->way);
		enemy->way = NULL;
		enemy->wait = 0;
		enemy->calc = true;
		printf("END TRAJ IN CASE\n");
		return ;
	}
	if (enemy->center.coo_x < 0 || enemy->center.coo_x > 64
		|| enemy->center.coo_y < 0 || enemy->center.coo_y > 64)
	{
		if (enemy->center.coo_x < 0)
			enemy->center.coo_x = 64;
		if (enemy->center.coo_x > 64)
			enemy->center.coo_x = 0;
		if (enemy->center.coo_y < 0)
			enemy->center.coo_y = 64;
		if (enemy->center.coo_y > 64)
			enemy->center.coo_y = 0;
		if (enemy->way->child)
			enemy->way->child->parent = NULL;
		else
		{
			f_case(enemy->way);
			enemy->way = NULL;
			enemy->wait = 0;
			enemy->calc = true;
			printf("OUT OF CASE END TRAJ\n");
			return ;
		}
		t_case	*tmp = enemy->way;
		enemy->way = enemy->way->child;
		enemy->center.case_x = enemy->way->case_x;
		enemy->center.case_y = enemy->way->case_y;
		f_case(tmp);
		enemy->calc = true;
	}
	// if (delta_x > 0)
	// 	rx = (64 - enemy->center.coo_x) / delta_x;
	// else
	// 	rx = -enemy->center.coo_x / delta_x;
	// if (delta_y > 0)
	// 	ry = (64 - enemy->center.coo_y) / delta_y;
	// else
	// 	ry = -enemy->center.coo_y / delta_y;
	// printf("enemy->rad >>>%lf\n", enemy->rad);
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
		else
			make_move_enemy(data, enemy);
		lst = lst->next;
	}
}
