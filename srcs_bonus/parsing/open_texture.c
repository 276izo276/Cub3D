#include "color_bonus.h"
#include "ft_printf.h"
#include "mlx.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"

static void	open_img(t_img *img, t_data *data)
{
	if (!img)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_END);
		ft_printf_fd(2, _BOLD _PURPLE "Image >>> Missing an identifiers !!\n"_END);
		f_exit(data, 1);
	}
	img->img = mlx_xpm_file_to_image(data->mlx.mlx, img->path, &img->width,
		&img->height);
	if (!img->img)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_END);
		ft_printf_fd(2, _BOLD _PURPLE "Image >>> '"
			_RED _ITALIC "%s"_END _PURPLE _BOLD "' is not a valid path\n"_END,
			img->path);
		f_exit(data, 1);
	}
	img->data_addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->size_line, &img->endian);
}

void	open_textures(t_data *data)
{
	open_img(data->map.north, data);
	open_img(data->map.south, data);
	open_img(data->map.west, data);
	open_img(data->map.east, data);

	open_img(data->map.floor, data);
	open_img(data->map.ceiling, data);
	open_img(data->map.dementor_front, data);
	open_img(data->map.dementor_back, data);

	// open_img(data->map.text_floor, data);
	// open_img(data->map.text_sky, data);
	open_img(data->map.door, data);
	open_img(data->map.fixed_door, data);
	open_img(data->coa[FIRE].img_coa, data);
	open_img(data->coa[WATER].img_coa, data);
	open_img(data->coa[EARTH].img_coa, data);
	open_img(data->coa[AIR].img_coa, data);
	open_img(data->coa[FIRE].border, data);
	open_img(data->coa[WATER].border, data);
	open_img(data->coa[EARTH].border, data);
	open_img(data->coa[AIR].border, data);
	// open_img(data->left_select, data);
	// open_img(data->select, data);


	// open_img(data->select_hand, data);
	// open_img(data->player_wand, data);
	open_img(data->spell.lumos, data);
	


	open_img(data->pause_menu.background, data);
	open_img(data->pause_menu.sensitivity, data);
	open_img(data->pause_menu.exit, data);
	open_img(data->pause_menu.resume, data);
	open_img(data->pause_menu.selector, data);

	if (!data->map.ceiling || !data->map.floor)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Texture >>> " "color not found !!\n"_END);
		f_exit(data, 1);
	}
}

void	open_img_msg(t_data *data)
{
	int i = 0;
	while (i < 7)
	{
		open_img(data->map.msg_img[i], data);
		++i;
	}
}

void select_right_hand(t_data *data)
{
	int				x;
	int				y;
	char			*pixel_addr;
	
	y = 0;
	if (data->is_right_handed == true)
		data->img[PLAYER_HAND].path = "./texture/player_hand/right_hand.xpm";
	else
		data->img[PLAYER_HAND].path = "./texture/player_hand/left_hand.xpm";
	open_img(&data->img[PLAYER_HAND], data);
	if (data->is_right_handed == true) // hand_pos
	{
		data->display.pos_x_hand = (data->mlx.width / 2) + data->img[PLAYER_HAND].width / 4 - 100;
		data->display.pos_y_hand = (data->mlx.height - data->img[PLAYER_HAND].height - 100);
	}
	else
	{
		data->display.pos_x_hand = (data->mlx.width / 2) - data->img[PLAYER_HAND].width / 4 - 150;
		data->display.pos_y_hand = (data->mlx.height - data->img[PLAYER_HAND].height - 100);
	}
	while (y < data->img[PLAYER_HAND].height)
	{
		x = 0;
		while (x < data->img[PLAYER_HAND].width)
		{
			pixel_addr = data->img[PLAYER_HAND].data_addr + (y * data->img[PLAYER_HAND].size_line + x
				* (data->img[PLAYER_HAND].bits_per_pixel / 8));
			if (*(unsigned int *)pixel_addr == YELLOW)
				*(unsigned int *)pixel_addr = data->color;
			++x;
		}
		++y;
	}
}
