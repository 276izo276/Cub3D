#include "struct_bonus.h"

void	cast_popo_heal(t_data *data)
{
	if (data->popo[1].nb > 0)
	{
		data->player.life += 34;
		if (data->player.life > 100)
			data->player.life = 100;
		data->popo[1].nb--;
	}
}