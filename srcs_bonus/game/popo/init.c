#include "struct_bonus.h"
#include "cub3d_bonus.h"

void	init_popo(t_data *data)
{
	data->popo[0].nb = 0;
	data->popo[0].img = &data->img[POPO_HEAL];
	data->popo[0].call = cast_popo_heal;

	data->popo[1].nb = 0;
	data->popo[1].img = &data->img[POPO_SHIELD];
	data->popo[1].call = cast_popo_heal;

	data->popo[2].nb = 0;
	data->popo[2].img = &data->img[POPO_HEAL];
	data->popo[2].call = cast_popo_heal;

	data->popo[3].nb = 0;
	data->popo[3].img = &data->img[POPO_HEAL];
	data->popo[3].call = cast_popo_heal;

}