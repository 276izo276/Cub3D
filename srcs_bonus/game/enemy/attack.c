#include "struct_bonus.h"
#include "color_bonus.h"
#include <stdlib.h>
#include "time_bonus.h"
#include "cub3d_bonus.h"

bool	is_sorcerer(int type)
{
	if (type == MARINA || type == CAMEO || type == DIRLO || type == NANCY
		|| type == PILO || type == ZIPPY || type == ANAIS || type == STEF
		|| type == KUNFANDI)
		return (true);
	return (false);
}

int	attack_dist(t_enemy *enemy, t_data *data, t_enemy_vision *visu)
{
	if (is_sorcerer(enemy->type) == true && rand() % 1000 < 50
		&& get_mtime() > enemy->time_attack_dist + enemy->cooldown_dist * 1000)
	{
		enemy->time_attack_dist = get_mtime();
		if (enemy->color_coa == AIR_COLOR)
			air_spell(data, enemy, visu->deg, visu->type);
		else if (enemy->color_coa == EARTH_COLOR)
			earth_spell(data, enemy, visu->deg, visu->type);
		else if (enemy->color_coa == WATER_COLOR)
			water_spell(data, enemy, visu->deg, visu->type);
		else if (enemy->color_coa == FIRE_COLOR)
			fire_spell(data, enemy, visu->deg, visu->type);
		return (1);
	}
	return (0);
}