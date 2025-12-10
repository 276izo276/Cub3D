/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:43:50 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:43:51 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "struct_bonus.h"

typedef void	(*t_txt_set)(char *, t_data *data);

// init.c
void			init_data(t_data *data, int ac, char **av);
void			init_coa(t_data *data);
void			init_sorcerer(t_data *data);
void			init_utils(t_data *data);
void			init_textures(t_data *data);
void			init_textures_wand(t_data *data);
void			init_sorcerer(t_data *data);

// check_map_is_closed
void			check_map_is_closed(t_data *data);

// start_parsing
void			parsing(t_data *data);

// read_content
void			get_content_file(t_data *data);
void			verif_file_name(t_data *data);

// fill_texture
void			set_east(char *line, t_data *data);
void			set_west(char *line, t_data *data);
void			set_south(char *line, t_data *data);
void			set_north(char *line, t_data *data);
int				fill_texture_color_data(t_lst *line, t_data *data);

// fill_texture_utils
int				get_start_path(char *line);
int				calc_path_size(char *line);

// fill_color
void			set_ceiling(char *line, t_data *data);
void			set_floor(char *line, t_data *data);

// open_texture
void			open_textures(t_data *data);

// verif_map
void			verif_map(t_data *data);

// which_type
void			is_item(char c, int y, int x, t_data *data);
void			is_door(char c, int y, int x, t_data *data);
bool			door_is_verti(t_data *data, int y, int x, char c);
void			is_enemy(char c, int y, int x, t_data *data);

// parse_item
void			add_door(t_data *data, int y, int x, char c);
void			save_wall(char c, int y, int x, t_data *data);

// set_path
void			set_path_char_texture(t_data *data);
void			set_path_player_spell(t_data *data);
void			set_path_enemy_texture(t_data *data);
void			set_path_others_texture(t_data *data);

// init
void			init_img_msg(t_data *data);
void			open_img_msg(t_data *data);

void			open_img(t_img *img, t_data *data);
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

// init_item
void			init_tig(t_data *data);
void			init_mac(t_data *data);
void			init_bh(t_data *data);
void			init_pizza(t_data *data);
void			init_fireball_elem(t_data *data);
void			init_death_anim(t_data *data);
void			init_web_spider(t_data *data);
void			init_folder(t_data *data);
void			init_marvin(t_data *data);
void			init_taylor_swift(t_data *data);
void			init_company(t_data *data);
void			init_logo_42(t_data *data);
void			init_popo_shield(t_data *data);
void			init_popo_floo(t_data *data);
void			init_portkey(t_data *data);
void			init_popo_invi(t_data *data);
void			init_popo_heal(t_data *data);
void			init_pillar(t_data *data);
void			init_spider_wand(t_data *data);
void			init_dementor_wand(t_data *data);
void			init_elem_wand(t_data *data);
void			init_wolf_wand(t_data *data);
void			init_mutex(t_data *data);
void			create_thread(t_data *data);
void			init_struct_item(t_data *data);
void			init_foot_tab(t_data *data);
t_item			*init_spell_item(t_data *data, int info);

void			set_spell_take(t_data *data);
void			init_spell(t_data *data);

#endif
