#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include <stdio.h>

void	cast_popo_heal(t_data *data)
{
	if (data->popo[0].active)
		return ;
	data->popo[0].active = 1;
	printf("popo heal\n");
	if (data->popo[0].nb > 0 && data->player.life < 100)
	{
		data->player.life += 25;
		if (data->player.life > 100)
			data->player.life = 100;
		data->popo[0].nb--;
	}
}

void	cast_popo_shield(t_data *data)
{
	if (data->popo[1].active)
		return ;
	data->popo[1].active = 1;
	printf("popo shield\n");
	if (data->popo[1].nb > 0 && data->player.shield < 100)
	{
		data->player.shield += 25;
		if (data->player.shield > 100)
			data->player.shield = 100;
		data->popo[1].nb--;
	}
}

void	cast_popo_floo(t_data *data)
{
	if (data->popo[2].active)
		return ;
	if (data->popo[2].nb == 0)
		return ;
	data->popo[2].active = 1;
	if (handle_floo_open(data) == true)
		data->popo[2].nb--;
	printf("popo floo\n");
}

void	cast_popo_invi(t_data *data)
{
	if (data->popo[3].active || data->popo[3].nb_part_cloak < 4)
		return;
	data->popo[3].active = 1;
	data->popo[3].nb--;
	data->popo[3].nb_part_cloak -= 4;
	printf("popo invi\n");
}

