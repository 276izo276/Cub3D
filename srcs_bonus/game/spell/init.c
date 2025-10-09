#include "struct_bonus.h"
#include "cub3d_bonus.h"

void	set_spell_take(t_data *data)
{
	data->cast_spell = -1;
	data->spell_take[0] = LUMOS;
	data->spell_take[1] = INCENDIO;
}

static void	init_lumos(t_data *data)
{
	data->spell[LUMOS].base_cooldown = 3;
	data->spell[LUMOS].base_timer = 7;
	data->spell[LUMOS].call = cast_lumos;
	data->spell[LUMOS].type = LUMOS;
}

static void	init_incendio(t_data *data)
{
	data->spell[INCENDIO].base_cooldown = 25;
	data->spell[INCENDIO].call = cast_spell;
	data->spell[INCENDIO].type = INCENDIO;
	data->spell[INCENDIO].img.path = "texture/spell/incendio.xpm";
	open_img(&data->spell[INCENDIO].img, data);
	data->spell[INCENDIO].damage.damage_do = 10;
	data->spell[INCENDIO].damage.fire_do = 25;
	data->spell[INCENDIO].item.speed = 15;
	data->spell[INCENDIO].item.radius = 2;
}

void	init_spell(t_data *data)
{
	data->active_spell = -1;
	data->cast_spell = -1;
	init_lumos(data);
	init_incendio(data);
}