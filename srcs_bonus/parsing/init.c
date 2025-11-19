#include "cub3d_bonus.h"
#include "mlx.h"
#include "texture_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "time_bonus.h"
#include <color_bonus.h>
#include "ft_printf.h"
#include "parsing_bonus.h"

static void	set_path_texture(t_data *data)
{
	set_path_player_spell(data);
	set_path_char_texture(data);
	set_path_enemy_texture(data);
	set_path_others_texture(data);
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

// void	init_textures_wand(t_data *data)
// {
// 	int	i;

// 	set_path_wand(data);
// 	i = 0;
// 	while (i < NB_WAND)
// 	{
// 		data->wand.img[i].img = mlx_xpm_file_to_image(data->mlx.mlx,
// 				data->wand.img[i].path, &data->wand.img[i].width,
// 				&data->wand.img[i].height);
// 		if (!data->wand.img[i].img)
// 		{
// 			ft_printf_fd(2, _BOLD _PURPLE "Image >>> '"
// 			_RED _ITALIC "%s"_END _PURPLE _BOLD "' is not a valid path\n"_END,
// 			data->wand.img[i].path);
// 			while (--i >= 0)
// 			{
// 				mlx_destroy_image(data->mlx.mlx, data->wand.img[i].img);
// 				data->wand.img[i].img = NULL;
// 			}
// 			f_exit(data, 1);
// 		}
// 		data->wand.img[i].data_addr = mlx_get_data_addr(data->wand.img[i].img,
// 				&data->wand.img[i].bits_per_pixel, &data->wand.img[i].size_line,
// 				&data->wand.img[i].endian);
// 		++i;
// 	}
// }

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
	int	i;

	i = 0;
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
	while (i < 4)
	{
		data->coa[i].xp = 1.0;
		data->coa[i].max_y = 0;
		++i;
	}
	data->selected = 0;
	data->select = malloc(sizeof(t_img));
	if (!data->select)
		f_exit(data, 1);
	ft_bzero(data->select, sizeof(t_img));
	data->select->mlx = data->mlx.mlx;
	data->select->path = "texture/menu/select.xpm";

	data->left_select = malloc(sizeof(t_img));
	if (!data->left_select)
		f_exit(data, 1);
	ft_bzero(data->left_select, sizeof(t_img));
	data->left_select->mlx = data->mlx.mlx;
	data->left_select->path = "texture/menu/left_select.xpm";

	data->select_hand = malloc(sizeof(t_img));
	if (!data->select_hand)
		f_exit(data, 1);
	ft_bzero(data->select_hand, sizeof(t_img));
	data->select_hand->mlx = data->mlx.mlx;
	data->select_hand->path = "texture/menu/select_hand.xpm";
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
	if (data->player.color == FIRE_COLOR)
		data->map.msg_img[3]->path = "texture/fire_msg.xpm";
	else if (data->player.color == WATER_COLOR)
		data->map.msg_img[3]->path = "texture/water_msg.xpm";
	else if (data->player.color == EARTH_COLOR)
		data->map.msg_img[3]->path = "texture/earth_msg.xpm";
	else if (data->player.color == AIR_COLOR)
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

void	init_sorcerer(t_data *data)
{
	int	i;

	i = 0;
	data->sorcerer[0].type = NANCY;
	data->sorcerer[0].color = WATER_COLOR;
	data->sorcerer[1].type = ZIPPY;
	data->sorcerer[1].color = FIRE_COLOR;
	data->sorcerer[2].type = KUNFANDI;
	data->sorcerer[2].color = AIR_COLOR;
	data->sorcerer[3].type = PILO;
	data->sorcerer[3].color = EARTH_COLOR;
	data->sorcerer[4].type = CAMEO;
	data->sorcerer[4].color = AIR_COLOR;
	data->sorcerer[5].type = ANAIS;
	data->sorcerer[5].color = AIR_COLOR;
	data->sorcerer[6].type = DIRLO;
	data->sorcerer[6].color = EARTH_COLOR;
	data->sorcerer[7].type = STEF;
	data->sorcerer[7].color = FIRE_COLOR;
	data->sorcerer[8].type = MARINA;
	data->sorcerer[8].color = EARTH_COLOR;
	while (i < 9)
	{
		data->sorcerer[i].is_alive = true;
		data->sorcerer[i].nb_spawn = 0;
		++i;
	}
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
	data->portkey_is_active = false;
	// init_texture(data);
	init_textures(data);
	init_coa(data);
	// init_pause_menu(data);
	// init_spell_menu(data);
	init_sorcerer(data);
	data->nb_msg = 7;
	data->display.time_remove = 10000;
	data->display.elapsed_time = 0;
	data->current_msg = 0;
	data->display.is_msg_active = true;
	data->display.is_first_msg = true;
	data->sensitivity = 100;
	data->pause_menu.selected = 0;
	data->pause_menu.elapsed = 0;

	data->player.life = 100;
	data->player.shield = 0;
	data->player.xp = 15.0;
	data->player.damage.damage_do = 1;
	data->player.invisible = 255;

	data->spawn_frame = 5000;
	data->last_spawn = get_mtime();
	data->map.zoom = 128;
	data->map.last_mouse_x = 960;
	data->map.last_mouse_y = 555;
	data->map.is_center = false;
	
	data->wand.secret_wand = "BAGUETTE";
	data->wand.secret_sword = "SWORD";
	int	i = 1;
	data->wand.wand_status[0] = true;
	data->wand.is_drop[0] = true;
	while (i < 6)
	{
		data->wand.wand_status[i] = false;
		data->wand.is_drop[i] = false;
		++i;
	}
	data->cheat_code_xp = "SAMAOUCH";
	data->cheat_code_life = "ALE-GUEL";
	data->wand.wand_status[5] = false;
	data->wand.wand_status[6] = false;
	data->map.pos_active_floo = init_t_coo(0, 0);
	set_spell_take(data);
	init_spell(data);
	init_item(data);
	init_popo(data);
}
