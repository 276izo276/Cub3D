#include "color_bonus.h"
#include "cub3d_bonus.h"
#include "mlx.h"
#include "utils_bonus.h"
#include <math.h>
#include "time_bonus.h"
#include "enemy_bonus.h"

void	cast_protego(t_data *data, int info)
{
	long	save_time;

	save_time = 0;
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1 && get_mtime() > data->spell[PROTEGO].end_time
		+ data->spell[PROTEGO].base_cooldown * 1000)
	{
		data->spell[PROTEGO].launch_time = get_mtime();
		data->player.protego = 6;
		data->spell[PROTEGO].end_time = get_mtime();
		data->lumos.active = true;
		data->lumos.count_frame = 50;
		save_time = data->spell[LUMOS].end_time;
		spell_lumos(data);
		data->spell[LUMOS].end_time = save_time;
	}
}

void	cast_opugno(t_data *data, int info)
{
	long	save_time;
	int		i;

	save_time = 0;
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1 && get_mtime() > data->spell[OPPUGNO].end_time
		+ data->spell[OPPUGNO].base_cooldown * 1000)
	{
		data->spell[OPPUGNO].launch_time = get_mtime();
		data->spell[OPPUGNO].end_time = get_mtime();
		i = -1;
		while (++i < 4)
			data->enemy = add_end_lst(init_enemy(BIRD,
						(t_fcoo){.case_x = data->player.coo.case_x,
						.case_y = data->player.coo.case_y,
						.coo_x = data->player.coo.coo_x,
						.coo_y = data->player.coo.coo_y},
						data, data->map.mini.deg), data->enemy, f_enemy);
		data->lumos.active = true;
		data->lumos.count_frame = 50;
		save_time = data->spell[LUMOS].end_time;
		spell_lumos(data);
		data->spell[LUMOS].end_time = save_time;
	}
}

void	cast_serpensortia(t_data *data, int info)
{
	t_fcoo	coo;
	long	save_time;

	save_time = 0;
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1
		&& get_mtime() > data->spell[SERPENSORTIA].end_time
		+ data->spell[SERPENSORTIA].base_cooldown * 1000)
	{
		data->spell[SERPENSORTIA].launch_time = get_mtime();
		data->spell[SERPENSORTIA].end_time = get_mtime();
		coo.case_x = data->player.coo.case_x;
		coo.case_y = data->player.coo.case_y;
		coo.coo_x = data->player.coo.coo_x;
		coo.coo_y = data->player.coo.coo_y;
		data->enemy = add_end_lst(init_enemy(SNAKE, coo, data,
					data->map.mini.deg), data->enemy, f_enemy);
		data->lumos.active = true;
		data->lumos.count_frame = 50;
		save_time = data->spell[LUMOS].end_time;
		spell_lumos(data);
		data->spell[LUMOS].end_time = save_time;
	}
}

void	cast_vulnera_sanentur(t_data *data, int info)
{
	long	save_time;

	save_time = 0;
	(void)info;
	data->cast_spell = -1;
	if (data->active_spell == -1
		&& get_mtime() > data->spell[VULNERA_SANENTUR].end_time
		+ data->spell[VULNERA_SANENTUR].base_cooldown * 1000)
	{
		data->spell[VULNERA_SANENTUR].launch_time = get_mtime();
		data->player.vul_sanen_frame = 300;
		data->player.vul_sanen_heal = .1;
		data->player.damage.curse_force_take = 0;
		data->player.damage.curse_frame_take = 0;
		data->spell[VULNERA_SANENTUR].end_time = get_mtime();
		data->lumos.active = true;
		data->lumos.count_frame = 50;
		save_time = data->spell[LUMOS].end_time;
		spell_lumos(data);
		data->spell[LUMOS].end_time = save_time;
	}
}
