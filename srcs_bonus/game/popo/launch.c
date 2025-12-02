#include "cub3d_bonus.h"
#include "time_bonus.h"

void	cast_popo_heal(t_data *data)
{
	if (data->popo[0].active || data->player.life <= 0)
		return ;
	data->popo[0].active = 1;
	if (data->popo[0].nb > 0 && data->player.life < 100)
	{
		data->player.life += 20;
		if (data->player.life > 100)
			data->player.life = 100;
		data->popo[0].nb--;
		data->sound = add_end_lst(create_sound(data, 29), data->sound,
				free_sound);
	}
}

void	cast_popo_shield(t_data *data)
{
	if (data->popo[1].active || data->player.life <= 0)
		return ;
	data->popo[1].active = 1;
	if (data->popo[1].nb > 0 && data->player.shield < 100)
	{
		data->player.shield += 20;
		if (data->player.shield > 100)
			data->player.shield = 100;
		data->popo[1].nb--;
		data->sound = add_end_lst(create_sound(data, 29), data->sound,
				free_sound);
	}
}

void	cast_popo_floo(t_data *data)
{
	if (data->popo[2].active || data->player.life <= 0)
		return ;
	if (data->popo[2].nb == 0)
		return ;
	data->popo[2].active = 1;
	if (handle_floo_open(data) == true)
	{
		data->popo[2].nb--;
		data->sound = add_end_lst(create_sound(data, 31), data->sound,
				free_sound);
	}
}

void	cast_popo_invi(t_data *data)
{
	if (data->popo[3].active || data->popo[3].nb < 4 || data->player.life <= 0)
		return ;
	data->popo[3].active = 1;
	data->player.invisible = 32;
	data->player.timer_invi = get_mtime();
}
