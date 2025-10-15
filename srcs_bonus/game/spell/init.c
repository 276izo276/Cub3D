#include "struct_bonus.h"
#include "cub3d_bonus.h"

void	set_spell_take(t_data *data)
{
	data->cast_spell = -1;
	data->spell_take[0] = LUMOS;
	data->spell_take[1] = INCENDIO;
	data->spell_take[2] = GLACIUS;
	data->spell_take[3] = GLACIUS;
}

static void	init_lumos(t_data *data)
{
	data->spell[LUMOS].base_cooldown = 3;
	data->spell[LUMOS].base_timer = 7;
	data->spell[LUMOS].call = cast_lumos;
	data->spell[LUMOS].type = LUMOS;
	data->spell[LUMOS].class = CLASIC_SPELL;
	data->spell[LUMOS].icn = &data->img[LUMOS_ICN];
}

static void	init_incendio(t_data *data)
{
	data->spell[INCENDIO].base_cooldown = 0;
	data->spell[INCENDIO].call = cast_spell;
	data->spell[INCENDIO].type = INCENDIO;
	// data->spell[INCENDIO].img.path = "texture/spell/incendio.xpm";
	// open_img(&data->spell[INCENDIO].img, data);
	data->spell[INCENDIO].damage.damage_do = 10;
	data->spell[INCENDIO].damage.fire_do = 25;
	data->spell[INCENDIO].item.speed = 0;
	data->spell[INCENDIO].item.radius = 3;
	data->spell[INCENDIO].item.front_img = &data->img[INCENDIO_IMG];
	data->spell[INCENDIO].item.back_img = &data->img[INCENDIO_IMG];
	data->spell[INCENDIO].class = OFFENSIVE_SPELL;
	data->spell[INCENDIO].icn = &data->img[INCENDIO_ICN];
}

static void	init_glacius(t_data *data)
{
	data->spell[GLACIUS].base_cooldown = 0;
	data->spell[GLACIUS].call = cast_spell;
	data->spell[GLACIUS].type = GLACIUS;
	// data->spell[GLACIUS].img.path = "texture/spell/GLACIUS.xpm";
	// open_img(&data->spell[GLACIUS].img, data);
	data->spell[GLACIUS].damage.damage_do = 5;
	data->spell[GLACIUS].damage.slow_do = 15;
	data->spell[GLACIUS].item.speed = 0;
	data->spell[GLACIUS].item.radius = 3;
	data->spell[GLACIUS].item.front_img = &data->img[GLACIUS_IMG];
	data->spell[GLACIUS].item.back_img = &data->img[GLACIUS_IMG];
	data->spell[GLACIUS].class = OFFENSIVE_SPELL;
	data->spell[GLACIUS].icn = &data->img[GLACIUS_ICN];
}

void	init_spell(t_data *data)
{
	data->active_spell = -1;
	data->cast_spell = -1;
	init_lumos(data);
	init_incendio(data);
	init_glacius(data);
}
