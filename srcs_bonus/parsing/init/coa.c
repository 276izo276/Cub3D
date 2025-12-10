/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:53:23 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:53:24 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"
#include <color_bonus.h>

void	init_coa(t_data *data)
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

static void	init_coa_sorcerer(t_data *data)
{
	data->sorcerer[0].color = WATER_COLOR;
	data->sorcerer[1].color = FIRE_COLOR;
	data->sorcerer[2].color = AIR_COLOR;
	data->sorcerer[3].color = EARTH_COLOR;
	data->sorcerer[4].color = AIR_COLOR;
	data->sorcerer[5].color = AIR_COLOR;
	data->sorcerer[6].color = EARTH_COLOR;
	data->sorcerer[7].color = FIRE_COLOR;
	data->sorcerer[8].color = EARTH_COLOR;
}

void	init_sorcerer(t_data *data)
{
	int	i;

	i = 0;
	data->sorcerer[0].type = NANCY;
	data->sorcerer[1].type = ZIPPY;
	data->sorcerer[2].type = KUNFANDI;
	data->sorcerer[3].type = PILO;
	data->sorcerer[4].type = CAMEO;
	data->sorcerer[5].type = ANAIS;
	data->sorcerer[6].type = DIRLO;
	data->sorcerer[7].type = STEF;
	data->sorcerer[8].type = MARINA;
	init_coa_sorcerer(data);
	while (i < 9)
	{
		data->sorcerer[i].is_alive = true;
		data->sorcerer[i].nb_spawn = 0;
		++i;
	}
}
