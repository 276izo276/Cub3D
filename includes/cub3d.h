#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include <stdbool.h>
# define MARGIN 100

//open_win
void	open_win(t_data *data, t_mlx *mlx);

//mini_map
void	display_mini_map(t_data *data, t_map *map);
bool	load_img_mini_map(t_mlx *mlx, t_mini *mini);

#endif
