#include "struct_bonus.h"
#include "cub3d_bonus.h"
#include "time_bonus.h"
#include <stdlib.h>

t_item	*init_spell_item(t_data *data, t_spells info)
{
	t_item	*item;

	item = malloc(sizeof(t_item));
	if (!item)
		return (NULL);
	item->center.case_x = data->map.player_coo->x;
	item->center.case_y = data->map.player_coo->y;
	item->center.coo_x = data->map.mini.player_coo.x;
	item->center.coo_y = data->map.mini.player_coo.y;
	item->deg = data->map.mini.deg;
	item->rad = item->deg * (M_PI / 180);
	item->speed = data->spell[info].item.speed;
	item->damage.damage_do = data->spell[info].damage.damage_do;
	item->damage.poison_do = data->spell[info].damage.poison_do;
	item->damage.fire_do = data->spell[info].damage.fire_do;
	item->damage.slow_do = data->spell[info].damage.slow_do;
	item->radius = data->spell[info].item.radius;
	return (item);
}