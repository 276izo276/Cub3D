#include "cub3d_bonus.h"
#include "mlx.h"
#include "texture_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "time_bonus.h"
#include <color_bonus.h>

static void	init_texture(t_data *data)
{
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
	data->map.door = malloc(sizeof(t_img));
	if (!data->map.door)
		f_exit(data, 1);
	ft_bzero(data->map.door, sizeof(t_img));
	data->map.door->mlx = data->mlx.mlx;
	data->map.door->path = "./texture/door_close.xpm";


	data->map.dementor = malloc(sizeof(t_img));
	if (!data->map.dementor)
		f_exit(data, 1);
	ft_bzero(data->map.dementor, sizeof(t_img));
	data->map.dementor->mlx = data->mlx.mlx;
	data->map.dementor->path = "./texture/dementor.xpm";

	data->map.fixed_door = malloc(sizeof(t_img));
	if (!data->map.fixed_door)
		f_exit(data, 1);
	ft_bzero(data->map.fixed_door, sizeof(t_img));
	data->map.fixed_door->mlx = data->mlx.mlx;
	data->map.fixed_door->path = "./texture/door_open.xpm";

	data->player_hand = malloc(sizeof(t_img));
	if (!data->player_hand)
		f_exit(data, 1);
	ft_bzero(data->player_hand, sizeof(t_img));
	data->player_hand->mlx = data->mlx.mlx;
	data->player_wand = malloc(sizeof(t_img));
	if (!data->player_wand)
		f_exit(data, 1);
	ft_bzero(data->player_wand, sizeof(t_img));
	data->player_wand->mlx = data->mlx.mlx;
	data->player_wand->path = "./texture/player_hand/wand_sureau.xpm";
	data->spell.lumos = malloc(sizeof(t_img));
	if (!data->spell.lumos)
		f_exit(data, 1);
	ft_bzero(data->spell.lumos, sizeof(t_img));
	data->spell.lumos->mlx = data->mlx.mlx;
	data->spell.lumos->path = "./texture/player_hand/lumos.xpm";
}

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

	data->coa[0].img_coa = malloc(sizeof(t_img));
	if (!data->coa[0].img_coa)
		f_exit(data, 1);
	ft_bzero(data->coa[0].img_coa, sizeof(t_img));
	data->coa[0].border = malloc(sizeof(t_img));
	if (!data->coa[0].border)
		f_exit(data, 1);
	ft_bzero(data->coa[0].border, sizeof(t_img));
	data->coa[0].img_coa->mlx = data->mlx.mlx;
	data->coa[0].name = "Fire";
	data->coa[0].color = FIRE_COLOR;
	data->coa[0].img_coa->path = "texture/menu/fire.xpm";
	data->coa[0].border->path = "texture/menu/border_fire.xpm";

	data->coa[1].img_coa = malloc(sizeof(t_img));
	if (!data->coa[1].img_coa)
		f_exit(data, 1);
	ft_bzero(data->coa[1].img_coa, sizeof(t_img));
	data->coa[1].border = malloc(sizeof(t_img));
	if (!data->coa[1].border)
		f_exit(data, 1);
	ft_bzero(data->coa[1].border, sizeof(t_img));
	data->coa[1].img_coa->mlx = data->mlx.mlx;
	data->coa[1].name = "Water";
	data->coa[1].color = WATER_COLOR;
	data->coa[1].img_coa->path = "texture/menu/water.xpm";
	data->coa[1].border->path = "texture/menu/border_water.xpm";

	data->coa[2].img_coa = malloc(sizeof(t_img));
	if (!data->coa[2].img_coa)
		f_exit(data, 1);
	ft_bzero(data->coa[2].img_coa, sizeof(t_img));
	data->coa[2].border = malloc(sizeof(t_img));
	if (!data->coa[2].border)
		f_exit(data, 1);
	ft_bzero(data->coa[2].border, sizeof(t_img));
	data->coa[2].img_coa->mlx = data->mlx.mlx;
	data->coa[2].name = "Earth";
	data->coa[2].color = EARTH_COLOR;
	data->coa[2].img_coa->path = "texture/menu/earth.xpm";
	data->coa[2].border->path = "texture/menu/border_earth.xpm";

	data->coa[3].img_coa = malloc(sizeof(t_img));
	if (!data->coa[3].img_coa)
		f_exit(data, 1);
	ft_bzero(data->coa[3].img_coa, sizeof(t_img));
	data->coa[3].border = malloc(sizeof(t_img));
	if (!data->coa[3].border)
		f_exit(data, 1);
	ft_bzero(data->coa[3].border, sizeof(t_img));
	data->coa[3].img_coa->mlx = data->mlx.mlx;
	data->coa[3].name = "Air";
	data->coa[3].color = AIR_COLOR;
	data->coa[3].img_coa->path = "texture/menu/air.xpm";
	data->coa[3].border->path = "texture/menu/border_air.xpm";

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
	data->spell.x_wand = 0;
	data->spell.y_wand = 0;
	data->spell.count_frame = 0;
	data->spell.active = false;
	init_coa(data);
	init_texture(data);
	init_pause_menu(data);
	data->nb_msg = 7;
	data->display.time_remove = 10000;
	data->display.elapsed_time = 0;
	data->current_msg = 0;
	data->display.is_msg_active = true;
	data->display.is_first_msg = true;
	data->sensitivity = 60;
	data->pause_menu.selected = 0;
	data->pause_menu.elapsed = 0;
}
