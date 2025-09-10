#include "struct_bonus.h"

void	try_hit_enemy(t_data *data, int i)
{
	t_hitray	ray;
	t_lst		*lst;
	t_enemy		*enemy;

	ray.i = i;
	lst = get_first_elem_lst(data->enemy);
	// ray.j = 0;
	// while (++ray.j < data->nb_enemy + MAX_CREATE_ENEMY)
	// 	if (data->ray[i].enemys[ray.j]->use == false)
	// 		break ;
	while (lst)
	{
		enemy = lst->dt;
		ray.ax = enemy->left.coo_x + enemy->left.case_x * 64;
		ray.ay = enemy->left.coo_y + enemy->left.case_y * 64;
		ray.bx = enemy->right.coo_x + enemy->right.case_x * 64;
		ray.by = enemy->right.coo_y + enemy->right.case_y * 64;
		ray.cx = data->ray[ray.i].coo_x + data->ray[ray.i].case_x * 64;
		ray.cy = data->ray[ray.i].coo_y + data->ray[ray.i].case_y * 64;
		ray.dx = 0;
		ray.dy = 0;
		lst = lst->next;
	}
}