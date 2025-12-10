/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:48:38 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:48:39 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

static void	error_occured(t_data *data, t_lst *open, t_lst *closed)
{
	if (!open)
	{
		f_all_lst(closed);
		f_exit(data, 1);
	}
}

static int	is_case_in_lst(int y, int x, t_lst *lst)
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

static int	add_case_near(t_lst **open, t_lst *closed, t_lst *node,
		t_data *data)
{
	const int	coo[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
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
			return (1);
		if (!is_case_in_lst(new_y, new_x, closed)
			&& (data->map.tabmap[new_y][new_x] != '1'))
		{
			*open = add_start_lst(init_t_coo(new_y, new_x), *open, f_elem);
			error_occured(data, *open, closed);
		}
	}
	return (0);
}

int	verif_enemy_is_closed(t_data *data, int y, int x)
{
	t_lst	*closed;
	t_lst	*open;
	t_lst	*node;

	closed = NULL;
	open = add_end_lst(init_t_coo(y, x), NULL, f_elem);
	if (!open)
		f_exit(data, 1);
	while (open)
	{
		node = open;
		open = remove_elem_lst(node);
		closed = move_to_end_lst(node, closed);
		if (add_case_near(&open, closed, node, data))
		{
			f_all_lst(open);
			f_all_lst(closed);
			return (1);
		}
	}
	f_all_lst(closed);
	return (0);
}

t_lst	*check_enemy_can_escape(t_data *data, t_lst *lst)
{
	t_enemy	*enemy;
	t_lst	*next;

	enemy = lst->dt;
	next = lst->next;
	if (verif_enemy_is_closed(data, enemy->center.case_y,
			enemy->center.case_x))
		data->enemy = remove_f_elem_lst(lst);
	return (next);
}
