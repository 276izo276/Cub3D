#include "struct.h"
#include "utils.h"
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

t_coo_mini	*init_t_coo_mini(double y, double x)
{
	t_coo_mini	*coo;

	coo = malloc(sizeof(t_coo_mini));
	if (!coo)
		return (NULL);
	coo->x = x;
	coo->y = y;
	return (coo);
}
