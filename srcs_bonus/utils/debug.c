#include "struct_bonus.h"
#include "ft_printf.h"

void	print_map(t_data *data)
{
	char	**map;
	int		i;

	map = data->map.tabmap;
	i = 0;
	while (map[i])
	{
		ft_printf_fd(2, "%s\n", map[i]);
		i++;
	}
}
