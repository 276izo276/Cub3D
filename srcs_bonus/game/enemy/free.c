#include "struct_bonus.h"
#include <stdlib.h>

void	f_enemy(void *elem)
{
	t_enemy	*enemy;

	enemy = (t_enemy *)elem;
	free(elem);
}

void	f_case(void *elem)
{
	t_case	*cel;

	cel = elem;
	free(cel);
}