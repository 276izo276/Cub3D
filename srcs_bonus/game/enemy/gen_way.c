#include "struct_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"

static void	get_case_way(t_data *data, int *x, int *y)
{
	int	count;
	int	len_line;
	int	len_tab;

	len_tab = ft_tab_strlen(data->map.tabmap) - 1;
	*y = rand() % len_tab;
	len_line = ft_strlen(data->map.tabmap[*y]);
	*x = rand() % len_line;
	count = 0;
	while (data->map.tabmap[*y][*x] != '0')
	{
		(*x)++;
		*x = *x % len_line;
		count++;
		if (count >= len_line)
		{
			len_tab = ft_tab_strlen(data->map.tabmap) - 1;
			*y = rand() % (len_tab);
			len_line = ft_strlen(data->map.tabmap[*y]);
			*x = rand() % len_line;
		}
	}
}

void	gen_enemy_way(t_data *data, t_enemy *enemy)
{
	int	x;
	int	y;

	if (enemy->wait < 10)
	{
		enemy->wait++;
		return ;
	}
	get_case_way(data, &x, &y);
	enemy->goal.case_x = x;
	enemy->goal.case_y = y;
	enemy->goal.coo_y = 32;
	enemy->goal.coo_x = 32;
	pathfinder(data, enemy);
	calc_in_cell_path(data, enemy);
}
