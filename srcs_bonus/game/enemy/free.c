#include "struct_bonus.h"
#include <stdlib.h>

void	f_enemy(void *elem)
{
	t_enemy	*enemy;

	enemy = (t_enemy *)elem;
	free(enemy);
}

void	f_case(void *elem)
{
	t_case	*cel;

	cel = elem;
	free(cel);
}

void	f_list_final_path(t_lst *open, t_lst *closed)
{
	t_lst	*tmp;
	open = get_first_elem_lst(open);
	while (open)
	{
		tmp = open->next;
		if (!((t_case *)open->dt)->is_path)
		{
			f_elem_lst(open);
		}
		else
		free(open);
		open = tmp;
	}
	closed = get_first_elem_lst(closed);
	while (closed)
	{
		tmp = closed->next;
		if (!((t_case *)closed->dt)->is_path)
		{
			f_elem_lst(closed);
		}
		else
			free(closed);
		closed = tmp;
	}
}