#include "color_bonus.h"
#include "ft_printf.h"
#include "parsing_bonus.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"
#include "enemy_bonus.h"

void	is_item(char c, int y, int x, t_data *data)
{
	int			i;
	const char	tab[] = {'z', 'x', 'c', 'v', 'f', 0};
	int			info;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
		{
			if (c == 'z')
				info = HEAL_POPO;
			if (c == 'x')
				info = SHIELD_POPO;
			if (c == 'c')
				info = FLOO_POPO;
			if (c == 'v')
				info = INVI_POPO;
			if (c == 'f')
			{
				if (data->portkey_is_active == true)
				{
					ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
					"Map >>> ""2 exit found\n"_END);
					f_exit(data, 1);
				}
				data->portkey_is_active = true;
				info = PORTKEY;
			}
			data->item = add_end_lst(create_item(data, info, &(t_fcoo){.case_x=x,.case_y=y,.coo_y=32,.coo_x=32}, data->map.mini.deg), data->item, f_item);
			if (!data->item)
				f_exit(data, 1);
			data->map.tabmap[y][x] = '0';
		}
		i++;
	}
}

void	is_door(char c, int y, int x, t_data *data)
{
	bool	is_verti;

	if (c != 'D' && c != 'F')
		return ;
	if (!((data->map.tabmap[y][x - 1] == '1' && data->map.tabmap[y][x + 1] == '1')
		|| (data->map.tabmap[y + 1][x] == '1' && data->map.tabmap[y - 1][x] == '1')))
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
	{
		if ((is_verti == false && data->map.tabmap[y - 1][x] == '1' && data->map.tabmap[y + 1][x] == '1')
		 || (is_verti == true && data->map.tabmap[y][x + 1] == '1' && data->map.tabmap[y][x - 1] == '1'))
		{
			ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>> " "floo found surrounded by wall\n"_END);
			f_exit(data, 1);
		}
		else if ((is_verti == false && data->map.tabmap[y - 1][x] != '1' && data->map.tabmap[y + 1][x] != '1')
			|| (is_verti == true && data->map.tabmap[y][x + 1] != '1' && data->map.tabmap[y][x - 1] != '1'))
		{
			ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Map >>> " "floo found without wall behind\n"_END);
			f_exit(data, 1);
		}
		data->map.nb_floo++;
	}
	add_door(data, y, x, c);
	if (is_verti == false)
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

void	is_enemy(char c, int y, int x, t_data *data)
{
	int			i;
	const char	tab[] = {'.', ',', '<', '>', ';', '2', '3', '4', '5', '6', '7', '8', '9', 'm', 0};

	i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
		{
			data->enemy = add_end_lst(init_enemy(c, (t_fcoo){.case_x=x,.case_y=y,.coo_y=32,.coo_x=32}, data, data->map.mini.deg), data->enemy, f_enemy);
			if (!data->enemy)
				f_exit(data, 1);
			data->map.tabmap[y][x] = '0';
			data->nb_enemy++;
		}
		i++;
	}
}
