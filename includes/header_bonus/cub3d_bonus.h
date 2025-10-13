#ifndef CUB3D_H
# define CUB3D_H

# include "struct_bonus.h"
# include <stdbool.h>
# define MARGIN 100
# define SEM_BACKGROUND "/sem_background"
# define SEM_DOOR "/sem_door"
# define SEM_DISPLAY "/sem_display"

// # define SEM_START "/sem_start"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif



void	calc_left_point_item(t_item *item);
void	calc_right_point_item(t_item *item);
void	display_item(t_data *data, int i);
void	calc_end_point(t_hitray *ray);
void	try_hit_item(t_data *data, int i, double x);
void	move_item(t_data *data);
void	f_item(void *elem);
t_item	*init_spell_item(t_data *data, t_spells info);

void	set_spell_take(t_data *data);
void	init_spell(t_data *data);


void	display_item_old(t_data *data, int i);
void	calc_delta(t_hitray *ray);
void	try_hit_enemy(t_data *data, int i);

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
void	set_player_in_mini_map(t_data *data, t_utils_mini *u, double rad);
void	save_and_move_foot(t_data *data, double rad);
void	set_trail_foot(t_data *data, t_utils_mini *u);
void	calc_value_player_mini_map_aff(t_utils_mini *u, t_img *img,
	double rad);

void	calc_door(t_data *data, int i);

void	display_door(t_data *data, int i);
void	*display_fst_part(void *ptr);
void	*display_snd_part(void *ptr);
void	*display_third_part(void *ptr);
void	*display_last_part(void *ptr);
void    display_blood_border(t_data *data);
void    display_floo_map(t_data *data);

void	*ray_launch_first(void *ptr);
void	*ray_launch_snd(void *ptr);
void	*ray_launch_third(void *ptr);
void	*ray_launch_last(void *ptr);

void	display_msg(t_data *data, int i, int y, int x);

// init 
void	init_img_msg(t_data *data);
void	open_img_msg(t_data *data);


void	open_img(t_img *img, t_data *data);

//raycasting
void	ray_launch(t_data *data);
int		handle_ray_y_down(t_data *data, int i);
int		handle_ray_y_top(t_data *data, int i);
int 	handle_ray_x_right(t_data *data, int i);
int		handle_ray_x_left(t_data *data, int i);
void	calc_sqrt(t_data *data, int i);

//display game
void    display_game(t_data *data);

//TODO display_hand (a move dans un utils ?)
int		get_texture_pixel(t_img *texture, int x, int y);

//input_move.c
bool	is_move_player(t_data *data, int i);
int		mouse_move(int x, int y, t_data *data);
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
int		is_key_pressed(t_data *data, int keycode);

//game_loop.c
int		game_loop(t_data *data);
int		close_win(t_data *data);

//display_floor.c
void	*display_floor(void *ptr);

//display_sky.c
void	*display_sky(void *ptr);

//display_hand.c
void	display_hand(t_data *data);

//coa
void 	display_menu(t_data *data);
void	draw_select_border(t_data *data, int start_x, int start_y);
void	pixel_put(t_data *data, int x, int y, unsigned int color);
void	select_right_hand(t_data *data);
int		get_right_color(int color, double distance);

//spell.c
void	spell_lumos(t_data *data);
void	cast_lumos(t_data *data, t_spells info);
void	cast_spell(t_data *data, t_spells info);

//handle_door.c
void	handle_door(t_data *data);


//break_menu
void	handle_pause_menu(t_data *data, long long int cur);
void	draw_gradient(t_data *data, int start_x, int start_y);


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
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_CTRL = 65507,
	KEY_SPACE = 32, 
	KEY_SHIFT = 65505,
	KEY_TAB = 65289,
	KEY_ESCAPE = 65307,
	KEY_ALT = 65513,
	KEY_ENTER = 65293
}	t_key;

#endif
