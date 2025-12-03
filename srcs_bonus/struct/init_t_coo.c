#include "struct_bonus.h"
#include "utils_bonus.h"
#include <stdlib.h>

t_coo	*init_t_coo(int y, int x)
{
	t_coo	*coo;

	coo = malloc(sizeof(t_coo));
	if (!coo)
		return (NULL);
	coo->x = x;
	coo->y = y;
	return (coo);
}
