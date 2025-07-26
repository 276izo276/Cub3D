#include "struct.h"
#include "cub3d.h"
#include "utils.h"
#include "mlx.h"

#include <stdio.h>

void	open_window(t_data *data, t_mlx *mlx)
{
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height - MARGIN, "./CUB3D");
	if (!mlx->win)
	{
		//error msg
		f_exit(data, 1);
	}
	// printf("Size Windows >>> width>%d   height>%d\n",data->mlx.width/2,data->mlx.height);
	// exit(1);
}
