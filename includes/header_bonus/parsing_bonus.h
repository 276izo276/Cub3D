#ifndef PARSING_H
# define PARSING_H

#include "struct_bonus.h"

typedef void	(*t_txt_set)(char *, t_data *data);

//init.c
void	init_data(t_data *data, int ac, char **av);

// check_map_is_closed
void	check_map_is_closed(t_data *data);

// start_parsing
void	parsing(t_data *data);

// read_content
void	get_content_file(t_data *data);
void	verif_file_name(t_data *data);

// fill_texture
void	set_east(char *line, t_data *data);
void	set_west(char *line, t_data *data);
void	set_south(char *line, t_data *data);
void	set_north(char *line, t_data *data);

// fill_texture_utils
int		get_start_path(char *line);
int		calc_path_size(char *line);

// fill_color
void	set_ceiling(char *line, t_data *data);
void	set_floor(char *line, t_data *data);

// open_texture
void	open_textures(t_data *data);

// verif_map
void	verif_map(t_data *data);

#endif
