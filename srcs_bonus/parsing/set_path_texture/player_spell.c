#include "cub3d_bonus.h"
#include "texture_bonus.h"
#include "utils_bonus.h"

static void	set_path_name(t_data *data)
{
	data->img[AGUAMENTI_NAME].path = "./texture/menu/aguamenti_name.xpm";
	data->img[INCENDIO_NAME].path = "./texture/menu/incendio_name.xpm";
	data->img[ARANIA_EXUMAI_NAME]
		.path = "./texture/menu/arania_exumai_name.xpm";
	data->img[GLACIUS_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[LUMOS_NAME]
		.path = "./texture/menu/lumos_name.xpm";
	data->img[AVADA_KEDAVRA_NAME]
		.path = "./texture/menu/avada_kedavra_name.xpm";
	data->img[PETRIFICUS_TOTALUS_NAME]
		.path = "./texture/menu/petrificus_totalus_name.xpm";
	data->img[PROTEGO_NAME].path = "./texture/menu/protego_name.xpm";
	data->img[BOMBARDA_NAME].path = "./texture/menu/bombarda_name.xpm";
	data->img[EPISKEY_NAME].path = "./texture/menu/episkey_name.xpm";
	data->img[EXPECTO_PATRONUM_NAME]
		.path = "./texture/menu/expecto_patronum_name.xpm";
	data->img[EXPELLIARMUS_NAME].path = "./texture/menu/expelliarmus_name.xpm";
	data->img[VULNERA_SANENTUR_NAME]
		.path = "./texture/menu/vulnera_sanentur_name.xpm";
	data->img[VIPERA_EVANESCA_NAME]
		.path = "./texture/menu/vipera_evanesca_name.xpm";
	data->img[OPPUGNO_NAME].path = "./texture/menu/oppugno_name.xpm";
	data->img[SERPENSORTIA_NAME].path = "./texture/menu/serpensortia_name.xpm";
	data->img[CONFUNDO_NAME].path = "./texture/menu/confundo_name.xpm";
	data->img[ENDOLORIS_NAME].path = "./texture/menu/endoloris_name.xpm";
}

static void	set_path_icn(t_data *data)
{
	data->img[AGUAMENTI_ICN].path = "./texture/spell/aguamenti_icn.xpm";
	data->img[INCENDIO_ICN].path = "./texture/spell/incendio_icn.xpm";
	data->img[ARANIA_EXUMAI_ICN].path = "./texture/spell/arania_exumai_icn.xpm";
	data->img[GLACIUS_ICN].path = "./texture/spell/glacius_icn.xpm";
	data->img[LUMOS_ICN].path = "./texture/spell/lumos_icn.xpm";
	data->img[AVADA_KEDAVRA_ICN].path = "./texture/spell/avada_kedavra_icn.xpm";
	data->img[PETRIFICUS_TOTALUS_ICN]
		.path = "./texture/spell/petrificus_totalus_icn.xpm";
	data->img[PROTEGO_ICN].path = "./texture/spell/protego_icn.xpm";
	data->img[BOMBARDA_ICN].path = "./texture/spell/bombarda_icn.xpm";
	data->img[CONFUNDO_ICN].path = "./texture/spell/confundo_icn.xpm";
	data->img[ENDOLORIS_ICN].path = "./texture/spell/endoloris_icn.xpm";
	data->img[EPISKEY_ICN].path = "./texture/spell/episkey_icn.xpm";
	data->img[EXPECTO_PATRONUM_ICN]
		.path = "./texture/spell/expecto_patronum_icn.xpm";
	data->img[EXPELLIARMUS_ICN].path = "./texture/spell/expelliarmus_icn.xpm";
	data->img[REPULSO_ICN].path = "./texture/spell/repulso_icn.xpm";
	data->img[STUPEFIX_ICN].path = "./texture/spell/stupefix_icn.xpm";
	data->img[OPPUGNO_ICN].path = "./texture/spell/oppugno_icn.xpm";
	data->img[SECTUMSEMPRA_ICN].path = "./texture/spell/sectumsempra_icn.xpm";
	data->img[SERPENSORTIA_ICN].path = "./texture/spell/serpensortia_icn.xpm";
	data->img[VENTUS_ICN].path = "./texture/spell/ventus_icn.xpm";
	data->img[VIPERA_EVANESCA_ICN]
		.path = "./texture/spell/vipera_evanesca_icn.xpm";
}

static void	set_path_img(t_data *data)
{
	data->img[INCENDIO_IMG].path = "./texture/spell/incendio.xpm";
	data->img[GLACIUS_IMG].path = "./texture/spell/glacius.xpm";
	data->img[AVADA_KEDAVRA_IMG].path = "./texture/spell/curse_spell.xpm";
	data->img[PETRIFICUS_TOTALUS_IMG]
		.path = "./texture/spell/petrificus_totalus.xpm";
	data->img[PROTEGO_IMG].path = "./texture/spell/glacius.xpm";
	data->img[BOMBARDA_IMG].path = "./texture/spell/bombarda.xpm";
	data->img[CONFUNDO_IMG].path = "./texture/spell/confundo.xpm";
	data->img[ENDOLORIS_IMG].path = "./texture/spell/curse_spell.xpm";
	data->img[EPISKEY_IMG].path = "./texture/spell/glacius.xpm";
	data->img[EXPECTO_PATRONUM_IMG].path = "./texture/spell/glacius.xpm";
	data->img[EXPELLIARMUS_IMG].path = "./texture/spell/expelliarmus.xpm";
	data->img[REPULSO_IMG].path = "./texture/spell/repulso.xpm";
	data->img[STUPEFIX_IMG].path = "./texture/spell/stupefix.xpm";
	data->img[OPPUGNO_IMG].path = "./texture/spell/glacius.xpm";
	data->img[SECTUMSEMPRA_IMG].path = "./texture/spell/sectumsempra.xpm";
	data->img[SERPENSORTIA_IMG].path = "./texture/spell/glacius.xpm";
	data->img[VENTUS_IMG].path = "./texture/spell/ventus.xpm";
	data->img[VIPERA_EVANESCA_IMG].path = "./texture/spell/glacius.xpm";
	data->img[VULNERA_SANENTUR_IMG].path = "./texture/spell/glacius.xpm";
	data->img[ARANIA_EXUMAI_IMG].path = "./texture/spell/arania_exumai.xpm";
	data->img[AGUAMENTI_IMG].path = "./texture/spell/aguamenti.xpm";
}

void	set_path_player_spell(t_data *data)
{
	set_path_name(data);
	data->img[REPULSO_NAME].path = "./texture/menu/repulso_name.xpm";
	data->img[STUPEFIX_NAME].path = "./texture/menu/stupefix_name.xpm";
	data->img[SECTUMSEMPRA_NAME].path = "./texture/menu/sectumsempra_name.xpm";
	data->img[VENTUS_NAME].path = "./texture/menu/ventus_name.xpm";
	set_path_icn(data);
	data->img[VULNERA_SANENTUR_ICN]
		.path = "./texture/spell/vulnera_sanentur_icn.xpm";
	set_path_img(data);
}
