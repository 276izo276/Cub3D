#include "color_bonus.h"
#include "debug_bonus.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"

static int	fill_texture_color_data(t_lst *line, t_data *data)
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

void	get_texture(t_data *data)
{
	t_lst	*map;

	map = get_first_elem_lst(data->map.lines);
	while (map)
	{
		if (fill_texture_color_data(map, data))
		{
			open_textures(data);
			break ;
		}
		map = map->next;
	}
	while (map)
	{
		data->map.map = add_end_lst(ft_strndup(map->dt, ft_strlen(map->dt)),
				data->map.map, f_elem);
		if (!data->map.map)
			return ;
		map = map->next;
	}
}

static	void create_door_map(t_data *data, int size)
{
	int	y;
	int	size_line;

	y = 0;
	data->map.door_map = malloc(sizeof(t_door **) * (size + 1));
	if (!data->map.door_map)
		f_exit(data, 1);
	ft_bzero(data->map.door_map, sizeof(t_door **) * (size + 1));
	while (y < size)
	{
		size_line = ft_strlen(data->map.tabmap[y]);
		data->map.door_map[y] = malloc(sizeof(t_door *) * (size_line + 1));
		if (!data->map.door_map[y])
			f_exit(data, 1);
		ft_bzero(data->map.door_map[y], sizeof(t_door *) * (size_line + 1));
		++y;
	}
}

static	void create_wall_map(t_data *data, int size)
{
	int	y;
	int	size_line;

	y = 0;
	data->map.wall_map = malloc(sizeof(t_wall_msg **) * (size + 1));
	if (!data->map.wall_map)
		f_exit(data, 1);
	ft_bzero(data->map.wall_map, sizeof(t_wall_msg **) * (size + 1));
	while (y < size)
	{
		size_line = ft_strlen(data->map.tabmap[y]);
		data->map.wall_map[y] = malloc(sizeof(t_wall_msg *) * (size_line + 1));
		if (!data->map.wall_map[y])
			f_exit(data, 1);
		ft_bzero(data->map.wall_map[y], sizeof(t_wall_msg *) * (size_line + 1));
		++y;
	}
	data->random_value = 0;
}

void	create_tabmap(t_data *data)
{
	int		size;
	t_lst	*map;
	int		i;

	size = ft_strlen_lst(data->map.map);
	data->map.tabmap = malloc(sizeof(char *) * (size + 1));
	if (!data->map.tabmap)
		f_exit(data, 1);
	ft_bzero(data->map.tabmap, sizeof(char *) * (size + 1));
	map = get_first_elem_lst(data->map.map);
	i = 0;
	while (map)
	{
		data->map.tabmap[i] = ft_strndup(map->dt, ft_strlen(map->dt));
		if (!data->map.tabmap[i])
			f_exit(data, 1);
		i++;
		map = map->next;
	}
	data->map.tabmap_height = i;
	create_door_map(data, size);
	create_wall_map(data, size);

}

void	parsing(t_data *data)
{
	verif_file_name(data);
	get_content_file(data);
	get_texture(data);
	create_tabmap(data);
	verif_map(data);
	if (DEBUG_VALUE)
	{
		print_map(data);
		ft_printf_fd(2, "Player start : \n\tdirection = %c\n\ty = %d\n\tx = "
			"%d\n",
			data->map.tabmap[data->map.player_coo->y][data->map.player_coo->x],
			data->map.player_coo->y,
			data->map.player_coo->x);
	}
}
