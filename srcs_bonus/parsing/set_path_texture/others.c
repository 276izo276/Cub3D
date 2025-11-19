#include "cub3d_bonus.h"
#include "texture_bonus.h"
#include "utils_bonus.h"

static void	set_path_menu(t_data *data)
{
	data->img[SPELL_LOCK].path = "./texture/menu/spell_lock.xpm";
	data->img[END_MENU].path = "./texture/menu/death_background.xpm";
	data->img[RETRY_BUTTON].path = "./texture/menu/retry_button.xpm";
	data->img[QUIT_BUTTON].path = "./texture/menu/quit_button.xpm";
	data->img[END_BACKGROUND].path = "./texture/menu/end_background.xpm";
	data->img[PORTKEY_IMG].path = "./texture/portkey.xpm";
	data->img[SANDGLASS].path = "./texture/menu/sandglass.xpm";
	data->img[SELECT].path = "./texture/menu/select.xpm";
	data->img[PAUSE_BACKGROUND].path = "./texture/menu/pause_background.xpm";
	data->img[PAUSE_SENSITIVITY].path = "./texture/menu/pause_sensitivity.xpm";
	data->img[PAUSE_RESUME].path = "./texture/menu/resume_button.xpm";
	data->img[PAUSE_EXIT].path = "./texture/menu/exit_button.xpm";
	data->img[PAUSE_SELECTOR].path = "./texture/menu/pause_selector.xpm";
	data->img[SPELL_BACKGROUND].path = "./texture/menu/spell_background.xpm";
	data->img[BORDER_FIRE].path = "./texture/menu/border_fire.xpm";
	data->img[BORDER_WATER].path = "./texture/menu/border_water.xpm";
	data->img[BORDER_EARTH].path = "./texture/menu/border_earth.xpm";
	data->img[BORDER_AIR].path = "./texture/menu/border_air.xpm";
	data->img[MENU_AIR].path = "./texture/menu/air.xpm";
	data->img[MENU_FIRE].path = "./texture/menu/fire.xpm";
	data->img[MENU_WATER].path = "./texture/menu/water.xpm";
	data->img[MENU_EARTH].path = "./texture/menu/earth.xpm";
}

static void	set_path_item(t_data *data)
{
	data->img[WAND_SPIDER_IMG].path = "./texture/player_hand/spider_wand.xpm";
	data->img[WAND_WOLF_IMG].path = "./texture/player_hand/wolf_wand.xpm";
	data->img[WAND_ELEM_IMG].path = "./texture/player_hand/elem_wand.xpm";
	data->img[WAND_DEMENTOR_IMG].path = "./texture/player_hand/dementor_wand.xpm";
	data->img[PILLAR_IMG].path = "./texture/player_hand/pillar.xpm";
	data->img[DOOR_MOVE].path = "./texture/door_close.xpm";
	data->img[DOOR_FIXED].path = "./texture/door_open.xpm";
	data->img[FLOO_CLOSE].path = "./texture/floo_close.xpm";
	data->img[FLOO_OPEN].path = "./texture/floo_open.xpm";
	data->img[POPO_HEAL].path = "./texture/popo_heal.xpm";
	data->img[POPO_SHIELD].path = "./texture/popo_shield.xpm";
	data->img[POPO_FLOO].path = "./texture/popo_floo.xpm";
	data->img[POPO_INVI].path = "./texture/invisibility_cloth.xpm";
	data->img[POPO_HEAL_IMG].path = "./texture/popo_heal_img.xpm";
	data->img[POPO_SHIELD_IMG].path = "./texture/popo_shield_img.xpm";
	data->img[POPO_FLOO_IMG].path = "./texture/popo_floo_img.xpm";
	data->img[POPO_INVI_IMG].path = "./texture/invisibility_cloth_img.xpm";
}

static void	set_path_status(t_data *data)
{
	data->img[HEART].path = "./texture/heart.xpm";
	data->img[SHIELD].path = "./texture/shield.xpm";
	data->img[XP].path = "./texture/xp.xpm";
	data->img[FLAME].path = "./texture/flame.xpm";
	data->img[POISON].path = "./texture/poison.xpm";
	data->img[SLOW].path = "./texture/slow.xpm";
	data->img[CURSE].path = "./texture/curse.xpm";
	data->img[SHIELD_1].path = "./texture/shield_1.xpm";
	data->img[SHIELD_2].path = "./texture/shield_2.xpm";
	data->img[SHIELD_3].path = "./texture/shield_3.xpm";
	data->img[SHIELD_4].path = "./texture/shield_4.xpm";
	data->img[SHIELD_5].path = "./texture/shield_5.xpm";
	data->img[SHIELD_6].path = "./texture/shield_6.xpm";
}

static void	set_path_wall_msg(t_data *data)
{
	data->img[WALL_MSG_1].path = "./texture/first_msg.xpm";
	data->img[WALL_MSG_2].path = "./texture/snd_msg.xpm";
	data->img[WALL_MSG_3].path = "./texture/third_msg.xpm";
	if (data->player.coa == FIRE)
		data->img[WALL_MSG_COA].path = "./texture/fire_msg.xpm";
	else if (data->player.coa == WATER)
		data->img[WALL_MSG_COA].path = "./texture/water_msg.xpm";
	else if (data->player.coa == EARTH)
		data->img[WALL_MSG_COA].path = "./texture/earth_msg.xpm";
	else if (data->player.coa == AIR)
		data->img[WALL_MSG_COA].path = "./texture/air_msg.xpm";
	data->img[WALL_MSG_4].path = "./texture/fourth_msg.xpm";
	data->img[WALL_MSG_5].path = "./texture/five_msg.xpm";
	data->img[WALL_MSG_6].path = "./texture/six_msg.xpm";
}

void	set_path_others_texture(t_data *data)
{

	set_path_menu(data);
	set_path_item(data);
	set_path_status(data);
	set_path_wall_msg(data);
	data->img[PLAYER_WAND].path = "./texture/player_hand/wand_sureau.xpm";
	data->img[PLAYER_WAND_2].path = "./texture/player_hand/wand_2.xpm";
	data->img[PLAYER_WAND_3].path = "./texture/player_hand/wand_3.xpm";
	data->img[PLAYER_WAND_4].path = "./texture/player_hand/wand_4.xpm";
	data->img[PLAYER_WAND_5].path = "./texture/player_hand/wand_5.xpm";
	data->img[PLAYER_WAND_6].path = "./texture/player_hand/wand_6.xpm";
	data->img[PLAYER_WAND_7].path = "./texture/player_hand/wand_7.xpm";
	data->img[SELECT_HAND].path = "./texture/menu/select_hand.xpm";
	data->img[PLAYER_HAND].path = "./texture/player_hand/wand_sureau.xpm";
	data->img[LEFT_SELECT].path = "./texture/menu/left_select.xpm";
}
