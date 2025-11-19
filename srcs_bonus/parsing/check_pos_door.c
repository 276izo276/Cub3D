#include "color_bonus.h"
#include "ft_printf.h"
#include "parsing_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"

static void	check_pos_floo(t_data *data, bool is_verti, int x, int y)
{
	if ((is_verti == false && data->map.tabmap[y - 1][x] == '1'
		&& data->map.tabmap[y + 1][x] == '1')
		|| (is_verti == true && data->map.tabmap[y][x + 1] == '1'
		&& data->map.tabmap[y][x - 1] == '1'))
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>> " "floo found surrounded by wall\n"_END);
		f_exit(data, 1);
	}
	else if ((is_verti == false && data->map.tabmap[y - 1][x] != '1'
		&& data->map.tabmap[y + 1][x] != '1')
		|| (is_verti == true && data->map.tabmap[y][x + 1] != '1'
		&& data->map.tabmap[y][x - 1] != '1'))
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>> " "floo found without wall behind\n"_END);
		f_exit(data, 1);
	}
	data->map.nb_floo++;
}

bool	door_is_verti(t_data *data, int y, int x, char c)
{
	bool	is_verti;

	if (!((data->map.tabmap[y][x - 1] == '1'
			&& data->map.tabmap[y][x + 1] == '1')
		|| (data->map.tabmap[y + 1][x] == '1'
			&& data->map.tabmap[y - 1][x] == '1')))
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>> " "door found without wall around\n"_END);
		f_exit(data, 1);
	}
	if (c == 'D')
		data->nb_door++;
	if (data->map.tabmap[y][x + 1] == '1' && data->map.tabmap[y][x - 1] == '1')
		is_verti = false;
	else
		is_verti = true;
	if (c == 'F')
		check_pos_floo(data, is_verti, x, y);
	return (is_verti);
}
