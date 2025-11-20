#include "struct_bonus.h"
#include "time_bonus.h"
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>

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
		int null_fd = open("/dev/null", O_WRONLY);
        if (null_fd < 0) {
            exit(EXIT_FAILURE);
        }
        if (dup2(null_fd, STDOUT_FILENO) == -1) {
            exit(EXIT_FAILURE);
        }
        if (dup2(null_fd, STDERR_FILENO) == -1) {
            exit(EXIT_FAILURE);
        }
		// if (info == 0)
		// 	execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", FICHIER_MP3, (char *)NULL);
		// else if (info == 1)
		// 	execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", SHOOT_MP3, (char *)NULL);
		// else if (info == 2)
		// 	execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", CRY_MP3, (char *)NULL);
		// else if (info == 3)
		// 	execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", FICHIER_MP3, (char *)NULL);
		exit(EXIT_FAILURE);
	}
	sound->start = get_mtime();
	sound->duration = -1;
	return (sound);
}