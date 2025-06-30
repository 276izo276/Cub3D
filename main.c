#include "struct.h"
#include "ft_printf.h"
#include "parsing.h"
#include "utils.h"
#include "mlx.h"
#include <stdlib.h>

void	init_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->mlx.mlx = mlx_init();
	data->ac = ac;
	data->av = av;
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac, av);
	parsing(&data);
	f_exit(&data, 0);
	return (1);
}
