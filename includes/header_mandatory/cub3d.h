/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:44:08 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/15 09:16:58 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include <stdbool.h>

# define MARGIN 100

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

//open_window
void		open_window(t_data *data, t_mlx *mlx);

//mini_map
t_coo_mini	*init_t_coo_mini(double y, double x);
void		display_mini_map(t_data *data, t_map *map);

// bool	load_img_mini_map(t_mlx *mlx, t_mini *mini);
void		init_img_mini(t_data *data, t_mini *mini);
void		print_mini_map(t_data *data);

// void	init_utils_mini(t_utils_mini *u,t_data *data);
void		set_player_in_mini_map(t_utils_mini *u, t_img *img, double rad);
void		get_pixel_color(t_data *data, int type);
void		init_utils_mini(t_data *data);
void		aff_mini_map(t_data *data);

//raycasting
void		ray_launch(t_data *data);
int			handle_ray_y_down(t_data *data, int i);
int			handle_ray_y_top(t_data *data, int i);
int			handle_ray_x_right(t_data *data, int i);
int			handle_ray_x_left(t_data *data, int i);
void		calc_sqrt(t_data *data, int i);

//display game
void		display_game(t_data *data);

//input_move.c
int			is_key_pressed(t_data *data, int keycode);
int			key_release(int keycode, t_data *data);
int			mouse_move(int x, int y, t_data *data);
int			key_press(int keycode, t_data *data);
bool		is_move_player(t_data *data, int i);

//game_loop.c
int			game_loop(t_data *data);
int			close_win(t_data *data);

//display_floor.c
void		display_floor(t_data *data, t_display display);

//display_sky.c
void		display_sky(t_data *data, t_display display);

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
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_W = 119,
	KEY_Q = 113,
	KEY_E = 101,
	KEY_C = 99,
	KEY_SPACE = 32,
	KEY_SHIFT = 65505,
	KEY_ESCAPE = 65307,
	KEY_ALT = 65513,
	KEY_RIGHT = 65363,
	KEY_LEFT = 65361
}	t_key;

#endif
