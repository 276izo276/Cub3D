#include "cub3d_bonus.h"
#include "mlx.h"
#include "texture_bonus.h"
#include "utils_bonus.h"
#include <math.h>
#include "time_bonus.h"
#include <color_bonus.h>
#include "ft_printf.h"
#include "parsing_bonus.h"

static void	set_path_texture(t_data *data)
{
	set_path_player_spell(data);
	set_path_char_texture(data);
	set_path_enemy_texture(data);
	set_path_others_texture(data);
}

void	init_textures(t_data *data)
{
	int	i;

	set_path_texture(data);
	i = 0;
	while (i < NB_TEXTURES)
	{
		data->img[i].img = mlx_xpm_file_to_image(data->mlx.mlx,
				data->img[i].path, &data->img[i].width,
				&data->img[i].height);
		if (!data->img[i].img)
		{
			ft_printf_fd(2, _BOLD _PURPLE "Image >>> '"
			_RED _ITALIC "%s"_END _PURPLE _BOLD "' is not a valid path\n"_END,
			data->img[i].path);
			while (--i >= 0)
			{
				mlx_destroy_image(data->mlx.mlx, data->img[i].img);
				data->img[i].img = NULL;
			}
			f_exit(data, 1);
		}
		data->img[i].data_addr = mlx_get_data_addr(data->img[i].img,
				&data->img[i].bits_per_pixel, &data->img[i].size_line,
				&data->img[i].endian);
		++i;
	}
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

static void	init_coa(t_data *data)
{
	int	i;

	i = 0;
	data->coa[FIRE].name = "Fire";
	data->coa[FIRE].color = FIRE_COLOR;
	data->coa[WATER].name = "Water";
	data->coa[WATER].color = WATER_COLOR;
	data->coa[EARTH].name = "Earth";
	data->coa[EARTH].color = EARTH_COLOR;
	data->coa[AIR].name = "Air";
	data->coa[AIR].color = AIR_COLOR;
	while (i < 4)
	{
		data->coa[i].xp = 1.0;
		data->coa[i].max_y = 0;
		++i;
	}
	data->selected = 0;
}

void	init_sorcerer(t_data *data)
{
	int	i;

	i = 0;
	data->sorcerer[0].type = NANCY;
	data->sorcerer[0].color = WATER_COLOR;
	data->sorcerer[1].type = ZIPPY;
	data->sorcerer[1].color = FIRE_COLOR;
	data->sorcerer[2].type = KUNFANDI;
	data->sorcerer[2].color = AIR_COLOR;
	data->sorcerer[3].type = PILO;
	data->sorcerer[3].color = EARTH_COLOR;
	data->sorcerer[4].type = CAMEO;
	data->sorcerer[4].color = AIR_COLOR;
	data->sorcerer[5].type = ANAIS;
	data->sorcerer[5].color = AIR_COLOR;
	data->sorcerer[6].type = DIRLO;
	data->sorcerer[6].color = EARTH_COLOR;
	data->sorcerer[7].type = STEF;
	data->sorcerer[7].color = FIRE_COLOR;
	data->sorcerer[8].type = MARINA;
	data->sorcerer[8].color = EARTH_COLOR;
	while (i < 9)
	{
		data->sorcerer[i].is_alive = true;
		data->sorcerer[i].nb_spawn = 0;
		++i;
	}
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
	data->mlx.height = 1110;
	data->mlx.width = 1920;
	data->nb_coalition = 4;
	data->status = MENU;
	data->display.player_height = 16;
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
	data->lumos.x_wand = 0;
	data->lumos.y_wand = 0;
	data->lumos.count_frame = 0;
	data->lumos.active = false;
	data->portkey_is_active = false;
	init_textures(data);
	init_coa(data);
	init_sorcerer(data);
	data->nb_msg = 7;
	data->display.time_remove = 10000;
	data->display.elapsed_time = 0;
	data->current_msg = 0;
	data->display.is_msg_active = true;
	data->display.is_first_msg = true;
	data->sensitivity = 100;
	data->pause_menu.selected = 0;
	data->pause_menu.elapsed = 0;

	data->player.life = 100;
	data->player.shield = 0;
	data->player.xp = 15.0;
	data->player.damage.damage_do = 1;
	data->player.invisible = 255;

	data->spawn_frame = 5000;
	data->last_spawn = get_mtime();
	data->map.zoom = 128;
	data->map.last_mouse_x = 960;
	data->map.last_mouse_y = 555;
	data->map.is_center = false;
	
	data->wand.secret_wand = "BAGUETTE";
	data->wand.secret_sword = "SWORD";
	int	i = 1;
	data->wand.wand_status[0] = true;
	data->wand.is_drop[0] = true;
	while (i < 6)
	{
		data->wand.wand_status[i] = false;
		data->wand.is_drop[i] = false;
		++i;
	}
	data->cheat_code_xp = "SAMAOUCH";
	data->cheat_code_life = "ALE-GUEL";
	data->wand.wand_status[5] = false;
	data->wand.wand_status[6] = false;
	data->map.pos_active_floo = init_t_coo(0, 0);
	set_spell_take(data);
	init_spell(data);
	init_item(data);
	init_popo(data);
}
