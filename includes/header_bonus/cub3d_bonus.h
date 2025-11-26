#ifndef CUB3D_H
# define CUB3D_H

# include "struct_bonus.h"
# include <stdbool.h>
# define MARGIN 100
// # define SEM_BACKGROUND "/sem_background"
// # define SEM_DOOR "/sem_door"
// # define SEM_DISPLAY "/sem_display"

// # define SEM_START "/sem_start"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif



void			right_case_replace(t_enemy *enemy, t_data *data);
void			visu_enemy_valid(t_data *data, t_enemy_vision *visu, t_enemy *enemy);
void			launch_ray_enemy(t_ray *ray, t_data *data);
void			fill_ray_enemy(t_enemy *enemy, t_ray *ray, double deg);
bool			is_sorcerer(int type);
int				handle_ray_x_right_gen(t_data *data, t_ray *ray);
int				handle_ray_x_left_gen(t_data *data, t_ray *ray);
int				handle_ray_y_down_gen(t_data *data, t_ray *ray);
int				handle_ray_y_top_gen(t_data *data, t_ray *ray);
void			spawn_elem_wand(t_enemy *enemy, t_data *data);
void			spawn_wolf_wand(t_enemy *enemy, t_data *data);
void			spawn_dementor_wand(t_enemy *enemy, t_data *data);
void			spawn_spider_wand(t_enemy *enemy, t_data *data);
void			set_valid_spawn(double *new_x, double *new_y);
void			move_more_hit_pos(t_enemy *enemy, t_item *item);
void			reverse_hit_pos(t_enemy *enemy, t_item *item);
void			add_sound_xp(t_enemy *enemy, t_data *data);
void			cancel_move(t_data *data, t_enemy *enemy, int dy, int dx);
void			left_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void			right_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void			center_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void			move_center_point(t_data *data, t_enemy *enemy, double *dy, double *dx);
int				are_double_close(double nb1, double nb2);
void			apply_slow_enemy(t_enemy *enemy, double *dx, double *dy);
void			calc_dx_dy_enemy(double *dy, double *dx, double rad);
void			earth_spell(t_data *data, t_enemy *enemy, double deg, int type);
void			fire_spell(t_data *data, t_enemy *enemy, double deg, int type);
void			water_spell(t_data *data, t_enemy *enemy, double deg, int type);
void			air_spell(t_data *data, t_enemy *enemy, double deg, int type);
void			low_life_enemy(t_enemy *enemy, t_data *data, t_lst **lst);
void			take_damage_enemy(t_enemy *enemy);
int				enemy_vision(t_data *data, t_enemy *enemy);
int				repulso_neg_enemy(t_enemy *enemy, t_data *data);
void			set_before_point_enemy(t_enemy *enemy, t_data *data);
int				confundo_move_enemy(t_enemy *enemy, t_data *data);
int				repulso_move_enemy(t_enemy *enemy, t_data *data);
void			try_hit_enemys(t_enemy *elem, t_data *data, int type);
void			spawn_item(t_data *data, t_enemy *enemy);
int				attack_dist(t_enemy *enemy, t_data *data, t_enemy_vision *visu);
void			recalc_fcoo(t_fcoo *coo, t_fcoo *center, double dy, double dx);
void			remove_child_path(t_enemy *enemy);
void			path_move_enemy(t_enemy *enemy, t_data *data, double *dx, double *dy);
void			calc_dist_target(t_enemy *enemy, t_enemy *elem, t_ray *ray);
void			calc_dist_wall(t_ray *ray);
void			recalc_path(t_enemy *enemy, t_enemy_vision *visu, t_data *data);
// player_input
void	handle_menu_keys(int keycode, t_data *data);
void	handle_death_menu_keys(int keycode, t_data *data);
void	handle_map_keys(int keycode, t_data *data);
void	cheat_code(t_data *data, int keycode);
bool	change_game_status(t_data *data, int keycode);
void	handle_exit_map(int keycode, t_data *data);
bool			is_move_player(t_data *data, int i);
int				mouse_move(int x, int y, t_data *data);
int				mouse_key(int key, int x, int y, t_data *data);
int				key_release(int keycode, t_data *data);
int				key_press(int keycode, t_data *data);
int				is_key_pressed(t_data *data, int keycode);



void	visu_enemy_valid(t_data *data, t_enemy_vision *visu, t_enemy *enemy);
void	launch_ray_enemy(t_ray *ray, t_data *data);
void	fill_ray_enemy(t_enemy *enemy, t_ray *ray, double deg);
bool			is_sorcerer(int type);
int				handle_ray_x_right_gen(t_data *data, t_ray *ray);
int				handle_ray_x_left_gen(t_data *data, t_ray *ray);
int				handle_ray_y_down_gen(t_data *data, t_ray *ray);
int				handle_ray_y_top_gen(t_data *data, t_ray *ray);
void			spawn_elem_wand(t_enemy *enemy, t_data *data);
void			spawn_wolf_wand(t_enemy *enemy, t_data *data);
void			spawn_dementor_wand(t_enemy *enemy, t_data *data);
void			spawn_spider_wand(t_enemy *enemy, t_data *data);
void			set_valid_spawn(double *new_x, double *new_y);
void			move_more_hit_pos(t_enemy *enemy, t_item *item);
void			reverse_hit_pos(t_enemy *enemy, t_item *item);
void			add_sound_xp(t_enemy *enemy, t_data *data);
void			cancel_move(t_data *data, t_enemy *enemy, int dy, int dx);
void			left_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void			right_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void			center_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void			move_center_point(t_data *data, t_enemy *enemy, double *dy, double *dx);
int				are_double_close(double nb1, double nb2);
void			apply_slow_enemy(t_enemy *enemy, double *dx, double *dy);
void			calc_dx_dy_enemy(double *dy, double *dx, double rad);
void			earth_spell(t_data *data, t_enemy *enemy, double deg, int type);
void			fire_spell(t_data *data, t_enemy *enemy, double deg, int type);
void			water_spell(t_data *data, t_enemy *enemy, double deg, int type);
void			air_spell(t_data *data, t_enemy *enemy, double deg, int type);
void			low_life_enemy(t_enemy *enemy, t_data *data, t_lst **lst);
void			take_damage_enemy(t_enemy *enemy);
int				enemy_vision(t_data *data, t_enemy *enemy);
int				repulso_neg_enemy(t_enemy *enemy, t_data *data);
void			set_before_point_enemy(t_enemy *enemy, t_data *data);
int				confundo_move_enemy(t_enemy *enemy, t_data *data);
int				repulso_move_enemy(t_enemy *enemy, t_data *data);
void			try_hit_enemys(t_enemy *elem, t_data *data, int type);
void			spawn_item(t_data *data, t_enemy *enemy);
int				attack_dist(t_enemy *enemy, t_data *data, t_enemy_vision *visu);
void			recalc_fcoo(t_fcoo *coo, t_fcoo *center, double dy, double dx);
void			remove_child_path(t_enemy *enemy);
void			path_move_enemy(t_enemy *enemy, t_data *data, double *dx, double *dy);
void			calc_dist_target(t_enemy *enemy, t_enemy *elem, t_ray *ray);
void			calc_dist_wall(t_ray *ray);
void			recalc_path(t_enemy *enemy, t_enemy_vision *visu, t_data *data);
// hit item
int	try_hit_items(t_item *elem, t_data *data);
bool	hit_calc_scal_enemy(t_enemy *enemy, t_item *elem, t_hitray *ray,
		t_lst **lst);
void	hit_calc_scal_player(bool *hit, t_fcoo *coo, t_item *elem,
		t_hitray *ray);

// move item
double	calc_dist_attraction(t_item *attract, t_enemy *enemy);
bool	item_destruction(t_item *item, t_data *data);
void	define_item_radius(t_item *item, t_data *data);
void	save_item_last_pos(t_item *item);

// mouse key
void	mouse_key_ig(t_data *data, int key);
void	mouse_key_spell_menu(t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	mouse_move_map(t_data *data, int y, int x);
void	mouse_key_map(t_data *data, int key);

void			fill_right_img_sorcerer(t_data *data, t_enemy *enemy, char c);
void			fill_bird(t_data *data, t_enemy *enemy);
void			fill_snake(t_data *data, t_enemy *enemy);
void			fill_wolf(t_data *data, t_enemy *enemy);
void			fill_elem(t_data *data, t_enemy *enemy);
void			fill_spider(t_data *data, t_enemy *enemy);
void			pathfinder(t_data *data, t_enemy *enemy);
void			calc_in_cell_path(t_data *data, t_enemy *enemy);
void			gen_enemy_way(t_data *data, t_enemy *enemy);
int				is_case_in_lst(int y, int x, t_lst *lst);
void			error_map_not_closed(t_lst *closed, t_lst *open, t_data *data);
void			error_occured(t_data *data, t_lst *open, t_lst *closed);
void			check_enemy_can_escape(t_data *data, t_lst *lst);
int				verif_enemy_is_closed(t_data *data, int y, int x);
void			verif_map_is_closed(t_data *data, int y, int x);
void			try_hit_player(t_data *data);
bool			is_skip_type(t_item *item, t_data *data);
bool			is_compatible_wall(t_data *data, int y, int x);
void			spawn_wall_msg(t_data *data, int i, int y, int x);
void			raycast_loop(t_data *data, int i, double x);
void			save_data_ray(t_data *data, int i, double x);
void			ray_try_hit_enemy(t_data *data, int i, double x, t_lst *lst);
void			ray_try_hit_door(t_data *data, int i, double x, t_lst *lst);
void			calc_item_value(t_data *data, t_hitray *ray, double x);
void			pick_up_items(t_data *data, t_item *item, t_lst **lst);
void			free_sound(void *elem);
t_sound			*create_sound(t_data *data, int info);
void			apply_transparancy(t_data *data, int x, int y,
					unsigned int color);
bool			handle_floo_open(t_data *data);
void			cast_popo_invi(t_data *data);
void			cast_popo_floo(t_data *data);
void			cast_popo_shield(t_data *data);
void			init_popo(t_data *data);
void			cast_popo_heal(t_data *data);
void			cast_opugno(t_data *data, int info);
void			init_item(t_data *data);
t_item			*create_item(t_data *data, int info, t_fcoo *coo, double deg);
t_item			*create_spell_item_sorcerer(t_data *data, int info, t_fcoo *coo,
					double deg);
int				get_right_white(t_data *data, int color, double distance);
void			start(int ac, char **av);
void			restart(t_data *data);
void			take_damage(t_data *data);
void			calc_left_and_right_point(t_enemy *enemy, t_data *data);
void			cast_vulnera_sanentur(t_data *data, int info);
void			f_way(t_enemy *enemy);
void			cast_episkey(t_data *data, int info);
void			spell_heal(t_data *data);
void			apply_damage(t_damage *take, t_damage *apply);
void			spell_protego(t_data *data);
void			cast_protego(t_data *data, int info);
int				calc_start_text(char *str, int x, t_data *data, int height);
void			aff_text(char *str, int height, t_coo coo, t_data *data);
void			calc_left_point_player(t_data *data);
void			calc_right_point_player(t_data *data);
void			make_move_item(t_item *item, double speed);
void			calc_scal(t_hitray *ray);
void			calc_left_point_item(t_item *item);
void			calc_right_point_item(t_item *item);
void			display_item(t_data *data, int i);
void			calc_end_point(t_hitray *ray);
void			try_hit_item(t_data *data, int i, double x);
void			move_item(t_data *data);
void			f_item(void *elem);
t_item			*init_spell_item(t_data *data, int info);

void			set_spell_take(t_data *data);
void			init_spell(t_data *data);

void			display_item_old(t_data *data, int i);
void			calc_delta(t_hitray *ray);
// void			try_hit_enemy(t_data *data, int i);

// open_window
void			open_window(t_data *data, t_mlx *mlx);

// mini_map
void			display_mini_map(t_data *data, t_map *map);
t_coo_mini		*init_t_coo_mini(double y, double x);
// bool	load_img_mini_map(t_mlx *mlx, t_mini *mini);
void			init_img_mini(t_data *data, t_mini *mini);
void			print_mini_map(t_data *data);
// void	init_utils_mini(t_utils_mini *u,t_data *data);
void			init_utils_mini(t_data *data);
void			get_pixel_color(t_data *data, int type);
void			aff_mini_map(t_data *data);
void			set_player_in_mini_map(t_data *data, t_utils_mini *u,
					double rad);
void			save_and_move_foot(t_data *data, double rad);
void			set_trail_foot(t_data *data, t_utils_mini *u);
void			calc_gap(t_data *data, int i, int *gap_x, int *gap_y);
void			get_good_offset_y(t_data *data, int angle_deg, int *start_y,
					int i);
void			get_good_offset_x(t_data *data, int angle_deg, int *start_x,
					int i);
void			set_pix_old_player(t_utils_mini *u, int start_y, int start_x,
					t_data *data);
void			calc_value_player_mini_map_aff(t_utils_mini *u, t_img *img,
					double rad);

void			calc_door(t_data *data, int i);

void			display_door(t_data *data, int i);
void			*display_fst_part(void *ptr);
void			*display_snd_part(void *ptr);
void			*display_third_part(void *ptr);
void			*display_last_part(void *ptr);
void			display_blood_border(t_data *data, int start_x, int max_x);
void			display_floo_map(t_data *data);
bool			is_center_floo(t_data *data, int pos_x, int pos_y);
void			draw_player(t_data *data, int pos_x, int pos_y);
void			draw_cursor(t_data *data);
void			draw_texture(t_data *data, int pos_x, int pos_y, char c);

void			*ray_launch_first(void *ptr);
void			*ray_launch_snd(void *ptr);
void			*ray_launch_third(void *ptr);
void			*ray_launch_last(void *ptr);

void			display_msg(t_data *data, int i, int y, int x);

// init
void			init_img_msg(t_data *data);
void			open_img_msg(t_data *data);

void			open_img(t_img *img, t_data *data);

// raycasting
void			ray_launch(t_data *data);
int				handle_ray_y_down(t_data *data, int i);
int				handle_ray_y_top(t_data *data, int i);
int				handle_ray_x_right(t_data *data, int i);
int				handle_ray_x_left(t_data *data, int i);
void			calc_sqrt(t_data *data, int i);

// display game
void			display_game(t_data *data);

unsigned int	get_texture_pixel(t_img *texture, int x, int y);

// game_loop.c
int				game_loop(t_data *data);
int				close_win(t_data *data);

// display_floor.c
void			*display_floor_first(void *ptr);
void			*display_floor_snd(void *ptr);
void			*display_floor_third(void *ptr);
void			*display_floor_last(void *ptr);

// display_sky.c
void			*display_sky_first(void *ptr);
void			*display_sky_snd(void *ptr);
void			*display_sky_third(void *ptr);
void			*display_sky_last(void *ptr);

// display_hand.c
void			display_hand(t_data *data);

// coa
void			display_menu(t_data *data);
void			draw_select_border(t_data *data, int start_x, int start_y);
void			pixel_put(t_data *data, int x, int y, unsigned int color);
void			select_right_hand(t_data *data);
int				get_right_color(int color, double distance);
void			select_your_hand(t_data *data);
void			draw_texture_menu(t_data *data, t_img *texture, int final_x,
					int final_y);
// menu spell
void			display_spell_take(t_data *data);
void			display_spell_list(t_data *data);
void			update_spell_cooldown(t_data *data);
int				menu_border_case_spell(t_data *data, double x, double y);

// spell.c
void			spell_lumos(t_data *data);
void			cast_lumos(t_data *data, int info);
void			cast_spell(t_data *data, int info);
void			cast_serpensortia(t_data *data, int info);

// handle_door.c
void			handle_door(t_data *data);

int				border_case_spell(double x, double y, double base_x,
					double base_y);
void			define_spell_color(t_data *data, unsigned int *color, int i);

// break_menu
void			handle_pause_menu(t_data *data, long long int cur);
void			draw_gradient(t_data *data, int start_x, int start_y);
void			display_menu_background(t_data *data, t_img *img, int start_x,
					int start_y);
void			display_exit(t_data *data, int start_x, int start_y);
void			display_resume(t_data *data, int start_x, int start_y);
void			display_selector(t_data *data, int start_x, int start_y);
// spells menu
void			handle_spells_menu(t_data *data);
void			handle_menu_spell_keys(int keycode, t_data *data);

// end menu
void			handle_end_menu(t_data *data);
void			display_retry_button(t_data *data, int start_x, int start_y);
void			display_quit_button(t_data *data, int start_x, int start_y);
void			handle_death_menu(t_data *data);

int				darken_the_color(int color);

// mini_move
void			movex(t_map *map, t_mini *mini, t_data *data);
void			calc_dx_dy(t_data *data, int keycode, t_mini *mini);
void			v_norm_sd(t_mini *mini, t_data *data);
void			v_norm_d(t_mini *mini, t_data *data);
void			recalc_x(t_data *data, t_mini *mini, t_map *map);
void			recalc_y(t_data *data, t_mini *mini, t_map *map);
void			movey(t_map *map, t_mini *mini, t_data *data);
void			movex(t_map *map, t_mini *mini, t_data *data);
void			save_pos_before_floo(t_data *data);

// ranking
void			get_ranking_xp(t_data *data);

// init spell
void			init_lumos(t_data *data);
void			init_incendio(t_data *data);
void			init_glacius(t_data *data);
void			init_repulso(t_data *data);
void			init_aguamenti(t_data *data);
void			init_arania_exumai(t_data *data);
void			init_protego(t_data *data);
void			init_expelliarmus(t_data *data);
void			init_expecto_patronum(t_data *data);
void			init_vipera_evanesca(t_data *data);
void			init_serpensortia(t_data *data);
void			init_ventus(t_data *data);
void			init_bombarda(t_data *data);
void			init_episkey(t_data *data);
void			init_stupefix(t_data *data);
void			init_confundo(t_data *data);
void			init_sectumsempra(t_data *data);
void			init_petrificus_totalus(t_data *data);
void			init_vulnera_sanentur(t_data *data);
void			init_oppugno(t_data *data);

//init_item
void	init_tig(t_data *data);
void	init_mac(t_data *data);
void	init_bh(t_data *data);
void	init_pizza(t_data *data);
void	init_fireball_elem(t_data *data);
void	init_death_anim(t_data *data);
void	init_web_spider(t_data *data);
void	init_folder(t_data *data);
void	init_marvin(t_data *data);
void	init_taylor_swift(t_data *data);
void	init_company(t_data *data);
void	init_logo_42(t_data *data);
void	init_popo_shield(t_data *data);
void	init_popo_floo(t_data *data);
void	init_portkey(t_data *data);
void	init_popo_invi(t_data *data);
void	init_popo_heal(t_data *data);
void	init_pillar(t_data *data);
void	init_spider_wand(t_data *data);
void	init_dementor_wand(t_data *data);
void	init_elem_wand(t_data *data);
void	init_wolf_wand(t_data *data);

typedef enum e_key_down
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}				t_key_down;

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
	KEY_M = 109,
	KEY_N = 110,
	KEY_X = 120,
	KEY_B = 98,
	KEY_G = 103,
	KEY_U = 117,
	KEY_T = 116,
	KEY_Z = 122,
	KEY_V = 118,
	KEY_MINUS = 45,
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
	KEY_ENTER = 65293,
}				t_key;

#endif
