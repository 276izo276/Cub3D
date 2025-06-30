#include "struct.h"
#include "utils.h"
#include <stdlib.h>
#include "parsing.h"
#include "ft_printf.h"
#include "color.h"

static int	calc_path_size(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
	{
		i++;
	}
	return (i);
}

void	set_north(char *line, t_data *data)
{
	if (!line[2])
		return ;
	if (data->map.north)
	{
		ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"\
Texture >>> Duplicate entry for north\n");
		f_exit(data, 1);
	}
	data->map.north = malloc(sizeof(t_img));
	if (!data->map.north)
		f_exit(data, 1);
	ft_bzero(data->map.north, sizeof(t_img));
	data->map.north->mlx = data->mlx.mlx;
	data->map.north->path = ft_strndup(&line[3], calc_path_size(&line[3]));
	if (!data->map.north->path)
		f_exit(data, 1);
}

void	set_south(char *line, t_data *data)
{
	if (!line[2])
		return ;
	if (data->map.south)
	{
		ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"\
Texture >>> Duplicate entry for south\n");
		f_exit(data, 1);
	}
	data->map.south = malloc(sizeof(t_img));
	if (!data->map.south)
		f_exit(data, 1);
	ft_bzero(data->map.south, sizeof(t_img));
	data->map.south->mlx = data->mlx.mlx;
	data->map.south->path = ft_strndup(&line[3], calc_path_size(&line[3]));
	if (!data->map.south->path)
		f_exit(data, 1);
}

void	set_west(char *line, t_data *data)
{
	if (!line[2])
		return ;
	if (data->map.west)
	{
		ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"\
Texture >>> Duplicate entry for west\n");
		f_exit(data, 1);
	}
	data->map.west = malloc(sizeof(t_img));
	if (!data->map.west)
		f_exit(data, 1);
	ft_bzero(data->map.west, sizeof(t_img));
	data->map.west->mlx = data->mlx.mlx;
	data->map.west->path = ft_strndup(&line[3], calc_path_size(&line[3]));
	if (!data->map.west->path)
		f_exit(data, 1);
}

void	set_east(char *line, t_data *data)
{
	if (!line[2])
		return ;
	if (data->map.east)
	{
		ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"\
Texture >>> Duplicate entry for east\n");
		f_exit(data, 1);
	}
	data->map.east = malloc(sizeof(t_img));
	if (!data->map.east)
		f_exit(data, 1);
	ft_bzero(data->map.east, sizeof(t_img));
	data->map.east->mlx = data->mlx.mlx;
	data->map.east->path = ft_strndup(&line[3], calc_path_size(&line[3]));
	if (!data->map.east->path)
		f_exit(data, 1);
}
