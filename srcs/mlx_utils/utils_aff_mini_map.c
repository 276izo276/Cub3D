#include "cub3d.h"
#include "ft_printf.h"
#include "math.h"
#include "mlx.h"
#include "struct.h"
#include "utils.h"

void	get_pixel_color(t_utils_mini *u, int type)
{
	if (u->data->map.mini.need_print[u->s.y + u->i.y][u->s.x + u->i.x] == 0)
	{
		u->color = 0x00000000;
	}
	else
	{
		u->color = *(unsigned int *)(u->data->map.mini.img[type].data_addr
				+ ((u->i.y) * u->data->map.mini.img[type].size_line + (u->i.x)
					* (u->data->map.mini.img[type].bits_per_pixel / 8)));
	}
}

void	init_utils_mini(t_utils_mini *u, t_data *data)
{
	ft_bzero(u, sizeof(t_utils_mini));
	u->data = data;
	u->size = 5 * 64;
	u->mmap = malloc(sizeof(t_img));
	u->mmap->img = mlx_new_image(data->mlx.mlx, u->size, u->size);
	u->mmap->data_addr = mlx_get_data_addr(u->mmap->img,
			&u->mmap->bits_per_pixel, &u->mmap->size_line, &u->mmap->endian);
	u->y = -4;
}

void	print_mini_map(t_utils_mini *u)
{
	mlx_put_image_to_window(u->data->mlx.mlx, u->data->mlx.win, u->mmap->img, 0,
		u->data->mlx.height - MARGIN - u->size);
	mlx_destroy_image(u->data->mlx.mlx, u->mmap->img);
	free(u->mmap);
}
