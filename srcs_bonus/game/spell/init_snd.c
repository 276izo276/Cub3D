#include "cub3d_bonus.h"

void	init_arania_exumai(t_data *data)
{
	data->spell[ARANIA_EXUMAI].base_cooldown = 5;
	data->spell[ARANIA_EXUMAI].call = cast_spell;
	data->spell[ARANIA_EXUMAI].type = ARANIA_EXUMAI;
	data->spell[ARANIA_EXUMAI].damage.damage_do = 5;
	data->spell[ARANIA_EXUMAI].damage.damage_spider_do = 30;
	data->spell[ARANIA_EXUMAI].item.speed = 50;
	data->spell[ARANIA_EXUMAI].item.radius = 3;
	data->spell[ARANIA_EXUMAI].item.front_img = &data->img[ARANIA_EXUMAI_IMG];
	data->spell[ARANIA_EXUMAI].item.back_img = &data->img[ARANIA_EXUMAI_IMG];
	data->spell[ARANIA_EXUMAI].class = DEFENSIVE_SPELL;
	data->spell[ARANIA_EXUMAI].icn = &data->img[ARANIA_EXUMAI_ICN];
	data->spell[ARANIA_EXUMAI].icn_name = &data->img[ARANIA_EXUMAI_NAME];
	data->spell[ARANIA_EXUMAI].necessary_lvl = 3.0;
}

void	init_protego(t_data *data)
{
	data->spell[PROTEGO].base_cooldown = 15;
	data->spell[PROTEGO].base_timer = 5;
	data->spell[PROTEGO].call = cast_protego;
	data->spell[PROTEGO].type = PROTEGO;
	data->spell[PROTEGO].class = DEFENSIVE_SPELL;
	data->spell[PROTEGO].icn = &data->img[PROTEGO_ICN];
	data->spell[PROTEGO].icn_name = &data->img[PROTEGO_NAME];
	data->spell[PROTEGO].necessary_lvl = 3.5;
}

void	init_expelliarmus(t_data *data)
{
	data->spell[EXPELLIARMUS].base_cooldown = 10;
	data->spell[EXPELLIARMUS].call = cast_spell;
	data->spell[EXPELLIARMUS].type = EXPELLIARMUS;
	data->spell[EXPELLIARMUS].damage.damage_do = 25;
	data->spell[EXPELLIARMUS].item.speed = 40;
	data->spell[EXPELLIARMUS].item.radius = 3;
	data->spell[EXPELLIARMUS].item.front_img = &data->img[EXPELLIARMUS_IMG];
	data->spell[EXPELLIARMUS].item.back_img = &data->img[EXPELLIARMUS_IMG];
	data->spell[EXPELLIARMUS].class = OFFENSIVE_SPELL;
	data->spell[EXPELLIARMUS].icn = &data->img[EXPELLIARMUS_ICN];
	data->spell[EXPELLIARMUS].icn_name = &data->img[EXPELLIARMUS_NAME];
	data->spell[EXPELLIARMUS].necessary_lvl = 4.0;
}

void	init_expecto_patronum(t_data *data)
{
	data->spell[EXPECTO_PATRONUM].base_cooldown = 10;
	data->spell[EXPECTO_PATRONUM].call = cast_spell;
	data->spell[EXPECTO_PATRONUM].type = EXPECTO_PATRONUM;
	data->spell[EXPECTO_PATRONUM].damage.damage_dementor_do = 10;
	data->spell[EXPECTO_PATRONUM].damage.repulso_force_do = .2;
	data->spell[EXPECTO_PATRONUM].damage.repulso_frame_do = 10;
	data->spell[EXPECTO_PATRONUM].item.speed = 1;
	data->spell[EXPECTO_PATRONUM].item.radius = 0;
	data->spell[EXPECTO_PATRONUM].item.front_img
		= &data->img[EXPECTO_PATRONUM_IMG];
	data->spell[EXPECTO_PATRONUM].item.back_img
		= &data->img[EXPECTO_PATRONUM_IMG];
	data->spell[EXPECTO_PATRONUM].class = OFFENSIVE_SPELL;
	data->spell[EXPECTO_PATRONUM].icn
		= &data->img[EXPECTO_PATRONUM_ICN];
	data->spell[EXPECTO_PATRONUM].icn_name = &data->img[EXPECTO_PATRONUM_NAME];
	data->spell[EXPECTO_PATRONUM].necessary_lvl = 5.0;
}

void	init_vipera_evanesca(t_data *data)
{
	data->spell[VIPERA_EVANESCA].base_cooldown = 3;
	data->spell[VIPERA_EVANESCA].call = cast_spell;
	data->spell[VIPERA_EVANESCA].type = VIPERA_EVANESCA;
	data->spell[VIPERA_EVANESCA].damage.damage_snake_do = 25;
	data->spell[VIPERA_EVANESCA].damage.damage_do = 2;
	data->spell[VIPERA_EVANESCA].item.speed = 40;
	data->spell[VIPERA_EVANESCA].item.radius = 3;
	data->spell[VIPERA_EVANESCA].item.front_img = &data->img[ARANIA_EXUMAI_IMG];
	data->spell[VIPERA_EVANESCA].item.back_img = &data->img[ARANIA_EXUMAI_IMG];
	data->spell[VIPERA_EVANESCA].class = OFFENSIVE_SPELL;
	data->spell[VIPERA_EVANESCA].icn = &data->img[VIPERA_EVANESCA_ICN];
	data->spell[VIPERA_EVANESCA].icn_name = &data->img[VIPERA_EVANESCA_NAME];
	data->spell[VIPERA_EVANESCA].necessary_lvl = 5.5;
}
