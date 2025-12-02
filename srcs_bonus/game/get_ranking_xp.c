#include "cub3d_bonus.h"

static void	get_max_xp(t_data *data, double *max_xp, int *index_max_xp)
{
	int	i;

	i = 0;
	data->coa[data->player.coa].xp = data->player.xp;
	while (i < 4)
	{
		if (data->coa[i].xp > *max_xp)
		{
			*index_max_xp = i;
			*max_xp = data->coa[i].xp;
		}
		++i;
	}
}

void	get_ranking_xp(t_data *data)
{
	int		i;
	int		index_max_xp;
	double	max_xp;

	max_xp = 1.0;
	index_max_xp = 0;
	data->sound = add_end_lst(create_sound(data, 30), data->sound, free_sound);
	remove_sound(data, 22);
	get_max_xp(data, &max_xp, &index_max_xp);
	data->coa[index_max_xp].max_y = 196 ;
	i = 0;
	while (i < 4)
	{
		if (index_max_xp == i)
		{
			++i;
			continue ;
		}
		data->coa[i].max_y = 674
			- (data->coa[i].xp / data->coa[index_max_xp].xp) * (674 - 196);
		++i;
	}
}
