#include "cub3d_bonus.h"

void	init_oppugno(t_data *data)
{
	data->spell[OPPUGNO].base_cooldown = 15;
	data->spell[OPPUGNO].call = cast_opugno;
	data->spell[OPPUGNO].type = OPPUGNO;
	data->spell[OPPUGNO].class = OFFENSIVE_SPELL;
	data->spell[OPPUGNO].icn = &data->img[OPPUGNO_ICN];
	data->spell[OPPUGNO].icn_name = &data->img[OPPUGNO_NAME];
	data->spell[OPPUGNO].necessary_lvl = 8.0;
}

void	init_vulnera_sanentur(t_data *data)
{
	data->spell[VULNERA_SANENTUR].base_cooldown = 15;
	data->spell[VULNERA_SANENTUR].call = cast_vulnera_sanentur;
	data->spell[VULNERA_SANENTUR].type = VULNERA_SANENTUR;
	data->spell[VULNERA_SANENTUR].class = CLASIC_SPELL;
	data->spell[VULNERA_SANENTUR].icn = &data->img[VULNERA_SANENTUR_ICN];
	data->spell[VULNERA_SANENTUR].icn_name = &data->img[VULNERA_SANENTUR_NAME];
	data->spell[VULNERA_SANENTUR].necessary_lvl = 8.5;
}

void	init_petrificus_totalus(t_data *data)
{
	data->spell[PETRIFICUS_TOTALUS].base_cooldown = 15;
	data->spell[PETRIFICUS_TOTALUS].call = cast_spell;
	data->spell[PETRIFICUS_TOTALUS].type = PETRIFICUS_TOTALUS;
	data->spell[PETRIFICUS_TOTALUS].damage.slow_force_do = 90;
	data->spell[PETRIFICUS_TOTALUS].damage.slow_frame_do = 180;
	data->spell[PETRIFICUS_TOTALUS].item.speed = 40;
	data->spell[PETRIFICUS_TOTALUS].damage.damage_do = 5;
	data->spell[PETRIFICUS_TOTALUS].item.radius = 5;
	data->spell[PETRIFICUS_TOTALUS].item.front_img
		= &data->img[PETRIFICUS_TOTALUS_IMG];
	data->spell[PETRIFICUS_TOTALUS].item.back_img
		= &data->img[PETRIFICUS_TOTALUS_IMG];
	data->spell[PETRIFICUS_TOTALUS].class = DEFENSIVE_SPELL;
	data->spell[PETRIFICUS_TOTALUS].icn
		= &data->img[PETRIFICUS_TOTALUS_ICN];
	data->spell[PETRIFICUS_TOTALUS].icn_name
		= &data->img[PETRIFICUS_TOTALUS_NAME];
	data->spell[PETRIFICUS_TOTALUS].necessary_lvl = 9.0;
}

void	init_sectumsempra(t_data *data)
{
	data->spell[SECTUMSEMPRA].base_cooldown = 21;
	data->spell[SECTUMSEMPRA].call = cast_spell;
	data->spell[SECTUMSEMPRA].type = SECTUMSEMPRA;
	data->spell[SECTUMSEMPRA].damage.damage_do = 21;
	data->spell[SECTUMSEMPRA].damage.slow_force_do = 60;
	data->spell[SECTUMSEMPRA].damage.slow_frame_do = 300;
	data->spell[SECTUMSEMPRA].damage.curse_frame_do = 210;
	data->spell[SECTUMSEMPRA].damage.curse_force_do = .1;
	data->spell[SECTUMSEMPRA].item.speed = 40;
	data->spell[SECTUMSEMPRA].item.radius = 3;
	data->spell[SECTUMSEMPRA].item.front_img = &data->img[SECTUMSEMPRA_IMG];
	data->spell[SECTUMSEMPRA].item.back_img = &data->img[SECTUMSEMPRA_IMG];
	data->spell[SECTUMSEMPRA].class = OFFENSIVE_SPELL;
	data->spell[SECTUMSEMPRA].icn = &data->img[SECTUMSEMPRA_ICN];
	data->spell[SECTUMSEMPRA].icn_name = &data->img[SECTUMSEMPRA_NAME];
	data->spell[SECTUMSEMPRA].necessary_lvl = 9.5;
}

void	init_confundo(t_data *data)
{
	data->spell[CONFUNDO].base_cooldown = 25;
	data->spell[CONFUNDO].call = cast_spell;
	data->spell[CONFUNDO].type = CONFUNDO;
	data->spell[CONFUNDO].damage.confundo_frame_do = 300;
	data->spell[CONFUNDO].damage.confundo_force_do = 1;
	data->spell[CONFUNDO].damage.slow_force_do = 25;
	data->spell[CONFUNDO].damage.slow_frame_do = 150;
	data->spell[CONFUNDO].item.speed = 35;
	data->spell[CONFUNDO].item.radius = 2;
	data->spell[CONFUNDO].item.front_img = &data->img[CONFUNDO_IMG];
	data->spell[CONFUNDO].item.back_img = &data->img[CONFUNDO_IMG];
	data->spell[CONFUNDO].class = OFFENSIVE_SPELL;
	data->spell[CONFUNDO].icn = &data->img[CONFUNDO_ICN];
	data->spell[CONFUNDO].icn_name = &data->img[CONFUNDO_NAME];
	data->spell[CONFUNDO].necessary_lvl = 10.0;
}
