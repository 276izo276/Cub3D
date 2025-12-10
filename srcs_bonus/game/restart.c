/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:52:13 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:52:14 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "parsing_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"

static void	reset_data_value(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 23)
		data->spell[i].end_time = 0;
	ft_bzero(&data->player.damage, sizeof(t_damage));
	data->popo[0].nb = 0;
	data->popo[1].nb = 0;
	data->popo[2].nb = 1;
	data->popo[3].nb = 0;
	i = -1;
	while (++i < 9)
	{
		data->sorcerer[i].is_alive = false;
		data->sorcerer[i].nb_spawn = 0;
	}
	i = -1;
	while (++i < 4)
		data->coa[i].xp = 1.0;
	data->selected = 0;
	data->player.color = 0;
	data->status = MENU;
}

static void	clear_parsing_text(t_data *data)
{
	f_img(data->map.north);
	f_img(data->map.south);
	f_img(data->map.west);
	f_img(data->map.east);
	f_img(data->map.ceiling);
	f_img(data->map.floor);
	data->map.north = NULL;
	data->map.south = NULL;
	data->map.west = NULL;
	data->map.east = NULL;
	data->map.ceiling = NULL;
	data->map.floor = NULL;
}

static void	reset_player_status(t_data *data)
{
	int	i;

	data->portkey_is_active = false;
	data->wand.count_egg = 0;
	data->wand.nb_wand = 0;
	data->wand.count_sword = 0;
	data->player.life = 100;
	data->player.shield = 0;
	data->player.xp = 1;
	data->player.coo.case_x = 0;
	data->player.coo.case_y = 0;
	data->player.coo.coo_x = 32;
	data->player.coo.coo_y = 32;
	i = 1;
	while (i <= 6)
	{
		data->wand.wand_status[i] = false;
		data->wand.is_drop[i] = false;
		++i;
	}
}

static void	clear_all_lst(t_data *data)
{
	f_all_lst(data->enemy);
	f_all_lst(data->item);
	f_all_lst(data->door);
	f_all_lst(data->sound);
	free_door_map(data);
	free_wall_map(data);
	data->door = NULL;
	data->enemy = NULL;
	data->item = NULL;
	data->sound = NULL;
	f_all_lst(data->map.map);
	f_all_lst(data->map.lines);
	f_tab_char(data->map.tabmap);
	data->map.map = NULL;
	data->map.lines = NULL;
	data->map.tabmap = NULL;
}

void	restart(t_data *data)
{
	int	i;

	clear_all_lst(data);
	reset_player_status(data);
	clear_parsing_text(data);
	data->time_fps = get_mtime();
	data->time_move = get_mtime();
	data->nb_door = 0;
	data->map.nb_floo = 0;
	parsing(data);
	init_foot_tab(data);
	reset_data_value(data);
	i = 0;
	while (i < data->mlx.width)
	{
		reset_data_display(data, i);
		++i;
	}
}
