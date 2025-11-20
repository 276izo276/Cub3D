#include "cub3d_bonus.h"
#include "texture_bonus.h"
#include "utils_bonus.h"

static void	set_path_spell(t_data *data)
{
	data->img[TIG_IMG].path = "./texture/spell/TIG.xpm";
	data->img[PIZZA_IMG].path = "./texture/spell/pizza.xpm";
	data->img[MAC_IMG].path = "./texture/spell/mac.xpm";
	data->img[FOLDER_IMG].path = "./texture/spell/folder.xpm";
	data->img[MARVIN_IMG].path = "./texture/spell/marvin.xpm";
	data->img[TAYLOR_SWIFT_IMG].path = "./texture/spell/taylor_swift.xpm";
	data->img[COMPANY_IMG].path = "./texture/spell/company.xpm";
	data->img[LOGO_42_IMG].path = "./texture/spell/42.xpm";
	data->img[WEB_SPIDER_IMG].path = "./texture/web.xpm";
}

static void	set_path_front(t_data *data)
{
	data->img[BIRD_FRONT].path = "./texture/bird_front.xpm";
	data->img[ELEM_FRONT].path = "./texture/elem_front.xpm";
	data->img[WOLF_FRONT].path = "./texture/wolf_front.xpm";
	data->img[SPIDER_FRONT].path = "./texture/spider_front.xpm";
	data->img[KUNFANDI_FRONT].path = "./texture/kunfandi_front.xpm";
	data->img[NANCY_FRONT].path = "./texture/nancy_front.xpm";
	data->img[DEMENTOR_FRONT].path = "./texture/dementor_front.xpm";
	data->img[PILO_FRONT].path = "./texture/pilo_front.xpm";
	data->img[ZIPPY_FRONT].path = "./texture/zippy_front.xpm";
	data->img[STEF_FRONT].path = "./texture/stef_front.xpm";
	data->img[DIRLO_FRONT].path = "./texture/dirlo_front.xpm";
	data->img[CAMEO_FRONT].path = "./texture/cameo_front.xpm";
	data->img[ANAIS_FRONT].path = "./texture/anais_front.xpm";
	data->img[MARINA_FRONT].path = "./texture/marina_front.xpm";
}

static void	set_path_back(t_data *data)
{
	data->img[ELEM_BACK_45].path = "./texture/elem_back_45.xpm";
	data->img[ELEM_BACK].path = "./texture/elem_back.xpm";
	data->img[BIRD_BACK_45].path = "./texture/bird_back_45.xpm";
	data->img[BIRD_BACK].path = "./texture/bird_back.xpm";
	data->img[WOLF_BACK_45].path = "./texture/wolf_back_45.xpm";
	data->img[WOLF_BACK].path = "./texture/wolf_back.xpm";
	data->img[SPIDER_BACK_45].path = "./texture/spider_back_45.xpm";
	data->img[SPIDER_BACK].path = "./texture/spider_back.xpm";
	data->img[SNAKE_BACK].path = "./texture/snake_back.xpm";
	data->img[SNAKE_BACK_45].path = "./texture/snake_back_45.xpm";
	data->img[DEMENTOR_BACK_45].path = "./texture/dementor_back_45.xpm";
	data->img[DEMENTOR_BACK].path = "./texture/dementor_back.xpm";
	data->img[SORCERER_BACK].path = "./texture/sorcerer_back.xpm";
	data->img[SORCERER_BACK_45].path = "./texture/sorcerer_back_45.xpm";
}

static void	set_path_side(t_data *data)
{
	data->img[BIRD_SIDE_90].path = "./texture/bird_90.xpm";
	data->img[ELEM_SIDE_90].path = "./texture/elem_90.xpm";
	data->img[WOLF_SIDE_90].path = "./texture/wolf_90.xpm";
	data->img[SPIDER_SIDE_90].path = "./texture/spider_90.xpm";
	data->img[SNAKE_SIDE_90].path = "./texture/snake_90.xpm";
	data->img[SORCERER_SIDE_90].path = "./texture/sorcerer_90.xpm";
	data->img[DEMENTOR_SIDE_90].path = "./texture/dementor_90.xpm";
	data->img[PILO_FRONT_45].path = "./texture/pilo_front_45.xpm";
	data->img[ANAIS_FRONT_45].path = "./texture/anais_front_45.xpm";
	data->img[DIRLO_FRONT_45].path = "./texture/dirlo_front_45.xpm";
	data->img[STEF_FRONT_45].path = "./texture/stef_front_45.xpm";
	data->img[ZIPPY_FRONT_45].path = "./texture/zippy_front_45.xpm";
	data->img[CAMEO_FRONT_45].path = "./texture/cameo_front_45.xpm";
	data->img[NANCY_FRONT_45].path = "./texture/nancy_front_45.xpm";
	data->img[KUNFANDI_FRONT_45].path = "./texture/kunfandi_front_45.xpm";
	data->img[MARINA_FRONT_45].path = "./texture/marina_front_45.xpm";
	data->img[SPIDER_FRONT_45].path = "./texture/spider_front_45.xpm";
	data->img[SNAKE_FRONT].path = "./texture/snake_front.xpm";
	data->img[SNAKE_FRONT_45].path = "./texture/snake_front_45.xpm";
	data->img[DEMENTOR_FRONT_45].path = "./texture/dementor_front_45.xpm";
	data->img[WOLF_FRONT_45].path = "./texture/wolf_front_45.xpm";
	data->img[BIRD_FRONT_45].path = "./texture/bird_front_45.xpm";
	data->img[ELEM_FRONT_45].path = "./texture/elem_front_45.xpm";
}

void	set_path_enemy_texture(t_data *data)
{
	set_path_spell(data);
	set_path_front(data);
	set_path_back(data);
	set_path_side(data);
}
