#include "cub3d_bonus.h"
#include "mlx.h"
#include "time_bonus.h"

void	god_mod(long long int *cur, t_data *data)
{
	*cur = get_mtime();
	if (data->god_mod == true)
	{
		data->player.life = 100;
		data->player.shield = 100;
		data->player.damage.slow_force_take = 0;
	}
}

void	utils_loop(t_data *data)
{
	aff_xp(data);
	aff_life(data);
	aff_shield(data);
	aff_spell(data);
	aff_popo(data);
	aff_effect_info(data);
	spell_protego(data);
	spell_heal(data);
	aff_protego(data);
	display_hand(data);
	aff_mini_map(data);
	handle_door(data);
}

void	main_loop(long long int cur, t_data *data)
{
	if (cur >= data->spawn_frame + data->last_spawn)
	{
		update_sorcerer(data, cur);
		update_enemy(data, cur);
	}
	handle_input_move(data, cur);
	if (data->cast_spell != -1)
		data->spell[data->cast_spell].call(data, data->cast_spell);
	handle_wall_msg(data, cur);
	if (data->time_fps + 1000 / FPS < cur)
	{
		data->time_fps = cur;
		pthread_barrier_wait(&data->barrier_background);
		pthread_barrier_wait(&data->barrier_background);
		pthread_barrier_wait(&data->barrier_display);
		pthread_barrier_wait(&data->barrier_display);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->screen->img,
			0, 0);
		utils_loop(data);
	}
}

void	update_enemy(t_data *data, long long int cur)
{
	double	total_factor;

	data->spider_factor = max(10, 100 - (data->player.xp * 10));
	data->elem_factor = min(15, data->player.xp * 5);
	if (data->player.xp >= 3)
		data->dementor_factor = min(35, (data->player.xp - 2) * 2);
	if (data->player.xp >= 7)
		data->wolf_factor = min(40, (data->player.xp - 6) * 2);
	total_factor = data->spider_factor + data->dementor_factor
		+ data->elem_factor + data->wolf_factor;
	data->spider_factor = (data->spider_factor / total_factor) * 100;
	data->elem_factor = (data->elem_factor / total_factor) * 100;
	data->dementor_factor = (data->dementor_factor / total_factor) * 100;
	data->wolf_factor = (data->wolf_factor / total_factor) * 100;
	spawn_enemy(data, total_factor, cur);
}
