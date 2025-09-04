#include "struct_bonus.h"
#include "utils_bonus.h"

t_enemy	*init_enemy(char c, int y, int x, t_data *data)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	ft_bzero(enemy, sizeof(t_enemy));
	enemy->type = c;
	enemy->center.case_x = x;
	enemy->center.case_y = y;
	enemy->center.coo_x = 32;
	enemy->center.coo_y = 32;
	(void)data;
	return (enemy);
}

t_case	*init_case(int cost, int y, int x, t_case *parent)
{
	t_case	*cel;

	cel = malloc(sizeof(t_case));
	if (!cel)
		return (cel);
	ft_bzero(cel, (sizeof(t_case)));
	cel->parent = parent;
	cel->case_x = x;
	cel->case_y = y;
	cel->h_cost = cost;
	cel->t_cost = cost;
	return (cel);
}
