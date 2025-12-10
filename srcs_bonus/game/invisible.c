/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invisible.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:51:54 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:51:55 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "time_bonus.h"

void	player_invisible(t_data *data)
{
	if (data->player.invisible < 255)
	{
		if (get_mtime() > data->player.timer_invi_short + 100)
		{
			data->player.timer_invi_short = get_mtime();
			data->player.invisible += 1;
		}
		if (get_mtime() > data->player.timer_invi + 5 * 1000)
		{
			data->player.timer_invi = get_mtime();
			data->popo[3].nb--;
			data->player.invisible = 255 - data->popo[3].nb * 55;
			if (data->player.invisible < 32)
				data->player.invisible = 32;
		}
		if (data->player.invisible > 255)
		{
			data->player.invisible = 255;
		}
	}
}
