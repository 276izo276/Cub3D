#include <stdlib.h>
#include "struct_bonus.h"
#include "mlx.h"

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
	// if (data->map.text_sky->img)
	// 	mlx_destroy_image(data->mlx.mlx, data->map.text_sky->img);
	// if (data->map.text_floor->img)
	// 	mlx_destroy_image(data->mlx.mlx, data->map.text_floor->img);
	// free(data->map.text_sky);
	// free(data->map.text_floor);
	// free(data->map.floor);
	// free(data->map.ceiling);
	i = -1;
	while (++i <= 5 && data->map.mini.img[i].img)
		mlx_destroy_image(data->mlx.mlx, data->map.mini.img[i].img);
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


#include <stdio.h>

void	f_exit(t_data *data, int code)
{
	if (data->mlx.mlx)
		mlx_do_key_autorepeaton(data->mlx.mlx);
	f_imgs(data);
	f_all_lst(data->map.map);
	f_all_lst(data->map.lines);
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
