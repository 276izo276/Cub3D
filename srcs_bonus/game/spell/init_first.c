#include "cub3d_bonus.h"

void	init_lumos(t_data *data)
{
	data->spell[LUMOS].base_cooldown = 3;
	data->spell[LUMOS].base_timer = 7;
	data->spell[LUMOS].call = cast_lumos;
	data->spell[LUMOS].type = LUMOS;
	data->spell[LUMOS].class = CLASIC_SPELL;
	data->spell[LUMOS].icn = &data->img[LUMOS_ICN];
	data->spell[LUMOS].icn_name = &data->img[LUMOS_NAME];
	data->spell[LUMOS].necessary_lvl = 1.0;
}

void	init_incendio(t_data *data)
{
	data->spell[INCENDIO].base_cooldown = 0;
	data->spell[INCENDIO].call = cast_spell;
	data->spell[INCENDIO].type = INCENDIO;
	data->spell[INCENDIO].damage.damage_do = 10;
	data->spell[INCENDIO].damage.fire_frame_do = 60;
	data->spell[INCENDIO].damage.fire_force_do = .1;
	data->spell[INCENDIO].damage.damage_elem_do = -10;
	data->spell[INCENDIO].item.speed = 10;
	data->spell[INCENDIO].item.radius = 3;
	data->spell[INCENDIO].item.front_img = &data->img[INCENDIO_IMG];
	data->spell[INCENDIO].item.back_img = &data->img[INCENDIO_IMG];
	data->spell[INCENDIO].class = OFFENSIVE_SPELL;
	data->spell[INCENDIO].icn = &data->img[INCENDIO_ICN];
	data->spell[INCENDIO].icn_name = &data->img[INCENDIO_NAME];
	data->spell[INCENDIO].necessary_lvl = 1.0;
}

void	init_glacius(t_data *data)
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
	data->spell[GLACIUS].necessary_lvl = 1.5;
}

void	init_repulso(t_data *data)
{
	data->spell[REPULSO].base_cooldown = 8;
	data->spell[REPULSO].call = cast_spell;
	data->spell[REPULSO].type = REPULSO;
	data->spell[REPULSO].damage.damage_do = 5;
	data->spell[REPULSO].damage.repulso_force_do = 1.2;
	data->spell[REPULSO].damage.repulso_frame_do = 15;
	data->spell[REPULSO].item.speed = 0;
	data->spell[REPULSO].item.radius = 3;
	data->spell[REPULSO].item.front_img = &data->img[REPULSO_IMG];
	data->spell[REPULSO].item.back_img = &data->img[REPULSO_IMG];
	data->spell[REPULSO].class = OFFENSIVE_SPELL;
	data->spell[REPULSO].icn = &data->img[REPULSO_ICN];
	data->spell[REPULSO].icn_name = &data->img[REPULSO_NAME];
	data->spell[REPULSO].necessary_lvl = 2.0;
}

void	init_aguamenti(t_data *data)
{
	data->spell[AGUAMENTI].base_cooldown = 5;
	data->spell[AGUAMENTI].call = cast_spell;
	data->spell[AGUAMENTI].type = AGUAMENTI;
	data->spell[AGUAMENTI].damage.damage_do = 5;
	data->spell[AGUAMENTI].damage.damage_elem_do = 35;
	data->spell[AGUAMENTI].item.speed = 0;
	data->spell[AGUAMENTI].item.radius = 3;
	data->spell[AGUAMENTI].item.front_img = &data->img[AGUAMENTI_IMG];
	data->spell[AGUAMENTI].item.back_img = &data->img[AGUAMENTI_IMG];
	data->spell[AGUAMENTI].class = OFFENSIVE_SPELL;
	data->spell[AGUAMENTI].icn = &data->img[AGUAMENTI_ICN];
	data->spell[AGUAMENTI].icn_name = &data->img[AGUAMENTI_NAME];
	data->spell[AGUAMENTI].necessary_lvl = 2.5;
}
