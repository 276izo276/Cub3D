#include "struct.h"
#include "color.h"
#include "utils.h"
#include "ft_printf.h"

static void	is_valid_char_map(char c, int y, int x, t_data *data)
{
	const char	tab[] = {'0', '1', ' ', 'N', 'S', 'W', 'E', 0};
	int			i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == c && i >= 3)
		{
			if (data->map.player_start)
			{
				ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"Map >>> "\
					"2 player start found\n"_END);
				f_exit(data, 1);
			}
			data->map.player_start = init_t_coo(y, x);
			if (!data->map.player_start)
				f_exit(data, 1);
			return ;
		}
		else if (tab[i] == c && i <= 2)
			return ;
		i++;
	}
	ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"Map >>> '"\
_RED"%c"_PURPLE"' is not a valid character\n"_END, c);
	f_exit(data, 1);
}

static void	check_map_valid_char(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.tabmap && data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			is_valid_char_map(data->map.tabmap[y][x], y, x, data);
			x++;
		}
		y++;
	}
}

int	is_case_in_lst(int y, int x, t_lst *lst)
{
	lst = get_first_elem_lst(lst);
	while (lst)
	{
		if (((t_coo *)lst->dt)->y == y && ((t_coo *)lst->dt)->x == x)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	error_map_not_closed(t_lst *closed, t_lst *open, t_data *data)
{
	ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"Map >>> "\
		"map is not closed\n"_END);
	f_all_lst(closed);
	f_all_lst(open);
	f_exit(data, 1);
}

t_lst	*add_case_near(t_lst *open, t_lst *closed, t_lst *node, t_data *data)
{
	const int	coo[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};
	int			i;
	int			new_y;
	int			new_x;

	i = -1;
	while (++i < 4)
	{
		new_y = ((t_coo *)node->dt)->y + coo[i][0];
		new_x = ((t_coo *)node->dt)->x + coo[i][1];
		if (new_y >= data->map.tabmap_height || new_y < 0
			|| new_x >= ft_strlen(data->map.tabmap[new_y]) || new_x < 0
			|| data->map.tabmap[new_y][new_x] == ' ')
			error_map_not_closed(closed, open, data);
		if (!is_case_in_lst(new_y, new_x, closed) && data->map.tabmap[new_y][new_x] != '1')
		{
			open = add_start_lst(init_t_coo(new_y, new_x), open, f_elem);
			if (!open)
			{
				f_all_lst(closed);
				f_exit(data, 1);
			}
		}
	}
	return (open);
}

void	check_map_is_closed(t_data *data)
{
	t_lst	*closed;
	t_lst	*open;
	t_lst	*node;

	closed = NULL;
	open = add_end_lst(init_t_coo(data->map.player_start->y,
				data->map.player_start->x), NULL, f_elem);
	if (!open)
		f_exit(data, 1);
	while (open)
	{
		node = open;
		open = remove_elem_lst(node);
		closed = move_to_end_lst(node, closed);
		open = add_case_near(open, closed, node, data);
	}
	f_all_lst(closed);
}

void	verif_map(t_data *data)
{
	check_map_valid_char(data);
	if (!data->map.player_start)
	{
		ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"Map >>> "\
			"no player start found\n"_END);
		f_exit(data, 1);
	}
	check_map_is_closed(data);
}
