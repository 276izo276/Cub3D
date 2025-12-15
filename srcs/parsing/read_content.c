/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:45:50 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/15 11:52:17 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "struct.h"
#include "unistd.h"
#include "utils.h"
#include <fcntl.h>

void	verif_file_name(t_data *data)
{
	if (data->ac != 2 || ft_strlen(data->av[1]) <= 4
		|| ft_strcmp(&data->av[1][ft_strlen(data->av[1]) - 4], ".cub"))
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>>" " no map in argument\n"_END);
		f_exit(data, 1);
	}
}

static void	handle_fail_open(t_data *data)
{
	ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
		"Map >>>" " Fail to open map\n"_END);
	f_exit(data, 1);
}

void	get_content_file(t_data *data)
{
	char	*line;

	data->map.fd = open(data->av[1], O_RDONLY);
	if (data->map.fd == -1)
		handle_fail_open(data);
	while (get_next_line(data->map.fd, &line))
	{
		if (!line)
		{
			data->map.lines = get_first_elem_lst(data->map.lines);
			close(data->map.fd);
			return ;
		}
		data->map.lines = add_end_lst(rmbn_dup(line), data->map.lines, f_elem);
		if (!data->map.lines)
		{
			close(data->map.fd);
			f_exit(data, 1);
		}
	}
	close(data->map.fd);
	f_exit(data, 1);
}
