/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:45:47 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:45:48 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ft_printf.h"
#include "mlx.h"
#include "struct.h"
#include "utils.h"

static void	open_img(t_img *img, t_data *data)
{
	if (!img)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_END);
		ft_printf_fd(2, _BOLD _PURPLE
			"Image >>> Missing an identifiers !!\n"_END);
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
	if (!data->map.ceiling || !data->map.floor)
	{
		ft_printf_fd(2, _RED _BOLD "Error\n"_PURPLE
			"Texture >>> " "color not found !!\n"_END);
		f_exit(data, 1);
	}
}
