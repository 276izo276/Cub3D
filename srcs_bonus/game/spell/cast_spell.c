/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_spell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:51:13 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:51:14 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "enemy_bonus.h"
#include "time_bonus.h"

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
		data->count_frame = 50;
		data->sound = add_end_lst(create_sound(data, 2), data->sound,
				free_sound);
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
						.coo_y = data->player.coo.coo_y}, data,
						data->map.mini.deg), data->enemy, f_enemy);
		data->count_frame = 50;
		data->sound = add_end_lst(create_sound(data, 15), data->sound,
				free_sound);
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
		data->count_frame = 50;
		data->sound = add_end_lst(create_sound(data, 11), data->sound,
				free_sound);
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
		data->count_frame = 50;
		data->sound = add_end_lst(create_sound(data, 16), data->sound,
				free_sound);
	}
}
