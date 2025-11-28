#include <stdlib.h>
#include "struct_bonus.h"
#include "mlx.h"
#include "cub3d_bonus.h"

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
	while (++i <= 5 && data->map.mini.img[i].img)
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

void	f_exit(t_data *data, int code)
{
	f_all_lst(data->sound);
	if (data->mlx.mlx)
		mlx_do_key_autorepeaton(data->mlx.mlx);
	f_imgs(data);
	f_all_lst(data->enemy);

	free(data->map.door_map);
	free(data->map.wall_map);

	f_all_lst(data->map.map);
	f_all_lst(data->map.lines);
	f_all_lst(data->door);
	f_all_lst(data->item);
	f_tab_char(data->map.tabmap);
	if (data->u.mmap.img)
		mlx_destroy_image(data->mlx.mlx, data->u.mmap.img);
	if (data->screen)
		mlx_destroy_image(data->mlx.mlx, data->screen->img);
	free(data->screen);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	free(data->ray);
	exit(code);
}
