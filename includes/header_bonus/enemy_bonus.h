/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:43:46 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 09:14:22 by samaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_BONUS_H
# define ENEMY_BONUS_H

# include "struct_bonus.h"

t_enemy	*init_enemy(char c, t_fcoo coo, t_data *data, double deg);
void	f_enemy(void *elem);
void	f_case(void *elem);
void	move_enemy(t_data *data);
t_case	*init_case(int h_cost, int r_cost, int dir[2], t_case *parent);
void	f_list_final_path(t_lst *open, t_lst *closed);
void	calc_left_point(t_enemy *enemy);
void	calc_deg(t_fcoo *start, t_fcoo *end, double *rad, double *deg);
void	calc_right_point(t_enemy *enemy);
int		open_loop(t_enemy *enemy, t_lst **open, t_lst **closed, t_data *data);
int		man_dist(int startY, int startX, int endY, int endX);
t_lst	*need_update_node(t_case *cel, t_case *cur, t_lst *save, t_lst **lst);
int		is_in_lst(t_case *cur, const int dir[2], t_lst *lst, t_enemy *enemy);
int		is_a_wall(t_case *cur, const int dir[2], t_data *data);
void	set_final_path(t_lst *lst, t_enemy *enemy);
int		is_end_path(t_lst *open, t_enemy *enemy);
t_lst	*add_case_open(t_lst *open, t_lst **closed, t_enemy *enemy,
			t_data *data);
void	right_case_replace(t_enemy *enemy, t_data *data);
void	visu_enemy_valid(t_data *data, t_enemy_vision *visu, t_enemy *enemy);
void	launch_ray_enemy(t_ray *ray, t_data *data);
void	fill_ray_enemy(t_enemy *enemy, t_ray *ray, double deg);
bool	is_sorcerer(int type);
int		handle_ray_x_right_gen(t_data *data, t_ray *ray);
int		handle_ray_x_left_gen(t_data *data, t_ray *ray);
int		handle_ray_y_down_gen(t_data *data, t_ray *ray);
int		handle_ray_y_top_gen(t_data *data, t_ray *ray);
void	spawn_elem_wand(t_enemy *enemy, t_data *data);
void	spawn_wolf_wand(t_enemy *enemy, t_data *data);
void	spawn_dementor_wand(t_enemy *enemy, t_data *data);
void	spawn_spider_wand(t_enemy *enemy, t_data *data);
void	set_valid_spawn(double *new_x, double *new_y);
void	move_more_hit_pos(t_enemy *enemy, t_item *item);
void	reverse_hit_pos(t_enemy *enemy, t_item *item);
void	add_sound_xp(t_enemy *enemy, t_data *data);
void	cancel_move(t_data *data, t_enemy *enemy, int dy, int dx);
void	left_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void	right_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void	center_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void	move_center_point(t_data *data, t_enemy *enemy, double *dy, double *dx);
int		are_double_close(double nb1, double nb2);
void	apply_slow_enemy(t_enemy *enemy, double *dx, double *dy);
void	calc_dx_dy_enemy(double *dy, double *dx, double rad);
void	earth_spell(t_data *data, t_enemy *enemy, double deg, int type);
void	fire_spell(t_data *data, t_enemy *enemy, double deg, int type);
void	water_spell(t_data *data, t_enemy *enemy, double deg, int type);
void	air_spell(t_data *data, t_enemy *enemy, double deg, int type);
void	take_damage_enemy(t_enemy *enemy);
int		enemy_vision(t_data *data, t_enemy *enemy);
int		repulso_neg_enemy(t_enemy *enemy, t_data *data);
void	set_before_point_enemy(t_enemy *enemy, t_data *data);
int		confundo_move_enemy(t_enemy *enemy, t_data *data);
int		repulso_move_enemy(t_enemy *enemy, t_data *data);
void	try_hit_enemys(t_enemy *elem, t_data *data, int type);
void	spawn_item(t_data *data, t_enemy *enemy);
int		attack_dist(t_enemy *enemy, t_data *data, t_enemy_vision *visu);
void	recalc_fcoo(t_fcoo *coo, t_fcoo *center, double dy, double dx);
void	remove_child_path(t_enemy *enemy);
void	path_move_enemy(t_enemy *enemy, t_data *data, double *dx, double *dy);
void	calc_dist_target(t_enemy *enemy, t_enemy *elem, t_ray *ray);
void	calc_dist_wall(t_ray *ray);
void	recalc_path(t_enemy *enemy, t_enemy_vision *visu, t_data *data);

void	visu_enemy_valid(t_data *data, t_enemy_vision *visu, t_enemy *enemy);
void	launch_ray_enemy(t_ray *ray, t_data *data);
void	fill_ray_enemy(t_enemy *enemy, t_ray *ray, double deg);
bool	is_sorcerer(int type);
int		handle_ray_x_right_gen(t_data *data, t_ray *ray);
int		handle_ray_x_left_gen(t_data *data, t_ray *ray);
int		handle_ray_y_down_gen(t_data *data, t_ray *ray);
int		handle_ray_y_top_gen(t_data *data, t_ray *ray);
void	spawn_elem_wand(t_enemy *enemy, t_data *data);
void	spawn_wolf_wand(t_enemy *enemy, t_data *data);
void	spawn_dementor_wand(t_enemy *enemy, t_data *data);
void	spawn_spider_wand(t_enemy *enemy, t_data *data);
void	set_valid_spawn(double *new_x, double *new_y);
void	move_more_hit_pos(t_enemy *enemy, t_item *item);
void	reverse_hit_pos(t_enemy *enemy, t_item *item);
void	add_sound_xp(t_enemy *enemy, t_data *data);
void	cancel_move(t_data *data, t_enemy *enemy, int dy, int dx);
void	left_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void	right_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void	center_move_calc_case(t_mv_enemy *coo, t_fcoo enemy, int dx, int dy);
void	move_center_point(t_data *data, t_enemy *enemy, double *dy, double *dx);
int		are_double_close(double nb1, double nb2);
void	apply_slow_enemy(t_enemy *enemy, double *dx, double *dy);
void	calc_dx_dy_enemy(double *dy, double *dx, double rad);
void	earth_spell(t_data *data, t_enemy *enemy, double deg, int type);
void	fire_spell(t_data *data, t_enemy *enemy, double deg, int type);
void	water_spell(t_data *data, t_enemy *enemy, double deg, int type);
void	air_spell(t_data *data, t_enemy *enemy, double deg, int type);
int		low_life_enemy(t_enemy *enemy, t_data *data, t_lst **lst);
void	take_damage_enemy(t_enemy *enemy);
int		enemy_vision(t_data *data, t_enemy *enemy);
int		repulso_neg_enemy(t_enemy *enemy, t_data *data);
void	set_before_point_enemy(t_enemy *enemy, t_data *data);
int		confundo_move_enemy(t_enemy *enemy, t_data *data);
int		repulso_move_enemy(t_enemy *enemy, t_data *data);
void	try_hit_enemys(t_enemy *elem, t_data *data, int type);
void	spawn_item(t_data *data, t_enemy *enemy);
int		attack_dist(t_enemy *enemy, t_data *data, t_enemy_vision *visu);
void	recalc_fcoo(t_fcoo *coo, t_fcoo *center, double dy, double dx);
void	remove_child_path(t_enemy *enemy);
void	path_move_enemy(t_enemy *enemy, t_data *data, double *dx, double *dy);
void	calc_dist_target(t_enemy *enemy, t_enemy *elem, t_ray *ray);
void	calc_dist_wall(t_ray *ray);
void	recalc_path(t_enemy *enemy, t_enemy_vision *visu, t_data *data);
void	recalc_fcoo(t_fcoo *coo, t_fcoo *center, double dy, double dx);
#endif
