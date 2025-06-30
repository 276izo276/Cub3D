#include "struct.h"
#include "utils.h"
#include <stdlib.h>

t_coo	*init_t_coo(t_data *data,  int y, int x)
{
	t_coo	*coo;

	coo = malloc(sizeof(t_coo));
	if (!coo)
		f_exit(data, 1);
	coo->x = x;
	coo->y = y;
	return (coo);
}
