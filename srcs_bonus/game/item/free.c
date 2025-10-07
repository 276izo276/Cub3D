#include "struct_bonus.h"
#include <stdlib.h>

void	f_item(void *elem)
{
	t_item	*item;

	item = elem;
	free(item);
}