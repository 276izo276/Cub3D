/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:46:34 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:46:35 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"

void	get_world_size(t_data *data, t_display *display, int y)
{
	display->dist_center = y - data->screen->height * 0.5;
	if (display->dist_center == 0)
		display->dist_center = 0.0001;
	display->screen_y = (double)display->dist_center / data->screen->height;
	display->dist_texture = 16.0 / display->screen_y;
}
