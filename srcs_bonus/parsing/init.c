#include "cub3d_bonus.h"
#include "mlx.h"
#include "texture_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "time_bonus.h"

static void	init_texture(t_data *data)
{
	data->map.text_floor = malloc(sizeof(t_img));
	if (!data->map.text_floor)
		f_exit(data, 1);
	ft_bzero(data->map.text_floor, sizeof(t_img));
	data->map.text_floor->mlx = data->mlx.mlx;
	data->map.text_floor->path = "./texture/wall4k.xpm";
	data->map.text_sky = malloc(sizeof(t_img));
	if (!data->map.text_sky)
		f_exit(data, 1);
	ft_bzero(data->map.text_sky, sizeof(t_img));
	data->map.text_sky->mlx = data->mlx.mlx;
	data->map.text_sky->path = "./texture/sky.xpm";
	data->map.door = malloc(sizeof(t_img));
	if (!data->map.door)
		f_exit(data, 1);
	ft_bzero(data->map.door, sizeof(t_img));
	data->map.door->mlx = data->mlx.mlx;
	data->map.door->path = "./texture/door.xpm";
}

static void	fill_need_print(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < SIZE_MAP)
	{
		x = 0;
		while (x < SIZE_MAP)
		{
			if (sqrt(pow(y - SIZE_MAP / 2, 2) + pow(x - SIZE_MAP / 2,
						2)) > SIZE_MAP / 2)
				data->map.mini.need_print[y][x] = 0;
			else
				data->map.mini.need_print[y][x] = 1;
			x++;
		}
		y++;
	}
}

static void	init_ray(t_data *data)
{
	double	fov;
	int		i;

	i = 0;
	fov = data->mlx.height / 2 * tan((45 * (M_PI / 180)));
	data->ray = malloc(sizeof(t_ray) * data->mlx.width);
	if (data->ray == NULL)
		f_exit(data, 1);
	ft_bzero(data->ray, sizeof(t_ray) * data->mlx.width);
	// if (data->mlx.height < data->mlx.width)
		// fov *= (data->mlx.width / data->mlx.height);
	// else
	// 	fov /= (data->mlx.height / data->mlx.width) * 0.75;
	while (i < data->mlx.width)
	{
		data->ray[i].d_proj = fov;
		data->ray[i].pix_y = data->mlx.height >> 1;
		data->ray[i].max_height = data->mlx.height >> 1;
		++i;
	}
}

static void	init_menu(t_data *data)
{
	data->menu = malloc(sizeof(t_menu) * data->nb_coalition);
	if (data->menu == NULL)
		f_exit(data, 1); //error msg

	data->menu[0].img_coa = malloc(sizeof(t_img));
	if (!data->menu[0].img_coa)
		f_exit(data, 1);
	ft_bzero(data->menu[0].img_coa, sizeof(t_img));
	data->menu[0].img_coa->mlx = data->mlx.mlx;
	data->menu[0].name = "Fire";
	data->menu[0].color = 0xFF0000;
	data->menu[0].img_coa->path = "texture/menu/fire.xpm";

	data->menu[1].img_coa = malloc(sizeof(t_img));
	if (!data->menu[1].img_coa)
		f_exit(data, 1);
	ft_bzero(data->menu[1].img_coa, sizeof(t_img));
	data->menu[1].img_coa->mlx = data->mlx.mlx;
	data->menu[1].name = "Water";
	data->menu[1].color = 0x0000FF;
	data->menu[1].img_coa->path = "texture/menu/water.xpm";

	data->menu[2].img_coa = malloc(sizeof(t_img));
	if (!data->menu[2].img_coa)
		f_exit(data, 1);
	ft_bzero(data->menu[2].img_coa, sizeof(t_img));
	data->menu[2].img_coa->mlx = data->mlx.mlx;
	data->menu[2].name = "Earth";
	data->menu[2].color = 0x00FF00;
	data->menu[2].img_coa->path = "texture/menu/earth.xpm";

	data->menu[3].img_coa = malloc(sizeof(t_img));
	if (!data->menu[3].img_coa)
		f_exit(data, 1);
	ft_bzero(data->menu[3].img_coa, sizeof(t_img));
	data->menu[3].img_coa->mlx = data->mlx.mlx;
	data->menu[3].name = "Air";
	data->menu[3].color = 0xFFFFFF;
	data->menu[3].img_coa->path = "texture/menu/air.xpm";
	data->selected = 0;

	data->select = malloc(sizeof(t_img));
	if (!data->select)
		f_exit(data, 1);
	ft_bzero(data->select, sizeof(t_img));
	data->select->mlx = data->mlx.mlx;
	data->select->path = "texture/menu/select.xpm";
}
void	init_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->time_fps = get_mtime();
	data->time_move = get_mtime();
	fill_need_print(data);
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		// error msg
		f_exit(data, 1);
	}
	// mlx_get_screen_size(data->mlx.mlx, &data->mlx.width, &data->mlx.height);
	data->mlx.height = 1000;
	data->mlx.width = 1000;
	data->nb_coalition = 4;
	data->status = MENU;
	init_utils_mini(data);
	init_ray(data);
	data->screen = malloc(sizeof(t_img));
	data->screen->img = mlx_new_image(data->mlx.mlx, data->mlx.width,
			data->mlx.height);
	data->screen->data_addr = mlx_get_data_addr(data->screen->img,
			&data->screen->bits_per_pixel, &data->screen->size_line,
			&data->screen->endian);
	data->screen->width = data->mlx.width;
	data->screen->height = data->mlx.height;
	data->ac = ac;
	data->av = av;
	init_menu(data);
	init_texture(data);
}
