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

	// open_img(data->map.text_floor, data);
	// open_img(data->map.text_sky, data);
	open_img(data->map.door, data);
	open_img(data->map.fixed_door, data);
	open_img(data->coa[0].img_coa, data);
	open_img(data->coa[1].img_coa, data);
	open_img(data->coa[2].img_coa, data);
	open_img(data->coa[3].img_coa, data);
	open_img(data->coa[0].border, data);
	open_img(data->coa[1].border, data);
	open_img(data->coa[2].border, data);
	open_img(data->coa[3].border, data);
	open_img(data->left_select, data);
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
	int				x;
	int				y;
	char			*pixel_addr;
	
	y = 0;
	if (data->is_right_handed == true)
		data->player_hand->path = "./texture/player_hand/right_hand.xpm";
	else
		data->player_hand->path = "./texture/player_hand/left_hand.xpm";
	open_img(data->player_hand, data);
	while (y < data->player_hand->height)
	{
		x = 0;
		while (x < data->player_hand->width)
		{
			pixel_addr = data->player_hand->data_addr + (y * data->player_hand->size_line + x
				* (data->player_hand->bits_per_pixel / 8));
			if (*(unsigned int *)pixel_addr == YELLOW)
				*(unsigned int *)pixel_addr = data->color;
			++x;
		}
		++y;
	}
}
