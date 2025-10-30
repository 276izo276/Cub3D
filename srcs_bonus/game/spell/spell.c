#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include <math.h>
#include "time_bonus.h"
#include "enemy_bonus.h"

int	get_right_white(t_data *data, int color, double distance)
{
	int r;
	int g;
	int b;

	b = (color & 255);
	b = (int)(b + (255 - b) * ((1 - distance / 350 )) * data->lumos.count_frame / 100);
	if (b > 255)
		b = 255;
	g = (color >> 8 & 255);
	g = (int)(g + ( 255 - g) * ((1 - distance / 350 )) * data->lumos.count_frame / 100);
	if (g > 255)
		g = 255;
	r = (color >> 16 & 255);
	r = (int)(r + ( 255 - r) * ((1 - distance / 350 )) * data->lumos.count_frame / 100);
	if (r > 255)
		r = 255;
	color = (r << 16) + (g << 8) + b;
	return (color);
}

void	lumos_loop(t_data *data, int start_x, int start_y)
{
	unsigned int	color;
	int				x;
	int				y;
	double			distance;

	y = -350;
	color = 0;
	while (y < 350)
	{
		x = -350;
		while (x < 350)
		{
			distance = sqrt(y * y + x *x);
			if (distance < 350)
			{
				color = get_texture_pixel(data->screen, x + start_x, y
					+ start_y);
				color = get_right_white(data, color, distance);
				pixel_put(data, x + start_x, y + start_y, color);
			}
			++x;
		}
		++y;
	}
}

#include <stdio.h>

void	cast_lumos(t_data *data, t_spells info)
{
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1 && !data->lumos.active && get_mtime() > data->spell[LUMOS].end_time
		+ data->spell[LUMOS].base_cooldown * 1000)
	{
		data->lumos.active = true;
		data->active_spell = LUMOS;
		data->lumos.count_frame = 100;
		data->spell[LUMOS].launch_time = get_mtime();
	}
	else if (data->lumos.active == true)
	{
		data->lumos.active = false;
		data->active_spell = -1;
		data->spell[LUMOS].end_time = get_mtime();
	}
}

void	spell_lumos(t_data *data)
{
	int				start_x;
	int				start_y;

	if (data->lumos.active && get_mtime() > data->spell[LUMOS].launch_time
		+ data->spell[LUMOS].base_timer * 1000)
	{
		data->spell[LUMOS].end_time = get_mtime();
		data->lumos.active = false;
		data->active_spell = -1;
	}
	start_x = data->lumos.x_wand + (data->wand.img[PLAYER_WAND].width / 2) - 2;
	start_y = data->lumos.y_wand + 5;
	lumos_loop(data, start_x, start_y);
	if (data->lumos.active == false)
		data->lumos.count_frame -= 3;
}

void	spell_protego(t_data *data)
{
	if (data->player.protego > 0 && get_mtime() > data->spell[PROTEGO].launch_time
		+ data->spell[PROTEGO].base_timer * 1000)
	{
		data->player.protego = 0;
	}
}

void	cast_protego(t_data *data, t_spells info)
{
	(void)data;
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1 && get_mtime() > data->spell[PROTEGO].end_time
		+ data->spell[PROTEGO].base_cooldown * 1000)
	{
		data->spell[PROTEGO].launch_time = get_mtime();
		data->player.protego = 6;
		data->spell[PROTEGO].end_time = get_mtime();
	}
}

void	spell_heal(t_data *data)
{
	if (data->player.episkey_heal > 0)
	{
		if (data->player.episkey_frame > 0)
			data->player.episkey_frame--;
		data->player.life += data->player.episkey_heal;
		if (data->player.episkey_frame <= 0)
			data->player.episkey_heal = 0;
	}
	if (data->player.vul_sanen_heal > 0)
	{
		if (data->player.vul_sanen_frame > 0)
			data->player.vul_sanen_frame--;
		data->player.life += data->player.vul_sanen_heal;
		if (data->player.vul_sanen_frame <= 0)
			data->player.vul_sanen_heal = 0;
	}
	if (data->player.life > 100)
		data->player.life = 100;
}

void	cast_episkey(t_data *data, t_spells info)
{
	(void)data;
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1 && get_mtime() > data->spell[EPISKEY].end_time
		+ data->spell[EPISKEY].base_cooldown * 1000)
	{
		data->spell[EPISKEY].launch_time = get_mtime();
		data->player.episkey_frame = 150;
		data->player.episkey_heal = .1;
		data->spell[EPISKEY].end_time = get_mtime();
	}
}

#include <unistd.h>

void	cast_opugno(t_data *data, t_spells info)
{
	t_fcoo	coo;
	(void)info;

	data->cast_spell = -1;
	if (data->active_spell == -1 && get_mtime() > data->spell[OPPUGNO].end_time + data->spell[OPPUGNO].base_cooldown * 1000)
	{
		write(1,"a1\n",3);
		data->spell[OPPUGNO].launch_time = get_mtime();
		data->spell[OPPUGNO].end_time = get_mtime();
		coo.case_x = data->player.coo.case_x;
		coo.case_y = data->player.coo.case_y;
		coo.coo_x = data->player.coo.coo_x;
		coo.coo_y = data->player.coo.coo_y;
		data->enemy = add_end_lst(init_enemy(BIRD, coo, data, data->map.mini.deg),data->enemy,f_enemy);
		write(1,"a2\n",3);
	}
}

void	cast_serpensortia(t_data *data, t_spells info)
{
	t_fcoo	coo;
	(void)info;

	data->cast_spell = -1;
	if (data->active_spell == -1 && get_mtime() > data->spell[SERPENSORTIA].end_time + data->spell[SERPENSORTIA].base_cooldown * 1000)
	{
		data->spell[SERPENSORTIA].launch_time = get_mtime();
		data->spell[SERPENSORTIA].end_time = get_mtime();
		coo.case_x = data->player.coo.case_x;
		coo.case_y = data->player.coo.case_y;
		coo.coo_x = data->player.coo.coo_x;
		coo.coo_y = data->player.coo.coo_y;
		data->enemy = add_end_lst(init_enemy(SNAKE, coo, data, data->map.mini.deg),data->enemy,f_enemy);
	}
}

void	cast_vulnera_sanentur(t_data *data, t_spells info)
{
	(void)data;
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1 && get_mtime() > data->spell[VULNERA_SANENTUR].end_time
		+ data->spell[VULNERA_SANENTUR].base_cooldown * 1000)
	{
		data->spell[VULNERA_SANENTUR].launch_time = get_mtime();
		data->player.vul_sanen_frame = 300;
		data->player.vul_sanen_heal = .1;
		data->player.damage.curse_force_take = 0;
		data->player.damage.curse_frame_take = 0;
		data->spell[VULNERA_SANENTUR].end_time = get_mtime();
	}
}

void	cast_spell(t_data *data, t_spells info)
{
	data->cast_spell = -1;
	if (data->active_spell == -1 && get_mtime() > data->spell[info].end_time + data->spell[info].base_cooldown * 1000)
	{
		printf("CAST SPELL\n");
		data->spell[info].launch_time = get_mtime();
		data->item = add_end_lst(init_spell_item(data, info), data->item, f_item);
		// printf("data_>item >%p\n",data->item);
		data->spell[info].end_time = get_mtime();
	}
}
