/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:43:52 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:43:53 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_BONUS_H
# define PLAYER_BONUS_H

# include "struct_bonus.h"

void	handle_move(t_map *map, t_mini *mini, t_data *data);
void	rotate_right(t_data *data);
void	rotate_left(t_data *data);
void	movex(t_map *map, t_mini *mini, t_data *data);
void	calc_dx_dy(t_data *data, int keycode, t_mini *mini);
void	v_norm_sd(t_mini *mini, t_data *data);
void	v_norm_d(t_mini *mini, t_data *data);
void	recalc_x(t_data *data, t_mini *mini, t_map *map);
void	recalc_y(t_data *data, t_mini *mini, t_map *map);
void	movey(t_map *map, t_mini *mini, t_data *data);
void	movex(t_map *map, t_mini *mini, t_data *data);
void	save_pos_before_floo(t_data *data);
void	handle_menu_keys(int keycode, t_data *data);
void	handle_death_menu_keys(int keycode, t_data *data);
void	handle_map_keys(int keycode, t_data *data);
void	cheat_code(t_data *data, int keycode);
bool	change_game_status(t_data *data, int keycode);
void	handle_exit_map(int keycode, t_data *data);
bool	is_move_player(t_data *data, int i);
int		mouse_move(int x, int y, t_data *data);
int		mouse_key(int key, int x, int y, t_data *data);
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
int		is_key_pressed(t_data *data, int keycode);
#endif
