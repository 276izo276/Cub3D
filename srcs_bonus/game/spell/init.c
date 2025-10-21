#include "struct_bonus.h"
#include "cub3d_bonus.h"

void	set_spell_take(t_data *data)
{
	data->cast_spell = -1;
	data->spell_take[0] = BOMBARDA;
	data->spell_take[1] = INCENDIO;
	data->spell_take[2] = ARANIA_EXUMAI;
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
	data->spell[AVADA_KEDAVRA].item.damage.damage_do = 5;
	data->spell[AVADA_KEDAVRA].item.damage.curse_force_do = 40;
	data->spell[AVADA_KEDAVRA].item.damage.curse_frame_do = 3;
	data->spell[AVADA_KEDAVRA].item.speed = 50;
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
}
