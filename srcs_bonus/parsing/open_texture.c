#include "color_bonus.h"
#include "ft_printf.h"
#include "mlx.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include "cub3d_bonus.h"

void	open_img(t_img *img, t_data *data)
{
	if (!img)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_END);
		ft_printf_fd(2, _BOLD _PURPLE
			"Image >>> Missing some informations!!\n"_END);
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
	if (!data->map.ceiling || !data->map.floor)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Texture >>> " "color not found !!\n"_END);
		f_exit(data, 1);
	}
}

static void	get_hand_pos(t_data *data)
{
	if (data->is_right_handed == true)
	{
		data->display.pos_x_hand = (data->mlx.width / 2)
			- data->img[PLAYER_HAND].width / 2 + 10;
		data->display.pos_y_hand = (data->mlx.height
				- data->img[PLAYER_HAND].height - 100);
	}
	else
	{
		data->display.pos_x_hand = (data->mlx.width / 2)
			- data->img[PLAYER_HAND].width / 2 - 10;
		data->display.pos_y_hand = (data->mlx.height
				- data->img[PLAYER_HAND].height - 100);
	}
}

void	select_right_hand(t_data *data)
{
	int				x;
	int				y;
	char			*pixel_addr;

	y = 0;
	// DESTROY L ANCIENNE TEXTURE DE PLAYER_HAND
	if (data->is_right_handed == true)
		data->img[PLAYER_HAND].path = "./texture/player_hand/right_hand.xpm";
	else
		data->img[PLAYER_HAND].path = "./texture/player_hand/left_hand.xpm";
	open_img(&data->img[PLAYER_HAND], data);
	get_hand_pos(data);
	while (y < data->img[PLAYER_HAND].height)
	{
		x = 0;
		while (x < data->img[PLAYER_HAND].width)
		{
			pixel_addr = data->img[PLAYER_HAND].data_addr
				+ (y * data->img[PLAYER_HAND].size_line + x
					* (data->img[PLAYER_HAND].bits_per_pixel / 8));
			if (*(unsigned int *)pixel_addr == YELLOW)
				*(unsigned int *)pixel_addr = data->player.color;
			++x;
		}
		++y;
	}
}
