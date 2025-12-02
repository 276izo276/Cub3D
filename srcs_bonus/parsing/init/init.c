#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include <math.h>
#include "time_bonus.h"
#include "parsing_bonus.h"

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

	fov = data->mlx.height / 2 * tan((45 * (M_PI / 180)));
	data->ray = malloc(sizeof(t_ray) * data->mlx.width);
	if (data->ray == NULL)
		f_exit(data, 1);
	ft_bzero(data->ray, sizeof(t_ray) * data->mlx.width);
	i = 0;
	while (i < data->mlx.width)
	{
		data->ray[i].d_proj = fov;
		data->ray[i].pix_y = data->mlx.height >> 1;
		data->ray[i].max_height = data->mlx.height >> 1;
		++i;
	}
}

static void	init_player(t_data *data)
{
	data->player.life = 100;
	data->player.shield = 0;
	data->player.xp = 1.0;
	data->player.damage.damage_do = 1;
	data->player.invisible = 255;
}

static void	run_all_init(t_data *data)
{
	init_textures(data);
	init_coa(data);
	init_sorcerer(data);
	init_player(data);
	set_spell_take(data);
	init_spell(data);
	init_item(data);
	init_popo(data);
	init_utils(data);
}

void	init_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->sound = add_end_lst(create_sound(data, 23), data->sound, free_sound);
	data->time_fps = get_mtime();
	data->time_move = get_mtime();
	fill_need_print(data);
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		f_exit(data, 1);
	data->mlx.height = 1110;
	data->mlx.width = 1920;
	data->nb_coalition = 4;
	data->info = -1;
	data->status = MENU;
	init_utils_mini(data);
	init_ray(data);
	data->screen = malloc(sizeof(t_img));
	data->screen->img = mlx_new_image(data->mlx.mlx, data->mlx.width,
			data->mlx.height);
	data->screen->data_addr = mlx_get_data_addr(data->screen->img,
			&data->screen->bits_per_pixel, &data->screen->size_line,
			&data->screen->endian);
	data->ac = ac;
	data->av = av;
	run_all_init(data);
}
