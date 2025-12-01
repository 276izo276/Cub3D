#include "utils_bonus.h"
#include "cub3d_bonus.h"

static t_lst	*add_case_near(t_lst *open, t_lst *closed, t_lst *node,
		t_data *data)
{
	const int	coo[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	int			i;
	int			new_y;
	int			new_x;

	i = -1;
	while (++i < 4)
	{
		new_y = ((t_coo *)node->dt)->y + coo[i][0];
		new_x = ((t_coo *)node->dt)->x + coo[i][1];
		if (new_y >= data->map.tabmap_height || new_y < 0
			|| new_x >= ft_strlen(data->map.tabmap[new_y]) || new_x < 0
			|| data->map.tabmap[new_y][new_x] == ' ')
			error_map_not_closed(closed, open, data);
		if (data->map.tabmap[new_y][new_x] == '-'
			&& (data->map.tabmap[new_y][new_x] != '1'))
		{
			open = add_start_lst(init_t_coo(new_y, new_x), open, f_elem);
			error_occured(data, open, closed);
		}
	}
	return (open);
}

void	verif_map_is_closed(t_data *data, int y, int x)
{
	t_lst	*closed;
	t_lst	*open;
	t_lst	*node;

	closed = NULL;
	open = add_end_lst(init_t_coo(y, x), NULL, f_elem);
	if (!open)
		f_exit(data, 1);
	while (open)
	{
		node = open;
		open = remove_elem_lst(node);
		data->map.tabmap[((t_coo*)node->dt)->y][((t_coo*)node->dt)->x] = '0';
		closed = move_to_end_lst(node, closed);
		open = add_case_near(open, closed, node, data);
	}
	f_all_lst(closed);
}

void	check_map_is_closed(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.tabmap_height)
	{
		x = 0;
		while (x < ft_strlen(data->map.tabmap[y]))
		{
			if (data->map.tabmap[y][x] == 'F')
			{
				verif_map_is_closed(data, y, x);
			}
			x++;
		}
		y++;
	}
	verif_map_is_closed(data, data->player.coo.case_y,
		data->player.coo.case_x);
}
