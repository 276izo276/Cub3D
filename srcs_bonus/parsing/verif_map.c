#include "color_bonus.h"
#include "ft_printf.h"
#include "parsing_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"

static void	print_is_not_char(char c)
{
	ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE "Map >>> '"
		_RED "%c"_PURPLE "' is not a valid character\n"_END, c);
}

static void	is_valid_char_map(char c, int y, int x, t_data *data)
{
	const char	tab[] = {'0', '1', 'D', 'F', ' ', '.', ',', '<', '>', ';', 'f',
		'2', '3', '4', '5', '6', '7', '8', '9', 'm', 'z', 'x', 'c', 'v', 'N',
		'S', 'W', 'E', 0};
	int			i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i] == c && i >= 24)
		{
			if (data->player.coo.case_x != 0 && data->player.coo.case_y != 0)
			{
				ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
					"Map >>> ""2 player start found\n"_END);
				f_exit(data, 1);
			}
			data->player.coo.case_y = y;
			data->player.coo.case_x = x;
			return ;
		}
		else if (tab[i] == c && i <= 23)
			return ;
	}
	print_is_not_char(c);
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
			save_wall(data->map.tabmap[y][x], y, x, data);
			is_door(data->map.tabmap[y][x], y, x, data);
			is_enemy(data->map.tabmap[y][x], y, x, data);
			is_item(data->map.tabmap[y][x], y, x, data);
			if (data->map.tabmap[y][x] == '0')
				data->map.tabmap[y][x] = '-';
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
	char	c;

	c = data->map.tabmap[data->player.coo.case_y][data->player.coo.case_x];
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
	if (data->player.coo.case_x == 0 && data->player.coo.case_y == 0)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>> " "no player start found\n"_END);
		f_exit(data, 1);
	}
	if (data->map.nb_floo == 1)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>> " "only one floo found\n"_END);
		f_exit(data, 1);
	}
	set_deg_start(data);
	check_map_is_closed(data);
}
