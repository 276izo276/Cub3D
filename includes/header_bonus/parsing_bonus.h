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

#endif
