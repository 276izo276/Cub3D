#include "cub3d_bonus.h"
#include "parsing_bonus.h"

void	set_spell_take(t_data *data)
{
	data->cast_spell = -1;
	data->spell_take[0] = LUMOS;
	data->spell_take[1] = INCENDIO;
	data->spell_take[2] = GLACIUS;
	data->spell_take[3] = REPULSO;
}

static void	init_endoloris(t_data *data)
{
	data->spell[ENDOLORIS].base_cooldown = 18;
	data->spell[ENDOLORIS].call = cast_spell;
	data->spell[ENDOLORIS].type = ENDOLORIS;
	data->spell[ENDOLORIS].damage.damage_do = 10;
	data->spell[ENDOLORIS].damage.curse_force_do = .2;
	data->spell[ENDOLORIS].damage.curse_frame_do = 600;
	data->spell[ENDOLORIS].item.speed = 25;
	data->spell[ENDOLORIS].item.radius = 3.0;
	data->spell[ENDOLORIS].item.front_img = &data->img[ENDOLORIS_IMG];
	data->spell[ENDOLORIS].item.back_img = &data->img[ENDOLORIS_IMG];
	data->spell[ENDOLORIS].class = DARK_SPELL;
	data->spell[ENDOLORIS].icn = &data->img[ENDOLORIS_ICN];
	data->spell[ENDOLORIS].icn_name = &data->img[ENDOLORIS_NAME];
	data->spell[ENDOLORIS].necessary_lvl = 11.0;
}

static void	init_avada_kedavra(t_data *data)
{
	data->spell[AVADA_KEDAVRA].base_cooldown = 20;
	data->spell[AVADA_KEDAVRA].call = cast_spell;
	data->spell[AVADA_KEDAVRA].type = AVADA_KEDAVRA;
	data->spell[AVADA_KEDAVRA].damage.damage_do = 25;
	data->spell[AVADA_KEDAVRA].damage.curse_force_do = 45;
	data->spell[AVADA_KEDAVRA].damage.curse_frame_do = 4;
	data->spell[AVADA_KEDAVRA].item.speed = 25;
	data->spell[AVADA_KEDAVRA].item.radius = 3.0;
	data->spell[AVADA_KEDAVRA].item.front_img = &data->img[AVADA_KEDAVRA_IMG];
	data->spell[AVADA_KEDAVRA].item.back_img = &data->img[AVADA_KEDAVRA_IMG];
	data->spell[AVADA_KEDAVRA].class = DARK_SPELL;
	data->spell[AVADA_KEDAVRA].icn = &data->img[AVADA_KEDAVRA_ICN];
	data->spell[AVADA_KEDAVRA].icn_name = &data->img[AVADA_KEDAVRA_NAME];
	data->spell[AVADA_KEDAVRA].necessary_lvl = 12.0;
}

static void	init_sorcerer_spell(t_data *data)
{
	init_endoloris(data);
	init_aguamenti(data);
}

void	init_spell(t_data *data)
{
	data->active_spell = -1;
	data->cast_spell = -1;
	data->spell_menu.selected = -1;
	init_lumos(data);
	init_incendio(data);
	init_glacius(data);
	init_repulso(data);
	init_arania_exumai(data);
	init_protego(data);
	init_expelliarmus(data);
	init_expecto_patronum(data);
	init_vipera_evanesca(data);
	init_serpensortia(data);
	init_ventus(data);
	init_bombarda(data);
	init_episkey(data);
	init_stupefix(data);
	init_oppugno(data);
	init_vulnera_sanentur(data);
	init_petrificus_totalus(data);
	init_sectumsempra(data);
	init_confundo(data);
	init_avada_kedavra(data);
	init_sorcerer_spell(data);
}
