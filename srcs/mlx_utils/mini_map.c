/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:45:15 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:45:16 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "texture.h"
#include "mlx.h"

static void	set_path_texture_mini_map(t_mini *mini)
{
	mini->img[MINI_FLOOR].path = "texture/mini_map/floor.xpm";
	mini->img[MINI_WALL].path = "texture/mini_map/wall.xpm";
	mini->img[MINI_PLAYER].path = "texture/mini_map/cursor.xpm";
	mini->img[MINI_DOOR].path = "texture/mini_map/door.xpm";
	mini->img[MINI_MOB].path = "texture/mini_map/mob.xpm";
	mini->img[MINI_CURS].path = "texture/mini_map/curs.xpm";
}

void	init_img_mini(t_data *data, t_mini *mini)
{
	int	i;

	set_path_texture_mini_map(mini);
	i = 0;
	while (i < 6)
	{
		mini->img[i].img = mlx_xpm_file_to_image(data->mlx.mlx,
				mini->img[i].path, &mini->img[i].width,
				&mini->img[i].height);
		if (!mini->img[i].img)
		{
			while (--i >= 0)
			{
				mlx_destroy_image(data->mlx.mlx, mini->img[i].img);
				mini->img[i].img = NULL;
			}
			f_exit(data, 1);
		}
		mini->img[i].data_addr = mlx_get_data_addr(mini->img[i].img,
				&mini->img[i].bits_per_pixel, &mini->img[i].size_line,
				&mini->img[i].endian);
		++i;
	}
}
