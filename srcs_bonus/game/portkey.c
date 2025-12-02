#include "cub3d_bonus.h"
#include "utils_bonus.h"

void	portkey_utils(t_data *data, int attempts, int random_x, int random_y)
{
	if (attempts >= 1000)
		return ;
	data->item = add_end_lst(create_item(data, PORTKEY,
				&(t_fcoo){.case_x = random_x, .case_y = random_y, .coo_y = 32,
				.coo_x = 32}, data->map.mini.deg), data->item, f_item);
	if (!data->item)
		f_exit(data, 1);
	data->item = add_end_lst(create_item(data, PILLAR,
				&(t_fcoo){.case_x = random_x, .case_y = random_y, .coo_y = 32,
				.coo_x = 32}, data->map.mini.deg), data->item, f_item);
	if (!data->item)
		f_exit(data, 1);
	data->portkey_is_active = true;
}

void	spawn_portkey(t_data *data)
{
	int	y;
	int	x;
	int	random_y;
	int	random_x;
	int	attempts;

	attempts = 0;
	random_y = 0;
	while (attempts < 1000)
	{
		y = 0;
		while (data->map.tabmap[y])
			++y;
		random_y = rand() % y;
		x = 0;
		while (data->map.tabmap[random_y][x])
			++x;
		random_x = rand() % x;
		if (data->map.tabmap[random_y][random_x] == '0')
			break ;
		++attempts;
	}
	portkey_utils(data, attempts, random_x, random_y);
}
