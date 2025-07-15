#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include <stdbool.h>
# define MARGIN 100

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

//open_window
void	open_window(t_data *data, t_mlx *mlx);

//mini_map
void	display_mini_map(t_data *data, t_map *map);
t_coo_mini	*init_t_coo_mini(double y, double x);
// bool	load_img_mini_map(t_mlx *mlx, t_mini *mini);
void	init_img_mini(t_data *data, t_mini *mini);
void	print_mini_map(t_data *data);
// void	init_utils_mini(t_utils_mini *u,t_data *data);
void	init_utils_mini(t_data *data);
void	get_pixel_color(t_data *data, int type);
void	aff_mini_map(t_data *data);

//display_game
void	get_pixel_col(t_data *data, t_display *f_display, double wall_height);
void init_display(t_data *data, t_display *f_display);


typedef enum e_key_down
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	t_key_down;

typedef enum e_key
{
	KEY_0 = 48 , 
	KEY_1 = 49 , 
	KEY_2 = 50 , 
	KEY_3 = 51 , 
	KEY_4 = 52 , 
	KEY_5 = 53 , 
	KEY_6 = 54 , 
	KEY_7 = 55 , 
	KEY_8 = 56 , 
	KEY_9 = 57 , 
	KEY_A = 97 , 
	KEY_S = 115 , 
	KEY_D = 100 , 
	KEY_W = 119, 
	KEY_Q = 113 , 
	KEY_E = 101 , 
	KEY_C = 99 ,
	KEY_SPACE = 32, 
	KEY_SHIFT = 65505,
	KEY_ESCAPE = 65307,
	KEY_ALT = 65513
}	t_key;

#endif
