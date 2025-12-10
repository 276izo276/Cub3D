/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:51:46 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:51:47 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils_bonus.h"

double	max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}

double	min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

void	update_sorcerer(t_data *data, long long int cur)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (data->sorcerer[i].is_alive == false
			&& data->player.color != data->sorcerer[i].color)
			spawn_sorcerer(data, data->sorcerer[i].type);
		if (!(cur >= data->spawn_frame + data->last_spawn))
			return ;
		++i;
	}
}

int	game_loop(t_data *data)
{
	long long int	cur;

	god_mod(&cur, data);
	if (data->portkey_is_active == false && data->player.xp >= 16)
		spawn_portkey(data);
	if (data->status == MENU)
		display_menu(data);
	else if (data->status == PAUSE)
		handle_pause_menu(data, cur);
	else if (data->status == FLOO_MAP)
		display_floo_map(data);
	else if (data->status == MAP)
		display_floo_map(data);
	else if (data->status == MENU_SPELL)
		handle_spells_menu(data);
	else if (data->status == MENU_DEATH)
		handle_death_menu(data);
	else if (data->status == MENU_END)
		handle_end_menu(data);
	else
		main_loop(cur, data);
	return (0);
}

int	close_win(t_data *data)
{
	f_exit(data, 1);
	return (1);
}
