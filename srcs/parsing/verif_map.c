#include "color.h"
#include "ft_printf.h"
#include "parsing.h"
#include "struct.h"
#include "utils.h"
#include "cub3d.h"

static void	is_valid_char_map(char c, int y, int x, t_data *data)
{
	const char	tab[] = {'0', '1', ' ', 'N', 'S', 'W', 'E', 0};
	int			i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i] == c && i >= 3)
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
		else if (tab[i] == c && i <= 2)
			return ;
	}
	ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE "Map >>> '"
		_RED "%c"_PURPLE "' is not a valid character\n"_END, c);
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
