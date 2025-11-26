#include "struct_bonus.h"
#include "cub3d_bonus.h"

void	win_xp(t_data *data, int type, double *xp)
{
	if (type == DEMENTOR)
		*xp += 0.42 / (0.8 + (data->player.xp * 0.1));
	else if (type == SPIDER)
		*xp += 0.23 / (0.8 + (data->player.xp * 0.1));
	else if (type == ELEM)
		*xp += 0.35 / (0.8 + (data->player.xp * 0.1));
	else if (type == WOLF)
		*xp += 0.5 / (0.8 + (data->player.xp * 0.1));
	else
		*xp += 3 / (0.8 + (data->player.xp * 0.1));
}

void	add_sound_xp(t_enemy *enemy, t_data *data)
{
	if (enemy->damage.which_coa_take == data->player.coa)
	{
		data->sound = add_end_lst(create_sound(data, 25), data->sound,
				free_sound);
		win_xp(data, enemy->type, &data->player.xp);
		data->coa[data->player.coa].xp = data->player.xp;
	}
	else if (enemy->damage.which_coa_take == EARTH)
		win_xp(data, enemy->type, &data->coa[EARTH].xp);
	else if (enemy->damage.which_coa_take == AIR)
		win_xp(data, enemy->type, &data->coa[AIR].xp);
	else if (enemy->damage.which_coa_take == WATER)
		win_xp(data, enemy->type, &data->coa[WATER].xp);
	else if (enemy->damage.which_coa_take == FIRE)
		win_xp(data, enemy->type, &data->coa[FIRE].xp);
}
