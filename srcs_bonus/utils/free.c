#include "cub3d_bonus.h"
#include "mlx.h"
#include "struct_bonus.h"
#include "utils_bonus.h"
#include <stdlib.h>

void	f_elem(void *elem)
{
	free(elem);
}

void	f_img(t_img *img)
{
	if (!img)
		return ;
	if (img->img)
		mlx_destroy_image(img->mlx, img->img);
	free(img->path);
	free(img);
}

void	f_imgs(t_data *data)
{
	int	i;

	f_img(data->map.north);
	f_img(data->map.south);
	f_img(data->map.west);
	f_img(data->map.east);
	f_img(data->map.floor);
	f_img(data->map.ceiling);
	i = -1;
	while (++i <= 13 && data->map.mini.img[i].img)
		mlx_destroy_image(data->mlx.mlx, data->map.mini.img[i].img);
	i = -1;
	while (++i < NB_TEXTURES)
		mlx_destroy_image(data->mlx.mlx, data->img[i].img);
	data->img[i].img = NULL;
}

void	f_tab_char(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_door_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.door_map && data->map.door_map[i])
	{
		free(data->map.door_map[i]);
		++i;
	}
	free(data->map.door_map);
}

void	free_wall_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.tabmap && data->map.tabmap[y])
	{
		x = 0;
		while (data->map.tabmap[y][x])
		{
			free(data->map.wall_map[y][x]);
			++x;
		}
		free(data->map.wall_map[y]);
		++y;
	}
	free(data->map.wall_map);
}


