/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_way.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:47:48 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:47:49 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "utils_bonus.h"

static t_lst	*add_case_near(t_lst *open, t_lst *closed, t_lst *node,
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
		if (!is_case_in_lst(new_y, new_x, closed)
			&& (data->map.tabmap[new_y][new_x] != '1'))
		{
			open = add_start_lst(init_t_coo(new_y, new_x), open, f_elem);
			error_occured(data, open, closed);
		}
	}
	return (open);
}

static void	get_case_way(t_lst *closed, t_lst *open, t_enemy *enemy)
{
	int	nb_elem_lst;
	int	nb_take;

	nb_elem_lst = ft_strlen_lst(closed);
	nb_take = rand() % nb_elem_lst;
	nb_elem_lst = 0;
	closed = get_first_elem_lst(closed);
	while (closed->next)
	{
		if (nb_elem_lst == nb_take)
		{
			enemy->goal.case_x = ((t_coo *)closed->dt)->x;
			enemy->goal.case_y = ((t_coo *)closed->dt)->y;
			f_all_lst(closed);
			f_all_lst(open);
			return ;
		}
		nb_elem_lst++;
		closed = closed->next;
	}
	f_all_lst(closed);
	f_all_lst(open);
}

void	flood_fill_get_way(t_data *data, int y, int x, t_enemy *enemy)
{
	t_lst	*closed;
	t_lst	*open;
	t_lst	*node;
	int		count;

	closed = NULL;
	open = add_end_lst(init_t_coo(y, x), NULL, f_elem);
	if (!open)
		f_exit(data, 1);
	count = 0;
	while (open)
	{
		node = open;
		open = remove_elem_lst(node);
		closed = move_to_end_lst(node, closed);
		if (count < 100)
		{
			open = add_case_near(open, closed, node, data);
			count++;
		}
	}
	get_case_way(closed, open, enemy);
}

void	gen_enemy_way(t_data *data, t_enemy *enemy)
{
	if (enemy->wait < 10)
	{
		enemy->wait++;
		return ;
	}
	flood_fill_get_way(data, enemy->center.case_y, enemy->center.case_x, enemy);
	pathfinder(data, enemy);
	calc_in_cell_path(data, enemy);
}
