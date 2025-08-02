#ifndef PLAYER_H
# define PLAYER_H

# include "struct.h"

//move mini_map
void	handle_move(t_map *map, t_mini *mini, int keycode, t_data *data);
void	rotate_right(t_data *data);
void	rotate_left(t_data *data);



#endif
