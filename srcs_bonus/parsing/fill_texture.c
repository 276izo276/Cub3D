/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:57:55 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:57:56 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "utils_bonus.h"
#include "ft_printf.h"
#include "color_bonus.h"
#include "parsing_bonus.h"

void	set_floor(char *line, t_data *data)
{
	int	start;

	if (!line[2])
		return ;
	if (data->map.floor)
	{
		ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"\
Texture >>> Duplicate entry for floor\n");
		f_exit(data, 1);
	}
	data->map.floor = malloc(sizeof(t_img));
	if (!data->map.floor)
		f_exit(data, 1);
	ft_bzero(data->map.floor, sizeof(t_img));
	data->map.floor->mlx = data->mlx.mlx;
	start = 3;
	start += get_start_path(&line[3]);
	data->map.floor->path = ft_strndup(&line[start],
			calc_path_size(&line[start]));
	if (!data->map.floor->path)
		f_exit(data, 1);
}

void	set_ceiling(char *line, t_data *data)
{
	int	start;

	if (!line[2])
		return ;
	if (data->map.ceiling)
	{
		ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"\
Texture >>> Duplicate entry for ceiling\n"_END);
		f_exit(data, 1);
	}
	data->map.ceiling = malloc(sizeof(t_img));
	if (!data->map.ceiling)
		f_exit(data, 1);
	ft_bzero(data->map.ceiling, sizeof(t_img));
	data->map.ceiling->mlx = data->mlx.mlx;
	start = 3;
	start += get_start_path(&line[3]);
	data->map.ceiling->path = ft_strndup(&line[start],
			calc_path_size(&line[start]));
	if (!data->map.ceiling->path)
		f_exit(data, 1);
}

int	fill_texture_color_data(t_lst *line, t_data *data)
{
	const char		*identifiers[] = {"NO", "SO", "WE", "EA", "FL", "CE", NULL};
	const t_txt_set	func_set_texture[] = {set_north, set_south, set_west,
		set_east, set_floor, set_ceiling};
	int				i;

	i = 0;
	while (identifiers[i])
	{
		if (ft_strncmp(identifiers[i], line->dt,
				ft_strlen(identifiers[i])) == 0)
		{
			func_set_texture[i](line->dt, data);
			return (0);
		}
		i++;
	}
	i = 0;
	while (((char *)line->dt)[i] && ((char *)line->dt)[i] == ' ')
		i++;
	if (((char *)line->dt)[i] == 0)
		return (0);
	return (1);
}
