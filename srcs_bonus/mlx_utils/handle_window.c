#include "cub3d_bonus.h"
#include "utils_bonus.h"
#include "mlx.h"

void	open_window(t_data *data, t_mlx *mlx)
{
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height - MARGIN,
			"./CUB3D");
	if (!mlx->win)
	{
		//error msg
		f_exit(data, 1);
	}
}
