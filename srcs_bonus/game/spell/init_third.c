#include "cub3d_bonus.h"

void	init_serpensortia(t_data *data)
{
	data->spell[SERPENSORTIA].base_cooldown = 5;
	data->spell[SERPENSORTIA].call = cast_serpensortia;
	data->spell[SERPENSORTIA].type = SERPENSORTIA;
	data->spell[SERPENSORTIA].class = OFFENSIVE_SPELL;
	data->spell[SERPENSORTIA].icn = &data->img[SERPENSORTIA_ICN];
	data->spell[SERPENSORTIA].icn_name = &data->img[SERPENSORTIA_NAME];
	data->spell[SERPENSORTIA].necessary_lvl = 6.0;
}

void	init_ventus(t_data *data)
{
	data->spell[VENTUS].base_cooldown = 8;
	data->spell[VENTUS].call = cast_spell;
	data->spell[VENTUS].type = VENTUS;
	data->spell[VENTUS].damage.damage_do = 1.0;
	data->spell[VENTUS].damage.repulso_force_do = -10.0;
	data->spell[VENTUS].damage.repulso_frame_do = 1;
	data->spell[VENTUS].item.speed = 1.0;
	data->spell[VENTUS].item.radius = 6;
	data->spell[VENTUS].item.front_img = &data->img[VENTUS_IMG];
	data->spell[VENTUS].item.back_img = &data->img[VENTUS_IMG];
	data->spell[VENTUS].class = OFFENSIVE_SPELL;
	data->spell[VENTUS].icn = &data->img[VENTUS_ICN];
	data->spell[VENTUS].icn_name = &data->img[VENTUS_NAME];
	data->spell[VENTUS].necessary_lvl = 6.5;
}

void	init_bombarda(t_data *data)
{
	data->spell[BOMBARDA].base_cooldown = 7;
	data->spell[BOMBARDA].call = cast_spell;
	data->spell[BOMBARDA].type = BOMBARDA;
	data->spell[BOMBARDA].damage.damage_do = 30;
	data->spell[BOMBARDA].damage.fire_force_do = .5;
	data->spell[BOMBARDA].damage.fire_frame_do = 10;
	data->spell[BOMBARDA].item.speed = 20;
	data->spell[BOMBARDA].item.radius = 6;
	data->spell[BOMBARDA].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[BOMBARDA].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[BOMBARDA].class = OFFENSIVE_SPELL;
	data->spell[BOMBARDA].icn = &data->img[BOMBARDA_ICN];
	data->spell[BOMBARDA].icn_name = &data->img[BOMBARDA_NAME];
	data->spell[BOMBARDA].necessary_lvl = 7.0;
}

void	init_episkey(t_data *data)
{
	data->spell[EPISKEY].base_cooldown = 8;
	data->spell[EPISKEY].call = cast_episkey;
	data->spell[EPISKEY].type = EPISKEY;
	data->spell[EPISKEY].class = CLASIC_SPELL;
	data->spell[EPISKEY].icn = &data->img[EPISKEY_ICN];
	data->spell[EPISKEY].icn_name = &data->img[EPISKEY_NAME];
	data->spell[EPISKEY].necessary_lvl = 7.0;
}

void	init_stupefix(t_data *data)
{
	data->spell[STUPEFIX].base_cooldown = 10;
	data->spell[STUPEFIX].call = cast_spell;
	data->spell[STUPEFIX].type = STUPEFIX;
	data->spell[STUPEFIX].damage.damage_do = 40;
	data->spell[STUPEFIX].damage.slow_force_do = 80;
	data->spell[STUPEFIX].damage.slow_frame_do = 60;
	data->spell[STUPEFIX].item.speed = 20;
	data->spell[STUPEFIX].item.radius = 2;
	data->spell[STUPEFIX].item.front_img = &data->img[STUPEFIX_IMG];
	data->spell[STUPEFIX].item.back_img = &data->img[STUPEFIX_IMG];
	data->spell[STUPEFIX].class = OFFENSIVE_SPELL;
	data->spell[STUPEFIX].icn = &data->img[STUPEFIX_ICN];
	data->spell[STUPEFIX].icn_name = &data->img[STUPEFIX_NAME];
	data->spell[STUPEFIX].necessary_lvl = 7.5;
}
