#include "struct_bonus.h"
#include <stdlib.h>

void	f_case(void *elem)
{
	t_case	*cel;

	cel = elem;
	free(cel);
}

void	f_way(t_enemy *enemy)
{
	while (enemy->way)
	{
		if (enemy->way->child)
		{
			enemy->way = enemy->way->child;
			f_case(enemy->way->parent);
			enemy->way->parent = NULL;
		}
		else
		{
			f_case(enemy->way);
			enemy->way = NULL;
		}
	}
	enemy->way = NULL;
}

void	f_enemy(void *elem)
{
	t_enemy	*enemy;

	enemy = (t_enemy *)elem;
	f_way(enemy);
	free(enemy);
}

void	f_list_final_path(t_lst *open, t_lst *closed)
{
	t_lst	*tmp;

	open = get_first_elem_lst(open);
	while (open)
	{
		tmp = open->next;
		if (!((t_case *)open->dt)->is_path)
			f_elem_lst(open);
		else
			free(open);
		open = tmp;
	}
	closed = get_first_elem_lst(closed);
	while (closed)
	{
		tmp = closed->next;
		if (!((t_case *)closed->dt)->is_path)
			f_elem_lst(closed);
		else
			free(closed);
		closed = tmp;
	}
}
