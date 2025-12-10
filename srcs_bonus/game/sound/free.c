/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-guel <ale-guel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:50:56 by ale-guel          #+#    #+#             */
/*   Updated: 2025/12/10 07:50:57 by ale-guel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_bonus.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void	free_sound(void *elem)
{
	t_sound	*sound;

	sound = elem;
	if (waitpid(sound->pid, NULL, WNOHANG) == 0)
	{
		kill(sound->pid, SIGTERM);
	}
	free(sound);
}
