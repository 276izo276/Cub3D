/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:52:49 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:52:50 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include "mlx.h"

void	open_window(t_data *data, t_mlx *mlx)
{
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height - MARGIN,
			"./CUB3D");
	if (!mlx->win)
		f_exit(data, 1);
}
