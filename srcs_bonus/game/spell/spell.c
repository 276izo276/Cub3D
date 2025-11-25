#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include <math.h>
#include "time_bonus.h"
#include "enemy_bonus.h"

void	spell_protego(t_data *data)
{
	if (data->player.protego > 0
		&& get_mtime() > data->spell[PROTEGO].launch_time
		+ data->spell[PROTEGO].base_timer * 1000)
	{
		data->player.protego = 0;
	}
}

void	spell_heal(t_data *data)
{
	if (data->player.life <= 0)
		return ;
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

void	cast_episkey(t_data *data, int info)
{
	long	save_time;

	save_time = 0;
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1 && get_mtime() > data->spell[EPISKEY].end_time
		+ data->spell[EPISKEY].base_cooldown * 1000)
	{
		data->spell[EPISKEY].launch_time = get_mtime();
		data->player.episkey_frame = 150;
		data->player.episkey_heal = .1;
		data->spell[EPISKEY].end_time = get_mtime();
		data->count_frame = 50;
	}
}

void	cast_spell(t_data *data, int info)
{
	data->cast_spell = -1;
	if (data->player.life > 0 && data->active_spell == -1
		&& get_mtime() > data->spell[info].end_time
		+ data->spell[info].base_cooldown * 1000)
	{
		data->spell[info].launch_time = get_mtime();
		data->item = add_end_lst(init_spell_item(data, info),
				data->item, f_item);
		data->spell[info].end_time = get_mtime();
	}
}
