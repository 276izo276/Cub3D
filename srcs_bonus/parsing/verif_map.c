#include "color_bonus.h"
#include "ft_printf.h"
#include "parsing_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"
#include "enemy_bonus.h"

static void	is_valid_char_map(char c, int y, int x, t_data *data)
{
	const char	tab[] = {'0', '1', 'D', ' ', '.', 'N', 'S', 'W', 'E', 0};
	int			i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i] == c && i >= 5)
		{
			if (data->map.player_coo)
			{
				ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
					"Map >>> ""2 player start found\n"_END);
				f_exit(data, 1);
			}
			data->map.player_coo = init_t_coo(y, x);
			if (!data->map.player_coo)
				f_exit(data, 1);
			return ;
		}
		else if (tab[i] == c && i <= 4)
			return ;
	}
	ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE "Map >>> '"
		_RED "%c"_PURPLE "' is not a valid character\n"_END, c);
	f_exit(data, 1);
}

static void	init_door(t_door *door, int y, int x)
{
	door->coo.y = y;
	door->coo.x = x;
	door->is_open = false;
	door->pos = 0;
}

static void	add_door(t_data *data, int y, int x)
{
	t_door *door;
	t_door **doors;
	int	i;

	door = malloc(sizeof(t_door));
	if (!door)
		f_exit(data, 1);
	init_door(door, y, x);
	data->door = add_end_lst(door, data->door, f_elem);
	if (!data->door)
		f_exit(data, 1);
	data->map.door_map[y][x] = door;
	i = 0;
	while (data->doors && data->doors[i])
		i++;
	doors = malloc(sizeof(t_door *) * (i + 2));
	if (!doors)
	{
		free(door);
		f_exit(data, 1);
	}
	doors[i + 1] = NULL;
	i = 0;
	while (data->doors && data->doors[i])
	{
		doors[i] = data->doors[i];
		i++;
	}
	doors[i] = door;
	free(data->doors);
	data->doors = doors;
}

static void	is_door(char c, int y, int x, t_data *data)
{
	if (c != 'D')
		return ;
	if (!((data->map.tabmap[y][x - 1] == '1' && data->map.tabmap[y][x + 1] == '1')
		|| (data->map.tabmap[y + 1][x] == '1' && data->map.tabmap[y - 1][x] == '1')))
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>> " "door found alone\n"_END);
		f_exit(data, 1);
	}
	data->nb_door++;
	add_door(data, y, x);
	if (data->map.tabmap[y][x + 1] == '1' && data->map.tabmap[y][x - 1] == '1')
	{
		data->map.door_map[y][x]->is_verti = false;
		data->map.door_map[y][x]->first_p.x = 0;
		data->map.door_map[y][x]->first_p.y = 32;
		data->map.door_map[y][x]->second_p.x = 64;
		data->map.door_map[y][x]->second_p.y = 32;
	}
	else
	{
		data->map.door_map[y][x]->is_verti = true;
		data->map.door_map[y][x]->first_p.x = 32;
		data->map.door_map[y][x]->first_p.y = 0;
		data->map.door_map[y][x]->second_p.x = 32;
		data->map.door_map[y][x]->second_p.y = 64;
	}
}

static void	save_wall(char c, int y, int x, t_data *data)
{
	t_wall_msg *wall_msg;

	if (c != '1')
		return ;
	wall_msg = malloc(sizeof(t_wall_msg));
	if (!wall_msg)
		f_exit(data, 1);
	wall_msg->msg_nb = 0;
	wall_msg->img_addr = NULL;
	wall_msg->pix_y = 0;
	wall_msg->coo.x = x;
	wall_msg->coo.y = y;
	wall_msg->is_active = false;
	data->map.wall_map[y][x] = wall_msg;
}

static void	is_enemy(char c, int y, int x, t_data *data)
{
	int			i;
	const char	tab[] = {'.', 0};

	i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
		{
			data->enemy = add_end_lst(init_enemy(c, y, x, data), data->enemy, f_enemy);
			if (!data->enemy)
				f_exit(data, 1);
			data->map.tabmap[y][x] = '0';
			data->nb_enemy++;
		}
		i++;
	}
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
			save_wall(data->map.tabmap[y][x], y, x, data);
			is_door(data->map.tabmap[y][x], y, x, data);
			is_enemy(data->map.tabmap[y][x], y, x, data);
			x++;
		}
		if (x == 0)
		{
			ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE "Map >>>"
				" empty line found !\n"_END);
			f_exit(data, 1);
		}
		y++;
	}
}

static void	set_deg_start(t_data *data)
{
	char c;

	c = data->map.tabmap[data->map.player_coo->y][data->map.player_coo->x];
	if (c == 'S')
		data->map.mini.deg = 180;
	else if (c == 'E')
		data->map.mini.deg = 270;
	else if (c == 'W')
		data->map.mini.deg = 90;
	data->map.mini.rad = data->map.mini.deg * (M_PI / 180.0);
}

void	verif_map(t_data *data)
{
	check_map_valid_char(data);
	if (!data->map.player_coo)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>> " "no player start found\n"_END);
		f_exit(data, 1);
	}
	set_deg_start(data);
	check_map_is_closed(data);

}
