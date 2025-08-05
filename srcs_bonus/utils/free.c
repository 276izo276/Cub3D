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
	free(data->map.floor);
	free(data->map.ceiling);
	i = -1;
	while (++i < 5)
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

void	f_exit(t_data *data, int code)
{
	if (data->mlx.mlx)
		mlx_do_key_autorepeaton(data->mlx.mlx);
	f_imgs(data);
	f_all_lst(data->map.map);
	f_all_lst(data->map.lines);
	f_tab_char(data->map.tabmap);
	free(data->map.player_coo);
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	exit(code);
}
