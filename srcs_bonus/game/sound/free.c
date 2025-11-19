#include "struct_bonus.h"
#include <stdlib.h>

void	free_sound(void *elem)
{
	t_sound *sound;

	sound = elem;
	free(sound);
}