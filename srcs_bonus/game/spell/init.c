#include "struct_bonus.h"
#include "cub3d_bonus.h"

void	set_spell_take(t_data *data)
{
	data->cast_spell = -1;
	data->spell_take[0] = AGUAMENTI;
	data->spell_take[1] = INCENDIO;
	data->spell_take[2] = GLACIUS;
	data->spell_take[3] = ARANIA_EXUMAI;
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
	data->spell[INCENDIO].base_cooldown = 15;
	data->spell[INCENDIO].call = cast_spell;
	data->spell[INCENDIO].type = INCENDIO;
	data->spell[INCENDIO].damage.damage_do = 25;
	data->spell[INCENDIO].damage.fire_do = 25;
	data->spell[INCENDIO].item.speed = 30;
	data->spell[INCENDIO].item.radius = 3;
	data->spell[INCENDIO].item.front_img = &data->img[INCENDIO_IMG];
	data->spell[INCENDIO].item.back_img = &data->img[INCENDIO_IMG];
	data->spell[INCENDIO].class = OFFENSIVE_SPELL;
	data->spell[INCENDIO].icn = &data->img[INCENDIO_ICN];
	data->spell[INCENDIO].icn_name = &data->img[INCENDIO_NAME];
}

static void	init_glacius(t_data *data)
{
	data->spell[GLACIUS].base_cooldown = 3;
	data->spell[GLACIUS].call = cast_spell;
	data->spell[GLACIUS].type = GLACIUS;
	data->spell[GLACIUS].damage.damage_do = 3;
	data->spell[GLACIUS].damage.slow_do = 50;
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
	data->spell[ARANIA_EXUMAI].base_cooldown = 10;
	data->spell[ARANIA_EXUMAI].call = cast_spell;
	data->spell[ARANIA_EXUMAI].type = ARANIA_EXUMAI;
	data->spell[ARANIA_EXUMAI].damage.damage_do = 50;
	data->spell[ARANIA_EXUMAI].damage.slow_do = 15;
	data->spell[ARANIA_EXUMAI].item.speed = 50;
	data->spell[ARANIA_EXUMAI].item.radius = 3;
	data->spell[ARANIA_EXUMAI].item.front_img = &data->img[ARANIA_EXUMAI_IMG];
	data->spell[ARANIA_EXUMAI].item.back_img = &data->img[ARANIA_EXUMAI_IMG];
	data->spell[ARANIA_EXUMAI].class = DEFENSIVE_SPELL;
	data->spell[ARANIA_EXUMAI].icn = &data->img[ARANIA_EXUMAI_ICN];
	data->spell[ARANIA_EXUMAI].icn_name = &data->img[ARANIA_EXUMAI_NAME];
}

static void	init_aguamenti(t_data *data)
{
	data->spell[AGUAMENTI].base_cooldown = 0;
	data->spell[AGUAMENTI].call = cast_spell;
	data->spell[AGUAMENTI].type = AGUAMENTI;
	data->spell[AGUAMENTI].damage.damage_do = 5;
	data->spell[AGUAMENTI].damage.slow_do = 15;
	data->spell[AGUAMENTI].item.speed = 20;
	data->spell[AGUAMENTI].item.radius = 3;
	data->spell[AGUAMENTI].item.front_img = &data->img[AGUAMENTI_IMG];
	data->spell[AGUAMENTI].item.back_img = &data->img[AGUAMENTI_IMG];
	data->spell[AGUAMENTI].class = DEFENSIVE_SPELL;
	data->spell[AGUAMENTI].icn = &data->img[AGUAMENTI_ICN];
	data->spell[AGUAMENTI].icn_name = &data->img[AGUAMENTI_NAME];
}

void	init_spell(t_data *data)
{
	data->active_spell = -1;
	data->cast_spell = -1;
	data->spell_menu.selected = -1;
	init_lumos(data);
	init_incendio(data);
	init_glacius(data);
	init_arania_exumai(data);
	init_aguamenti(data);
}
