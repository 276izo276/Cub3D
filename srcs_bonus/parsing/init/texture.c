#include "parsing_bonus.h"
#include <color_bonus.h>
#include "utils_bonus.h"
#include "mlx.h"
#include "ft_printf.h"

static void	set_path_texture(t_data *data)
{
	set_path_player_spell(data);
	set_path_char_texture(data);
	set_path_enemy_texture(data);
	set_path_others_texture(data);
}

static void	print_err(t_data *data, int i)
{
	ft_printf_fd(2, _BOLD _PURPLE "Image >>> '"
		_RED _ITALIC "%s"_END _PURPLE _BOLD "' is not a valid path\n"_END,
		data->img[i].path);
}

void	init_textures(t_data *data)
{
	int	i;

	set_path_texture(data);
	i = -1;
	while (++i < NB_TEXTURES)
	{
		data->img[i].img = mlx_xpm_file_to_image(data->mlx.mlx,
				data->img[i].path, &data->img[i].width,
				&data->img[i].height);
		if (!data->img[i].img)
		{
			print_err(data, i);
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
	}
}

