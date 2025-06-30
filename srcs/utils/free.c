#include <stdlib.h>
#include "struct.h"
#include "mlx.h"

void	f_elem(void *elem)
{
	free(elem);
}

void	f_texture(t_img *img)
{
	if (!img)
		return ;
	if (img->img)
		mlx_destroy_image(img->mlx, img->img);
	free(img->path);
	free(img);
}

void	f_textures(t_data *data)
{
	f_texture(data->map.north);
	f_texture(data->map.south);
	f_texture(data->map.west);
	f_texture(data->map.east);
	free(data->map.floor);
	free(data->map.ceiling);
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
	(void)data;
	f_textures(data);
	f_all_lst(data->map.map);
	f_all_lst(data->map.lines);
	f_tab_char(data->map.tabmap);
	free(data->map.player_start);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	exit(code);
}
