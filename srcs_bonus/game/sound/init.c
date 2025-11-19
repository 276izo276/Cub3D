#include "struct_bonus.h"
#include "time_bonus.h"
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

t_sound	*create_sound(t_data *data, int info)
{
	t_sound	*sound;

	(void)info;
	(void)data;
	sound = malloc(sizeof(t_sound));
	bzero(sound, sizeof(t_sound));
	sound->pid = fork();
	if (sound->pid == 0)
	{
		execlp("cvlc", "cvlc", "--play-and-exit", SHOOT_MP3, (char *)NULL);
		exit(EXIT_FAILURE);
	}
	sound->start = get_mtime();
	sound->duration = 5;
	return (sound);
}