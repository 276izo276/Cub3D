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
	if (data->map.tabmap[cur->case_y + dir[0]][cur->case_x + dir[1]] == '1')
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

#include <string.h>
#include <errno.h>

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
	// printf("OPEN VALUE RM LST >>%p\n",open);
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
			// printf("ADD CASE  i>>%d   %c\n",i,data->map.tabmap[((t_case *)lst->dt)->case_y + dir[i][0]][((t_case *)lst->dt)->case_x + dir[i][1]] );
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
			{
				// printf("EXIT HERE >>%p    i>%d   %s\n",open,i,strerror(errno));
				exit_path_finder(data);
			}
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
	while (cel->child)
	{
		cel = cel->child;
	}
	enemy->goal.case_x = cel->case_x;
	enemy->goal.case_y = cel->case_y;
	// printf("GOTO  case_y>>%d      case_x>>%d\n",enemy->goal.case_y,enemy->goal.case_x);
}

static void	pathfinder(t_data *data, t_enemy *enemy)
{
	t_lst	*open;
	t_lst	*closed;
	const int	dir[2] = {enemy->center.case_y, enemy->center.case_x};

	open = add_end_lst(init_case(man_dist(enemy->center.case_y,
		enemy->center.case_x,enemy->goal.case_y,enemy->goal.case_x),
		0, (int *)dir, NULL), NULL, f_case);
	// printf("PASS HERE next case y>>%d   x>>%d\n",((t_case *)open->dt)->case_y,((t_case *)open->dt)->case_x);
	closed = NULL;
	// exit(1);
	if (open && is_end_path(open, enemy))
	{
		set_final_path(get_first_elem_lst(open), enemy);
		f_list_final_path(open, closed);
		// printf("FOUND PATH\n");
		return ;
	}
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
		// t_lst	*tmp = open;
		// printf("start print open \n");
		// while (tmp)
		// {
		// 	printf("t_cost>%d   r_cost>%d    h_cost>%d\n",((t_case*)tmp->dt)->t_cost,((t_case*)tmp->dt)->r_cost,((t_case*)tmp->dt)->h_cost);
		// 	tmp = tmp->next;
		// }
		// printf("PASS HERE next case y>>%d   x>>%d\n",((t_case *)open->dt)->case_y,((t_case *)open->dt)->case_x);
	}
	int	nb_elem_lst = ft_strlen_lst(closed);
	int	nb_take = rand() % nb_elem_lst;
	// printf("TAKE NB >>>%d in    >>>%d   elem",nb_take,nb_elem_lst);
	nb_elem_lst = 0;
	closed = get_first_elem_lst(closed);
	while (closed->next)
	{
		if (nb_elem_lst == nb_take)
		{
			set_final_path(closed, enemy);
			f_list_final_path(open, closed);
			// printf("CREATE NEW PATH AFTER NOT FOUND\n");
			return;
		}
		nb_elem_lst++;
		closed = closed->next;
	}
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
		// printf("case_y>>>%d      case_x>>>%d    cooy>>%d    coox>%d\n",cel->case_y,cel->case_x,cel->coo_y,cel->coo_x);
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
	// printf("Found Case y>%d   x>%d     value>>%c     center   y>%d   x>%d\n", y, x, data->map.tabmap[y][x],enemy->center.case_y,enemy->center.case_x);
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


void	try_hit_enemys(t_enemy *elem, t_data *data)
{
	// t_enemy		*enemy;
	t_item		*item;
	t_lst		*lst;
	t_hitray	ray;
	t_lst		*next;

	lst = get_first_elem_lst(data->item);
	while (lst)
	{
		item = lst->dt;
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
			elem->damage.damage_take += item->damage.damage_do;
			elem->damage.damage_spider_take += item->damage.damage_spider_do;
			elem->damage.damage_dementor_take += item->damage.damage_dementor_do;
			elem->damage.slow_force_take += item->damage.slow_force_do;
			elem->damage.slow_frame_take += item->damage.slow_frame_do;
			elem->damage.poison_force_take += item->damage.poison_force_do;
			elem->damage.poison_frame_take += item->damage.poison_frame_do;
			elem->damage.fire_force_take += item->damage.fire_force_do;
			elem->damage.fire_frame_take += item->damage.fire_frame_do;
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue;
		}
		ray.dx = item->center.case_x * 64 + item->center.coo_x;
		ray.dy = item->center.case_y * 64 + item->center.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			elem->damage.damage_take += item->damage.damage_do;
			elem->damage.damage_spider_take += item->damage.damage_spider_do;
			elem->damage.damage_dementor_take += item->damage.damage_dementor_do;
			elem->damage.slow_force_take += item->damage.slow_force_do;
			elem->damage.slow_frame_take += item->damage.slow_frame_do;
			elem->damage.poison_force_take += item->damage.poison_force_do;
			elem->damage.poison_frame_take += item->damage.poison_frame_do;
			elem->damage.fire_force_take += item->damage.fire_force_do;
			elem->damage.fire_frame_take += item->damage.fire_frame_do;
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue;
		}
		ray.dx = item->right.case_x * 64 + item->right.coo_x;
		ray.dy = item->right.case_y * 64 + item->right.coo_y;
		calc_scal(&ray);
		if (ray.hit == true)
		{
			elem->damage.damage_take += item->damage.damage_do;
			elem->damage.damage_spider_take += item->damage.damage_spider_do;
			elem->damage.damage_dementor_take += item->damage.damage_dementor_do;
			elem->damage.slow_force_take += item->damage.slow_force_do;
			elem->damage.slow_frame_take += item->damage.slow_frame_do;
			elem->damage.poison_force_take += item->damage.poison_force_do;
			elem->damage.poison_frame_take += item->damage.poison_frame_do;
			elem->damage.fire_force_take += item->damage.fire_force_do;
			elem->damage.fire_frame_take += item->damage.fire_frame_do;
			next = lst->next;
			data->item = remove_elem_lst(lst);
			f_elem_lst(lst);
			lst = next;
			continue;
		}
		lst = lst->next;
	}
}

static void	make_move_enemy(t_data *data, t_enemy *enemy)
{
	if (enemy->calc == true)
	{
		// printf("recalc\n");
		enemy->calc = false;
		double	deg;
		deg = 0;
		enemy->rad = 0;
		double	diff_x = enemy->way->coo_x - enemy->center.coo_x;
		double	diff_y = enemy->way->coo_y - enemy->center.coo_y;
		// printf("x>>>%d     y>>>%d\n",diff_x,diff_y);
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
		// printf("deg angle >>>%lf\n",deg);
		// printf("deg angle >>>%lf     player>>%lf\n",deg,data->map.mini.deg);
		enemy->deg = deg;
		enemy->rad = deg * (M_PI / 180);
	}
	//DBG1printf("m3\n");
	calc_left_point(enemy);
	calc_right_point(enemy);
	enemy->left_before.coo_x = enemy->left.coo_x;
	enemy->left_before.coo_y = enemy->left.coo_y;
	enemy->left_before.case_x = enemy->left.case_x;
	enemy->left_before.case_y = enemy->left.case_y;
	enemy->right_before.coo_x = enemy->right.coo_x;
	enemy->right_before.coo_y = enemy->right.coo_y;
	enemy->right_before.case_x = enemy->right.case_x;
	enemy->right_before.case_y = enemy->right.case_y;
	// enemy->center_before.coo_x = enemy->center.coo_x;
	// enemy->center_before.coo_y = enemy->center.coo_y;
	// enemy->center_before.case_x = enemy->center.case_x;
	// enemy->center_before.case_y = enemy->center.case_y;

	if (enemy->dist_player < 20)
		return ;
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
	if (are_double_close(enemy->center.coo_x, enemy->goal.coo_x)
		&& are_double_close(enemy->center.coo_y, enemy->goal.coo_y)
		&& enemy->center.case_x == enemy->goal.case_x
		&& enemy->center.case_y == enemy->goal.case_y)
	{
		f_case(enemy->way);
		enemy->way = NULL;
		enemy->wait = 0;
		enemy->calc = true;
		// printf("END TRAJ IN CASE\n");
		return ;
	}
	//DBG1printf("m4\n");
	enemy->center.coo_x += dx;
	enemy->center.coo_y += dy;
	if (enemy->calc_path > 0)
		enemy->calc_path--;
	// printf("calc_path >>%d\n",enemy->calc_path);
	calc_left_point(enemy);
	calc_right_point(enemy);
	//DBG1printf("m5\n");
	try_hit_enemys(enemy, data);
	// enemy->center.coo_x = round(enemy->center.coo_x);
	// enemy->center.coo_y = round(enemy->center.coo_y);
	// printf("CURRENT   y>>>%d    x>>%d\n",enemy->center.case_x,enemy->center.case_y);
	// printf("y>>>%lf      x>>>%lf\n",enemy->center.coo_y,enemy->center.coo_x);
	// printf("way_y>%d   way_x>%d\n",enemy->way->coo_y,enemy->way->coo_x);
	// printf("GOAL   y>>>%d    x>>%d\n",enemy->goal.case_x,enemy->goal.case_y);
	// printf("goal >>%lf   %lf\n",enemy->goal.coo_x,enemy->goal.coo_y);
	// printf("goal case >>%d   %d\n",enemy->goal.case_x,enemy->goal.case_y);
	// printf("enemy is in case  >>%d   %d\n",enemy->center.case_x,enemy->center.case_y);
	if (enemy->center.coo_x < 0 || enemy->center.coo_x >= 64
		|| enemy->center.coo_y < 0 || enemy->center.coo_y >= 64)
	{
		// printf("Change Case\n");
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
			// printf("OUT OF CASE END TRAJ\n");
			return ;
		}
		t_case	*tmp = enemy->way;
		enemy->way = enemy->way->child;
		enemy->center.case_x = enemy->way->case_x;
		enemy->center.case_y = enemy->way->case_y;
		f_case(tmp);
		enemy->calc = true;
	}
	//DBG1printf("m6\n");
	//DBG1printf("m7\n");

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

int	see_player(t_data *data, t_enemy *enemy)
{
	double	deg;

	deg = 0;
	int	diff_x = data->player.coo.case_x * 64 + data->player.coo.coo_x
	- enemy->center.case_x * 64 - enemy->center.coo_x;
	int	diff_y = data->player.coo.case_y * 64 + data->player.coo.coo_y
	- enemy->center.case_y * 64 - enemy->center.coo_y;
	if (diff_x == 0 && diff_y == 0)
	{
		return (0);
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
	// printf("\ndeg angle to player>>>%lf     base>>%lf\n",deg,enemy->deg);
	// printf("\ndeg angle to player>>>%lf     %lf     %lf\n",enemy->deg - 90 + 360, deg + 360, enemy->deg + 90 + 360);
	if ((deg + 360 >= enemy->deg - 90 + 360
		&& deg + 360 <= enemy->deg + 90 + 360)
	||
		enemy->calc_path > 0)
	{
		// printf("ray lauch try see enemy   %lf     %lf\n",deg,enemy->deg);
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
		// printf("Angle >%lf       dx>>%lf        dy>>%lf\n",ray.deg,ray.delta_x,ray.delta_y);
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
		double	dist_player = sqrt(((data->player.coo.case_y
		- ray.start_case_y) * 64.0 + (data->player.coo.coo_y
		- ray.start_coo_y)) * ((data->player.coo.case_y
		- ray.start_case_y) * 64.0 + (data->player.coo.coo_y
		- ray.start_coo_y)) + ((data->player.coo.case_x
		- ray.start_case_x) * 64.0 + (data->player.coo.coo_x
		- ray.start_coo_x)) * ((data->player.coo.case_x
		- ray.start_case_x) * 64.0 + (data->player.coo.coo_x
		- ray.start_coo_x)));
		enemy->dist_player = dist_player;
		// printf("dist player >%lf    dist_wall >%lf\n",dist_player, ray.dist_wall);
		if (dist_player < ray.dist_wall || enemy->calc_path > 0)
		{
			// printf("SEE PLAYER GO ON IT     im in x>%d  y>%d\n",enemy->center.case_x,enemy->center.case_y);
			if (dist_player < ray.dist_wall)
				enemy->calc_path = 30;
			if (dist_player < 32)
			{
				// printf("Damage player\n");
				// data->player.damage.damage_take += enemy->damage.damage_do;
				// data->player.damage.slow_force_take += enemy->damage.slow_force_do;
				// data->player.damage.poison_force_take += enemy->damage.poison_force_do;
				// data->player.damage.fire_force_take += enemy->damage.fire_force_do;
			}
			while (enemy->way)
			{
				if (enemy->way->child)
				{
					enemy->way = enemy->way->child;
					f_case(enemy->way->parent);
					enemy->way->parent = NULL;
				}
				else
				{
					f_case(enemy->way);
					enemy->way = NULL;
				}
			}
			// printf("pointer way >%p",enemy->way);
			enemy->goal.case_x = data->player.coo.case_x;
			enemy->goal.case_y = data->player.coo.case_y;
			enemy->goal.coo_y = data->player.coo.coo_y;
			enemy->goal.coo_x = data->player.coo.coo_x;
			pathfinder(data, enemy);
			calc_in_cell_path(data, enemy);
			print_path(enemy);
			enemy->calc = true;
			return (1);
		}
	}
	return (0);
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
		if ((see_player(data, enemy) && enemy->way) || enemy->way)
			make_move_enemy(data, enemy);
		else
			gen_enemy_way(data, enemy);
		
		enemy->life -= enemy->damage.damage_take;
		enemy->damage.damage_take = 0;
		//DBG1printf("enemy life > %lf\n",enemy->life);
		if (enemy->life <= 0)
		{
			data->enemy = remove_elem_lst(lst);
			f_elem_lst(lst);
			return ;
		}
		lst = next;
	}
}
