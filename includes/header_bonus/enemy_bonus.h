#ifndef ENEMY_BONUS
# define ENEMY_BONUS

# include "struct_bonus.h"

t_enemy	*init_enemy(char c, t_fcoo coo, t_data *data, double deg);
void	f_enemy(void *elem);
void	f_case(void *elem);
void	move_enemy(t_data *data);
t_case	*init_case(int h_cost, int r_cost, int dir[2], t_case *parent);
void	f_list_final_path(t_lst *open, t_lst *closed);
void	calc_left_point(t_enemy *enemy);
void	calc_right_point(t_enemy *enemy);

#endif