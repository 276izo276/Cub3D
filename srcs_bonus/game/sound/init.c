/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:50:59 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:51:00 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include "time_bonus.h"
#include "utils_bonus.h"
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

static void	play_sound(t_data *data, t_sound *sound, int info, const char **tab)
{
	int	null_fd;

	if (sound->pid == 0)
	{
		null_fd = open("/dev/null", O_WRONLY);
		if (null_fd < 0)
			exit(EXIT_FAILURE);
		if (dup2(null_fd, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (dup2(null_fd, STDERR_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (info == 26)
			execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", "--loop",
				DIE_MP3, (char *) NULL);
		else if (info == 30)
			execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", "--loop",
				FREEDOM_MP3, (char *) NULL);
		else if (info == 22)
			execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", "--loop",
				BACK_SOUND_MP3, (char *) NULL);
		else
			execlp("cvlc", "cvlc", "--play-and-exit", "--quiet", tab[info],
				(char *) NULL);
		f_exit(data, 1);
	}
}

static void	init_child(t_sound *sound)
{
	sound->pid = fork();
	if (sound->pid == -1)
		free(sound);
}

t_sound	*create_sound(t_data *data, int info)
{
	t_sound		*sound;
	const char	*tab[] = {LUMOS_MP3, ARANIA_EXUMAI_MP3, PROTEGO_MP3,
		INCENDIO_MP3, GLACIUS_MP3, REPULSO_MP3, AGUAMENTI_MP3,
		EXPELLIARMUS_MP3, EPISKEY_MP3, EXPECTO_PATRONUM_MP3,
		PETRIFICUS_TOTALUS_MP3, SERPENSORTIA_MP3, VENTUS_MP3, BOMBARDA_MP3,
		STUPEFIX_MP3, OPPUGNO_MP3, VULNERA_SANENTUR_MP3,
		VIPERA_EVANESCA_MP3, CONFUNDO_MP3, SECTUMSEMPRA_MP3, ENDOLORIS_MP3,
		AVADA_KEDAVRA_MP3, BACK_SOUND_MP3, THEME_HP_MP3, CRY_MP3, TP_MP3,
		DIE_MP3, PAPER_MP3, COLLECT_WAND_MP3, POPO_MP3, FREEDOM_MP3,
		FLOO_MP3, HEART_MP3, LVL_UP, WALL_MP3};

	sound = malloc(sizeof(t_sound));
	if (!sound)
		f_exit(data, 1);
	bzero(sound, sizeof(t_sound));
	sound->id = info;
	init_child(sound);
	if (sound->pid == -1)
		return (NULL);
	play_sound(data, sound, info, tab);
	sound->start = get_mtime();
	sound->duration = -1;
	return (sound);
}
