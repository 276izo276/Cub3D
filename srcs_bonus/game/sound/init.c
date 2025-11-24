#include "struct_bonus.h"
#include "utils_bonus.h"
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
	if (sound->pid == -1)
	{
		free(sound);
		return (NULL);
	}
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
		// 	execlp("cvlc", "cvlc", "--play-and-exit","--volume","128", "--quiet", FICHIER_MP3, (char *)NULL);
		const char *tab[] = {LUMOS_MP3,ARANIA_EXUMAI_MP3,PROTEGO_MP3,INCENDIO_MP3,GLACIUS_MP3,REPULSO_MP3,AGUAMENTI_MP3,EXPELLIARMUS_MP3,EPISKEY_MP3,EXPECTO_PATRONUM_MP3,PETRIFICUS_TOTALUS_MP3,SERPENSORTIA_MP3,VENTUS_MP3,BOMBARDA_MP3,STUPEFIX_MP3,OPPUGNO_MP3,VULNERA_SANENTUR_MP3,VIPERA_EVANESCA_MP3,CONFUNDO_MP3,SECTUMSEMPRA_MP3,ENDOLORIS_MP3,AVADA_KEDAVRA_MP3,BACK_SOUND_MP3,THEME_HP_MP3,SHOOT_MP3,CRY_MP3,TP_MP3,DIE_MP3,PAPER_MP3};
		if (info == 27)
			execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", "--loop", DIE_MP3, (char *)NULL);
		else
			execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", tab[info], (char *)NULL);
		exit(EXIT_FAILURE);
		f_exit(data, 1);
	}
	sound->start = get_mtime();
	sound->duration = -1;
	return (sound);
}