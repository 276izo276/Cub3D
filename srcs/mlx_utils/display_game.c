#include "cub3d.h"
#include "ft_printf.h"
#include "mlx.h"
#include "parsing.h"
#include "player.h"
#include "struct.h"
#include "texture.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

// void init_display(t_data *data, t_display *f_display)
// {
//     ft_bzero(f_display, sizeof(t_display));
//     f_display->img = mlx_new_image(data->mlx.mlx, data->mlx.width/2, data->mlx.height - MARGIN);
//     if (f_display->img == NULL)
//         f_exit(data, 1);
//     f_display->data_addr = mlx_get_data_addr(f_display->img, &f_display->bits_per_pixel,
//         &f_display->size_line, &f_display->endian);
// }

// void	set_path_texture_display(t_display *f_display)
// {
// 	f_display->sprite[NORTH] = "texture/north.xpm";
// 	f_display->sprite[SOUTH] = "texture/south.xpm";
// 	f_display->sprite[EAST] = "texture/east.xpm";
// 	f_display->sprite[WEST] = "texture/west.xpm";
// }

// void	display_game(t_data *data, t_display *f_display, int case_y, int case_x)
// {
// 	init_display(data, f_display);
// 	put_pixel(data, case_x, case_y, get_color());
// 	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, f_display->img, 0, 0);
// }
