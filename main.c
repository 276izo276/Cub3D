#include "struct.h"
#include "ft_printf.h"
#include "parsing.h"
#include "cub3d.h"
#include "utils.h"
#include "mlx.h"
#include <stdlib.h>

void	init_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		// error msg
		f_exit(data, 1);
	}
	data->ac = ac;
	data->av = av;
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac, av);
	parsing(&data);
	open_win(&data, &data.mlx);
	if (!load_img_mini_map(&data.mlx, &data.map.mini))
		f_exit(&data, 1);
	display_mini_map(&data, &data.map);
	f_exit(&data, 0);
	return (1);
}
