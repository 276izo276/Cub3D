/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:58:06 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:58:07 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_bonus.h"
#include "utils_bonus.h"
#include "ft_printf.h"

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
	ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
		"Map >>> ""map is not closed, player can escape\n"_END);
	f_all_lst(closed);
	f_all_lst(open);
	f_exit(data, 1);
}

void	error_occured(t_data *data, t_lst *open, t_lst *closed)
{
	if (!open)
	{
		f_all_lst(closed);
		f_exit(data, 1);
	}
}
