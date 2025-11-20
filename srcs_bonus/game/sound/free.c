#include "struct_bonus.h"
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>

void	free_sound(void *elem)
{
	t_sound *sound;

	sound = elem;
	if (waitpid(sound->pid, NULL, WNOHANG) == 0)
	{
		kill(sound->pid, SIGTERM);
		printf("KILL sound end game\n");
	}
	free(sound);
}