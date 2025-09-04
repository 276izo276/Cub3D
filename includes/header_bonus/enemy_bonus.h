#ifndef ENEMY_BONUS
# define ENEMY_BONUS

# include "struct_bonus.h"

t_enemy	*init_enemy(char c, int y, int x, t_data *data);
void	f_enemy(void *elem);
void	f_case(void *elem);
void	move_enemy(t_data *data);
t_case	*init_case(int cost, int y, int x, t_case *parent);

#endif