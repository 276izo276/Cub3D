#include "cub3d_bonus.h"
#include "mlx.h"
#include "texture_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "time_bonus.h"
#include <color_bonus.h>
#include "ft_printf.h"

static void	set_path_texture(t_data *data)
{
	data->img[SELECT].path = "./texture/menu/select.xpm";
	data->img[SELECT_HAND].path = "./texture/menu/select_hand.xpm";
	data->img[PLAYER_HAND].path = "./texture/player_hand/wand_sureau.xpm";
	data->img[PLAYER_WAND].path = "./texture/player_hand/wand_sureau.xpm";
	data->img[LEFT_SELECT].path = "./texture/menu/left_select.xpm";
	data->img[DEMENTOR_FRONT].path = "./texture/dementor_front.xpm";
	data->img[DEMENTOR_BACK].path = "./texture/dementor_back.xpm";
	data->img[DOOR_MOVE].path = "./texture/door_close.xpm";
	data->img[DOOR_FIXED].path = "./texture/door_open.xpm";
	data->img[FLOO_CLOSE].path = "./texture/floo_close.xpm";
	data->img[FLOO_OPEN].path = "./texture/floo_open.xpm";
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

	data->img[INCENDIO_IMG].path = "./texture/spell/incendio.xpm";
	data->img[GLACIUS_IMG].path = "./texture/spell/glacius.xpm";
	data->img[AVADA_KEDAVRA_IMG].path = "./texture/spell/avada_kedavra.xpm";
	data->img[PETRIFICUS_TOTALUS_IMG].path = "./texture/spell/petrificus_totalus.xpm";
	data->img[PROTEGO_IMG].path = "./texture/spell/glacius.xpm";
	data->img[BOMBARDA_IMG].path = "./texture/spell/bombarda.xpm";
	data->img[CONFUNDO_IMG].path = "./texture/spell/glacius.xpm";
	data->img[ENDOLORIS_IMG].path = "./texture/spell/glacius.xpm";
	data->img[EPISKEY_IMG].path = "./texture/spell/glacius.xpm";
	data->img[EXPECTO_PATRONUM_IMG].path = "./texture/spell/glacius.xpm";
	data->img[EXPELLIARMUS_IMG].path = "./texture/spell/glacius.xpm";
	data->img[REPULSO_IMG].path = "./texture/spell/glacius.xpm";
	data->img[STUPEFIX_IMG].path = "./texture/spell/glacius.xpm";
	data->img[OPPUGNO_IMG].path = "./texture/spell/glacius.xpm";
	data->img[SECTUMSEMPRA_IMG].path = "./texture/spell/glacius.xpm";
	data->img[SERPENSORTIA_IMG].path = "./texture/spell/glacius.xpm";
	data->img[VENTUS_IMG].path = "./texture/spell/glacius.xpm";
	data->img[VIPERA_EVANESCA_IMG].path = "./texture/spell/glacius.xpm";
	data->img[VULNERA_SANENTUR_IMG].path = "./texture/spell/glacius.xpm";
	data->img[ARANIA_EXUMAI_IMG].path = "./texture/spell/arania_exumai.xpm";
	data->img[AGUAMENTI_IMG].path = "./texture/spell/aguamenti.xpm";


	data->img[LUMOS_ICN].path = "./texture/spell/lumos_icn.xpm";
	data->img[INCENDIO_ICN].path = "./texture/spell/incendio_icn.xpm";
	data->img[GLACIUS_ICN].path = "./texture/spell/glacius_icn.xpm";
	data->img[ARANIA_EXUMAI_ICN].path = "./texture/spell/arania_exumai_icn.xpm";
	data->img[AGUAMENTI_ICN].path = "./texture/spell/aguamenti_icn.xpm";
	data->img[AVADA_KEDAVRA_ICN].path = "./texture/spell/avada_kedavra_icn.xpm";
	data->img[PETRIFICUS_TOTALUS_ICN].path = "./texture/spell/petrificus_totalus_icn.xpm";
	data->img[PROTEGO_ICN].path = "./texture/spell/protego_icn.xpm";
	data->img[BOMBARDA_ICN].path = "./texture/spell/bombarda_icn.xpm";
	data->img[CONFUNDO_ICN].path = "./texture/spell/confundo_icn.xpm";
	data->img[ENDOLORIS_ICN].path = "./texture/spell/endoloris_icn.xpm";
	data->img[EPISKEY_ICN].path = "./texture/spell/episkey_icn.xpm";
	data->img[EXPECTO_PATRONUM_ICN].path = "./texture/spell/expecto_patronum_icn.xpm";
	data->img[EXPELLIARMUS_ICN].path = "./texture/spell/expelliarmus_icn.xpm";
	data->img[REPULSO_ICN].path = "./texture/spell/repulso_icn.xpm";
	data->img[STUPEFIX_ICN].path = "./texture/spell/stupefix_icn.xpm";
	data->img[OPPUGNO_ICN].path = "./texture/spell/oppugno_icn.xpm";
	data->img[SECTUMSEMPRA_ICN].path = "./texture/spell/sectumsempra_icn.xpm";
	data->img[SERPENSORTIA_ICN].path = "./texture/spell/serpensortia_icn.xpm";
	data->img[VENTUS_ICN].path = "./texture/spell/ventus_icn.xpm";
	data->img[VIPERA_EVANESCA_ICN].path = "./texture/spell/vipera_evanesca_icn.xpm";
	data->img[VULNERA_SANENTUR_ICN].path = "./texture/spell/vulnera_sanentur_icn.xpm";


	data->img[LUMOS_NAME].path = "./texture/menu/lumos_name.xpm";
	data->img[INCENDIO_NAME].path = "./texture/menu/incendio_name.xpm";
	data->img[GLACIUS_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[AVADA_KEDAVRA_NAME].path = "./texture/menu/avada_kedavra_name.xpm";
	data->img[PETRIFICUS_TOTALUS_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[PROTEGO_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[BOMBARDA_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[CONFUNDO_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[ENDOLORIS_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[EPISKEY_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[EXPECTO_PATRONUM_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[EXPELLIARMUS_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[REPULSO_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[STUPEFIX_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[OPPUGNO_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[SECTUMSEMPRA_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[SERPENSORTIA_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[VENTUS_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[VIPERA_EVANESCA_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[VULNERA_SANENTUR_NAME].path = "./texture/menu/glacius_name.xpm";
	data->img[ARANIA_EXUMAI_NAME].path = "./texture/menu/arania_exumai_name.xpm";
	data->img[AGUAMENTI_NAME].path = "./texture/menu/aguamenti_name.xpm";

	data->img[SPACE].path = "./texture/Letters/space.xpm";
	data->img[CHAR_A].path = "./texture/Letters/A.xpm";
	data->img[CHAR_B].path = "./texture/Letters/B.xpm";
	data->img[CHAR_C].path = "./texture/Letters/C.xpm";
	data->img[CHAR_D].path = "./texture/Letters/D.xpm";
	data->img[CHAR_E].path = "./texture/Letters/E.xpm";
	data->img[CHAR_F].path = "./texture/Letters/F.xpm";
	data->img[CHAR_G].path = "./texture/Letters/G.xpm";
	data->img[CHAR_H].path = "./texture/Letters/H.xpm";
	data->img[CHAR_I].path = "./texture/Letters/I.xpm";
	data->img[CHAR_J].path = "./texture/Letters/J.xpm";
	data->img[CHAR_K].path = "./texture/Letters/K.xpm";
	data->img[CHAR_L].path = "./texture/Letters/L.xpm";
	data->img[CHAR_M].path = "./texture/Letters/M.xpm";
	data->img[CHAR_N].path = "./texture/Letters/N.xpm";
	data->img[CHAR_O].path = "./texture/Letters/O.xpm";
	data->img[CHAR_P].path = "./texture/Letters/P.xpm";
	data->img[CHAR_Q].path = "./texture/Letters/Q.xpm";
	data->img[CHAR_R].path = "./texture/Letters/R.xpm";
	data->img[CHAR_S].path = "./texture/Letters/S.xpm";
	data->img[CHAR_T].path = "./texture/Letters/T.xpm";
	data->img[CHAR_U].path = "./texture/Letters/U.xpm";
	data->img[CHAR_V].path = "./texture/Letters/V.xpm";
	data->img[CHAR_W].path = "./texture/Letters/W.xpm";
	data->img[CHAR_X].path = "./texture/Letters/X.xpm";
	data->img[CHAR_Y].path = "./texture/Letters/Y.xpm";
	data->img[CHAR_Z].path = "./texture/Letters/Z.xpm";
	data->img[NB_0].path = "./texture/Numbers/0.xpm";
	data->img[NB_1].path = "./texture/Numbers/1.xpm";
	data->img[NB_2].path = "./texture/Numbers/2.xpm";
	data->img[NB_3].path = "./texture/Numbers/3.xpm";
	data->img[NB_4].path = "./texture/Numbers/4.xpm";
	data->img[NB_5].path = "./texture/Numbers/5.xpm";
	data->img[NB_6].path = "./texture/Numbers/6.xpm";
	data->img[NB_7].path = "./texture/Numbers/7.xpm";
	data->img[NB_8].path = "./texture/Numbers/8.xpm";
	data->img[NB_9].path = "./texture/Numbers/9.xpm";
}

void	init_textures(t_data *data)
{
	int	i;

	set_path_texture(data);
	i = 0;
	while (i < NB_TEXTURES)
	{
		data->img[i].img = mlx_xpm_file_to_image(data->mlx.mlx,
				data->img[i].path, &data->img[i].width,
				&data->img[i].height);
		if (!data->img[i].img)
		{
			ft_printf_fd(2, _BOLD _PURPLE "Image >>> '"
			_RED _ITALIC "%s"_END _PURPLE _BOLD "' is not a valid path\n"_END,
			data->img[i].path);
			while (--i >= 0)
			{
				mlx_destroy_image(data->mlx.mlx, data->img[i].img);
				data->img[i].img = NULL;
			}
			f_exit(data, 1);
		}
		data->img[i].data_addr = mlx_get_data_addr(data->img[i].img,
				&data->img[i].bits_per_pixel, &data->img[i].size_line,
				&data->img[i].endian);
		++i;
	}
}

// static void	init_texture(t_data *data)
// {
	// data->map.text_floor = malloc(sizeof(t_img));
	// if (!data->map.text_floor)
	// 	f_exit(data, 1);
	// ft_bzero(data->map.text_floor, sizeof(t_img));
	// data->map.text_floor->mlx = data->mlx.mlx;
	// data->map.text_floor->path = "./texture/wall4k.xpm";
	// data->map.text_sky = malloc(sizeof(t_img));
	// if (!data->map.text_sky)
	// 	f_exit(data, 1);
	// ft_bzero(data->map.text_sky, sizeof(t_img));
	// data->map.text_sky->mlx = data->mlx.mlx;
	// data->map.text_sky->path = "./texture/sky.xpm";
	// data->map.door = malloc(sizeof(t_img));
	// if (!data->map.door)
	// 	f_exit(data, 1);
	// ft_bzero(data->map.door, sizeof(t_img));
	// data->map.door->mlx = data->mlx.mlx;
	// data->map.door->path = "./texture/door_close.xpm";


	// data->map.floo = malloc(sizeof(t_img));
	// if (!data->map.floo)
	// 	f_exit(data, 1);
	// ft_bzero(data->map.floo, sizeof(t_img));
	// data->map.floo->mlx = data->mlx.mlx;
	// data->map.floo->path = "./texture/floo_close.xpm";

	// data->map.floo_open = malloc(sizeof(t_img));
	// if (!data->map.floo_open)
	// 	f_exit(data, 1);
	// ft_bzero(data->map.floo_open, sizeof(t_img));
	// data->map.floo_open->mlx = data->mlx.mlx;
	// data->map.floo_open->path = "./texture/floo_open.xpm";

	// data->map.dementor_front = malloc(sizeof(t_img));
	// if (!data->map.dementor_front)
	// 	f_exit(data, 1);
	// ft_bzero(data->map.dementor_front, sizeof(t_img));
	// data->map.dementor_front->mlx = data->mlx.mlx;
	// data->map.dementor_front->path = "./texture/dementor_front.xpm";

	// data->map.dementor_back = malloc(sizeof(t_img));
	// if (!data->map.dementor_back)
	// 	f_exit(data, 1);
	// ft_bzero(data->map.dementor_back, sizeof(t_img));
	// data->map.dementor_back->mlx = data->mlx.mlx;
	// data->map.dementor_back->path = "./texture/dementor_back.xpm";

	// data->map.fixed_door = malloc(sizeof(t_img));
	// if (!data->map.fixed_door)
	// 	f_exit(data, 1);
	// ft_bzero(data->map.fixed_door, sizeof(t_img));
	// data->map.fixed_door->mlx = data->mlx.mlx;
	// data->map.fixed_door->path = "./texture/door_open.xpm";

	// data->player_hand = malloc(sizeof(t_img));
	// if (!data->player_hand)
	// 	f_exit(data, 1);
	// ft_bzero(data->player_hand, sizeof(t_img));
	// data->player_hand->mlx = data->mlx.mlx;
	// data->player_wand = malloc(sizeof(t_img));
	// if (!data->player_wand)
	// 	f_exit(data, 1);
	// ft_bzero(data->player_wand, sizeof(t_img));
	// data->player_wand->mlx = data->mlx.mlx;
	// data->player_wand->path = "./texture/player_hand/wand_sureau.xpm";
	// data->lumos.img = malloc(sizeof(t_img));
	// if (!data->lumos.img)
	// 	f_exit(data, 1);
	// ft_bzero(data->lumos.img, sizeof(t_img));
	// data->lumos.img->mlx = data->mlx.mlx;
	// data->lumos.img->path = "./texture/player_hand/lumos.xpm";
// }

void	init_pause_menu(t_data *data)
{
	data->pause_menu.background = malloc(sizeof(t_img));
	if (!data->pause_menu.background)
		f_exit(data, 1);
	ft_bzero(data->pause_menu.background, sizeof(t_img));
	data->pause_menu.background->mlx = data->mlx.mlx;
	data->pause_menu.background->path = "./texture/menu/pause_background.xpm";

	data->pause_menu.sensitivity = malloc(sizeof(t_img));
	if (!data->pause_menu.sensitivity)
		f_exit(data, 1);
	ft_bzero(data->pause_menu.sensitivity, sizeof(t_img));
	data->pause_menu.sensitivity->mlx = data->mlx.mlx;
	data->pause_menu.sensitivity->path = "./texture/menu/pause_sensitivity.xpm";

	data->pause_menu.resume = malloc(sizeof(t_img));
	if (!data->pause_menu.resume)
		f_exit(data, 1);
	ft_bzero(data->pause_menu.resume, sizeof(t_img));
	data->pause_menu.resume->mlx = data->mlx.mlx;
	data->pause_menu.resume->path = "./texture/menu/resume_button.xpm";

	data->pause_menu.exit = malloc(sizeof(t_img));
	if (!data->pause_menu.exit)
		f_exit(data, 1);
	ft_bzero(data->pause_menu.exit, sizeof(t_img));
	data->pause_menu.exit->mlx = data->mlx.mlx;
	data->pause_menu.exit->path = "./texture/menu/exit_button.xpm";

	data->pause_menu.selector = malloc(sizeof(t_img));
	if (!data->pause_menu.selector)
		f_exit(data, 1);
	ft_bzero(data->pause_menu.selector, sizeof(t_img));
	data->pause_menu.selector->mlx = data->mlx.mlx;
	data->pause_menu.selector->path = "./texture/menu/pause_selector.xpm";
}

void	init_spell_menu(t_data *data)
{
	data->spell_menu.background = malloc(sizeof(t_img));
	if (!data->spell_menu.background)
		f_exit(data, 1);
	ft_bzero(data->spell_menu.background, sizeof(t_img));
	data->spell_menu.background->mlx = data->mlx.mlx;
	data->spell_menu.background->path = "./texture/menu/spell_background.xpm";
}
static void	fill_need_print(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < SIZE_MAP)
	{
		x = 0;
		while (x < SIZE_MAP)
		{
			if (sqrt(pow(y - SIZE_MAP / 2, 2) + pow(x - SIZE_MAP / 2,
						2)) > SIZE_MAP / 2)
				data->map.mini.need_print[y][x] = 0;
			else
				data->map.mini.need_print[y][x] = 1;
			x++;
		}
		y++;
	}
}

#include <stdio.h>

static void	init_ray(t_data *data)
{
	double	fov;
	int		i;

	fov = data->mlx.height / 2 * tan((45 * (M_PI / 180)));
	data->ray = malloc(sizeof(t_ray) * data->mlx.width);
	if (data->ray == NULL)
		f_exit(data, 1);
	ft_bzero(data->ray, sizeof(t_ray) * data->mlx.width);
	printf("width>>>%d\n",data->mlx.width);
	
	i = 0;
	// if (data->mlx.height < data->mlx.width)
		// fov *= (data->mlx.width / data->mlx.height);
	// else
	// 	fov /= (data->mlx.height / data->mlx.width) * 0.75;
	while (i < data->mlx.width)
	{
		data->ray[i].d_proj = fov;
		data->ray[i].pix_y = data->mlx.height >> 1;
		data->ray[i].max_height = data->mlx.height >> 1;
		++i;
	}
}

static void	init_coa(t_data *data)
{
	data->coa = malloc(sizeof(t_coa) * data->nb_coalition);
	if (data->coa == NULL)
		f_exit(data, 1); //error msg

	data->coa[FIRE].img_coa = malloc(sizeof(t_img));
	if (!data->coa[FIRE].img_coa)
		f_exit(data, 1);
	ft_bzero(data->coa[FIRE].img_coa, sizeof(t_img));
	data->coa[FIRE].border = malloc(sizeof(t_img));
	if (!data->coa[FIRE].border)
		f_exit(data, 1);
	ft_bzero(data->coa[FIRE].border, sizeof(t_img));
	data->coa[FIRE].img_coa->mlx = data->mlx.mlx;
	data->coa[FIRE].name = "Fire";
	data->coa[FIRE].color = FIRE_COLOR;
	data->coa[FIRE].img_coa->path = "texture/menu/fire.xpm";
	data->coa[FIRE].border->path = "texture/menu/border_fire.xpm";

	data->coa[WATER].img_coa = malloc(sizeof(t_img));
	if (!data->coa[WATER].img_coa)
		f_exit(data, 1);
	ft_bzero(data->coa[WATER].img_coa, sizeof(t_img));
	data->coa[WATER].border = malloc(sizeof(t_img));
	if (!data->coa[WATER].border)
		f_exit(data, 1);
	ft_bzero(data->coa[WATER].border, sizeof(t_img));
	data->coa[WATER].img_coa->mlx = data->mlx.mlx;
	data->coa[WATER].name = "Water";
	data->coa[WATER].color = WATER_COLOR;
	data->coa[WATER].img_coa->path = "texture/menu/water.xpm";
	data->coa[WATER].border->path = "texture/menu/border_water.xpm";

	data->coa[EARTH].img_coa = malloc(sizeof(t_img));
	if (!data->coa[EARTH].img_coa)
		f_exit(data, 1);
	ft_bzero(data->coa[EARTH].img_coa, sizeof(t_img));
	data->coa[EARTH].border = malloc(sizeof(t_img));
	if (!data->coa[EARTH].border)
		f_exit(data, 1);
	ft_bzero(data->coa[EARTH].border, sizeof(t_img));
	data->coa[EARTH].img_coa->mlx = data->mlx.mlx;
	data->coa[EARTH].name = "Earth";
	data->coa[EARTH].color = EARTH_COLOR;
	data->coa[EARTH].img_coa->path = "texture/menu/earth.xpm";
	data->coa[EARTH].border->path = "texture/menu/border_earth.xpm";

	data->coa[AIR].img_coa = malloc(sizeof(t_img));
	if (!data->coa[AIR].img_coa)
		f_exit(data, 1);
	ft_bzero(data->coa[AIR].img_coa, sizeof(t_img));
	data->coa[AIR].border = malloc(sizeof(t_img));
	if (!data->coa[AIR].border)
		f_exit(data, 1);
	ft_bzero(data->coa[AIR].border, sizeof(t_img));
	data->coa[AIR].img_coa->mlx = data->mlx.mlx;
	data->coa[AIR].name = "Air";
	data->coa[AIR].color = AIR_COLOR;
	data->coa[AIR].img_coa->path = "texture/menu/air.xpm";
	data->coa[AIR].border->path = "texture/menu/border_air.xpm";

	data->selected = 0;

	// data->select = malloc(sizeof(t_img));
	// if (!data->select)
	// 	f_exit(data, 1);
	// ft_bzero(data->select, sizeof(t_img));
	// data->select->mlx = data->mlx.mlx;
	// data->select->path = "texture/menu/select.xpm";

	// data->left_select = malloc(sizeof(t_img));
	// if (!data->left_select)
	// 	f_exit(data, 1);
	// ft_bzero(data->left_select, sizeof(t_img));
	// data->left_select->mlx = data->mlx.mlx;
	// data->left_select->path = "texture/menu/left_select.xpm";

	// data->select_hand = malloc(sizeof(t_img));
	// if (!data->select_hand)
	// 	f_exit(data, 1);
	// ft_bzero(data->select_hand, sizeof(t_img));
	// data->select_hand->mlx = data->mlx.mlx;
	// data->select_hand->path = "texture/menu/select_hand.xpm";
}

void	init_img_msg(t_data *data)
{
	data->map.msg_img = malloc(sizeof(t_img **) * (data->nb_msg));
	if (!data->map.msg_img)
		f_exit(data, 1);
	data->map.msg_img[0] = malloc(sizeof(t_img));
	if (!data->map.msg_img[0])
		f_exit(data, 1);
	ft_bzero(data->map.msg_img[0], sizeof(t_img));
	data->map.msg_img[0]->mlx = data->mlx.mlx;
	data->map.msg_img[0]->path = "texture/first_msg.xpm";
	data->map.msg_img[1] = malloc(sizeof(t_img));
	if (!data->map.msg_img[1])
		f_exit(data, 1);
	ft_bzero(data->map.msg_img[1], sizeof(t_img));
	data->map.msg_img[1]->mlx = data->mlx.mlx;
	data->map.msg_img[1]->path = "texture/snd_msg.xpm";
	data->map.msg_img[2] = malloc(sizeof(t_img));
	if (!data->map.msg_img[2])
		f_exit(data, 1);
	ft_bzero(data->map.msg_img[2], sizeof(t_img));
	data->map.msg_img[2]->mlx = data->mlx.mlx;
	data->map.msg_img[2]->path = "texture/third_msg.xpm";
	data->map.msg_img[3] = malloc(sizeof(t_img));
	if (!data->map.msg_img[3])
		f_exit(data, 1);
	ft_bzero(data->map.msg_img[3], sizeof(t_img));
	data->map.msg_img[3]->mlx = data->mlx.mlx;
	if (data->color == FIRE_COLOR)
		data->map.msg_img[3]->path = "texture/fire_msg.xpm";
	else if (data->color == WATER_COLOR)
		data->map.msg_img[3]->path = "texture/water_msg.xpm";
	else if (data->color == EARTH_COLOR)
		data->map.msg_img[3]->path = "texture/earth_msg.xpm";
	else if (data->color == AIR_COLOR)
		data->map.msg_img[3]->path = "texture/air_msg.xpm";
	data->map.msg_img[4] = malloc(sizeof(t_img));
	if (!data->map.msg_img[4])
		f_exit(data, 1);
	ft_bzero(data->map.msg_img[4], sizeof(t_img));
	data->map.msg_img[4]->mlx = data->mlx.mlx;
	data->map.msg_img[4]->path = "texture/fourth_msg.xpm";
	data->map.msg_img[5] = malloc(sizeof(t_img));
	if (!data->map.msg_img[5])
		f_exit(data, 1);
	ft_bzero(data->map.msg_img[5], sizeof(t_img));
	data->map.msg_img[5]->mlx = data->mlx.mlx;
	data->map.msg_img[5]->path = "texture/five_msg.xpm";

	data->map.msg_img[6] = malloc(sizeof(t_img));
	if (!data->map.msg_img[6])
		f_exit(data, 1);
	ft_bzero(data->map.msg_img[6], sizeof(t_img));
	data->map.msg_img[6]->mlx = data->mlx.mlx;
	data->map.msg_img[6]->path = "texture/six_msg.xpm";
	open_img_msg(data);
}

void	init_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->time_fps = get_mtime();
	data->time_move = get_mtime();
	fill_need_print(data);
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		// error msg
		f_exit(data, 1);
	}
	// mlx_get_screen_size(data->mlx.mlx, &data->mlx.width, &data->mlx.height);
	data->mlx.height = 1110;
	data->mlx.width = 1920;
	data->nb_coalition = 4;
	data->status = MENU;
	data->display.player_height = 16;
	init_utils_mini(data);
	init_ray(data);
	data->screen = malloc(sizeof(t_img));
	data->screen->img = mlx_new_image(data->mlx.mlx, data->mlx.width,
			data->mlx.height);
	data->screen->data_addr = mlx_get_data_addr(data->screen->img,
			&data->screen->bits_per_pixel, &data->screen->size_line,
			&data->screen->endian);
	data->screen->width = data->mlx.width;
	data->screen->height = data->mlx.height;
	data->ac = ac;
	data->av = av;
	data->lumos.x_wand = 0;
	data->lumos.y_wand = 0;
	data->lumos.count_frame = 0;
	data->lumos.active = false;
	// init_texture(data);
	init_textures(data);
	init_coa(data);
	init_pause_menu(data);
	init_spell_menu(data);
	data->nb_msg = 7;
	data->display.time_remove = 10000;
	data->display.elapsed_time = 0;
	data->current_msg = 0;
	data->display.is_msg_active = true;
	data->display.is_first_msg = true;
	data->sensitivity = 60;
	data->pause_menu.selected = 0;
	data->pause_menu.elapsed = 0;

	data->player.life = 50;
	data->player.shield = 10;
	data->player.xp = 5.868486;
	data->player.damage.damage_do = 1;

	data->map.zoom = 128;
	data->map.last_mouse_x = 960;
	data->map.last_mouse_y = 555;
	data->map.is_center = false;
	data->map.pos_active_floo = init_t_coo(0, 0);
	set_spell_take(data);
	init_spell(data);
}
