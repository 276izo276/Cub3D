#include "struct.h"
#include "color.h"
#include "utils.h"
#include "ft_printf.h"

static void	is_valid_char_map(char c, int y, int x, t_data *data)
{
	const char	tab[] = {'0', '1', ' ', 'N', 'S', 'W', 'E', 0};
	int			i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == c && i >= 3)
		{
			if (data->map.player_start)
			{
				ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"Map >>> "\
					"2 player start found\n"_END);
				f_exit(data, 1);
			}
			data->map.player_start = init_t_coo(data, y, x);
			return ;
		}
		else if (tab[i] == c && i <= 2)
			return ;
		i++;
	}
	ft_printf_fd(2, _RED _BOLD"Error\n"_PURPLE"Map >>> '"\
_RED"%c"_PURPLE"' is not a valid character\n"_END, c);
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
		y++;
	}
}

void	check_map_is_closed(t_data *data)
{
	t_lst	*closed;
	t_lst	*open;

	(void)closed;
	open = add_end_lst(init_t_coo(data, data->map.player_start->y,
				data->map.player_start->x), NULL, f_elem);
	if (!open)
		f_exit(data, 1);
	while (open)
	{
		break ;
	}
}

void	verif_map(t_data *data)
{
	check_map_valid_char(data);
	// check_map_is_closed(data);
}
