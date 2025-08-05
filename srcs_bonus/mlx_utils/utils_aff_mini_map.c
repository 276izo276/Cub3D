#include "cub3d.h"
#include "mlx.h"
#include "utils.h"

void	get_pixel_color(t_data *data, int type)
{
	if (data->map.mini.need_print[data->u.s.y + data->u.i.y][data->u.s.x
		+ data->u.i.x] == 0)
	{
		data->u.color = *(unsigned int *)(data->screen->data_addr
				+ (((data->mlx.height - MARGIN - data->u.size) + (data->u.s.y
							+ data->u.i.y)) * data->screen->size_line
					- (data->mlx.width - (data->u.s.x + data->u.i.x))
					* (data->screen->bits_per_pixel / 8)));
	}
	else
	{
		data->u.color = *(unsigned int *)(data->map.mini.img[type].data_addr
				+ ((data->u.i.y) * data->map.mini.img[type].size_line
					+ (data->u.i.x) * (data->map.mini.img[type].bits_per_pixel
						/ 8)));
	}
}

void	init_utils_mini(t_data *data)
{
	ft_bzero(&data->u, sizeof(t_utils_mini));
	data->u.size = 5 * 64;
	data->u.mmap.img = mlx_new_image(data->mlx.mlx, data->u.size, data->u.size);
	data->u.mmap.data_addr = mlx_get_data_addr(data->u.mmap.img,
			&data->u.mmap.bits_per_pixel, &data->u.mmap.size_line,
			&data->u.mmap.endian);
}

void	print_mini_map(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->u.mmap.img, 0,
		data->mlx.height - MARGIN - data->u.size);
}
