#ifndef PLAYER_H
# define PLAYER_H

# include "struct.h"

//move mini_map
void	move_left(t_map *map, t_mini *mini);
void	move_right(t_map *map, t_mini *mini);
void	move_down(t_map *map, t_mini *mini);
void	move_up(t_map *map, t_mini *mini);


#endif
