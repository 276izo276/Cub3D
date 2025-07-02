#include "struct.h"
#include "cub3d.h"
#include "utils.h"
#include "mlx.h"


void	open_win(t_data *data, t_mlx *mlx)
{
	mlx_get_screen_size(mlx->mlx, &mlx->width, &mlx->height);
	mlx->win = mlx_new_window(mlx->mlx, mlx->width - MARGIN, mlx->height - MARGIN, "./CUB3D");
	if (!mlx->win)
	{
		//error msg
		f_exit(data, 1);
	}
}
