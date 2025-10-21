#include "struct_bonus.h"
#include "cub3d_bonus.h"

void	set_spell_take(t_data *data)
{
	data->cast_spell = -1;
	data->spell_take[0] = BOMBARDA;
	data->spell_take[1] = INCENDIO;
	data->spell_take[2] = AVADA_KEDAVRA;
	data->spell_take[3] = PROTEGO;
}

static void	init_lumos(t_data *data)
{
	data->spell[LUMOS].base_cooldown = 3;
	data->spell[LUMOS].base_timer = 7;
	data->spell[LUMOS].call = cast_lumos;
	data->spell[LUMOS].type = LUMOS;
	data->spell[LUMOS].class = CLASIC_SPELL;
	data->spell[LUMOS].icn = &data->img[LUMOS_ICN];
	data->spell[LUMOS].icn_name = &data->img[LUMOS_NAME];
}

static void	init_incendio(t_data *data)
{
	data->spell[INCENDIO].base_cooldown = 10;
	data->spell[INCENDIO].call = cast_spell;
	data->spell[INCENDIO].type = INCENDIO;
	data->spell[INCENDIO].damage.damage_do = 10;
	data->spell[INCENDIO].damage.fire_frame_do = 70;
	data->spell[INCENDIO].damage.fire_force_do = .1;
	data->spell[INCENDIO].item.speed = 0;
	data->spell[INCENDIO].item.radius = 3;
	data->spell[INCENDIO].item.front_img = &data->img[INCENDIO_IMG];
	data->spell[INCENDIO].item.back_img = &data->img[INCENDIO_IMG];
	data->spell[INCENDIO].class = OFFENSIVE_SPELL;
	data->spell[INCENDIO].icn = &data->img[INCENDIO_ICN];
	data->spell[INCENDIO].icn_name = &data->img[INCENDIO_NAME];
}

#include <stdio.h>

static void	init_glacius(t_data *data)
{
	data->spell[GLACIUS].base_cooldown = 3;
	data->spell[GLACIUS].call = cast_spell;
	data->spell[GLACIUS].type = GLACIUS;
	data->spell[GLACIUS].damage.damage_do = 5;
	data->spell[GLACIUS].damage.slow_force_do = 30;
	data->spell[GLACIUS].damage.slow_frame_do = 35;
	data->spell[GLACIUS].item.speed = 0;
	data->spell[GLACIUS].item.radius = 3;
	data->spell[GLACIUS].item.front_img = &data->img[GLACIUS_IMG];
	data->spell[GLACIUS].item.back_img = &data->img[GLACIUS_IMG];
	data->spell[GLACIUS].class = OFFENSIVE_SPELL;
	data->spell[GLACIUS].icn = &data->img[GLACIUS_ICN];
	data->spell[GLACIUS].icn_name = &data->img[GLACIUS_NAME];
}

static void	init_arania_exumai(t_data *data)
{
	data->spell[ARANIA_EXUMAI].base_cooldown = 5;
	data->spell[ARANIA_EXUMAI].call = cast_spell;
	data->spell[ARANIA_EXUMAI].type = ARANIA_EXUMAI;
	data->spell[ARANIA_EXUMAI].damage.damage_spider_do = 25;
	data->spell[ARANIA_EXUMAI].damage.poison_force_do = .05;
	data->spell[ARANIA_EXUMAI].damage.poison_frame_do = 100;
	data->spell[ARANIA_EXUMAI].damage.damage_do = 5;
	data->spell[ARANIA_EXUMAI].item.speed = 0;
	data->spell[ARANIA_EXUMAI].item.radius = 3;
	data->spell[ARANIA_EXUMAI].item.front_img = &data->img[ARANIA_EXUMAI_IMG];
	data->spell[ARANIA_EXUMAI].item.back_img = &data->img[ARANIA_EXUMAI_IMG];
	data->spell[ARANIA_EXUMAI].class = DEFENSIVE_SPELL;
	data->spell[ARANIA_EXUMAI].icn = &data->img[ARANIA_EXUMAI_ICN];
	data->spell[ARANIA_EXUMAI].icn_name = &data->img[ARANIA_EXUMAI_NAME];
}

static void	init_aguamenti(t_data *data)
{
	data->spell[AGUAMENTI].base_cooldown = 5;
	data->spell[AGUAMENTI].call = cast_spell;
	data->spell[AGUAMENTI].type = AGUAMENTI;
	data->spell[AGUAMENTI].damage.damage_do = 5;
	data->spell[AGUAMENTI].item.speed = 25;
	data->spell[AGUAMENTI].item.radius = 3;
	data->spell[AGUAMENTI].item.front_img = &data->img[AGUAMENTI_IMG];
	data->spell[AGUAMENTI].item.back_img = &data->img[AGUAMENTI_IMG];
	data->spell[AGUAMENTI].class = OFFENSIVE_SPELL;
	data->spell[AGUAMENTI].icn = &data->img[AGUAMENTI_ICN];
	data->spell[AGUAMENTI].icn_name = &data->img[AGUAMENTI_NAME];
}

static void	init_avada_kedavra(t_data *data)
{
	data->spell[AVADA_KEDAVRA].base_cooldown = 30;
	data->spell[AVADA_KEDAVRA].call = cast_spell;
	data->spell[AVADA_KEDAVRA].type = AVADA_KEDAVRA;
	data->spell[AVADA_KEDAVRA].damage.damage_do = 5;
	data->spell[AVADA_KEDAVRA].damage.curse_force_do = .1;
	data->spell[AVADA_KEDAVRA].damage.curse_frame_do = 400;
	data->spell[AVADA_KEDAVRA].item.speed = 0;
	data->spell[AVADA_KEDAVRA].item.radius = 1;
	data->spell[AVADA_KEDAVRA].item.front_img = &data->img[AVADA_KEDAVRA_IMG];
	data->spell[AVADA_KEDAVRA].item.back_img = &data->img[AVADA_KEDAVRA_IMG];
	data->spell[AVADA_KEDAVRA].class = DARK_SPELL;
	data->spell[AVADA_KEDAVRA].icn = &data->img[AVADA_KEDAVRA_ICN];
	data->spell[AVADA_KEDAVRA].icn_name = &data->img[AVADA_KEDAVRA_NAME];
}

static void	init_petrificus_totalus(t_data *data)
{
	data->spell[PETRIFICUS_TOTALUS].base_cooldown = 15;
	data->spell[PETRIFICUS_TOTALUS].call = cast_spell;
	data->spell[PETRIFICUS_TOTALUS].type = PETRIFICUS_TOTALUS;
	data->spell[PETRIFICUS_TOTALUS].damage.slow_force_do = 90;
	data->spell[PETRIFICUS_TOTALUS].damage.slow_frame_do = 120;
	data->spell[PETRIFICUS_TOTALUS].item.speed = 35;
	data->spell[PETRIFICUS_TOTALUS].item.radius = 5;
	data->spell[PETRIFICUS_TOTALUS].item.front_img = &data->img[PETRIFICUS_TOTALUS_IMG];
	data->spell[PETRIFICUS_TOTALUS].item.back_img = &data->img[PETRIFICUS_TOTALUS_IMG];
	data->spell[PETRIFICUS_TOTALUS].class = DEFENSIVE_SPELL;
	data->spell[PETRIFICUS_TOTALUS].icn = &data->img[PETRIFICUS_TOTALUS_ICN];
	data->spell[PETRIFICUS_TOTALUS].icn_name = &data->img[PETRIFICUS_TOTALUS_NAME];
}

static void	init_protego(t_data *data)
{
	data->spell[PROTEGO].base_cooldown = 10;
	data->spell[PROTEGO].base_timer = 10;
	data->spell[PROTEGO].call = cast_protego;
	data->spell[PROTEGO].type = PROTEGO;
	data->spell[PROTEGO].class = DEFENSIVE_SPELL;
	data->spell[PROTEGO].icn = &data->img[PROTEGO_ICN];
	data->spell[PROTEGO].icn_name = &data->img[PROTEGO_NAME];
}

static void	init_bombarda(t_data *data)
{
	data->spell[BOMBARDA].base_cooldown = 5;
	data->spell[BOMBARDA].call = cast_spell;
	data->spell[BOMBARDA].type = BOMBARDA;
	data->spell[BOMBARDA].damage.damage_do = 25;
	data->spell[BOMBARDA].item.speed = 0;
	data->spell[BOMBARDA].item.radius = 6;
	data->spell[BOMBARDA].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[BOMBARDA].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[BOMBARDA].class = OFFENSIVE_SPELL;
	data->spell[BOMBARDA].icn = &data->img[BOMBARDA_ICN];
	data->spell[BOMBARDA].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_confundo(t_data *data)
{
	data->spell[CONFUNDO].base_cooldown = 5;
	data->spell[CONFUNDO].call = cast_spell;
	data->spell[CONFUNDO].type = CONFUNDO;
	data->spell[CONFUNDO].damage.damage_do = 25;
	data->spell[CONFUNDO].item.speed = 0;
	data->spell[CONFUNDO].item.radius = 6;
	data->spell[CONFUNDO].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[CONFUNDO].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[CONFUNDO].class = OFFENSIVE_SPELL;
	data->spell[CONFUNDO].icn = &data->img[CONFUNDO_ICN];
	data->spell[CONFUNDO].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_endoloris(t_data *data)
{
	data->spell[ENDOLORIS].base_cooldown = 5;
	data->spell[ENDOLORIS].call = cast_spell;
	data->spell[ENDOLORIS].type = BOMBARDA;
	data->spell[ENDOLORIS].damage.damage_do = 25;
	data->spell[ENDOLORIS].item.speed = 0;
	data->spell[ENDOLORIS].item.radius = 6;
	data->spell[ENDOLORIS].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[ENDOLORIS].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[ENDOLORIS].class = OFFENSIVE_SPELL;
	data->spell[ENDOLORIS].icn = &data->img[ENDOLORIS_ICN];
	data->spell[ENDOLORIS].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_episkey(t_data *data)
{
	data->spell[EPISKEY].base_cooldown = 5;
	data->spell[EPISKEY].call = cast_spell;
	data->spell[EPISKEY].type = BOMBARDA;
	data->spell[EPISKEY].damage.damage_do = 25;
	data->spell[EPISKEY].item.speed = 0;
	data->spell[EPISKEY].item.radius = 6;
	data->spell[EPISKEY].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[EPISKEY].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[EPISKEY].class = OFFENSIVE_SPELL;
	data->spell[EPISKEY].icn = &data->img[EPISKEY_ICN];
	data->spell[EPISKEY].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_expecto_patronum(t_data *data)
{
	data->spell[EXPECTO_PATRONUM].base_cooldown = 5;
	data->spell[EXPECTO_PATRONUM].call = cast_spell;
	data->spell[EXPECTO_PATRONUM].type = BOMBARDA;
	data->spell[EXPECTO_PATRONUM].damage.damage_do = 25;
	data->spell[EXPECTO_PATRONUM].item.speed = 0;
	data->spell[EXPECTO_PATRONUM].item.radius = 6;
	data->spell[EXPECTO_PATRONUM].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[EXPECTO_PATRONUM].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[EXPECTO_PATRONUM].class = OFFENSIVE_SPELL;
	data->spell[EXPECTO_PATRONUM].icn = &data->img[EXPECTO_PATRONUM_ICN];
	data->spell[EXPECTO_PATRONUM].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_expelliarmus(t_data *data)
{
	data->spell[EXPELLIARMUS].base_cooldown = 5;
	data->spell[EXPELLIARMUS].call = cast_spell;
	data->spell[EXPELLIARMUS].type = BOMBARDA;
	data->spell[EXPELLIARMUS].damage.damage_do = 25;
	data->spell[EXPELLIARMUS].item.speed = 0;
	data->spell[EXPELLIARMUS].item.radius = 6;
	data->spell[EXPELLIARMUS].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[EXPELLIARMUS].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[EXPELLIARMUS].class = OFFENSIVE_SPELL;
	data->spell[EXPELLIARMUS].icn = &data->img[EXPELLIARMUS_ICN];
	data->spell[EXPELLIARMUS].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_repulso(t_data *data)
{
	data->spell[REPULSO].base_cooldown = 5;
	data->spell[REPULSO].call = cast_spell;
	data->spell[REPULSO].type = BOMBARDA;
	data->spell[REPULSO].damage.damage_do = 25;
	data->spell[REPULSO].item.speed = 0;
	data->spell[REPULSO].item.radius = 6;
	data->spell[REPULSO].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[REPULSO].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[REPULSO].class = OFFENSIVE_SPELL;
	data->spell[REPULSO].icn = &data->img[REPULSO_ICN];
	data->spell[REPULSO].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_stupefix(t_data *data)
{
	data->spell[STUPEFIX].base_cooldown = 5;
	data->spell[STUPEFIX].call = cast_spell;
	data->spell[STUPEFIX].type = BOMBARDA;
	data->spell[STUPEFIX].damage.damage_do = 25;
	data->spell[STUPEFIX].item.speed = 0;
	data->spell[STUPEFIX].item.radius = 6;
	data->spell[STUPEFIX].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[STUPEFIX].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[STUPEFIX].class = OFFENSIVE_SPELL;
	data->spell[STUPEFIX].icn = &data->img[STUPEFIX_ICN];
	data->spell[STUPEFIX].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_oppugno(t_data *data)
{
	data->spell[OPPUGNO].base_cooldown = 5;
	data->spell[OPPUGNO].call = cast_spell;
	data->spell[OPPUGNO].type = BOMBARDA;
	data->spell[OPPUGNO].damage.damage_do = 25;
	data->spell[OPPUGNO].item.speed = 0;
	data->spell[OPPUGNO].item.radius = 6;
	data->spell[OPPUGNO].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[OPPUGNO].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[OPPUGNO].class = OFFENSIVE_SPELL;
	data->spell[OPPUGNO].icn = &data->img[OPPUGNO_ICN];
	data->spell[OPPUGNO].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_sectumsempra(t_data *data)
{
	data->spell[SECTUMSEMPRA].base_cooldown = 5;
	data->spell[SECTUMSEMPRA].call = cast_spell;
	data->spell[SECTUMSEMPRA].type = BOMBARDA;
	data->spell[SECTUMSEMPRA].damage.damage_do = 25;
	data->spell[SECTUMSEMPRA].item.speed = 0;
	data->spell[SECTUMSEMPRA].item.radius = 6;
	data->spell[SECTUMSEMPRA].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[SECTUMSEMPRA].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[SECTUMSEMPRA].class = OFFENSIVE_SPELL;
	data->spell[SECTUMSEMPRA].icn = &data->img[SECTUMSEMPRA_ICN];
	data->spell[SECTUMSEMPRA].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_serpensortia(t_data *data)
{
	data->spell[SERPENSORTIA].base_cooldown = 5;
	data->spell[SERPENSORTIA].call = cast_spell;
	data->spell[SERPENSORTIA].type = BOMBARDA;
	data->spell[SERPENSORTIA].damage.damage_do = 25;
	data->spell[SERPENSORTIA].item.speed = 0;
	data->spell[SERPENSORTIA].item.radius = 6;
	data->spell[SERPENSORTIA].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[SERPENSORTIA].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[SERPENSORTIA].class = OFFENSIVE_SPELL;
	data->spell[SERPENSORTIA].icn = &data->img[SERPENSORTIA_ICN];
	data->spell[SERPENSORTIA].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_ventus(t_data *data)
{
	data->spell[VENTUS].base_cooldown = 5;
	data->spell[VENTUS].call = cast_spell;
	data->spell[VENTUS].type = BOMBARDA;
	data->spell[VENTUS].damage.damage_do = 25;
	data->spell[VENTUS].item.speed = 0;
	data->spell[VENTUS].item.radius = 6;
	data->spell[VENTUS].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[VENTUS].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[VENTUS].class = OFFENSIVE_SPELL;
	data->spell[VENTUS].icn = &data->img[VENTUS_ICN];
	data->spell[VENTUS].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_vipera_evanesca(t_data *data)
{
	data->spell[VIPERA_EVANESCA].base_cooldown = 5;
	data->spell[VIPERA_EVANESCA].call = cast_spell;
	data->spell[VIPERA_EVANESCA].type = BOMBARDA;
	data->spell[VIPERA_EVANESCA].damage.damage_do = 25;
	data->spell[VIPERA_EVANESCA].item.speed = 0;
	data->spell[VIPERA_EVANESCA].item.radius = 6;
	data->spell[VIPERA_EVANESCA].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[VIPERA_EVANESCA].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[VIPERA_EVANESCA].class = OFFENSIVE_SPELL;
	data->spell[VIPERA_EVANESCA].icn = &data->img[VIPERA_EVANESCA_ICN];
	data->spell[VIPERA_EVANESCA].icn_name = &data->img[BOMBARDA_NAME];
}

static void	init_vulnera_samentur(t_data *data)
{
	data->spell[VULNERA_SANENTUR].base_cooldown = 5;
	data->spell[VULNERA_SANENTUR].call = cast_spell;
	data->spell[VULNERA_SANENTUR].type = BOMBARDA;
	data->spell[VULNERA_SANENTUR].damage.damage_do = 25;
	data->spell[VULNERA_SANENTUR].item.speed = 0;
	data->spell[VULNERA_SANENTUR].item.radius = 6;
	data->spell[VULNERA_SANENTUR].item.front_img = &data->img[BOMBARDA_IMG];
	data->spell[VULNERA_SANENTUR].item.back_img = &data->img[BOMBARDA_IMG];
	data->spell[VULNERA_SANENTUR].class = OFFENSIVE_SPELL;
	data->spell[VULNERA_SANENTUR].icn = &data->img[VULNERA_SANENTUR_ICN];
	data->spell[VULNERA_SANENTUR].icn_name = &data->img[BOMBARDA_NAME];
}

void	init_spell(t_data *data)
{
	data->active_spell = -1;
	data->cast_spell = -1;
	data->spell_menu.selected = -1;
	init_aguamenti(data);
	init_incendio(data);
	init_arania_exumai(data);
	init_glacius(data);
	init_lumos(data);
	init_avada_kedavra(data);
	init_petrificus_totalus(data);
	init_protego(data);
	init_bombarda(data);

	init_confundo(data);
	init_endoloris(data);
	init_episkey(data);
	init_expecto_patronum(data);
	init_expelliarmus(data);
	init_repulso(data);
	init_stupefix(data);
	init_oppugno(data);
	init_sectumsempra(data);
	init_serpensortia(data);
	init_ventus(data);
	init_vipera_evanesca(data);
	init_vulnera_samentur(data);
}
