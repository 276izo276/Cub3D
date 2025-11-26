#include "struct_bonus.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void	free_sound(void *elem)
{
	t_sound *sound;

	sound = elem;
	if (waitpid(sound->pid, NULL, WNOHANG) == 0)
	{
		kill(sound->pid, SIGTERM);
	}
	free(sound);
}
