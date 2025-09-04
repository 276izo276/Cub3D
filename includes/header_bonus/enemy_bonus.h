#ifndef ENEMY_BONUS
# define ENEMY_BONUS

# include "struct_bonus.h"

t_enemy	*init_enemy(char c, int y, int x, t_data *data);
void	f_enemy(void *elem);
void	f_case(void *elem);
void	move_enemy(t_data *data);
t_case	*init_case(int h_cost, int r_cost, const int dir[2], t_case *parent);
void	f_list_final_path(t_lst *open, t_lst *closed);

#endif