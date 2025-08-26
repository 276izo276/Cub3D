#include "color_bonus.h"
#include "ft_printf.h"
#include "mlx.h"
#include "struct_bonus.h"
#include "utils_bonus.h"

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

	// open_img(data->map.text_floor, data);
	// open_img(data->map.text_sky, data);
	open_img(data->map.door, data);
	open_img(data->coa[0].img_coa, data);
	open_img(data->coa[1].img_coa, data);
	open_img(data->coa[2].img_coa, data);
	open_img(data->coa[3].img_coa, data);
	open_img(data->select, data);
	open_img(data->select_hand, data);
	open_img(data->player_wand, data);
	open_img(data->spell.lumos, data);
	if (!data->map.ceiling || !data->map.floor)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Texture >>> " "color not found !!\n"_END);
		f_exit(data, 1);
	}
}

void select_right_hand(t_data *data)
{
	if (data->color == FIRE_COLOR && data->is_right_handed == true)
		data->player_hand->path = "./texture/player_hand/red_right_hand.xpm";
	else if (data->color == FIRE_COLOR)
		data->player_hand->path = "./texture/player_hand/red_left_hand.xpm";
	else if (data->color == EARTH_COLOR && data->is_right_handed == true)
		data->player_hand->path = "./texture/player_hand/green_right_hand.xpm";
	else if (data->color == EARTH_COLOR)
		data->player_hand->path = "./texture/player_hand/green_left_hand.xpm";
	else if (data->color == WATER_COLOR && data->is_right_handed == true)
		data->player_hand->path = "./texture/player_hand/blue_right_hand.xpm";
	else if (data->color == WATER_COLOR)
		data->player_hand->path = "./texture/player_hand/blue_left_hand.xpm";
	else if (data->color == AIR_COLOR && data->is_right_handed == true)
		data->player_hand->path = "./texture/player_hand/white_right_hand.xpm";
	else if (data->color == AIR_COLOR)
		data->player_hand->path = "./texture/player_hand/white_left_hand.xpm";
	open_img(data->player_hand, data);
}
